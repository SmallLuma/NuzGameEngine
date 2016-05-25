#include "Engine.h"
#include <memory>
#include "Renderer\OpenGL\glew.h"
#include <set>
#include "../../include/Nuz/Logs.h"
using namespace Nuz_;
using namespace Nuz;
using namespace std;

Engine::Engine():m_localFile(new Nuz_::LocalFile){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
}

Engine::~Engine(){
	if (m_window) {
		glDisable(GL_TEXTURE_2D);
		SDL_DestroyWindow(m_window);
		SDL_GL_DeleteContext(m_glContext);
	}
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
	if (!m_window || !m_glContext) throw std::runtime_error(std::string("SDL Error:") + SDL_GetError());

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
	extensionNeedSupposed.insert("GL_EXT_framebuffer_object");
	
	//要求支持ABGR像素格式
	extensionNeedSupposed.insert("GL_EXT_abgr");

	//要求可以支持VBO
	extensionNeedSupposed.insert("GL_ARB_vertex_buffer_object");

	extensionNeedSupposed.insert("GL_ARB_shader_objects");
	extensionNeedSupposed.insert("GL_ARB_vertex_shader");
	extensionNeedSupposed.insert("GL_ARB_fragment_shader");

	//要求支持DSA
	extensionNeedSupposed.insert("GL_EXT_direct_state_access");

	//检查扩展是否支持
	for (auto& p : extensionNeedSupposed) {
		if (allExtensions.count(p) == 0)
			throw RendererError(p + " is not supposed.");
	}


	//启动OpenGL特性
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
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


IEngine& Nuz::IEngine::GetGameDevice() noexcept{
    static Nuz_::Engine engine;
    return engine;
}

