#pragma once
#include "../Component.h"

namespace Nuz{

	/* 逻辑组件
	 * 实现逻辑
	 */
	class ILogic:public IComponent{
	public:
	    /* 构造时注意
	     * 组件名称，详见../IComponent.h
	     */
		void OnUpdate(bool& draw2D, bool& draw3D) override { }	//当组件需要更新逻辑时执行

		/* 当场景要求被切出时执行
		 * @param timeLimited 时间限制（帧）
		 */
        void OnFadeSwitchOut(int timeLimited) override{};

		/* 当场景被切出时会增加的增补逻辑
		 * @param finished 时间剩余百分比
		 */
        void OnFadeSwitchOutUpdate(float finished) override{};

		/* 当场景要求被切入时执行
		 * @param timeLimited 时间限制（帧）
		 */
        void OnFadeSwitchIn(int timeLimited) override{};

		/* 当场景被切入时会增加的增补逻辑
		 * @param finished 时间剩余百分比
		 */
        void OnFadeSwitchInUpdate(float finished) override{};

	};
}
/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月27日：
 * 星翼 修改为override方式
 * 2016年4月28日：
 * 星翼 给定名称
 */