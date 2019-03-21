#include "main.h"
#include "basic.h"
#include "input.h"
#include "sound.h"
#include "TitleBackground.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// 描画処理
void DrawTitleBG(void);				// 背景の描画処理
void DrawTitleName(void);			// 名前の描画処理
void DrawTitleCopyRight(void);		// 著作権宣言の描画処理
void DrawTitleDoor(void);			// ドアの描画処理

// 更新処理
void TitleScroll(void);				// 背景スクロール処理
void UpdateDoorRotation(void);		// ドアの回転処理

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTitle = NULL;				// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTextureTitleWall = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTextureTitleName = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTextureTitleCopyRight = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTextureTitleDoor01 = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTextureTitleDoor02 = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_D3DTextureTitleDoor03 = NULL;			// テクスチャへのポインタ

VERTEX_2D				g_TitleVertexWk[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_TitleWallVertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_TitleNameVertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_TitleCopyRightVertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
VERTEX_2D				g_TitleDoor01VertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_TitleDoor02VertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_TitleDoor03_00VertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
VERTEX_2D				g_TitleDoor03_01VertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
VERTEX_2D				g_TitleDoor03_02VertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
VERTEX_2D				g_TitleDoor03_03VertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

float					g_TitleScrollDistance;					// タイトル距離				

D3DXVECTOR3				g_Door01Pos;							// 座標

D3DXVECTOR3				g_Door03_00Pos;							// 座標
D3DXVECTOR3				g_Door03_01Pos;							// 座標
D3DXVECTOR3				g_Door03_02Pos;							// 座標
D3DXVECTOR3				g_Door03_03Pos;							// 座標

D3DXVECTOR3				g_DoorMovie;							// 移動量
float					g_DoorAngle;							// 角度
float					g_DoorLength;							// 中心から頂点までの距離
bool					g_DoorFlag;								// true:開く false:閉じる
bool					g_DoorDrawFlag;							// true:描画 false:描画しない

static int				g_Stage;								// ステージ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitleBackground(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_TITLE,								// ファイルの名前
		&g_D3DTextureTitle);						// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_TITLE_WALL,							// ファイルの名前
		&g_D3DTextureTitleWall);					// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_TITLE_NAME,							// ファイルの名前
		&g_D3DTextureTitleName);						// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_TITLE_COPYRIGHT,						// ファイルの名前
		&g_D3DTextureTitleCopyRight);				// 読み込むメモリー
	
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_DOOR_01,								// ファイルの名前
		&g_D3DTextureTitleDoor01);					// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_DOOR_02,								// ファイルの名前
		&g_D3DTextureTitleDoor02);					// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_DOOR_03,								// ファイルの名前
		&g_D3DTextureTitleDoor03);					// 読み込むメモリー
	}

	g_TitleScrollDistance = 0.0f;											// 初期距離

	g_Door03_00Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// 初期位置
	g_Door03_01Pos = D3DXVECTOR3(SCREEN_CENTER_X, 0.0f, 0.0f);				// 初期位置
	g_Door03_02Pos = D3DXVECTOR3(0.0f, SCREEN_CENTER_Y, 0.0f);				// 初期位置
	g_Door03_03Pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);	// 初期位置

	g_Door01Pos		= D3DXVECTOR3(											// 初期位置
					DOOR_POS_X + DOOR_SIZE_X / HALF,
					DOOR_POS_Y + DOOR_SIZE_Y / HALF, DOOR_POS_Z);
	g_DoorMovie		= D3DXVECTOR3(0.0f, 0.0f, DOOR_MOVIE_Z);				// 初期移動量
	g_DoorAngle		= atan2f(DOOR_SIZE_Y, DOOR_SIZE_X);						// 角度を初期化
	g_DoorDrawFlag  = true;													// true:描画
	g_DoorFlag		= false;												// false:閉じる
	g_DoorLength	= D3DXVec2Length(&D3DXVECTOR2(							// 中心から頂点までの距離
					DOOR_SIZE_Y / HALF,
					DOOR_SIZE_X / HALF));

	g_Stage = STAGE_START_GAME;

	// 頂点フォーマット(背景)
	MakeVtx4PointData(g_TitleVertexWk,									// 頂点情報格納ワーク
	D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, TITLE_POS_Z),					// 座標X,Y,Z
	TITLE_SIZE_X, TITLE_SIZE_Y);											// サイズX,Y

	// 頂点フォーマット(壁)
	MakeVtx4PointData(g_TitleWallVertexWk,								// 頂点情報格納ワーク
	D3DXVECTOR3(TITLE_WALL_POS_X, TITLE_WALL_POS_Y, TITLE_WALL_POS_Z),	// 座標X,Y,Z
	TITLE_WALL_SIZE_X, TITLE_WALL_SIZE_Y);								// サイズX,Y


	// 頂点フォーマット(名前)
	MakeVtx4PointData(g_TitleNameVertexWk,								// 頂点情報格納ワーク
	D3DXVECTOR3(TITLE_NAME_POS_X, TITLE_NAME_POS_Y, TITLE_NAME_POS_Z),	// 座標X,Y,Z
	TITLE_NAME_SIZE_X, TITLE_NAME_SIZE_Y);								// サイズX,Y

	// 頂点フォーマット(著作権宣言)
	MakeVtx4PointData(g_TitleCopyRightVertexWk,											// 頂点情報格納ワーク
	D3DXVECTOR3(TITLE_COPYRIGHT_POS_X, TITLE_COPYRIGHT_POS_Y, TITLE_COPYRIGHT_POS_Z),	// 座標X,Y,Z
	TITLE_COPYRIGHT_SIZE_X, TITLE_COPYRIGHT_SIZE_Y);										// サイズX,Y

	// 頂点フォーマット(ドア/門)
	// 門枠
	MakeVtx4PointData(g_TitleDoor01VertexWk,			// 頂点情報格納ワーク
	D3DXVECTOR3(DOOR_POS_X, DOOR_POS_Y, DOOR_POS_Z),	// 座標X,Y,Z
	DOOR_SIZE_X, DOOR_SIZE_Y);							// サイズX,Y
	// 門
	MakeVtx4PointData(g_TitleDoor02VertexWk,			// 頂点情報格納ワーク
	D3DXVECTOR3(DOOR_POS_X, DOOR_POS_Y, DOOR_POS_Z),	// 座標X,Y,Z
	DOOR_SIZE_X, DOOR_SIZE_Y);							// サイズX,Y
	
	// 門03-00
	MakeCutVtx4PointData(g_TitleDoor03_00VertexWk,		// 頂点情報格納ワーク
	g_Door03_00Pos,										// 座標X,Y,Z
	SCREEN_CENTER_X, SCREEN_CENTER_Y,					// サイズX,Y
	DOOR_CUT_PATTERN_X, DOOR_CUT_PATTERN_Y,				// 分割の座標(X,Y)
	0);													// 分割のサイズ(X,Y)
	// 門03-01
	MakeCutVtx4PointData(g_TitleDoor03_01VertexWk,		// 頂点情報格納ワーク
	g_Door03_01Pos,										// 座標X,Y,Z
	SCREEN_CENTER_X, SCREEN_CENTER_Y, 					// サイズX,Y
	DOOR_CUT_PATTERN_X, DOOR_CUT_PATTERN_Y,				// 分割の座標(X,Y)
	1);													// 分割のサイズ(X,Y)
	// 門03-02
	MakeCutVtx4PointData(g_TitleDoor03_02VertexWk,		// 頂点情報格納ワーク
	g_Door03_02Pos,							 			// 座標X,Y,Z
	SCREEN_CENTER_X, SCREEN_CENTER_Y,					// サイズX,Y
	DOOR_CUT_PATTERN_X, DOOR_CUT_PATTERN_Y,				// 分割の座標(X,Y)
	2);													// 分割のサイズ(X,Y)
	// 門03-03
	MakeCutVtx4PointData(g_TitleDoor03_03VertexWk,		// 頂点情報格納ワーク
	g_Door03_03Pos,										// 座標X,Y,Z
	SCREEN_CENTER_X, SCREEN_CENTER_Y,					// サイズX,Y
	DOOR_CUT_PATTERN_X, DOOR_CUT_PATTERN_Y,				// 分割の座標(X,Y)
	3);													// 分割のサイズ(X,Y)


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitleBackground(void)
{
	if(g_D3DTextureTitle != NULL)
	{// テクスチャの開放
		g_D3DTextureTitle->Release();
		g_D3DTextureTitle = NULL;
	}

	if (g_D3DTextureTitleWall != NULL)
	{// テクスチャの開放
		g_D3DTextureTitleWall->Release();
		g_D3DTextureTitleWall = NULL;
	}


	if (g_D3DTextureTitleName != NULL)
	{// テクスチャの開放
		g_D3DTextureTitleName->Release();
		g_D3DTextureTitleName = NULL;
	}

	if (g_D3DTextureTitleCopyRight != NULL)
	{// テクスチャの開放
		g_D3DTextureTitleCopyRight->Release();
		g_D3DTextureTitleCopyRight = NULL;
	}

	if (g_D3DTextureTitleDoor01 != NULL)
	{// テクスチャの開放
		g_D3DTextureTitleDoor01->Release();
		g_D3DTextureTitleDoor01 = NULL;
	}

	if (g_D3DTextureTitleDoor02 != NULL)
	{// テクスチャの開放
		g_D3DTextureTitleDoor02->Release();
		g_D3DTextureTitleDoor02 = NULL;
	}

	if (g_D3DTextureTitleDoor03 != NULL)
	{// テクスチャの開放	  
		g_D3DTextureTitleDoor03->Release();
		g_D3DTextureTitleDoor03 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitleBackground(void)
{
	TitleScroll();
	UpdateDoorRotation();
}

//=============================================================================
// ドアの回転処理とドアの開く処理
//=============================================================================
void UpdateDoorRotation(void)
{
	if (g_DoorFlag == true)
	{
		g_DoorMovie.z += DOOR_SCROLL_SPEED;

		if (g_DoorMovie.z >= DOOR_SCROLL_MAX)
		{
			g_DoorDrawFlag = false;

			g_Door03_00Pos.x -= DOOR_MOVE_SPEED;
			g_Door03_00Pos.y -= DOOR_MOVE_SPEED;
			g_Door03_01Pos.x += DOOR_MOVE_SPEED;
			g_Door03_01Pos.y -= DOOR_MOVE_SPEED;
			g_Door03_02Pos.x -= DOOR_MOVE_SPEED;
			g_Door03_02Pos.y += DOOR_MOVE_SPEED;
			g_Door03_03Pos.x += DOOR_MOVE_SPEED;
			g_Door03_03Pos.y += DOOR_MOVE_SPEED;

			if (g_Door03_00Pos.x <= 0.0f - SCREEN_CENTER_X)
			{
				g_DoorFlag = false;
				g_DoorMovie.z = DOOR_MOVIE_Z;
				SetStage(g_Stage);
				g_DoorDrawFlag = true;
			}
		}
	}
}

//=============================================================================
// 背景スクロール処理
//=============================================================================
void TitleScroll(void)
{
	g_TitleScrollDistance -= TITLE_SCROLL_SPEED;

	if (g_TitleScrollDistance <= FLT_MIN)
	{
		g_TitleScrollDistance -= FLT_MIN;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitleBackground(bool DrawFlag)
{

	DrawTitleBG();				// 描画処理(背景)
	DrawTitleDoor();			// 描画処理(ドア)

	if (DrawFlag == true)
	{
		DrawTitleName();		// 描画処理(名前)
		DrawTitleCopyRight();	// 描画処理(著作権宣言)
	}
}

//=============================================================================
// 描画処理(背景)
//=============================================================================
void DrawTitleBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTitle);

	// テクスチャ座標の設定(背景スクロール用)
	SetTextureScrollData(g_TitleVertexWk, g_TitleScrollDistance);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleVertexWk, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTitleWall);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleWallVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(名前)
//=============================================================================
void DrawTitleName(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTitleName);

	// 反射光の設定(一頂点ずつ)
	SetSingleDiffuseData(g_TitleNameVertexWk, 0, TITLE_NAME_COLOR_BLACK);	// 左上
	SetSingleDiffuseData(g_TitleNameVertexWk, 1, TITLE_NAME_COLOR_RED);		// 右上
	SetSingleDiffuseData(g_TitleNameVertexWk, 2, TITLE_NAME_COLOR_RED);		// 左下
	SetSingleDiffuseData(g_TitleNameVertexWk, 3, TITLE_NAME_COLOR_BLACK);	// 右下

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleNameVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(著作権宣言)
//=============================================================================
void DrawTitleCopyRight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTitleCopyRight);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleCopyRightVertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(ドア/門)
//=============================================================================
void DrawTitleDoor(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_D3DTextureTitleDoor03);
	
	// 頂点座標の設定(頂点情報)
	SetVtx4PointData(g_TitleDoor03_00VertexWk, g_Door03_00Pos, SCREEN_CENTER_X, SCREEN_CENTER_Y);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleDoor03_00VertexWk, sizeof(VERTEX_2D));

	// 頂点座標の設定(頂点情報)
	SetVtx4PointData(g_TitleDoor03_01VertexWk, g_Door03_01Pos, SCREEN_CENTER_X, SCREEN_CENTER_Y);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleDoor03_01VertexWk, sizeof(VERTEX_2D));

	// 頂点座標の設定(頂点情報)
	SetVtx4PointData(g_TitleDoor03_02VertexWk, g_Door03_02Pos, SCREEN_CENTER_X, SCREEN_CENTER_Y);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleDoor03_02VertexWk, sizeof(VERTEX_2D));

	// 頂点座標の設定(頂点情報)
	SetVtx4PointData(g_TitleDoor03_03VertexWk, g_Door03_03Pos, SCREEN_CENTER_X, SCREEN_CENTER_Y);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleDoor03_03VertexWk, sizeof(VERTEX_2D));

	if (g_DoorDrawFlag == true)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_D3DTextureTitleDoor01);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleDoor01VertexWk, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_D3DTextureTitleDoor02);

		// 頂点座標の設定(頂点情報)
		SetVtxRotData(g_TitleDoor02VertexWk, g_Door01Pos, g_DoorMovie, g_DoorAngle, g_DoorLength);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TitleDoor02VertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ドアを開ける処理
//=============================================================================
void SetDoorFlag(bool Flag)
{
	g_DoorFlag = Flag;
}

//=============================================================================
// ステージ遷移
//=============================================================================
void SetTitleSelectStage(int STAGE)
{
	g_Stage = STAGE;
}