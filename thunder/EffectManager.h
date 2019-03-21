#ifndef _EFFECT_MANAGER_H_
#define _EFFECT_MANAGER_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// EFFECT_01�摜
#define	TEXTURE_EFFECT_01		_T("data/TEXTURE/HitEffect.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
// �T�C�Y
#define EFFECT_01_SIZE_X			(50)	// �e�̕�(X)
#define EFFECT_01_SIZE_Y			(50)	// �e�̍���(Y)
// �A�j���[�V�����p�^�[��
#define EFFECT_01_PATTERN_DIVIDE_X	(8)		// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define EFFECT_01_PATTERN_DIVIDE_Y	(2)		// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define EFFECT_01_ANIM_PATTERN_NUM	(EFFECT_01_PATTERN_DIVIDE_X*EFFECT_01_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TIME_EFFECT_01_ANIMATION	(2)		// �A�j���[�V�����̐؂�ւ��J�E���g
// ���	
#define EFFECT_01_MAX				(50)	// ��ʏ㓯���ɕ`��ł���e�̐�

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct	// �G�t�F�N�g�\����
{
	D3DXVECTOR3		pos;			// �G�t�F�N�g�̍��W

	int				CountAnim;		// �A�j���[�V�����J�E���^�[
	int				PatternAnim;	// �A�j���[�V�����p�^�[���i���o�[

	bool			use;			// true:�g�p�� false:�g�p���Ă��Ȃ�

}EFFECT;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffectManager(int InitType);
void UninitEffectManager(void);
void UpdateEffectManager(void);
void DrawEffectManager(void);

void SetEffect01(D3DXVECTOR3 pos);

EFFECT *GetEffect01(int no);
#endif