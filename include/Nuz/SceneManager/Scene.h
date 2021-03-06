#pragma once
#include <memory>
#include <string>
#include "Camera2D.h"
#include "Camera3D.h"

namespace Nuz{
	class IComponent;
	class IGameObject;

	/* 场景
	 * 游戏中一个可以挂载组件和物件和子场景的场面。
     * 上层场景会悬浮在下层场景的上方。
     * 一个场景只允许被挂载到一个场景上。
	 * 对于场景/物件/组件的一切卸载的说明：卸载不会立即卸载，
	   会在下一帧时集中卸载，这一帧到来之前，依旧会正常参加逻辑和绘制。
	 */
	class IScene{
	public:
		virtual ~IScene() {};

		/* 从被挂载的父场景上卸载本场景。
		*/
		virtual void UnmountSelf() = 0;

		/* 挂载组件
		 * 同一个组件多次挂载和单次挂载没什么不同
		 * @param 组件实例
		 * @param mountName 挂载名，可以匿名
		 */
		virtual void MountComponent(const std::shared_ptr<IComponent>&,const std::string mountName = "") = 0;

        /* 卸载已挂载到该场景的组件
		 * @param mountName 组件挂载名
		 */
		virtual void UnmountComponent(const std::string& mountName) = 0;

		/* 获取已挂载到该场景组件实例
		 * @param mountName 挂载名
		 * @result 组件实例
		 */
		virtual std::shared_ptr<IComponent> GetMountedComponent(const std::string& mountName) const = 0;

		/* 挂载物件
		 * 同一个物件被挂载多次和挂载一次没什么不同。
		 * @param 物件实例
		 * @param mountName 挂载名（可以匿名）
		 */
		virtual void MountGameObject(const std::shared_ptr<IGameObject>&,const std::string& mountName = "") = 0;

        /* 卸载已挂载物件
		 * @param mountNameame 物件挂载名
		 */
		virtual void UnmountGameObject(const std::string& mountName) = 0;

		/* 获取已挂载物件实例
		 * @param mountName 物件挂载名
		 * @result 物件实例
		 */
		virtual std::shared_ptr<IGameObject> GetMountedGameObject(const std::string& mountName) const = 0;

		/* 挂载一个场景
		 * @param 场景实例
		 * @param mountName 场景挂载名
		 */
		virtual void MountScene(const std::shared_ptr<IScene>&,const std::string& mountName ="") = 0;

		/* 卸载已挂载的场景
		 * @param name 场景挂载名
		 */
		virtual void UnmountScene(const std::string& mountName) = 0;

		/* 设置摄像机
		 * 2D/3D摄像机均可各设置一个。
		 * @param camera 摄像机
		 */
        virtual void SetCamera2D(const std::shared_ptr<const ICamera2D>& camera) = 0;
        virtual void SetCamera3D(const std::shared_ptr<const ICamera3D>& camera) = 0;

		/* 创建场景
         * 创建场景时，名称必须保证唯一，否则弹出异常。
		 * 可以创建匿名场景。
         * @result 场景实例
         */
        static std::shared_ptr<IScene> CreateScene();
	};
}

/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 给定名称
 */