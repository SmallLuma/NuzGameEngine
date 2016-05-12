#pragma once
#include <memory>
#include "../../include/Nuz/Engine.h"

#include "SceneManager/SceneManager.h"
#include "FileSystem/FileSystem.h"
#include "FileSystem/LocalFile.h"


namespace Nuz_{

	class Engine:public Nuz::IEngine{
    private:
        Nuz_::FileSystem m_fileSystem;
        std::shared_ptr<Nuz_::LocalFile> m_localFile;
		Nuz_::SceneManager m_sceneManager;
	public:
	    Engine();
        ~Engine();
		Nuz::ISceneManager& GetSceneManager() override { 
			return m_sceneManager;
		};
		Nuz::IFileSystem& GetFileSystem() override
		{
			return m_fileSystem;
		}
        //Nuz::IInputDeviceManager& GetInputDeviceManager() override{};
        std::shared_ptr<Nuz::ILocalFile> GetLocalFile() override;
        void SetWindowTitle(const std::string&) noexcept override {};
        void InitWindow(int w,int h,bool fullScreen) override{};
        void CloseWindow() override{};
        void BindMessageProcessor(Message,std::function<void()>) override{};
	};

}