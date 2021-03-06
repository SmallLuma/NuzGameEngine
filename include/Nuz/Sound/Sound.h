#pragma once
#include <memory>
#include <string>
namespace Nuz{

	/* 音效
	 */
	class ISound{
	public:
		virtual ~ISound(){}

		/* 播放音效
		 * @param fadein 淡入时长（毫秒）
		 */
		virtual void Play(int fadein=0) = 0;


		/* 创建音效
		 * 为了节省资源，会对音效对象进行缓存。
		 * 当你创建两次同一个音效是，你将得到指向相同音效的指针。
		 * @param 文件
		 */
		static std::shared_ptr<ISound> CreateSound(const std::string&);

		/* 暂停所有音效（不含BGM）
		 */
		static void PauseAllSound();

		/* 恢复播放所有暂停的音效（不含BGM）
		 */
		static void ResumeAllSound();

		/* 停止所有音效（不含BGM）
		 */
		static void StopAllSound();

		/* 设置音效播放的音量（不含BGM）
		 * @param 音量（范围0~1）
		 */
		static void SetVolumeAllSound(float);
	};
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 * 2016年5月29日：
 * 星翼 更改音效的播放方式
 */
