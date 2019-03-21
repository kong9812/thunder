#include "main.h"
#include "EnemyBullet01.h"
#include "EnemyBullet02.h"
#include "EnemyBullet03.h"
#include "EnemyBulletManager.h"

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyBulletManager(int InitType)
{
	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{	// ������
		InitEnemyBullet01(FIRST_INIT);
		InitEnemyBullet02(FIRST_INIT);
		InitEnemyBullet03(FIRST_INIT);
	}

	else
	{	// �ď�����
		InitEnemyBullet01(RE_INIT);
		InitEnemyBullet02(RE_INIT);
		InitEnemyBullet03(RE_INIT);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyBulletManager(void)
{
	UninitEnemyBullet01();
	UninitEnemyBullet02();
	UninitEnemyBullet03();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyBulletManager(void)
{
	UpdateEnemyBullet01();
	UpdateEnemyBullet02();
	UpdateEnemyBullet03();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyBulletManager(void)
{
	DrawEnemyBullet01();
	DrawEnemyBullet02();
	DrawEnemyBullet03();
}

//=============================================================================
// �o���b�g��ݒu
//=============================================================================
void SetEnemyBullet(D3DXVECTOR3 EnemyPos, int BulletType)
{
	if (BulletType == ENEMY_BULLET_01)
	{
		SetEnemyBullet01(EnemyPos);
	}

	if (BulletType == ENEMY_BULLET_02)
	{
		SetEnemyBullet02(EnemyPos);
	}

	if (BulletType == ENEMY_BULLET_03)
	{
		SetEnemyBullet03(EnemyPos);
	}

}