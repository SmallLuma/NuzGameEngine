#pragma once
#include <memory>
#include <string>
namespace Nuz{
	class IComponent;

	/* 物件
	 * 游戏中一个可以挂载组件的物品。
	 * 下层物件会悬浮在上层物件的上方（2D绘制的状态下）。
     * 一个实例只允许被挂载到一个实例（物件或场景）上。
	 */
	class IGameObject{
	public:
		virtual ~IGameObject() {}

		/* 从父节点上卸载该物件
		*/
		virtual void UnmountSelf() = 0;

		/* 挂载组件
         * 同一个组件多次挂载和单次挂载没什么不同
         * 挂载名在本物件里是唯一的。
		 * @param 组件实例
		 * @param 挂载名（可以匿名，但你将无法通过挂载名找回它）
		 */
		virtual void MountComponent(const std::shared_ptr<IComponent>&,const std::string& mountName = "") = 0;

		/* 卸载已挂载组件
		 * @param mountName 组件挂载名
		 */
		virtual void UnmountComponent(const std::string& mountName) = 0;

		/* 获取已挂载组件实例
		 * @param mountName 组件挂载名
		 * @result 组件实例
		 */
		virtual std::shared_ptr<IComponent> GetMountedComponent(const std::string& mountName) const = 0;

		/* 挂载物件
		 * @param 物件实例
		 * @param mountName 物件挂载名（可以匿名）
		 */
		virtual void MountGameObject(const std::shared_ptr<IGameObject>&,const std::string& mountName = "") = 0;

        /* 卸载已挂载物件
		 * @param mountName 物件挂载名
		 */
		virtual void UnmountGameObject(const std::string& mountName) = 0;

		/* 获取已挂载物件实例
		 * @param mountName 物件挂载名
		 * @result 物件实例
		 */
		virtual std::shared_ptr<IGameObject> GetMountedGameObject(const std::string& mountName) const = 0;

		/* 设置绘制优先级
		 * @param 优先级（数值越小越优先，默认为0，可以为负数）
		 */
		virtual void SetDrawLevel(int) = 0;

        /* 创建物件
         * @result 物件实例
         */
        static std::shared_ptr<IGameObject> CreateGameObject();
	};
}

/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 给出名称
 */