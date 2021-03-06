#pragma once
#include <memory>
#include <string>
#include "../Component.h"

namespace Nuz{

	/* 着色器
	 * 每个游戏物件仅可使用一个Shader注意！
     * 如果Shader被挂在到了场景上，那么它的处理对象是场景的帧缓存而非场景内的物件。
	 */
	class IShader:public IComponent{
	public:

		/* 设置着色器的Uniform Float变量
		 * @param uniform uniform变量名
		 * @param size 标量个数（1~4）（不作参数检查）
		 * @param 这些都是变量，因为它可能有多个float值
		 */
		virtual void SetUniformFloat(const std::string& uniform,int size,float,float = 0,float = 0,float = 0) = 0;

        /* 设置着色器的Uniform Int变量
		 * @param uniform uniform变量名
		 * @param size 标量个数（1~4）（不作参数检查）
		 * @param 这些都是变量，因为它可能有多个int值
		 */
		virtual void SetUniformInt(const std::string& uniform,int size,int,int = 0,int = 0,int = 0) = 0;

		/* 着色器句柄 */
		typedef int ShaderHandle;

		/* 获取Handle以在组件中操作着色器
		 * @result Handle
		 */
        virtual ShaderHandle GetHandle() = 0;


		/* 着色器创建配置
		 * 在这里填入文件路径
		 * 没有的着色器会被默认着色器替代。
	 	 * 默认顶点着色器实现了坐标转换。
		 * 默认片元着色器实现了贴图。
	 	 */
		struct CreateConfig {
			std::string
				vertexShader,	//顶点着色器
				fragmentShader;	//片元着色器
		};

        /* 从文件创建着色器并返回着色器实例
         * @param 创建配置
		 * @throw ShaderCompileError
         * @result 着色器实例
         */
        static std::shared_ptr<IShader> CreateShaderFromFile(const CreateConfig&);

		class ShaderCompileError :public std::runtime_error {
			using std::runtime_error::runtime_error;
		};
	};
}
/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 * 2016年4月24日：
 * 星翼 添加方法SetUniformFloat和SetUniformInt。
 * 星翼 允许从字符串加载着色器。
 * 星翼 允许取得ShaderHandle。
 * 2016年4月28日：
 * 星翼 给定名称
 */
