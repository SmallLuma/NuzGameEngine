#pragma once
#include <memory>
#include <string>

namespace Nuz_ {
	class GameObjectFloder;
}

namespace Nuz{
	class IScene;
	class IGameObject;

	/* 组件
 	 * 依赖在物件或场景上的一组逻辑和功能。
     * 一个实例只允许被挂载到一个实例（物件或场景）上。
	 */
	class IComponent{
	public:
        /* 父节点类型 */
		enum class ParentType{
		    None,   //没有被挂载
			TypeScene,	//场景
			TypeGameObject	//游戏物件
		};
	private:
		friend class Nuz_::GameObjectFloder;
		ParentType m_parentType = ParentType::None;
		Nuz_::GameObjectFloder* m_parent = nullptr;
	public:

		/* 获取父节点类型
		 * @result 父节点类型
		 */
		inline ParentType GetParentType() const { return m_parentType; };

		/* 获取作为场景的父节点
		 * @result 父节点指针
		 */
		std::shared_ptr<IScene> GetParentAsScene() const;

		/* 获取作为物件的父节点
		 * @result 父节点指针
		 */
		std::shared_ptr<IGameObject> GetParentAsGameObject() const;

		/* 给定挂载名，取父节点中对应挂载名的组件
		 * @param 挂载名
		 */
		std::shared_ptr<IComponent> GetOtherComponent(const std::string& mountName) const;

        /* 给定挂载名，取父节点中对应挂载名的物件
		 * @param 挂载名
		 */
		std::shared_ptr<IGameObject> GetGameObject(const std::string& mountName);;;
        
        /* 从父节点上卸载自身
         */
		void UnmountSelf();;
	public:
	    virtual ~IComponent(){};

		virtual void OnUpdate(){};	//当组件需要更新逻辑时执行

		virtual void OnDraw3DReady(){};	//当准备绘制3D时执行
		virtual void OnDraw3D(){};	//当组件需要绘制3D时执行
		virtual void OnDraw3DFinished(){};	//当3D绘制完成后

        virtual void OnDraw2DReady(){};	//当准备绘制2D物件时执行
		virtual void OnDraw2D(){};	//当组件需要绘制2D物件时执行
		virtual void OnDraw2DFinished(){};	//当2D物件绘制完成后

        virtual void OnDrawScreenReady(){};    //当场景绘制准备开始时
		virtual void OnDrawScreenFinished(){}; //当场景绘制结束时
		/* 绘制流程
		 * 如果被挂载的是2D或3D物件，则会只调用物件绘制函数，不调用Scene绘制函数。
		 * 如果被挂载的是场景，则先作为一个物件进行绘制，然后把该场景绘制得到的图像作为帧缓存，再次调用场景绘制函数。
		 */

		/* 当场景要求被切出时执行
		 * @param timeLimited 时间限制（帧）
		 */
		virtual void OnFadeSwitchOut(int timeLimited){};

		/* 当场景被切出时会增加的增补逻辑
		 * @param finished 时间剩余百分比
		 */
		virtual void OnFadeSwitchOutUpdate(float finished){};

		/* 当场景要求被切入时执行
		 * @param timeLimited 时间限制（帧）
		 */
		virtual void OnFadeSwitchIn(int timeLimited){};

		/* 当场景被切入时会增加的增补逻辑
		 * @param finished 时间剩余百分比
		 */
		virtual void OnFadeSwitchInUpdate(float finished){};
	};

}

/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 给出组件名称
 */