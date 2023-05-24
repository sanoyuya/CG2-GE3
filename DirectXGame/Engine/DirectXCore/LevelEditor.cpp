#include "LevelEditor.h"
#include<json.hpp>
#include<fstream>

const std::string LevelEditor::defaultBaseDirectory = "Resources/levels/";
const std::string LevelEditor::extension = ".json";

LevelData* LevelEditor::LoadLevelEditorFile(const std::string& fileName)
{
	const std::string fullpath = defaultBaseDirectory + fileName + extension;

	// �t�@�C���X�g���[��
	std::ifstream file;

	// �t�@�C�����J��
	file.open(fullpath);
	// �t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail())
	{
		assert(0);
	}

	//json�����񂩂�𓀂����f�[�^
	nlohmann::json deserialized;

	//��
	file >> deserialized;

	//���������x���f�[�^�t�@�C�����`�F�b�N
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());
	//"name"�𕶎���Ƃ��Ď擾
	std::string name = deserialized["name"].get<std::string>();
	//���������x���f�[�^�t�@�C�����`�F�b�N
	assert(name.compare("scene") == 0);

	//���x���f�[�^�i�[�p�C���X�^���X�𐶐�
	LevelData* levelData = new LevelData();

	//"objects"�̑S�I�u�W�F�N�g�𑖍�
	for (nlohmann::json& object : deserialized["objects"])
	{
		assert(object.contains("type"));

		//��ʂ��擾
		std::string type = object["type"].get<std::string>();

		//mesh
		if (type.compare("MESH") == 0) {

			//�v�f�ǉ�
			levelData->objects.emplace_back(LevelData::ObjectData{});
			//���ǉ������v�f�̎Q�Ƃ𓾂�
			LevelData::ObjectData& objectData = levelData->objects.back();

			if (object.contains("file_name"))
			{
				// �t�@�C����
				objectData.fileName = object["file_name"];
			}

			//�g�����X�t�H�[���̃p�����[�^�ǂݍ���
			nlohmann::json& transform = object["transform"];

			//���s�ړ�
			objectData.translation.x = static_cast<float>(transform["translation"][1]);
			objectData.translation.y = static_cast<float>(transform["translation"][2]);
			objectData.translation.z = -static_cast<float>(transform["translation"][0]);
			// ��]�p
			objectData.rotation.x = -static_cast<float>(transform["rotation"][1]);
			objectData.rotation.y = -static_cast<float>(transform["rotation"][2]);
			objectData.rotation.z = static_cast<float>(transform["rotation"][0]);
			// �X�P�[�����O
			objectData.scaling.x = static_cast<float>(transform["scaling"][1]);
			objectData.scaling.y = static_cast<float>(transform["scaling"][2]);
			objectData.scaling.z = static_cast<float>(transform["scaling"][0]);

			//TODO: �R���C�_�[�̃p�����[�^�ǂݍ���
		}

		// TODO: �I�u�W�F�N�g�������ċA�֐��ɂ܂Ƃ߁A�ċA�ďo�Ŏ}�𑖍�����
		if (object.contains("children")) {

		}
	}

	return levelData;
}