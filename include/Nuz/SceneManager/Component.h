#pragma once
#include <memory>
#include <string>

namespace Nuz_ {
	class GameObjectFloder;
}

namespace Nuz{
	class IScene;
	class IGameObject;
	class ICamera2D;
	//class ICamera3D;

	/* 组件
 	 * 依赖在物件或场景上的一组逻辑和功能。
     * 一个实例只允许被挂载到一个实例（物件或场景）上。
	 */

	/* OpenGL 使用规范
	 * Nuz使用0号纹理单元作为默认纹理单元。
	 * 主要的贴图应当都使用0号纹理单元作为绘图方式。
	 * 除非您自己编写着色器，否则Nuz默认着色器只会从0号纹理单元贴图。
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
		std::shared_ptr<IGameObject> GetGameObject(const std::string& mountName) const;

		/* 取得使用的摄像机
		 * @result 摄像机*/
		std::shared_ptr<const ICamera2D> GetCamera2D() const;
        
        /* 从父节点上卸载自身
         */
		void UnmountSelf();
	public:
	    virtual ~IComponent(){};

		virtual void OnUpdate(bool& draw2D,bool& draw3D) {}
		//当组件需要更新逻辑时执行，如果组件需要绘制2D,则设draw2D为true，如果组件需要绘制3D,则设置draw3D为true
		//它们默认都是false。
		//注意！返回false并不代表引擎一定不会不调用绘制函数。
		//只要一个物体或场景下直属的任何一个组件在OnUpdate上返回了true，则它的兄弟组件全都会调用绘制回调函数，
		//无论他们返回了true还是false。
		//反之，当一个物体里所有的直属组件OnUpdate都返回false时，这个物体里所有的物体都不会调用绘制回调函数。

		virtual void OnDraw3DReady() const {}	//当准备绘制3D时执行
		virtual void OnDraw3D() const {}	//当组件需要绘制3D时执行
		virtual void OnDraw3DFinished() const{}	//当3D绘制完成后
		 
        virtual void OnDraw2DReady() const {}	//当准备绘制2D物件时执行
		virtual void OnDraw2D() const{}	//当组件需要绘制2D物件时执行
		virtual void OnDraw2DFinished() const{}	//当2D物件绘制完成后

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