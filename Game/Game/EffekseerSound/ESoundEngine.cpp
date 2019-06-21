/*!
 * @brief	サウンドエンジン
 */

#include "stdafx.h"
#include "sound/SoundEngine.h"
#include "sound/WaveFile.h"
#include "ESoundEngine.h"


#define NUM_PRESETS 30

namespace {
	//マイクロソフトのサンプルから引っ張ってきたサウンドコーン。
	// Specify sound cone to add directionality to listener for artistic effect:
	// Emitters behind the listener are defined here to be more attenuated,
	// have a lower LPF cutoff frequency,
	// yet have a slightly higher reverb send level.
	static const X3DAUDIO_CONE Listener_DirectionalCone = { X3DAUDIO_PI*5.0f / 6.0f, X3DAUDIO_PI*11.0f / 6.0f, 1.0f, 0.75f, 0.0f, 0.25f, 0.708f, 1.0f };

	// Specify LFE level distance curve such that it rolls off much sooner than
	// all non-LFE channels, making use of the subwoofer more dramatic.
	static const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_LFE_CurvePoints[3] = { 0.0f, 1.0f, 0.25f, 0.0f, 1.0f, 0.0f };
	static const X3DAUDIO_DISTANCE_CURVE       Emitter_LFE_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)&Emitter_LFE_CurvePoints[0], 3 };

	// Specify reverb send level distance curve such that reverb send increases
	// slightly with distance before rolling off to silence.
	// With the direct channels being increasingly attenuated with distance,
	// this has the effect of increasing the reverb-to-direct sound ratio,
	// reinforcing the perception of distance.
	static const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_Reverb_CurvePoints[3] = { 0.0f, 0.5f, 0.75f, 1.0f, 1.0f, 0.0f };
	static const X3DAUDIO_DISTANCE_CURVE       Emitter_Reverb_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)&Emitter_Reverb_CurvePoints[0], 3 };

	XAUDIO2FX_REVERB_I3DL2_PARAMETERS PRESET_PARAMS[NUM_PRESETS] =
	{
		XAUDIO2FX_I3DL2_PRESET_FOREST,
		XAUDIO2FX_I3DL2_PRESET_DEFAULT,
		XAUDIO2FX_I3DL2_PRESET_GENERIC,
		XAUDIO2FX_I3DL2_PRESET_PADDEDCELL,
		XAUDIO2FX_I3DL2_PRESET_ROOM,
		XAUDIO2FX_I3DL2_PRESET_BATHROOM,
		XAUDIO2FX_I3DL2_PRESET_LIVINGROOM,
		XAUDIO2FX_I3DL2_PRESET_STONEROOM,
		XAUDIO2FX_I3DL2_PRESET_AUDITORIUM,
		XAUDIO2FX_I3DL2_PRESET_CONCERTHALL,
		XAUDIO2FX_I3DL2_PRESET_CAVE,
		XAUDIO2FX_I3DL2_PRESET_ARENA,
		XAUDIO2FX_I3DL2_PRESET_HANGAR,
		XAUDIO2FX_I3DL2_PRESET_CARPETEDHALLWAY,
		XAUDIO2FX_I3DL2_PRESET_HALLWAY,
		XAUDIO2FX_I3DL2_PRESET_STONECORRIDOR,
		XAUDIO2FX_I3DL2_PRESET_ALLEY,
		XAUDIO2FX_I3DL2_PRESET_CITY,
		XAUDIO2FX_I3DL2_PRESET_MOUNTAINS,
		XAUDIO2FX_I3DL2_PRESET_QUARRY,
		XAUDIO2FX_I3DL2_PRESET_PLAIN,
		XAUDIO2FX_I3DL2_PRESET_PARKINGLOT,
		XAUDIO2FX_I3DL2_PRESET_SEWERPIPE,
		XAUDIO2FX_I3DL2_PRESET_UNDERWATER,
		XAUDIO2FX_I3DL2_PRESET_SMALLROOM,
		XAUDIO2FX_I3DL2_PRESET_MEDIUMROOM,
		XAUDIO2FX_I3DL2_PRESET_LARGEROOM,
		XAUDIO2FX_I3DL2_PRESET_MEDIUMHALL,
		XAUDIO2FX_I3DL2_PRESET_LARGEHALL,
		XAUDIO2FX_I3DL2_PRESET_PLATE,
	};
}
/*!
	* @brief	コンストラクタ。
	*/
ESoundEngine::ESoundEngine()
{
	//g_effektsound = this;
}
/*!
	* @brief	デストラクタ。
	*/
ESoundEngine::~ESoundEngine()
{
	Release();
}
/*!
	* @brief	初期化。
*/
/*!
	* @brief	開放。
	*/
void ESoundEngine::Release()
{
	//波形データバンクを解放。
	m_waveFileBank.ReleaseAll();

	if (m_submixVoice != nullptr) {
		m_submixVoice->DestroyVoice();
		m_submixVoice = nullptr;
	}
	if (m_reverbEffect != nullptr) {
		m_reverbEffect->Release();
		m_reverbEffect = nullptr;
	}
	if (m_masteringVoice != nullptr) {
		m_masteringVoice->DestroyVoice();
		m_masteringVoice = nullptr;
	}
	if (m_xAudio2 != nullptr) {
		m_xAudio2->Release();
		m_xAudio2 = nullptr;
	}


	CoUninitialize();
}
/*!
* @brief	XAudio2のソースボイスを作成。
*/
IXAudio2SourceVoice* ESoundEngine::CreateXAudio2SourceVoice(CWaveFile* waveFile, bool is3DSound)
{
	IXAudio2SourceVoice* pSourceVoice;

	//ソースボイスの濁世。
	if (FAILED(m_xAudio2->CreateSourceVoice(&pSourceVoice, waveFile->GetFormat())))
	{
		return nullptr;
	}
	return pSourceVoice;
}

