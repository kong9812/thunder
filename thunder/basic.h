#ifndef _BASIC_H_
#define _BASIC_H_






//*****************************************************************************
// �v���g�^�C�v�錾(���_�t�H�[�}�b�g)
//*****************************************************************************
// ���_�t�H�[�}�b�g
HRESULT MakeVtx4PointData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY);

// ���_�t�H�[�}�b�g
HRESULT MakeVtxCenterData(VERTEX_2D *vtx, float SizeX, float SizeY);

// ���_�t�H�[�}�b�g
HRESULT MakeCutVtx4PointData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY, int PatternX, int PatternY, int cntPattern);

//*****************************************************************************
// �v���g�^�C�v�錾(���_���̐ݒ�)
//*****************************************************************************
// ���_���W�̐ݒ�(���_���)
void SetVtx4PointData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY);

// ���_���W�̐ݒ�(���_���)
void SetVtxCenterData(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY);

// ���_���W�̐ݒ�(��]�p)
void SetVtxRotData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float angle, float Length);

// �e�N�X�`�����W�̐ݒ�(�X�N���[���p)
void SetTextureScrollData
(VERTEX_2D *vtx, float distance);

// ���ˌ��̐ݒ�(�꒸�_)
void SetSingleDiffuseData
(VERTEX_2D *vtx, int no, D3DCOLOR color);
// ���ˌ��̐ݒ�(�S�F)
void SetAllDiffuseData
(VERTEX_2D *vtx, D3DCOLOR color);



void SetVtx4PointGaugeDate
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY, float Length);

void SetTextureNumData
(VERTEX_2D *vtx, float x);


void SetTextureAnimationData
(VERTEX_2D *vtx, int cntPattern, int PatternX, int PatternY);


#endif