#pragma once

#include<list>
#include<minmax.h>
namespace time1 {
	class GameTime {
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		GameTime()
		{
		}
		/// <summary>
		/// �f�X�g���N�^
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
		/// 1�t���[���̌o�ߎ��Ԃ��擾
		/// </summary>
		/// <returns>
		/// �o�ߎ���(�b)
		/// </returns>
		const float GetFrameTime() const
		{
			//�Œ�FPS�ɂ���B�ς͗v�����B
			//return 1.0f / 30.0f;
			return m_frameDeltaTime;
		}
		/// <summary>
		/// ���ώ��Ԃ𐶐�
		/// </summary>
		/// <param name="deltaTime">
		/// �P�t���[���ł����������ԁi�b�j
		/// </param>
		void PushFrameDeltaTime(float deltaTime)
		{
			m_frameDeltaTimeQue.push_back(deltaTime);
			if (m_frameDeltaTimeQue.size() > 30.0f) {
				float totalTime = 0.0f;
				for (auto time : m_frameDeltaTimeQue) {
					totalTime += time;
				}
				//���ϒl���Ƃ�B
				m_frameDeltaTime = min(1.0f / 15.0f, totalTime / m_frameDeltaTimeQue.size());
				m_frameDeltaTimeQue.pop_front();
			}
		}
	private:
		std::list<float> m_frameDeltaTimeQue;				//���ς̂��߂̔z��
		float		m_frameDeltaTime = 1.0f / 30.0f;		//1�t���[���̌o�ߎ��ԁB
	};
	static GameTime& GetTime()
	{
		return GameTime::GetInstance();
	}
}
