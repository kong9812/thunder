#ifndef _BASIC_H_
#define _BASIC_H_






//*****************************************************************************
// プロトタイプ宣言(頂点フォーマット)
//*****************************************************************************
// 頂点フォーマット
HRESULT MakeVtx4PointData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY);

// 頂点フォーマット
HRESULT MakeVtxCenterData(VERTEX_2D *vtx, float SizeX, float SizeY);

// 頂点フォーマット
HRESULT MakeCutVtx4PointData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY, int PatternX, int PatternY, int cntPattern);

//*****************************************************************************
// プロトタイプ宣言(頂点情報の設定)
//*****************************************************************************
// 頂点座標の設定(頂点情報)
void SetVtx4PointData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY);

// 頂点座標の設定(頂点情報)
void SetVtxCenterData(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY);

// 頂点座標の設定(回転用)
void SetVtxRotData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float angle, float Length);

// テクスチャ座標の設定(スクロール用)
void SetTextureScrollData
(VERTEX_2D *vtx, float distance);

// 反射光の設定(一頂点)
void SetSingleDiffuseData
(VERTEX_2D *vtx, int no, D3DCOLOR color);
// 反射光の設定(全色)
void SetAllDiffuseData
(VERTEX_2D *vtx, D3DCOLOR color);



void SetVtx4PointGaugeDate
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY, float Length);

void SetTextureNumData
(VERTEX_2D *vtx, float x);


void SetTextureAnimationData
(VERTEX_2D *vtx, int cntPattern, int PatternX, int PatternY);


#endif