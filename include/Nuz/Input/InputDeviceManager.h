#pragma once
#include <memory>
#undef NUZ_VER_FULL
namespace Nuz{
	class IKeyboard;

	/* 此处不属于最小Nuz范围 */
	#ifdef NUZ_VER_FULL
	class IGamePad;
	#endif

	/* 输入设备基类
	 */
	class IInputDevice {
	public:
		virtual ~IInputDevice(){}

		/* 是否出现了新的输入
		 * @result 是否出现了新的输入
		 */
		virtual bool Changed() = 0;
	};

	/* 输入设备管理器
	 * 负责管理所有的输入设备
	 */
	class IInputDeviceManager{
	public:
		virtual ~IInputDeviceManager(){}

		/* 获取键盘控制器
		 * @result 键盘控制器
		 */
		virtual IKeyboard& GetKeyboard() = 0;

		/* 此处不属于最小Nuz范围 */
		#ifdef NUZ_VER_FULL

		/* 获取接入手柄数量
		 * @result 手柄数量
		 */
		virtual int GetGamePadNum() const = 0;

		/* 获取接入手柄
		 * @param 手柄编号
		 * @result 手柄实例
		 */
		 virtual IGamePad& GetGamePad(int) const = 0;
		#endif
	};
}
#define NUZ_VER_FULL
/* 更新日志：
 * 2016年4月17日：
 * 星翼 初稿
 * 2016年5月26日：
 * 星翼 加入IInputDevice类
 */
