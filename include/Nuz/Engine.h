#pragma once
#include <memory>
#include <stdexcept>
#include <set>
#include <functional>

namespace Nuz{
	class ISceneManager;
	class IFileSystem;
	class IInputDeviceManager;
	class ILocalFile;

	/* Nuz引擎主体部分
	 * 包含了Nuz引擎类
	 */
	class IEngine{
	public:
		virtual ~IEngine() {}

	    /* 初始化游戏窗口（只允许调用一次）
	     * @param w 宽度（如果全屏时采用屏幕分辨率，填入-1）
	     * @param h 高度（如果全屏时采用屏幕分辨率，填入-1）
	     * @param fullScreen 是否全屏
		 * @param extensions 需要的OpenGL扩展
		 * @throw RendererError
		 * @throw std::runtime_error
	     */
        virtual void InitWindow(int w,int h,bool fullScreen,const std::set<std::string>& extensions = std::set<std::string>()) = 0;

		/* 设置窗口是否显示FPS
		 * @param 是否显示FPS
		 */
		virtual void SetFPSShowEnable(bool) = 0;

		/* 设置窗口的跳帧率
		 * 不设置则60帧满帧运行。
		 * 跳帧率与fps对应关系：
		 *	0 - 60
		 *	1 - 30
		 *	2 - 20
		 *	3 - 15
		 * 注意：逻辑运行速度不受影响。
		 *	以防止跳帧状态下逻辑变慢的情况。
		 * @param skipFrame 跳帧率
		 */
		virtual void SetSkipFrame(int skipFrame) = 0;

		/* 获取跳帧率
		 * @result 跳帧率
		 */
		virtual int GetSkipFrame() = 0;

        /* 设置游戏窗口标题
         * @param title 标题
         */
        virtual void SetWindowTitle(const std::string& title) noexcept = 0;

		/* 获取游戏窗口分辨率
		 * @param w 宽
		 * @param h 高
		 */
		virtual void GetWindowSize(int& w, int& h) = 0;

	    /* 取得场景管理器
	     * @result 场景管理器
	     */
		virtual ISceneManager& GetSceneManager() = 0;

		/* 取得文件系统
		 * @result 文件系统
		 */
		virtual IFileSystem& GetFileSystem() = 0;

		/* 取得输入管理器
		 * @result 输入管理器
		 */
		virtual IInputDeviceManager& GetInputDeviceManager() = 0;

		/* 取得本地文件管理器
		 * @result 本地文件管理器
		 */
		virtual std::shared_ptr <ILocalFile> GetLocalFile() = 0;

		/* 系统消息 */
		enum class Message{
			Quit,	//当程序被要求退出时
            CloseWindow, //窗口被要求关闭时
			WindowMinimized,	//最小化时
			WindowMaximized,	//最大化时
			WindowRestored,	//窗口还原时
		};
		/* 绑定消息处理函数
		 * @param 消息
		 * @param 函数
		 */
        virtual void BindMessageProcessor(Message,std::function<void()>) = 0;

		/* 解绑消息处理函数
		 * @param 消息
		 */
		virtual void UnbindMessageProcessor(Message) = 0;

        /* 取得已被创建的引擎实例
		 * @throw RendererError
		 * @throw std::runtime_error
         * @result 引擎
         */
        static IEngine& GetGameDevice() noexcept;


		/* 渲染器异常
		 */
		class RendererError :public std::runtime_error {
		public:
			using std::runtime_error::runtime_error;
		};
	};

}

/* 更新日志：
 * 2016年4月17日：
 * 星翼 初稿
 * 2016年4月18日：
 * 星翼 修正CreateGameDevice函数的返回值并加上说明。
 * 星翼 添加GetLocalFile方法。
 * 2016年4月24日：
 * 星翼 添加引擎生命异常。
 * 2016年4月26日：
 * 星翼 修改引擎生命周期
 */
