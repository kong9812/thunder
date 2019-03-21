#include "main.h"
#include "basic.h"
#include "EffectManager.h"
#include "TutorialPlayer.h"
#include "TutorialEnemy.h"
#include "TutorialUI.h"
#include "TutorialBackground.h"
#include "PlayerBullet03.h"
#include "TutorialEnemy.h"
#include "TutorialCollider.h"
#include "TutorialPlayerBullet.h"
#include "TutorialPlayerBomb.h"
#include "TutorialManager.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void DrawTutoria(void);				// �R���g���[������

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTextureTutorial = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_TutorialVertexWk[NUM_VERTEX];		// ���_���i�[���[�N

float g_fTutorialMapScrollPos;		// �`���g���A���}�b�v�̋���

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTutorialManager(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// ������
		InitEffectManager(FIRST_INIT);
		InitTutorialCollider(FIRST_INIT);
		InitTutorialEnemy(FIRST_INIT);
		InitTutorialPlayerBomb(FIRST_INIT);
		InitTutorialPlayerBullet(FIRST_INIT);
		InitTutorialBackground(FIRST_INIT);
		InitTutorialPlayer(FIRST_INIT);
		InitTutorialUI(FIRST_INIT);

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_CONTROL,						// �t�@�C���̖��O
		&g_D3DTextureTutorial);				// �ǂݍ��ރ������[
	}

	else
	{
		// �ď�����
		InitEffectManager(RE_INIT);
		InitTutorialCollider(RE_INIT);
		InitTutorialEnemy(RE_INIT);
		InitTutorialPlayerBomb(RE_INIT);
		InitTutorialPlayerBullet(RE_INIT);
		InitTutorialBackground(RE_INIT);
		InitTutorialPlayer(RE_INIT);
		InitTutorialUI(RE_INIT);
	}

	g_fTutorialMapScrollPos = 0.0f;

	// ���_�t�H�[�}�b�g(�R���g���[������)
	MakeVtx4PointData(g_TutorialVertexWk,	// ���_���i�[���[�N
	D3DXVECTOR3(600, 30, 0),					// ���WX,Y,Z
	CONTROL_SIZE_X, CONTROL_SIZE_Y);			// �T�C�YX,Y

	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void UninitTutorialManager(void)
{
	UninitEffectManager();
	UninitTutorialCollider();
	UninitTutorialEnemy();
	UninitTutorialPlayerBomb();
	UninitTutorialPlayerBullet();
	UninitTutorialBackground();
	UninitTutorialPlayer();
	UninitTutorialUI();

	if (g_D3DTextureTutorial != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureTutorial->Release();
		g_D3DTextureTutorial = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorialManager(void)
{
	UpdateTutorialCollider();
	UpdateEffectManager();
	UpdateTutorialPlayerBomb();
	UpdateTutorialPlayerBullet();
	UpdateTutorialBackground();
	UpdateTutorialPlayer();
	UpdateTutorialEnemy(g_fTutorialMapScrollPos);
	UpdateTutorialUI();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorialManager(void)
{
	DrawTutorialCollider();
	DrawTutorialBackground();
	DrawTutorialPlayerBomb();
	DrawTutorialEngineEffect();
	DrawTutorialPlayerBullet();
	DrawTutorialEnemy();
	DrawTutorialPlayer();
	DrawEffectManager();
	DrawTutorialUI();
	DrawTutoria();
}

//=============================================================================
// �R���g���[�������̕`�揈��
//=============================================================================
void DrawTutoria(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_D3DTextureTutorial);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_TutorialVertexWk, sizeof(VERTEX_2D));

}


//=============================================================================
// �}�b�v�̈ʒu��ݒ�
//=============================================================================
void SetTutorialMapScrollPos(float MapPos)
{
	g_fTutorialMapScrollPos = MapPos;
}

