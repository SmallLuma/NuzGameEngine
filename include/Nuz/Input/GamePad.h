#pragma once
#include <memory>
#include "InputDeviceManager.h"

namespace Nuz{
	class IJoystick;

	/* 手柄控制器 */
	class IGamePad:IInputDevice{
	public:
		/* 取得按键数量
		 * @result 按键数量
		 */
		virtual int GetButtonNums() const = 0;

		/* 取得按键是否已经按下
		 * @param n 按键编号
		 * @result 按键是否已经按下
		 */
		virtual bool KeyPressed(int n) const = 0;

		/* 取得手柄的摇杆或十字键数量
		 * @result 数量
		 */
		virtual int GetJoystickNum() const = 0;

		/* 取得第n个摇杆或十字键
		 * @param n 摇杆或十字键编号
		 * @result 摇杆或十字键实例
		 */
		virtual IJoystick& GetJoystick() const = 0;

		/* 手柄状态是否被改变
		 * @result 手柄状态是否被改变
		 */
		virtual bool Changed() = 0;
	};
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 *
 */
