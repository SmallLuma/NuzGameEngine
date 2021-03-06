#pragma once
#include "../Component.h"
#include "../../Font.h"
#include <memory>
#include <string>

namespace Nuz{

	/* 2D精灵组件
	* 实现2D图像的绘制。
	* 在OpenGL里使用0号纹理单元贴图。
	*/
	class ISprite2D:public IComponent{
	public:
		/* 使用图像
		* 请在创建完场景，并在完成2D摄像机设置后再挂载。
		* 如果使用途中修改了摄像机，但想保持图像大小不变，请使用SetDstSizeAsDefault更新大小。
		* @param path 图像文件
		* @param num 图像编号
		* @throw std::runtime_error
		*/
		virtual void UseImage(const std::string& path,int num = 0) = 0;

		/* 使用文本
		 * @param fontPath 字体路径
		 * @param text 文本
		 * @param size 字体大小
		 * @throw std::runtime_error
		 */
		virtual void UseText(Nuz::IFont& font, const std::wstring& text, uint8_t r=255, uint8_t g=255, uint8_t b=255) = 0;

		/* 释放图像
		*/
		virtual void FreeImage() = 0;

		/* 设置只使用一块子图像
		* @param x 图像左上角x位置（像素）
		* @param y 图像左上角y位置(像素)
		* @param w 图像的宽
		* @param h 图像的高
		*/
		virtual void SetSrc(int x,int y,int w,int h) = 0;

		/* 获取当前图像总大小
		* @param w 宽
		* @param h 高
		*/
		virtual void GetSize(int& w,int& h) const = 0;

		/* 设置图像绘制的目的中心位置
		* @param x 当前摄像机x位置
		* @param y 当前摄像机y位置
		*/
		virtual void SetPos(float x,float y) = 0;

		/* 设置在当前摄像机下的的绘制大小
		* @param w 宽度（2D摄像机坐标）
		* @param h 高度（2D摄像机坐标）
		*/
		virtual void SetScale(float w,float h) = 0;

		/* 获取在当前摄像机下的的绘制大小
		 * @param w 宽度（2D摄像机坐标）
		 * @param h 高度（2D摄像机坐标）
		 */
		virtual void GetScale(float& w, float& h) = 0;

		/* 设置目标位置大小为图像实际大小，摄像机无关
		 */
		virtual void SetDstSizeAsDefault() = 0;

		/* 设置旋转
		 * 旋转中心：没有翻转的情况下(-1,-1)为左下角，(1,1)为右上角。
		 * @param enable 是否启用
		 * @param x 旋转中心x
		 * @param y 旋转中心y
		 * @param angle 旋转角度
		 * @param yFlip 是否绕y轴旋转
		 * @param xFlip 是否绕x轴旋转
		 */
		virtual void SetRotate(bool enable,float x=0,float y=0,float angle=180,bool yFlip=false,bool xFlip=false) = 0;

		/* 设置是否可见
		 * @param 可见
		 */
		virtual void SetVisible(bool) = 0;

		/* 设置不透明度
		 * @param 不透明度（范围0~1）
		 */
		virtual void SetAlpha(float) = 0;

		/* 设置滤色（范围0~1）
		 * @param r 红色因子
		 * @param g 绿色因子
		 * @param b 蓝色因子
		 */
		virtual void SetColorFliter(float r, float g, float b) = 0;

        /* 创建一个2D精灵组件
         * @result 精灵组件
         */
        static std::shared_ptr<ISprite2D> CreateSprite2D();
	};
}
/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 给定名称
 */
