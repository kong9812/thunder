#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

// �}�N����`
enum
{	// �T�E���h�ʂ��i���o�[
	TITLE_BGM,
	SE_SELECT,
	SE_PLAYER_RESPAWN,
	SE_PLAYER_START,
	SE_PLAYER_BOMB,
	SE_PLAYER_BULLET_01,
	SE_HIT_SOUND,
	SOUND_MAX
};

enum
{	// �Đ��p�t���O
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};

HRESULT					InitSound( HWND hWnd );	// ������
void					UninitSound();			// ��Еt��
LPDIRECTSOUNDBUFFER8	LoadSound( int no );	// �T�E���h�̃��[�h
void					StopSound(LPDIRECTSOUNDBUFFER8 pBuffer);					// �����~�߂�
void					PlaySound( LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0 );	// �����ƂɍĐ�
bool					IsPlaying( LPDIRECTSOUNDBUFFER8 pBuffer );					// �Đ������ǂ���

#endif