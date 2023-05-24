#pragma once
#include"myMath.h"
#include <vector>
#include <string>

//���x���f�[�^
struct LevelData {

	struct ObjectData {
		// �t�@�C����
		std::string fileName;
		// ���s�ړ�
		myMath::Vector3 translation;
		// ��]�p
		myMath::Vector3 rotation;
		// �X�P�[�����O
		myMath::Vector3 scaling;
	};

	// �I�u�W�F�N�g�z��
	std::vector<ObjectData> objects;
};

class LevelEditor
{
public:
	//�f�t�H���g�̓ǂݍ��݃f�B���N�g��
	static const std::string defaultBaseDirectory;
	//�t�@�C���g���q
	static const std::string extension;

public:

	/// <summary>
	/// json�t�@�C���̓ǂݍ���
	/// </summary>
	/// <param name="fileName">�t�@�C����</param>
	/// <returns></returns>
	static LevelData* LoadLevelEditorFile(const std::string& fileName);
};