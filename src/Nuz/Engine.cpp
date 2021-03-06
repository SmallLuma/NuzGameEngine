#include "Engine.h"
#include <memory>
#include "Renderer\OpenGL\glew.h"
#include <set>
#include "../../include/Nuz/Logs.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Renderer\OpenGL\GLSLProgram.h"
#include "Sound/Sound.h"
using namespace Nuz_;
using namespace Nuz;
using namespace std;

Engine::Engine():m_localFile(new Nuz_::LocalFile){
	if(SDL_Init(SDL_INIT_EVERYTHING)) throw std::runtime_error(string("SDL Init Error:") + SDL_GetError());
	if(TTF_Init()) throw std::runtime_error(string("SDL_ttf Init Error:") +TTF_GetError());
	if(Mix_Init(0) < 0)
		throw std::runtime_error(string("SDL_mixer Init Error:") + Mix_GetError());
	if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 8192))
		throw std::runtime_error(string("Cannot Open Audio:") + Mix_GetError());

	Mix_AllocateChannels(500);
	Mix_ChannelFinished(&channelFinishedHook);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
}

Engine::~Engine(){
	Nuz_::Renderer::GLSLProgram::DestroyNormalShaders();
	if (m_window) {
		glDisable(GL_TEXTURE_2D);
		SDL_DestroyWindow(m_window);
		SDL_GL_DeleteContext(m_glContext);
	}
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

Nuz::ISceneManager & Nuz_::Engine::GetSceneManager() {
	return m_sceneManager;
}

void Nuz_::Engine::SetWindowTitle(const std::string& s) noexcept {
	if (m_window) SDL_SetWindowTitle(m_window,s.c_str());
	m_windowTitle = s;
}

Nuz::IFileSystem & Nuz_::Engine::GetFileSystem()
{
	return m_fileSystem;
}

inline Nuz::IInputDeviceManager & Nuz_::Engine::GetInputDeviceManager() { return m_input; }

std::shared_ptr<Nuz::ILocalFile> Engine::GetLocalFile()
{
    return m_localFile;
}

void Nuz_::Engine::InitWindow(int w, int h, bool fullScreen, const std::set<std::string>& extensions) {
	if (m_window || m_glContext) throw std::runtime_error("Window have already created.");
	if (fullScreen) {
		if (w == 1)
			m_window = SDL_CreateWindow(m_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
		else
			m_window = SDL_CreateWindow(m_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else
		m_window = SDL_CreateWindow(m_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);

	m_glContext = SDL_GL_CreateContext(m_window);
	if (!m_window || !m_glContext) throw std::runtime_error(std::string("Cannot create window and renderer:") + SDL_GetError());

	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(m_window);

	glewInit();
	LogStd(string("Version:") + ((char*)glGetString(GL_VERSION)), "Nuz::Renderer");

	//最大纹理大小不小于4096*4096
	GLint max;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
	if (max < 4096) throw RendererError("OpenGL max texture size is less than 2048*2048.");
	LogStd(string("Biggest Texture Length:") + to_string(max), "Nuz::Renderer");

	set<string> allExtensions;
	string exs((char*)glGetString(GL_EXTENSIONS));
	while (!exs.empty()) {
		auto pos = exs.find(' ');
		if (pos == string::npos) {
			allExtensions.insert(exs);
			LogStd(string("Supposed Extension:") + exs, "Nuz::Renderer");
			exs.clear();
		}
		else {
			allExtensions.insert(exs.substr(0, pos));
			LogStd(string("Supposed Extension:") + exs.substr(0, pos), "Nuz::Renderer");
			exs = exs.substr(pos + 1, exs.size() - pos - 1);
		}
	}

	set<string> extensionNeedSupposed;
	for (auto& p : extensions) {
		extensionNeedSupposed.insert(p);
	}

	//要求支持FrameBuffer扩展
	//extensionNeedSupposed.insert("GL_EXT_framebuffer_object");
	
	//要求支持ABGR像素格式
	extensionNeedSupposed.insert("GL_EXT_abgr");

	//要求可以支持VBO
	//extensionNeedSupposed.insert("GL_ARB_vertex_buffer_object");

	//要求可以支持Shader
	extensionNeedSupposed.insert("GL_ARB_shader_objects");
	extensionNeedSupposed.insert("GL_ARB_vertex_shader");
	extensionNeedSupposed.insert("GL_ARB_fragment_shader");

	//要求可以支持长方形纹理
	extensionNeedSupposed.insert("GL_ARB_texture_rectangle");

	//要求支持DSA
	extensionNeedSupposed.insert("GL_EXT_direct_state_access");

	//检查扩展是否支持
	for (auto& p : extensionNeedSupposed) {
		if (allExtensions.count(p) == 0)
			throw RendererError(p + " is not supposed.");
	}


	//初始化OpenGL状态机
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//编译管线
	Nuz_::Renderer::GLSLProgram::CompileNormalShaders();
}

void Nuz_::Engine::BindMessageProcessor(Message m, std::function<void()> f) {
	m_sceneManager.BindMessageProcessor(m, f);
}

void Nuz_::Engine::UnbindMessageProcessor(Message m)
{
	m_sceneManager.UnbindMessageProcessor(m);
}

void Nuz_::Engine::SetSkipFrame(int skipFrame)
{
	if (skipFrame >= 4 || skipFrame < 0) throw std::invalid_argument("Invaild skip frame number.");
	m_skipFrame = skipFrame+1;
}

void Nuz_::Engine::SetFPSShowEnable(bool b)
{
	m_showFPS = b;
	if(m_window) SDL_SetWindowTitle(m_window, m_windowTitle.c_str());
}

inline void Nuz_::Engine::GetWindowSize(int & w, int & h) {
	SDL_GetWindowSize(m_window, &w, &h);
}


IEngine& Nuz::IEngine::GetGameDevice() noexcept{
    static Nuz_::Engine engine;
    return engine;
}

