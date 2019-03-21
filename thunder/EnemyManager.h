#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_


//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// �G�l�~�[�\����
{
	D3DXVECTOR3		pos;						// �G�l�~�[�̃|�W�V����
	D3DXVECTOR3		BasePos;					// �G�l�~�[�̊�|�W�V����
	D3DXVECTOR3		rot;						// �G�l�~�[�̉�]��

	D3DCOLOR		Duffuse;					// ���ˌ�(�_�ŗp)

	bool			alive;						// true:�����Ă��� false:�����Ă��Ȃ�
	bool			movie;						// true:�ړ�����   false:�ړ����Ȃ�
	bool			FlashFlag;					// true:�_�ł���   false:�_�ł��Ȃ�

	int				FlashingCount;				// �_�ŗp�J�E���^�[
	int				state;						// �G�l�~�[���
	int				HoldTimeCount;				// ��ʂɂ��鎞�Ԃ̃J�E���^�[
	int				ShootCount;					// �e���ˎ��Ԃ̃J�E���^�[

	float			rotAngle;					// ��]
	float			HP;							// ������
	float			Radius;						// ���a
	float			BaseAngle;					// �p�x

}ENEMY;

//enum��`
enum ENEMY_STATE
{
	ENEMY_MOVE,
	ENEMY_STOP,
	ENEMY_ESCAPE
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemyManager(int InitType);
void UninitEnemyManager(void);
void UpdateEnemyManager(float MapPos);
void DrawEnemyManager(void);


#endif
