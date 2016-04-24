#pragma once
#include <memory>
#include <string>

namespace NuzUtils{

	/* SnowRV阅读器
	 */
	class ISnowRVReader{
	public:

		/* 取得字符串常量
		 * @param 常量名
         * @throw ValueNotFound
		 * @result 常量字符串
		 */
		virtual std::string GetString(const std::string&) = 0;

		/* 取得数值常量
		 * @param 常量名
         * @throw ValueNotFound
		 * @result 常量数值
		 */
		virtual int GetInt(const std::string&) = 0;

		/* 取得浮点数常量
		 * @param 常量名
         * @throw ValueNotFound
		 * @result 常量浮点数
		 */
		virtual double GetFloat(const std::string&) = 0;

		/* 存储为可以快速读取的二进制码
		 * @param 文件名
         * @throw IFileSystem::CannotOpenFile
         * @throw IFileSystem::InvaildFileName
         */
        virtual void SaveToFastReadFile(const std::string&) = 0;

        /* 异常类：错误的SnowRV */
        class SnowRVCompileFailed:public std::runtime_error{
        public:
            inline SnowRVCompileFailed(const std::string& s):std::runtime_error(s){};
        };

        /* 异常类：SnowRV中未找到相应对象 */
        class ValueNotFound:public std::runtime_error{
        public:
            inline ValueNotFound(const std::string& s):std::runtime_error(s){};
        };
	};

	/* 创建SnowRV阅读器
	 * @param RV文件
     * @throw ISnowRVReader::SnowRVCompileFailed
     * @throw IFileSystem::CannotOpenFile
     * @throw IFileSystem::InvaildFileName
	 * @result RV阅读器
	 */
	std::shared_ptr<ISnowRVReader> CreateSnowRVReader(const std::string& path);
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 * 2016年4月22日：
 * 星翼 字节码加入
 * 2016年4月24日：
 * 星翼 加入异常
 */
