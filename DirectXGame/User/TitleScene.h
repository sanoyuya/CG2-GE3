#pragma once
#include"BaseScene.h"
#include"InputManager.h"
#include"DrawOversight.h"
#include"Camera.h"
#include"AudioManager.h"

//�^�C�g���V�[��
class TitleScene :public BaseScene
{
private:

	//�N���X�ǂݍ���
	InputManager* input = nullptr;
	AudioManager* audioManager = nullptr;

	std::unique_ptr<Camera>camera;
	myMath::Vector3 cameraPos;
	myMath::Vector3 cameraTarget;
	float angle = 0.0f;

	//�V��
	std::unique_ptr<DrawOversight>skyDome;
	Transform skyDomeTrans;
	uint32_t skyDomeTex = 0;

	std::unique_ptr<Sprite>violetSprite2D;
	uint32_t violetSprite2DTex = 0;
	float violetTime = 0.0f;

	//3D�X�v���C�g
	std::unique_ptr<Sprite>pokeSprite3D;
	Transform pokeSprite3DTrans;
	uint32_t pokeSprite3DTex = 0;
	myMath::Vector3 pokeSprite3DPos = {};
	myMath::Vector4 pokeColor = { 1.0f,1.0f ,1.0f ,1.0f };
	bool flipX = false;
	bool flipY = false;
	int pokeNowNum = 0;
	int nowBillboard = 0;
	uint16_t pokeNum = 0;
	uint16_t uintPokeNowNum = 0;
	uint8_t pokeTime = 0;

	//3D�X�v���C�g
	std::unique_ptr<Sprite>pokeSprite3D2;
	Transform pokeSprite3D2Trans;

	std::unique_ptr<Sprite>pokeSprite3D3;
	Transform pokeSprite3D3Trans;

	uint32_t bgm = 0;
	float bgmVolume = 0.0f;
	bool bgmFlag = false;

public:

	//����������
	void Initialize()override;

	//�I������
	void Destroy()override;

	//�X�V����
	void Update()override;

	//�`�揈��
	void Draw()override;

private:

	void camUpdate();
};