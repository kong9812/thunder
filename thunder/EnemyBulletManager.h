#ifndef _ENEMY_BULLET_MANAGER_H_
#define _ENEMY_BULLET_MANAGER_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// ���
#define PLAYER_BULLET_SHOOT_TIME		(10)		// ���ˊԊu

//*****************************************************************************
// �萔��`(enum��`)
//*****************************************************************************
enum E_ENEMYBULLET		// �G�l�~�[�o���b�g�萔
{
	ENEMY_BULLET_01,
	ENEMY_BULLET_02,
	ENEMY_BULLET_03,
	ENEMY_BULLET_04
};

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// �v���C���[�o���b�g�\����
{
	D3DXVECTOR3		pos;			// �o���b�g�̍��W

	int				type;			// �o���b�g�^

	float			ShotAngle;		// ���ˊp�x

	bool			use;			// true:�g�p�� false:�g�p���Ă��Ȃ�

}ENEMYBULLET;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemyBulletManager(int InitType);
void UninitEnemyBulletManager(void);
void UpdateEnemyBulletManager(void);
void DrawEnemyBulletManager(void);

void SetEnemyBullet(D3DXVECTOR3 EnemyPos, int BulletType);
#endif