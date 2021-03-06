#pragma once
#include <memory>
namespace Nuz{

	/* 2D摄像机
	* 实现2D图像的定位。
	*/
	/* 默认的摄像机
	 * 屏幕中心为(0,0)
	 * 屏幕左上角为(-1,-1)
	 * 屏幕右下角为(1,1)
	 * 以此类推。
	 */
	class ICamera2D{
	public:
		virtual ~ICamera2D() {}

		/* 设置初始状态
		 * @param left 左边缘
		 * @param right 右边缘
		 * @param top 上边缘
		 * @param bottom 下边缘
		 * @param near 近Z面
		 * @param far 远Z面
		 */
		virtual void SetCamera(float left,float right,float top,float bottom) = 0;

		/* 以当前摄像机为基准缩放
		 * @param w 横向大小倍数
		 * @param h 纵向大小倍数
		 */
		virtual void Zoom(float w,float h) = 0;

		/* 绕摄像机(0,0)点旋转当前摄像机
		 * @param angle 角度
		 */
		virtual void Rotate(float angle) = 0;

		/* 以当前摄像机为基准进行平移
		 * @param x 移动的x量
		 * @param y 移动的y量
		 */
		virtual void Move(float x,float y) = 0;

        /* 创建一个2D摄像机
         * @result 摄像机
         */
        static std::shared_ptr<ICamera2D> CreateCamera2D();
	};
}
/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 移动创建方法并给定名称
 * 2016年4月29日：
 * 星翼 不再是组件
 */
