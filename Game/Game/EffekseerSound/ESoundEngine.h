

#pragma once
#include "sound/WaveFileBank.h"

#define INPUTCHANNELS 2  // number of source channels
#define OUTPUTCHANNELS 8	//�ő�o�̓`�����l�����B
class CWaveFile;
class CSoundSource;
/// <summary>
/// �T�E���h�G���W���B
/// </summary>
class ESoundEngine :public Effekseer::SoundPlayer {
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	ESoundEngine();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~ESoundEngine();
	/// <summary>
	/// ���
	/// </summary>
	/// <remarks>
	/// �f�X�g���N�^����Ă΂�Ă��܂��B
	/// �����I�ɊJ���������ꍇ�Ɏg�p���Ă��������B
	/// </remarks>
	void Release();
	void* Play(void* tag, const InstanceParameter& parameter)
	{

		//	//�T�E���h�\�[�X�̍X�V�B
		//	auto it = m_soundSources.begin();
		//	while (it != m_soundSources.end()) {

		//		auto soundSource = *it;
		//		soundSource->Update();
		//		if (soundSource->IsPlaying() == false) {
		//			//�Đ��I���B
		//			it = RemoveSoundSource(*it);
		//		}
		//		else {
		//			it++;
		//		}
		//	}
		return NULL;
	}
	void Stop(void* handle, void* tag)
	{

	}
	void Pause(void* handle, void* tag, bool pause)
	{

	}

	bool CheckPlaying(void* handle, void* tag)
	{
		return true;
	}

	void StopTag(void* tag)
	{

	}

	void PauseTag(void* tag, bool pause)
	{

	}

	bool CheckPlayingTag(void* tag)
	{
		return true;
	}

	void StopAll()
	{

	}
	/// <summary>
	/// �T�E���h�\�[�X�̒ǉ��B
	/// </summary>
	/// <param name="s">�T�E���h�\�[�X</param>
	void AddSoundSource(CSoundSource* s) 
	{
		auto it = std::find(m_soundSources.begin(), m_soundSources.end(), s);
		if (it == m_soundSources.end()) {
			//���o�^�Ȃ�o�^����B
			m_soundSources.push_back(s);
		}
	}
	/// <summary>
	/// �T�E���h�\�[�X���폜�B
	/// </summary>
	/// <param name="s"></param>
	/// <returns>�폜�����v�f�̎����w���C�e���[�^�[</returns>
	auto RemoveSoundSource(CSoundSource* s)
	{
		auto it = std::find(m_soundSources.begin(), m_soundSources.end(), s);
		if (it != m_soundSources.end()) {
			it = m_soundSources.erase(it);
		}
		return it;
	
	}
	/// <summary>
	/// XAudio2�̃\�[�X�{�C�X�̍쐬�B
	/// </summary>
	/// <param name="waveFile"></param>
	/// <param name="is3DSound"></param>
	/// <returns></returns>
	IXAudio2SourceVoice* CreateXAudio2SourceVoice(CWaveFile* waveFile, bool is3DSound);
	IXAudio2MasteringVoice* GetMasteringVoice()
	{
		return m_masteringVoice;
	}
	IXAudio2SubmixVoice* GetSubmixVoice()
	{
		return m_submixVoice;
	}

	/// <summary>
	/// �o�̓`�����l���̐����擾�B
	/// </summary>
	/// <returns></returns>
	int GetNumChannel() const
	{
		return m_nChannels;
	}

	/// <summary>
	/// �g�`�f�[�^�o���N���擾�B
	/// </summary>
	CWaveFileBank& GetWaveFileBank()
	{
		return m_waveFileBank;
	}

private:
	IXAudio2* m_xAudio2 = nullptr;
	IXAudio2MasteringVoice* m_masteringVoice = nullptr;
	IUnknown* m_reverbEffect = nullptr;				//!<���o�[�v�G�t�F�N�g�B
	IXAudio2SubmixVoice* m_submixVoice = nullptr;	//!<�T�u�~�b�N�X�{�C�X�B
	DWORD m_channelMask = 0;						//!<�I�[�f�B�I�`�����l���}�X�N�B
	DWORD m_nChannels = 0;							//!<�`�����l�����B
	bool m_isInited = false;
	std::list<CSoundSource*>	m_soundSources;		//!<�T�E���h�\�[�X�̃��X�g�B
	CWaveFileBank m_waveFileBank;					//!<�g�`�f�[�^�̃o���N�B
};
class ESoundLood :Effekseer::SoundLoader
{
	void* Load(const EFK_CHAR* path)
	{
		m_bgmA.Init(path);
		m_bgmA.Play(true);
	}

	/**
	@brief	�T�E���h��j������B
	@param	data	[in]	�T�E���h
	@note
	�T�E���h��j������B
	::Effekseer::Effect�̃C���X�^���X���j�����ꂽ���Ɏg�p�����B
	*/
	void Unload(void* source);
private:
	CSoundSource m_bgmA;									//BGM�p�̃N���X
};