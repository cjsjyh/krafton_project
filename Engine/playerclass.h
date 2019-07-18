#pragma once
#ifndef _PLAYERCLASS_H_
#define _PLYAERCLASS_H_

#include "hpobjects.h"

class projectileclass;
class D3DClass;
class ModelClass;
class gameObject;
class gameManager;

#define PLAYER_IMAGE_NUM 8

class playerclass : public hpobjects
{
public:
	playerclass(int, D3DClass* ,D3DXVECTOR3 pos = D3DXVECTOR3(0, 0, 0));
	~playerclass();

	void InitializeModels();
	projectileclass* Fire(D3DXVECTOR3);
	
	void SetGameManager(gameManager*);
	void SetDirection(int*);
	void SetDirection(int);
	int GetDirection();
	D3DXVECTOR3 GetDirectionVector(int);

	void SetBullet(projectileclass*, D3DXVECTOR3);
	void SetSpeed(float);
	
	void SetImage();
	void Move(int*, int);

	void SavePlayerPos(int scene);
	D3DXVECTOR3 GetSavedPlayerPos(int scene);

	//player movement parameters
	float PLAYER_SPEED;
	int PLAYER_DASH_SPEED;
	int PLAYER_DASH_FRAME;
	int PLAYER_DASH_PAUSE_FRAME;

	//player bullet parameters
	int PLAYER_BULLET_DAMAGE;
	float PLAYER_BULLET_SPEED;
	int PLAYER_BULLET_DISTANCE;
	int PLAYER_BULLET_DELAY;

private:
	int direction;
	int dashFrame, dashPauseFrame;
	int dashDir;
	vector<D3DXVECTOR3> playerPosSave;
	gameManager* GM;
};

#endif