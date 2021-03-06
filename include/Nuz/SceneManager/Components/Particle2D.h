#pragma once
#include "../Component.h"
#include <string>
#include <functional>

namespace Nuz{

	/* 2D粒子组件 */
	class IParticle2D:public Nuz::IComponent{
	public:
		/* 单个粒子 */
		/* 注意：没有错误检查。
		* 你必须挂载全局粒子处理器、单个粒子处理器以及一个点纹理。
		* 你可以手动检查粒子系统是否可以使用。
		* 在OpenGL里使用0号纹理单元贴图。
		*/
		struct Dot2D {
		public:
			float speed = 0;	//速度
			float alpha = 1.0f;	//透明度（1为不透明，小于等于0时销毁粒子）
			float angle = 0;	//方向
			float userdataf[4] = { 0 };	//用户数据
			uint32_t userdata[4] = { 0 };
			float r = 1.0f, g = 1.0f, b = 1.0f;	//颜色过滤
			float x = 0, y = 0;	//坐标
			float size = 2.0;	//尺寸（2为标准大小，小于等于0时销毁粒子）
		};
		/* 使用一个粒子纹理
		* @param 文件
		* @param 图像编号
		*/
		virtual void UseImage(const std::string&,int = 0) = 0;

		/* 绑定单个粒子处理器
		 * 粒子处理器每帧都会遍历每个粒子
		 * 你可以处理这些粒子的行为
		 * @param 要绑定的粒子处理器
		*/
		virtual void BindSingle(std::function<void(IParticle2D&,Dot2D&)>) = 0;

		/* 绑定单个粒子初始化器
		* 粒子创建后会立刻执行
		* @param 要绑定的粒子处理器
		*/
		virtual void BindIniter(std::function<void(Nuz::IParticle2D&, Nuz::IParticle2D::Dot2D&)>) = 0;

		/* 添加粒子
		 * @param x 粒子初始x坐标
		 * @param y 粒子初始y坐标
		 * @param num 粒子数量
		 * 该粒子会立刻被执行粒子初始化器
		 */
		virtual void AddDot(float x,float y,int num) = 0;

		/* 检查粒子系统是否正确 
		 * 如果不可用则弹出std::runtime_error
		 * @throw std::runtime_error
		 */
		virtual void Check() = 0;

		/* 粒子是否为空
		 * @result 是否为空
		 */
		virtual bool Empty() = 0;

		/* 删除所有粒子
		 */
		virtual void Clear() = 0;

        /* 创建2D粒子系统
         * @result 2D粒子系统
         */
        static std::shared_ptr<IParticle2D> CreateParticle2D();
	};
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 给定名称
 */
