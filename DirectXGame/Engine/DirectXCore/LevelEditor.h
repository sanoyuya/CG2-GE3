#pragma once
#include"myMath.h"
#include <vector>
#include <string>
#include<json.hpp>

//���x���f�[�^
struct LevelData {

	struct Collider
	{
		myMath::Vector3 center_;
		myMath::Vector3 size_;
	};

	struct ObjectData {
		//�t�@�C����
		std::string fileName_;
		//���s�ړ�
		myMath::Vector3 translation_;
		//��]�p
		myMath::Vector3 rotation_;
		//�X�P�[�����O
		myMath::Vector3 scaling_;
		//�����蔻��
		Collider collider_;
	};

	// �I�u�W�F�N�g�z��
	std::vector<ObjectData> objects_;
};

class LevelEditor
{
public:
	//�f�t�H���g�̓ǂݍ��݃f�B���N�g��
	static const std::string sDefaultBaseDirectory_;
	//�t�@�C���g���q
	static const std::string sExtension_;

public:

	/// <summary>
	/// json�t�@�C���̓ǂݍ���
	/// </summary>
	/// <param name="fileName">�t�@�C����</param>
	/// <returns></returns>
	static LevelData* LoadLevelEditorFile(const std::string& fileName);

private:

	static void ObjectDataLoad(LevelData* levelData, nlohmann::json& object);
};