/*!
 *@brief	アニメーションクリップ。
 */

#pragma once

//////////////////////////////////////////////////////////////////////
// 各種構造体
//////////////////////////////////////////////////////////////////////
/*!
*@brief	アニメーションクリップのヘッダー。
*/
struct AnimClipHeader {
	std::uint32_t numKey;				//!<キーフレームの数。
	std::uint32_t numAnimationEvent;	//!<アニメーションイベントの数。
};
/*!
*@brief	アニメーションイベント
*@アニメーションイベントは未対応。
* やりたかったら自分で実装するように。
*/
struct AnimationEventData {
	float	invokeTime;					//!<アニメーションイベントが発生する時間(単位:秒)
	std::uint32_t eventNameLength;		//!<イベント名の長さ。
};
/*!
*@brief	キーフレーム。
*/
struct Keyframe {
	std::uint32_t boneIndex;	//!<ボーンインデックス。
	float time;					//!<時間。
	CMatrix transform;			//!<トランスフォーム。
};
/*!
*@brief	キーフレーム。
*/
struct KeyframeRow {
	std::uint32_t boneIndex;	//!<ボーンインデックス。
	float time;					//!<時間。
	CVector3 transform[4];		//!<トランスフォーム。
};
/// <summary>
/// アニメーションイベントクラス
/// </summary>
/// <remarks>
/// キーとキーの間を取るためのデータです
/// </remarks>
class AnimationEvent : Noncopyable
{
public:
	AnimationEvent()
	{

	}
	~AnimationEvent()
	{

	}
	/// <summary>
	/// イベントの名前のセット
	/// </summary>
	/// <param name="name">
	/// 名前（const wchar_t*）
	/// </param>
	void SetEventname(const wchar_t* name)
	{
		m_eventname = name;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="flag">
	/// 
	/// </param>
	void SetInvokedFlag(bool flag)
	{
		m_isInvoked = flag;
	}
	void SetinvokeTime(float taim)
	{
		m_invokeTime = taim;
	}	
	const wchar_t* GetEventname() const
	{
		return m_eventname.c_str();
	}
	bool GetInvokedFlag()
	{
		return m_isInvoked;
	}
	float GetinvokeTime()
	{
		return m_invokeTime;
	}
private:
	bool m_isInvoked = false;
	float m_invokeTime = -1.0f;		//フレームの発生位置（秒）
	std::wstring m_eventname=L"NULL";	//イベントの名前
};
/*!
*@brief	アニメーションクリップ。
*/
class AnimationClip:Noncopyable{
public:
	//タイプ量が長ったらしくて、うざいのでstd::vector<KeyFrame*>の別名定義。
	using keyFramePtrList = std::vector<Keyframe*>;
	/*!
	* @brief	コンストラクタ
	*/
	AnimationClip() 
	{
	}
	/*!
	*@brief	デストラクタ。
	*/
	~AnimationClip();
	/*!
	*@brief	アニメーションクリップをロード。
	*@param[in]	filePath	ファイルパス。
	*/
	void Load(const wchar_t* filePath);

	/*!
	*@brief	ループする？
	*/
	bool IsLoop() const
	{
		return m_isLoop;
	}
	/*!
	*@brief	ループフラグを設定する。
	*/
	void SetLoopFlag(bool flag)
	{
		m_isLoop = flag;
	}
	/*!
	*@brief
	*/
	const std::vector<keyFramePtrList>& GetKeyFramePtrListArray() const
	{
		return m_keyFramePtrListArray;
	}
	const keyFramePtrList& GetTopBoneKeyFrameList() const
	{
		return *m_topBoneKeyFramList;
	}
	const std::vector<AnimationEvent*>& GetAnimationEventlist()const
	{
		return m_AnimationEventlist;
	}
private:
	
	bool m_isLoop = false;									//!<ループフラグ。
	std::vector<Keyframe*> m_keyframes;						//全てのキーフレーム。
	std::vector<keyFramePtrList> m_keyFramePtrListArray;	//ボーンごとのキーフレームのリストを管理するための配列。
															//例えば、m_keyFramePtrListArray[0]は0番目のボーンのキーフレームのリスト、
															//m_keyFramePtrListArray[1]は1番目のボーンのキーフレームのリストといった感じ。
	std::vector<AnimationEvent*> m_AnimationEventlist;
	keyFramePtrList* m_topBoneKeyFramList = nullptr;
};

