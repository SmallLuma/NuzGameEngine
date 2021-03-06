#pragma once
#include "InputDeviceManager.h"
namespace Nuz{

	/* 摇杆或十字键控制器 */
	class IJoystick:public IInputDevice{
	public:

		/* 取得推动或按下的X方向分向量
		 * 最左边(-1)，最右边(1)
		 * @result X分向量
		 */
		virtual float GetX() const = 0;

		/* 取得推动或按下的Y方向分向量
		 * 最上边(-1)，最下边(1)
		 * @result Y分向量
		 */
		virtual float GetY() const = 0;

		/* 摇杆状态是否被改变
		 * @result 摇杆状态是否被改变
		 */
	};

}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 *
 */
