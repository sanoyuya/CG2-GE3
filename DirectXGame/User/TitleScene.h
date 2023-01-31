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

	//�V��
	std::unique_ptr<DrawOversight>skyDome;
	Transform skyDomeTrans;
	uint32_t skyDomeTex = 0;

	//3D�X�v���C�g
	std::unique_ptr<Sprite>pokeSprite3D;
	Transform pokeSprite3DTrans;
	uint32_t pokeSprite3DTex = 0;
	myMath::Vector3 pokeSprite3DPos;
	uint16_t pokeNowNum = 0;
	uint8_t pokeTime = 0;

public:

	//����������
	void Initialize()override;

	//�I������
	void Destroy()override;

	//�X�V����
	void Update()override;

	//�`�揈��
	void Draw()override;
};