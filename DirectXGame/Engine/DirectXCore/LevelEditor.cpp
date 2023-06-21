#include"LevelEditor.h"
#include<fstream>

const std::string LevelEditor::sDefaultBaseDirectory_ = "Resources/levels/";
const std::string LevelEditor::sExtension_ = ".json";

LevelData* LevelEditor::LoadLevelEditorFile(const std::string& fileName)
{
	const std::string fullpath = sDefaultBaseDirectory_ + fileName + sExtension_;

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
		ObjectDataLoad(levelData, object);
	}

	return levelData;
}

void LevelEditor::ObjectDataLoad(LevelData* levelData, nlohmann::json& object)
{
	assert(object.contains("type"));

	//��ʂ��擾
	std::string type = object["type"].get<std::string>();

	//mesh
	if (type.compare("MESH") == 0) {

		//�v�f�ǉ�
		levelData->objects_.emplace_back(LevelData::ObjectData{});
		//���ǉ������v�f�̎Q�Ƃ𓾂�
		LevelData::ObjectData& objectData = levelData->objects_.back();

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
		//��]�p
		objectData.rotation.x = -static_cast<float>(transform["rotation"][1]);
		objectData.rotation.y = -static_cast<float>(transform["rotation"][2]);
		objectData.rotation.z = static_cast<float>(transform["rotation"][0]);
		//�X�P�[�����O
		objectData.scaling.x = static_cast<float>(transform["scaling"][1]);
		objectData.scaling.y = static_cast<float>(transform["scaling"][2]);
		objectData.scaling.z = static_cast<float>(transform["scaling"][0]);

		//�R���C�_�[�̃p�����[�^�ǂݍ���
		nlohmann::json& collider = object["collider"];
		if (collider != nullptr)
		{
			//���S�_
			objectData.collider.center.x = static_cast<float>(collider["center"][1]);
			objectData.collider.center.y = static_cast<float>(collider["center"][2]);
			objectData.collider.center.z = static_cast<float>(collider["center"][0]);
			//�傫��
			objectData.collider.size.x = static_cast<float>(collider["size"][1]);
			objectData.collider.size.y = static_cast<float>(collider["size"][2]);
			objectData.collider.size.z = static_cast<float>(collider["size"][0]);
		}
	}

	//�I�u�W�F�N�g�������ċA�֐��ɂ܂Ƃ߁A�ċA�ďo�Ŏ}�𑖍�����
	if (object.contains("children"))
	{
		for (nlohmann::json& object_ : object["children"])
		{
			ObjectDataLoad(levelData, object_);
		}
	}
}