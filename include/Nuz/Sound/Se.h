#pragma once
#include <memory>
#include <string>
namespace Nuz{

	/* 音效
	 */
	class ISe{
	public:
		virtual ~ISe(){}

		/* 播放音效
		 * @param fadein 淡入时长（毫秒）
		 */
		virtual void Play(int fadein=0) = 0;


		/* 创建音效
		 * @param 文件
		 */
		static std::shared_ptr<ISe> CreateSe(const std::string&);
	};
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 * 2016年5月29日：
 * 星翼 更改音效的播放方式
 */
