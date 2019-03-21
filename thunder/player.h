#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 自機画像
#define	TEXTURE_PLAYER					_T("data/TEXTURE/player1.png")			// 読み込むテクスチャファイル名
// サイズ		
#define PLAYER_SIZE_X					(80)	// プレイヤーの幅(X)
#define PLAYER_SIZE_Y					(80)	// プレイヤーの高さ(Y)

// エンジンエフェクト
#define	TEXTURE_ENGINE_EFFECT			_T("data/TEXTURE/ENGINE_EFFECT.png")	// 読み込むテクスチャファイル名
// サイズ
#define ENGINE_EFFECT_SIZE_X			(30)	// プレイヤーの幅(X)
#define ENGINE_EFFECT_SIZE_Y			(30)	// プレイヤーの高さ(Y)
// アニメーションパターン
#define ENGINE_EFFECT_PATTERN_DIVIDE_X	(5)		// アニメパターンのテクスチャ内分割数（X)
#define ENGINE_EFFECT_PATTERN_DIVIDE_Y	(2)		// アニメパターンのテクスチャ内分割数（Y)
#define ENGINE_EFFECT_ANIM_PATTERN_NUM	(ENGINE_EFFECT_PATTERN_DIVIDE_X*ENGINE_EFFECT_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define TIME_ENGINE_EFFECT_ANIMATION	(4)		// アニメーションの切り替わるカウント

// プレイヤー情報
#define PLAYER_HP_MAX					(100)
#define PLAYER_NORMAL_SPEED				(10)
#define PLAYER_SHIFT_SPEED				(5)
#define PLAYER_SPAWN_POS				(D3DXVECTOR3(300.0f, 1000.0f, 0.0f))
#define PLAYER_START_POS_Y				(SCREEN_HEIGHT - PLAYER_SIZE_Y * HALF)				
#define PLAYER_LEVEL_UP_EXP				(10)

// 点滅用
#define PLAYER_FLASHING_ALPHA_ON		D3DCOLOR_RGBA(255, 255, 255, 255)	// 点の状態のα値
#define PLAYER_FLASHING_ALPHA_OFF		D3DCOLOR_RGBA(255, 255, 255, 0)		// 滅の状態のα値
#define PLAYER_FLASHING_HOLD_TIME		(5)									// 点/滅の状態時間
#define PLAYER_FLASHING_RESET			(PLAYER_FLASHING_HOLD_TIME*2)		// 点滅リセット


//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct	// プレイヤー構造体
{
	D3DXVECTOR3		pos;							// プレイヤーのポジション
	D3DXVECTOR3		EffectPos;					// プレイヤーのエンジンポジション
	D3DXVECTOR3		rot;							// プレイヤーの回転量

	bool				alive;						// true:生きている false:生きていない
	bool				MainControl;					// true:操作できる false:操作できない
	bool				ReSpawnSE;					// true:再生する   false:再生しない
	bool				StartSE;						// true:再生する   false:再生しない 
	bool				FlashFlag;					// true:点滅する   false:点滅しない

	int				PatternAnim;					// アニメーションパターンナンバー
	int				CountShoot;					// 弾発射カウンター
	int				CountAnim;					// アニメーションカウンター
	int				FlashingCount;				// 点滅用カウンター

	int				Level;						// レベル
	int				EXP;							// プレイヤーの経験値
	int				Life;						// 
	int				Bomb;						//

	float			HP;							// プレイヤーの生命力

	float			Radius;						// プレイヤーの半径
	float			BaseAngle;					// プレイヤーの角度

}PLAYER;

//*****************************************************************************
// 定数定義(enum定義)
//*****************************************************************************
enum E_PLAYER_LEVEL		// プレイヤーバレット定数
{
	PLAYER_LEVEL_00,
	PLAYER_LEVEL_01,
	PLAYER_LEVEL_02,
	PLAYER_LEVEL_03,
	PLAYER_LEVEL_04,
	PLAYER_LEVEL_MAX
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(int InitType);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void DrawEngineEffect(void);
PLAYER *GetPlayer(void);


#endif