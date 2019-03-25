#pragma once

#include<list>
#include<minmax.h>
namespace time1 {
	class GameTime {
		/// <summary>
		/// コンストラクタ
		/// </summary>
		GameTime()
		{
		}
		/// <summary>
		/// デストラクタ
		/// </summary>
		~GameTime()
		{
		}
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static inline GameTime& GetInstance()
		{
			static GameTime t;
			return t;
		}
		/// <summary>
		/// 1フレームの経過時間を取得
		/// </summary>
		/// <returns>
		/// 経過時間(秒)
		/// </returns>
		const float GetFrameTime() const
		{
			//固定FPSにする。可変は要検討。
			//return 1.0f / 30.0f;
			return m_frameDeltaTime;
		}
		/// <summary>
		/// 平均時間を生成
		/// </summary>
		/// <param name="deltaTime">
		/// １フレームでかかった時間（秒）
		/// </param>
		void PushFrameDeltaTime(float deltaTime)
		{
			m_frameDeltaTimeQue.push_back(deltaTime);
			if (m_frameDeltaTimeQue.size() > 30.0f) {
				float totalTime = 0.0f;
				for (auto time : m_frameDeltaTimeQue) {
					totalTime += time;
				}
				//平均値をとる。
				m_frameDeltaTime = min(1.0f / 15.0f, totalTime / m_frameDeltaTimeQue.size());
				m_frameDeltaTimeQue.pop_front();
			}
		}
	private:
		std::list<float> m_frameDeltaTimeQue;				//平均のための配列
		float		m_frameDeltaTime = 1.0f / 30.0f;		//1フレームの経過時間。
	};
	static GameTime& GetTime()
	{
		return GameTime::GetInstance();
	}
}
