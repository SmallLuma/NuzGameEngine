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
		 * @param 这些都是变量，因为它可能有多个float值
		 */
		virtual void SetUniformFloat(const std::string& uniform,float,float = 0,float = 0,float = 0,float = 0) = 0;

        /* 设置着色器的Uniform Int变量
		 * @param uniform uniform变量名
		 * @param 这些都是变量，因为它可能有多个int值
		 */
		virtual void SetUniformInt(const std::string& uniform,int,int = 0,int = 0,int = 0,int = 0) = 0;

		/* 着色器句柄 */
		typedef int ShaderHandle;

		/* 获取Handle以在组件中操作着色器
		 * @result Handle
		 */
        virtual ShaderHandle GetHandle() = 0;

        /* 从文件创建着色器并返回着色器实例
         * @param vert 顶点着色器文件名
         * @param frag 片元着色器文件名
         * @param name 组件名称
         * @result 着色器实例
         */
        static std::shared_ptr<IShader> CreateShaderFromFile(const std::string& vert,const std::string& frag,const std::string& name = "");

        /* 从字符串创建着色器并返回着色器实例
         * @param vert 顶点着色器文件名
         * @param frag 片元着色器文件名
         * @param name 组件名称
         * @result 着色器实例
         */
        static std::shared_ptr<IShader> CreateShaderFromstring(const std::string& vert,const std::string& frag,const std::string& name = "");
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
