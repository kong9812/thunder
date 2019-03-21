#include "main.h"
#include "basic.h"
#include "input.h"
#include "sound.h"
#include "UI.h"
#include "EffectManager.h"
#include "PlayerBulletManager.h"
#include "PlayerBomb.h"
#include "player.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void PlayerKeyboardControl(void);	// �L�[�{�[�h����
void PlayerEngineEffect(void);		// �G���W���G�t�F�N�g
void PlayerInScreen(void);			// �X�N���[���ɓ���A�j���V����

void PlayerPause(void);				// �|�[�Y
void PlayerShoot(void);				// �e����
void PlayerBomb(void);				// ����

void SetPlayerFlashing(void);		// �_�ŏ���
void SetPlayerFlashingOn(void);		// �_�ŏ���(�_)

void CheckPlayerHP(void);			
void RespawnPlayer(void);

void PlayerLeverUp(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_D3DTexturePlayer = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_D3DTextureEngineEffect = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECTSOUNDBUFFER8	g_pPlayerRespawnSE;					// SE�p�o�b�t�@
LPDIRECTSOUNDBUFFER8	g_pPlayerStartSE;					// SE�p�o�b�t�@

VERTEX_2D				g_PlayerVertexWk[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_EngineEffectVertexWk[NUM_VERTEX];	// ���_���i�[���[�N

PLAYER					PlayerWk;

//=============================================================================
// ����������
//=============================================================================
//=============================================================================
HRESULT InitPlayer(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PLAYER,							// �t�@�C���̖��O
		&g_D3DTexturePlayer);					// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_ENGINE_EFFECT,					// �t�@�C���̖��O
		&g_D3DTextureEngineEffect);				// �ǂݍ��ރ������[

		// SE���[�h
		g_pPlayerRespawnSE = LoadSound(SE_PLAYER_RESPAWN);
		g_pPlayerStartSE = LoadSound(SE_PLAYER_START);
	}

	player->pos = PLAYER_SPAWN_POS;
	player->alive = true;
	player->StartSE = true;
	player->MainControl = false;
	player->ReSpawnSE = true;
	player->FlashFlag = false;
	player->HP = PLAYER_HP_MAX;
	player->EXP = 0;
	player->Level = PLAYER_LEVEL_01;
	player->Life = 3;
	player->Bomb = 3;
	player->PatternAnim = 0;
	player->FlashingCount = 0;
	player->CountShoot = 0;
	player->CountAnim = 0;
	player->EffectPos = D3DXVECTOR3(player->pos.x + PLAYER_SIZE_X / 3, player->pos.y + PLAYER_SIZE_Y / HALF, 0.0f);

	// ���_�t�H�[�}�b�g(�`���g���A���v���C���[)
	MakeVtx4PointData(g_PlayerVertexWk,			// ���_���i�[���[�N
	player->pos,								// ���WX,Y,Z
	PLAYER_SIZE_X, PLAYER_SIZE_Y);				// �T�C�YX,Y

	// ���_�t�H�[�}�b�g(�G���W���G�t�F�N�g)
	MakeVtx4PointData(g_EngineEffectVertexWk,	// ���_���i�[���[�N
	player->EffectPos,							// ���WX,Y,Z
	ENGINE_EFFECT_SIZE_X, ENGINE_EFFECT_SIZE_Y);// �T�C�YX,Y

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	if (g_D3DTexturePlayer != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTexturePlayer->Release();
		g_D3DTexturePlayer = NULL;
	}

	if (g_D3DTextureEngineEffect != NULL)
	{// �e�N�X�`���̊J��
		g_D3DTextureEngineEffect->Release();
		g_D3DTextureEngineEffect = NULL;
	}

	if (g_pPlayerRespawnSE != NULL)
	{
		g_pPlayerRespawnSE->Release();
		g_pPlayerRespawnSE = NULL;
	}

	if (g_pPlayerStartSE != NULL)
	{
		g_pPlayerStartSE->Release();
		g_pPlayerStartSE = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER *player = GetPlayer();

	if (player->alive == true)
	{
		if (player->MainControl == true)
		{
			PlayerKeyboardControl();
			PlayerEngineEffect();
			PlayerPause();
			PlayerShoot();
			PlayerBomb();
		}

		if ((player->pos.y >= PLAYER_START_POS_Y) && (player->MainControl == false))
		{
			// SE�Đ�
			if ((IsPlaying(g_pPlayerRespawnSE) == false) &&
				player->ReSpawnSE == true)
			{
				g_pPlayerRespawnSE->SetCurrentPosition(0);
				PlaySound(g_pPlayerRespawnSE, E_DS8_FLAG_NONE);
				player->ReSpawnSE = false;
			}

			// SE�Đ�
			if ((IsPlaying(g_pPlayerRespawnSE) == false) &&
				player->StartSE == true)
			{
				g_pPlayerStartSE->SetCurrentPosition(0);
				PlaySound(g_pPlayerStartSE, E_DS8_FLAG_NONE);
				player->StartSE = false;
			}

			PlayerInScreen();
			player->MainControl = false;
		}

		else if ((player->pos.y < SCREEN_HEIGHT) && (player->MainControl == false))
		{
			SetPlayerFlashingOn();
			player->FlashFlag = false;
			player->MainControl = true;
			player->ReSpawnSE = true;
			player->StartSE = true;
		}

		SetPlayerFlashing();
		CheckPlayerHP();
		PlayerLeverUp();
	}

	else if (player->alive == false)
	{
		RespawnPlayer();
	}
}
//=============================================================================
// �L�[�{�[�h����
//=============================================================================
void PlayerKeyboardControl()
{
	PLAYER *player = GetPlayer();

	if (GetKeyboardPress(DIK_W))	 // ��
	{
		if (GetKeyboardPress(DIK_A))	 // ����
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // ����
			{
				player->pos.y -= cosf(45)*PLAYER_SHIFT_SPEED;
				player->pos.x -= cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				player->pos.y -= cosf(45)*PLAYER_NORMAL_SPEED;
				player->pos.x -= cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else	 if (GetKeyboardPress(DIK_D)) // �E��
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // ����
			{
				player->pos.y -= cosf(45)*PLAYER_SHIFT_SPEED;
				player->pos.x += cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				player->pos.y -= cosf(45)*PLAYER_NORMAL_SPEED;
				player->pos.x += cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // ����
			{
				player->pos.y -= PLAYER_SHIFT_SPEED;
			}
			else
			{
				player->pos.y -= PLAYER_NORMAL_SPEED;
			}
		}

	}

	else if (GetKeyboardPress(DIK_S)) // ��
	{
		if (GetKeyboardPress(DIK_A)) // ����
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // ����
			{
				player->pos.y += cosf(45)*PLAYER_SHIFT_SPEED;
				player->pos.x -= cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				player->pos.y += cosf(45)*PLAYER_NORMAL_SPEED;
				player->pos.x -= cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else if (GetKeyboardPress(DIK_D)) // �E��
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // ����
			{
				player->pos.y += cosf(45)*PLAYER_SHIFT_SPEED;
				player->pos.x += cosf(45)*PLAYER_SHIFT_SPEED;
			}
			else
			{
				player->pos.y += cosf(45)*PLAYER_NORMAL_SPEED;
				player->pos.x += cosf(45)*PLAYER_NORMAL_SPEED;
			}
		}

		else
		{
			if (GetKeyboardPress(DIK_LSHIFT)) // ����
			{
				player->pos.y += PLAYER_SHIFT_SPEED;
			}
			else
			{
				player->pos.y += PLAYER_NORMAL_SPEED;
			}
		}
	}

	else if (GetKeyboardPress(DIK_A)) // ��
	{
		if (GetKeyboardPress(DIK_LSHIFT)) // ����
		{
			player->pos.x -= PLAYER_SHIFT_SPEED;
		}
		else
		{
			player->pos.x -= PLAYER_NORMAL_SPEED;
		}
	}

	else if (GetKeyboardPress(DIK_D)) // �E
	{
		if (GetKeyboardPress(DIK_LSHIFT)) // ����
		{
			player->pos.x += PLAYER_SHIFT_SPEED;
		}
		else
		{
			player->pos.x += PLAYER_NORMAL_SPEED;
		}
	}

	if (player->pos.x < 0.0f)
	{
		player->pos.x = 0.0f;
	}

	if (player->pos.y < 0.0f)
	{
		player->pos.y = 0.0f;
	}

	if (player->pos.x > UI_POS_X - PLAYER_SIZE_X)
	{
		player->pos.x = UI_POS_X - PLAYER_SIZE_X;
	}

	if (player->pos.y > SCREEN_HEIGHT - PLAYER_SIZE_Y)
	{
		player->pos.y = SCREEN_HEIGHT - PLAYER_SIZE_Y;
	}
}

//=============================================================================
// �|�[�Y
//=============================================================================
void PlayerPause(void)
{
	if (GetKeyboardTrigger(DIK_P))
	{
		SetPauseStage(STAGE_START_GAME);
		SetStage(STAGE_PAUSE);
	}
}

//=============================================================================
// �e����
//=============================================================================
void PlayerShoot(void)
{
	PLAYER *player = GetPlayer();

	player->CountShoot++;

	if (player->CountShoot >= INT_MAX)
	{
		player->CountShoot -= INT_MAX;
	}
	

	if (GetKeyboardPress(DIK_K)) // �e����
	{
		if ((player->Level == PLAYER_LEVEL_04) &&
			((player->CountShoot % PLAYER_BULLET_SHOOT_TIME * 2) == 0))
		{
			SetPlayerBullet(player->pos, PLAYER_BULLET_LEFT);
			SetPlayerBullet(player->pos, PLAYER_BULLET_RIGHT);
		}

		else if ((player->CountShoot % PLAYER_BULLET_SHOOT_TIME) == 0)
		{
			SetPlayerBullet(player->pos, PLAYER_BULLET_LEFT);
			SetPlayerBullet(player->pos, PLAYER_BULLET_RIGHT);
		}

		if ((player->CountShoot % PLAYER_BULLET_SHOOT_TIME) == PLAYER_BULLET_SHOOT_TIME / HALF)
		{
			SetPlayerBullet(player->pos, PLAYER_BULLET_MID);
		}
	}
}

//=============================================================================
// ����
//=============================================================================
void PlayerBomb(void)
{
	PLAYER *player = GetPlayer();

	if (GetKeyboardTrigger(DIK_J)) // ����
	{
		if (player->Bomb > 0)
		{
			player->Bomb--;
			SetPlayerBomb();
		}
	}
}

//=============================================================================
// �v���C���[�̃��x���A�b�v����
//=============================================================================
void PlayerLeverUp(void)
{
	PLAYER *player = GetPlayer();

	if (player->EXP >= PLAYER_LEVEL_UP_EXP)
	{
		player->Level++;
		player->EXP = 0;
	}

	if (player->Level >= PLAYER_LEVEL_04)
	{
		player->Level = PLAYER_LEVEL_03;
	}
}

//=============================================================================
// �v���C���[�mHP���`�F�b�N
//=============================================================================
void CheckPlayerHP(void)
{
	PLAYER *player = GetPlayer();

	if (player->HP <= 0)
	{
		player->Life --;
		player->MainControl = false;
		SetEffect01(player->pos);
		player->alive = false;
	}

}

//=============================================================================
// �v���C���[�̍Đ�
//=============================================================================
void RespawnPlayer(void)
{
	PLAYER *player = GetPlayer();

	if (player->Life > 0)
	{
		player->pos = PLAYER_SPAWN_POS;
		player->HP = PLAYER_HP_MAX;
		player->alive = true;
	}

	else
	{
		SetStage(STAGE_LOSE);
	}
}

//=============================================================================
// �_�ŏ���
//=============================================================================
void SetPlayerFlashing(void)
{
	PLAYER *player = GetPlayer();

	if (player->FlashFlag == true)
	{
		player->FlashingCount++;

		if (player->FlashingCount < PLAYER_FLASHING_HOLD_TIME)
		{
			SetAllDiffuseData(g_PlayerVertexWk,			// �_
				PLAYER_FLASHING_ALPHA_ON);
			SetAllDiffuseData(g_EngineEffectVertexWk,	// �_
				PLAYER_FLASHING_ALPHA_ON);
		}

		if (player->FlashingCount > PLAYER_FLASHING_HOLD_TIME)
		{
			SetAllDiffuseData(g_PlayerVertexWk,			// ��
				PLAYER_FLASHING_ALPHA_OFF);
			SetAllDiffuseData(g_EngineEffectVertexWk,	// ��
				PLAYER_FLASHING_ALPHA_OFF);
		}

		if (player->FlashingCount > PLAYER_FLASHING_RESET)
		{
			player->FlashingCount = 0;					// ���Z�b�g
			player->FlashFlag = false;
			SetPlayerFlashingOn();
		}
	}
}

//=============================================================================
// �_�ŏ���(�_)
//=============================================================================
void SetPlayerFlashingOn(void)
{
	SetAllDiffuseData(g_PlayerVertexWk,			// �_
		PLAYER_FLASHING_ALPHA_ON);
	SetAllDiffuseData(g_EngineEffectVertexWk,	// �_
		PLAYER_FLASHING_ALPHA_ON);
}


//=============================================================================
// �G���W���G�t�F�N�g
//=============================================================================
void PlayerEngineEffect(void)
{
	PLAYER *player = GetPlayer();

	player->CountAnim++;

	if (player->CountAnim%TIME_ENGINE_EFFECT_ANIMATION == 0)
	{
		player->PatternAnim++;

		if (player->PatternAnim > ENGINE_EFFECT_ANIM_PATTERN_NUM)
		{
			player->PatternAnim = 0;
		}
	}

	if (player->CountAnim >= INT_MAX)
	{
		player->CountAnim -= INT_MAX;
	}

	// ������
	player->EffectPos = D3DXVECTOR3(player->pos.x + PLAYER_SIZE_X / 3,
	player->pos.y + PLAYER_SIZE_Y / 2,
	0.0f);

}

//=============================================================================
// �X�N���[���ɓ���A�j���V����
//=============================================================================
void PlayerInScreen(void)
{
	PLAYER *player = GetPlayer();

	player->pos.y -= PLAYER_SHIFT_SPEED;

	player->FlashFlag = true;

}

//=============================================================================
// �`�揈��(�`���g���A���v���C���[)
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer();

	if (player->alive == true)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_D3DTexturePlayer);

		// ���_���W�̐ݒ�(���_���)
		SetVtx4PointData(g_PlayerVertexWk, player->pos, PLAYER_SIZE_X, PLAYER_SIZE_Y);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_PlayerVertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// �`�揈��(�`���g���A���G���W���G�t�F�N�g)
//=============================================================================
void DrawEngineEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer();

	if (player->alive == true)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_D3DTextureEngineEffect);

		// �e�N�X�`�����W�̐ݒ�(�A�j���[�V����)
		SetTextureAnimationData(g_EngineEffectVertexWk, player->PatternAnim, ENGINE_EFFECT_PATTERN_DIVIDE_X, ENGINE_EFFECT_PATTERN_DIVIDE_Y);

		// ���_���W�̐ݒ�(���_���)
		SetVtx4PointData(g_EngineEffectVertexWk, player->EffectPos, ENGINE_EFFECT_SIZE_X, ENGINE_EFFECT_SIZE_Y);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_EngineEffectVertexWk, sizeof(VERTEX_2D));
	}
}


//=============================================================================
// �`���g���A���v���C���[�̏����擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &PlayerWk;
}
