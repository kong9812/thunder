#include "main.h"
#include "basic.h"

//=============================================================================
// ���_�t�H�[�}�b�g(���_���)
// ����:���_���i�[���[�N	���WX,Y,Z	�T�C�YX,Y
//=============================================================================
HRESULT MakeVtx4PointData(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY)
{
	// ���_���W�̐ݒ�
	vtx[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vtx[1].vtx = D3DXVECTOR3(pos.x + SizeX, pos.y, pos.z);
	vtx[2].vtx = D3DXVECTOR3(pos.x, pos.y + SizeY, pos.z);
	vtx[3].vtx = D3DXVECTOR3(pos.x + SizeX, pos.y + SizeY, pos.z);

	// rhw�̐ݒ�
	vtx[0].rhw =
	vtx[1].rhw =
	vtx[2].rhw =
	vtx[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_�t�H�[�}�b�g(���S���W)
//=============================================================================
HRESULT MakeVtxCenterData(VERTEX_2D *vtx, float SizeX, float SizeY)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	vtx[0].vtx.x = 0.0f - SizeX;
	vtx[0].vtx.y = 0.0f - SizeY;
	vtx[0].vtx.z = 0.0f;

	vtx[1].vtx.x = 0.0f + SizeX;
	vtx[1].vtx.y = 0.0f - SizeY;
	vtx[1].vtx.z = 0.0f;

	vtx[2].vtx.x = 0.0f - SizeX;
	vtx[2].vtx.y = 0.0f + SizeY;
	vtx[2].vtx.z = 0.0f;

	vtx[3].vtx.x = 0.0f + SizeX;
	vtx[3].vtx.y = 0.0f + SizeY;
	vtx[3].vtx.z = 0.0f;

	// rhw�̐ݒ�
	vtx[0].rhw =
		vtx[1].rhw =
		vtx[2].rhw =
		vtx[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


//=============================================================================
// ���_�t�H�[�}�b�g(�����e�N�X�`�����_���)
// ����:���_���i�[���[�N	���WX,Y,Z	�T�C�YX,Y
//=============================================================================
HRESULT MakeCutVtx4PointData(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY, int PatternX, int PatternY, int cntPattern)
{
	// ���_���W�̐ݒ�
	vtx[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vtx[1].vtx = D3DXVECTOR3(pos.x + SizeX, pos.y, pos.z);
	vtx[2].vtx = D3DXVECTOR3(pos.x, pos.y + SizeY, pos.z);
	vtx[3].vtx = D3DXVECTOR3(pos.x + SizeX, pos.y + SizeY, pos.z);

	// rhw�̐ݒ�
	vtx[0].rhw =
	vtx[1].rhw =
	vtx[2].rhw =
	vtx[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % PatternX;
	int y = cntPattern / PatternX;
	float sizeX = 1.0f / PatternX;
	float sizeY = 1.0f / PatternY;

	vtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�(���_���)
// ����:���_���i�[���[�N	���WX,Y,Z	�T�C�YX,Y
//=============================================================================
void SetVtx4PointData(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY)
{
	// ���_���W�̐ݒ�
	vtx[0].vtx.x = pos.x;
	vtx[0].vtx.y = pos.y;
	vtx[0].vtx.z = 0.0f;

	vtx[1].vtx.x = pos.x + SizeX;
	vtx[1].vtx.y = pos.y;
	vtx[1].vtx.z = 0.0f;

	vtx[2].vtx.x = pos.x;
	vtx[2].vtx.y = pos.y + SizeY;
	vtx[2].vtx.z = 0.0f;

	vtx[3].vtx.x = pos.x + SizeX;
	vtx[3].vtx.y = pos.y + SizeY;
	vtx[3].vtx.z = 0.0f;

}

//=============================================================================
// ���_���W�̐ݒ�(���S���W)
//=============================================================================
void SetVtxCenterData(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	vtx[0].vtx.x = pos.x - SizeX;
	vtx[0].vtx.y = pos.y - SizeY;
	vtx[0].vtx.z = 0.0f;

	vtx[1].vtx.x = pos.x + SizeX;
	vtx[1].vtx.y = pos.y - SizeY;
	vtx[1].vtx.z = 0.0f;

	vtx[2].vtx.x = pos.x - SizeX;
	vtx[2].vtx.y = pos.y + SizeY;
	vtx[2].vtx.z = 0.0f;

	vtx[3].vtx.x = pos.x + SizeX;
	vtx[3].vtx.y = pos.y + SizeY;
	vtx[3].vtx.z = 0.0f;

}


//=============================================================================
// ���_���W�̐ݒ�(��])
//=============================================================================
void SetVtxRotData(VERTEX_2D *vtx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float angle,float Length)
{
	// ���_���W�̐ݒ�
	vtx[0].vtx.x = pos.x - cosf(angle + rot.z) * Length;
	vtx[0].vtx.y = pos.y - sinf(angle + rot.z) * Length;
	vtx[0].vtx.z = 0.0f;						 

	vtx[1].vtx.x = pos.x + cosf(angle - rot.z) * Length;
	vtx[1].vtx.y = pos.y - sinf(angle - rot.z) * Length;
	vtx[1].vtx.z = 0.0f;						 
												 
	vtx[2].vtx.x = pos.x - cosf(angle - rot.z) * Length;
	vtx[2].vtx.y = pos.y + sinf(angle - rot.z) * Length;
	vtx[2].vtx.z = 0.0f;						 
												 
	vtx[3].vtx.x = pos.x + cosf(angle + rot.z) * Length;
	vtx[3].vtx.y = pos.y + sinf(angle + rot.z) * Length;
	vtx[3].vtx.z = 0.0f;
}

//=============================================================================
// ���_���W�̐ݒ�(�Q�[�W�p)
//=============================================================================
void SetVtx4PointGaugeDate(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY, float Length)
{
	// ���_���W�̐ݒ�
	vtx[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vtx[1].vtx = D3DXVECTOR3(pos.x + SizeX * Length, pos.y, pos.z);
	vtx[2].vtx = D3DXVECTOR3(pos.x, pos.y + SizeY, pos.z);
	vtx[3].vtx = D3DXVECTOR3(pos.x + SizeX * Length, pos.y + SizeY, pos.z);
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�(�����X�N���[���p)
//=============================================================================
void SetTextureNumData(VERTEX_2D *vtx, float x)
{
	// �e�N�X�`�����W�̐ݒ�
	vtx[0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
	vtx[1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
	vtx[2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
	vtx[3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�(�w�i�X�N���[���p)
//=============================================================================
void SetTextureScrollData(VERTEX_2D *vtx, float distance)
{
	// �e�N�X�`�����W�̐ݒ�
	vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + distance);
	vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + distance);
	vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + distance);
	vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + distance);
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�(�A�j���[�V����)
//=============================================================================
void SetTextureAnimationData(VERTEX_2D *vtx, int cntPattern, int PatternX, int PatternY)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % PatternX;
	int y = cntPattern / PatternX;
	float sizeX = 1.0f / PatternX;
	float sizeY = 1.0f / PatternY;

	vtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���ˌ��̐ݒ�(�꒸�_����)
//=============================================================================
void SetSingleDiffuseData(VERTEX_2D *vtx, int no, D3DCOLOR color)
{
	// ���ˌ��̐ݒ�
	vtx[no].diffuse = color;
}

//=============================================================================
// ���ˌ��̐ݒ�(�S�F)
//=============================================================================
void SetAllDiffuseData(VERTEX_2D *vtx, D3DCOLOR color)
{
	// ���ˌ��̐ݒ�
	vtx[0].diffuse = color;
	vtx[1].diffuse = color;
	vtx[2].diffuse = color;
	vtx[3].diffuse = color;
}
