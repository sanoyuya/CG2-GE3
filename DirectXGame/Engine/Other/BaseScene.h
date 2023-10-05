#pragma once
#include"WindowsApp.h"
#include"myMath.h"

//�V�[�����N���X
class BaseScene
{
protected:

	static myMath::Vector2 windowsSize_;
	static myMath::Vector2 windowsCenter_;

public:

	virtual ~BaseScene() = default;

	//����������
	virtual void Initialize() = 0;

	//�I������
	virtual void Destroy() = 0;

	//�X�V����
	virtual void Update() = 0;

	//�`�揈��
	virtual void Draw() = 0;

	static void StaticInitialize(WindowsApp* windowsApp);
};