#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_


//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct	// エネミー構造体
{
	D3DXVECTOR3		pos;						// エネミーのポジション
	D3DXVECTOR3		BasePos;					// エネミーの基準ポジション
	D3DXVECTOR3		rot;						// エネミーの回転量

	D3DCOLOR		Duffuse;					// 反射光(点滅用)

	bool			alive;						// true:生きている false:生きていない
	bool			movie;						// true:移動する   false:移動しない
	bool			FlashFlag;					// true:点滅する   false:点滅しない

	int				FlashingCount;				// 点滅用カウンター
	int				state;						// エネミー状態
	int				HoldTimeCount;				// 画面にいる時間のカウンター
	int				ShootCount;					// 弾発射時間のカウンター

	float			rotAngle;					// 回転
	float			HP;							// 生命力
	float			Radius;						// 半径
	float			BaseAngle;					// 角度

}ENEMY;

//enum定義
enum ENEMY_STATE
{
	ENEMY_MOVE,
	ENEMY_STOP,
	ENEMY_ESCAPE
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemyManager(int InitType);
void UninitEnemyManager(void);
void UpdateEnemyManager(float MapPos);
void DrawEnemyManager(void);


#endif
