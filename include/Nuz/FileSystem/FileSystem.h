#pragma once
#include <string>
#include <memory>
#include <vector>
#include <cstdint>
namespace Nuz{
	class IFileSource;

	/* 文件系统
	 * 提供对文件的读入，可以挂载数据源，使用虚拟磁盘。
	 * 路径参考Linux/Unix的路径格式。
	 */
	class IFileSystem{
	public:
		/* 挂载数据源
		 * @param source 数据源实例
         * @throw CannotMountFileSource 如果挂载时出错则报出异常
		 */
		virtual void Mount(std::shared_ptr<IFileSource> source) = 0;

		/* 加载文件
		 * 它会把整个文件加载到内存中并返回一个已经被加载完的缓存区指针。
		 * @param path 文件路径
		 * @throw InvalidFileName 无效的文件名
		 * @throw CannotOpenFile 无法打开文件
		 * @result 得到的文件的缓存区指针
		 */
		virtual std::shared_ptr<std::vector<uint8_t>> LoadFile(const std::string& path) const = 0;

        /* 异常类：错误的文件名格式 */
        class InvalidFileName:public std::invalid_argument{
        public:
            inline InvalidFileName(const std::string& s):std::invalid_argument(s){};
        };

        /* 异常类：无法打开文件 */
        class CannotOpenFile:public std::runtime_error{
        public:
            inline CannotOpenFile(const std::string& s):std::runtime_error(s){};
        };

        /* 异常类：无法挂载数据源 */
        class CannotMountFileSource:public std::runtime_error{
        public:
            inline CannotMountFileSource(const std::string& s):std::runtime_error(s){};
        };
	};
}

/* 更新日志：
 * 2016年4月17日：
 * 星翼 初稿
 * 2016年4月21日：
 * 星翼 简化数据源模型
 * 2016年4月24日：
 * 星翼 移动异常类
 */
