#pragma once
#include"myMath.h"
#include <vector>
#include <string>
#include<json.hpp>

//���x���f�[�^
struct LevelData {

	struct Collider
	{
		myMath::Vector3 center;
		myMath::Vector3 size;
	};

	struct Timer
	{
		float spawnTimer;
		float deathTimer;
	};

	struct EnemyProperty
	{
		myMath::Vector3 spawnPos;
		float toMovePosTime;
		myMath::Vector3 movePos;
		float waitTime;
		float toEscapePosTime;
		myMath::Vector3 escapePos;
	};

	struct ObjectData {
		//�t�@�C����
		std::string fileName;
		//���s�ړ�
		myMath::Vector3 translation;
		//��]�p
		myMath::Vector3 rotation;
		//�X�P�[�����O
		myMath::Vector3 scaling;
		//�����蔻��
		Collider collider;
		//�^�C�}�[
		Timer timer;
		//�G�̃v���p�e�B
		EnemyProperty enemyProperty;
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