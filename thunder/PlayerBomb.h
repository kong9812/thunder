#ifndef _PLAYER_BOMB_H_
#define _PLAYER_BOMB_H_

#include "main.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �����摜
#define	TEXTURE_PLAYER_BOMB		_T("data/TEXTURE/PlayerBomb.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y
#define PLAYER_BOMB_SIZE_X		(960)		// �e�̕�(X)
#define PLAYER_BOMB_SIZE_Y		(720)		// �e�̍���(Y)
// �A�j���[�V�����p�^�[��
#define PLAYER_BOMB_PATTERN_DIVIDE_X	(8)		// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define PLAYER_BOMB_PATTERN_DIVIDE_Y	(2)		// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define PLAYER_BOMB_ANIM_PATTERN_NUM	(PLAYER_BOMB_PATTERN_DIVIDE_X*PLAYER_BOMB_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TIME_PLAYER_BOMB_ANIMATION		(4)		// �A�j���[�V�����̐؂�ւ��J�E���g
// ���
#define PLAYER_BOMB_COLOR				D3DCOLOR_RGBA(255, 255, 255, 127)	// �_�̏�Ԃ̃��l
#define PLAYER_BOMB_ATK					(10)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// �v���C���[�����\����
{
	D3DXVECTOR3		pos;			// �����̍��W

	int				CountAnim;	// �A�j���[�V�����J�E���^�[
	int				PatternAnim;	// �A�j���[�V�����p�^�[���i���o�[

	bool			use;			// true:�g�p�� false:�g�p���Ă��Ȃ�

}PLAYERBOMB;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerBomb(int InitType);
void UninitPlayerBomb(void);
void UpdatePlayerBomb(void);
void DrawPlayerBomb(void);

void SetPlayerBomb(void);
PLAYERBOMB *GetPlayerBomb(void);


#endif