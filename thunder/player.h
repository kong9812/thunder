#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// ���@�摜
#define	TEXTURE_PLAYER					_T("data/TEXTURE/player1.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y		
#define PLAYER_SIZE_X					(80)	// �v���C���[�̕�(X)
#define PLAYER_SIZE_Y					(80)	// �v���C���[�̍���(Y)

// �G���W���G�t�F�N�g
#define	TEXTURE_ENGINE_EFFECT			_T("data/TEXTURE/ENGINE_EFFECT.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y
#define ENGINE_EFFECT_SIZE_X			(30)	// �v���C���[�̕�(X)
#define ENGINE_EFFECT_SIZE_Y			(30)	// �v���C���[�̍���(Y)
// �A�j���[�V�����p�^�[��
#define ENGINE_EFFECT_PATTERN_DIVIDE_X	(5)		// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define ENGINE_EFFECT_PATTERN_DIVIDE_Y	(2)		// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ENGINE_EFFECT_ANIM_PATTERN_NUM	(ENGINE_EFFECT_PATTERN_DIVIDE_X*ENGINE_EFFECT_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TIME_ENGINE_EFFECT_ANIMATION	(4)		// �A�j���[�V�����̐؂�ւ��J�E���g

// �v���C���[���
#define PLAYER_HP_MAX					(100)
#define PLAYER_NORMAL_SPEED				(10)
#define PLAYER_SHIFT_SPEED				(5)
#define PLAYER_SPAWN_POS				(D3DXVECTOR3(300.0f, 1000.0f, 0.0f))
#define PLAYER_START_POS_Y				(SCREEN_HEIGHT - PLAYER_SIZE_Y * HALF)				
#define PLAYER_LEVEL_UP_EXP				(10)

// �_�ŗp
#define PLAYER_FLASHING_ALPHA_ON		D3DCOLOR_RGBA(255, 255, 255, 255)	// �_�̏�Ԃ̃��l
#define PLAYER_FLASHING_ALPHA_OFF		D3DCOLOR_RGBA(255, 255, 255, 0)		// �ł̏�Ԃ̃��l
#define PLAYER_FLASHING_HOLD_TIME		(5)									// �_/�ł̏�Ԏ���
#define PLAYER_FLASHING_RESET			(PLAYER_FLASHING_HOLD_TIME*2)		// �_�Ń��Z�b�g


//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// �v���C���[�\����
{
	D3DXVECTOR3		pos;							// �v���C���[�̃|�W�V����
	D3DXVECTOR3		EffectPos;					// �v���C���[�̃G���W���|�W�V����
	D3DXVECTOR3		rot;							// �v���C���[�̉�]��

	bool				alive;						// true:�����Ă��� false:�����Ă��Ȃ�
	bool				MainControl;					// true:����ł��� false:����ł��Ȃ�
	bool				ReSpawnSE;					// true:�Đ�����   false:�Đ����Ȃ�
	bool				StartSE;						// true:�Đ�����   false:�Đ����Ȃ� 
	bool				FlashFlag;					// true:�_�ł���   false:�_�ł��Ȃ�

	int				PatternAnim;					// �A�j���[�V�����p�^�[���i���o�[
	int				CountShoot;					// �e���˃J�E���^�[
	int				CountAnim;					// �A�j���[�V�����J�E���^�[
	int				FlashingCount;				// �_�ŗp�J�E���^�[

	int				Level;						// ���x��
	int				EXP;							// �v���C���[�̌o���l
	int				Life;						// 
	int				Bomb;						//

	float			HP;							// �v���C���[�̐�����

	float			Radius;						// �v���C���[�̔��a
	float			BaseAngle;					// �v���C���[�̊p�x

}PLAYER;

//*****************************************************************************
// �萔��`(enum��`)
//*****************************************************************************
enum E_PLAYER_LEVEL		// �v���C���[�o���b�g�萔
{
	PLAYER_LEVEL_00,
	PLAYER_LEVEL_01,
	PLAYER_LEVEL_02,
	PLAYER_LEVEL_03,
	PLAYER_LEVEL_04,
	PLAYER_LEVEL_MAX
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(int InitType);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void DrawEngineEffect(void);
PLAYER *GetPlayer(void);


#endif