#pragma once

//�Q�[���S��
class YFramework
{
public:

	virtual ~YFramework() = default;

	//����������
	virtual void Initialize();

	//�I������
	virtual void Destroy();

	//�X�V����
	virtual void Update();

	//�`�揈��
	virtual void Draw() = 0;

	//���s����
	void Run();
};