#pragma once
#include <memory>
#include <string>
#include <SDL.h>
#include <map>
#include "../../include/Nuz/Engine.h"
#include "Input/InputDevice.h"
#include "SceneManager/SceneManager.h"
#include "FileSystem/FileSystem.h"
#include "Renderer/ImageCacheManager.h"
#include "FileSystem/LocalFile.h"


namespace Nuz_{

	class Engine final :public Nuz::IEngine {
	private:
		Nuz_::FileSystem m_fileSystem;
		std::shared_ptr<Nuz_::LocalFile> m_localFile;
		Nuz_::SceneManager m_sceneManager;

		int m_skipFrame = 1;
		bool m_showFPS = false;

		InputDeviceManager m_input;

		std::string m_windowTitle;
		SDL_Window* m_window = nullptr;
		SDL_GLContext m_glContext = nullptr;

		Renderer::ImageCacheManager m_imageLoader;
	public:
		Engine();
		~Engine();

		Renderer::ImageCacheManager& GetTextureLoader() {
			return m_imageLoader;
		}
		
		Nuz::ISceneManager& GetSceneManager() override;;
		Nuz::IFileSystem& GetFileSystem() override;
		Nuz::IInputDeviceManager& GetInputDeviceManager() override;
        std::shared_ptr<Nuz::ILocalFile> GetLocalFile() override;
        void SetWindowTitle(const std::string&) noexcept override;
		void InitWindow(int w, int h, bool fullScreen, const std::set<std::string>& extensions = std::set<std::string>()) override;
		void BindMessageProcessor(Message m, std::function<void()> f) override;
		void UnbindMessageProcessor(Message m) override;

		SDL_Window* GetWindow() { return m_window; }
		std::string GetWindowTitle() { return m_windowTitle; }

		void SetSkipFrame(int skipFrame) override;
		inline int GetSkipFrame() override
		{
			return m_skipFrame;
		}
		void SetFPSShowEnable(bool) override;
		inline bool GetFPSShowEnable() { return m_showFPS; }

		void GetWindowSize(int& w, int& h) override;
	};

}
