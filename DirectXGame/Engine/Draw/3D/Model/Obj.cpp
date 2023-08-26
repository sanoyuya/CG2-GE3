#include "Obj.h"
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include <cassert>
#include"myMath.h"
#include"File.h"

void Obj::Create(const char* filePath, bool smoothing, ModelData* data, bool flipX, bool flipY, bool flipZ)
{
	std::vector<std::string> files;
	files = GetFileNames(filePath);
	std::string fileName;

	for (std::string file : files)
	{
		if (file.find("obj") != std::string::npos)
		{
			fileName = file;
		}
	}

	//�t�@�C���X�g���[��
	std::ifstream file;
	//obj�t�@�C�����J��
	file.open(fileName);
	//�t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail())
	{
		assert(0);
	}

	//���_���W
	std::vector<myMath::Vector3> positions;
	//�@���x�N�g��
	std::vector<myMath::Vector3> normals;
	//�e�N�X�`��UV
	std::vector<myMath::Vector2> texcoords;

	PosNormalUv tmp = { {},{},{} };
	PosNormalUv triangle[3];

	//1�s���ǂݍ���
	std::string line;
	while (std::getline(file, line))
	{
		//1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		//���p�X�y�[�X��؂�ōs�̐擪�������擾
		std::string key;
		std::getline(line_stream, key, ' ');

		//�擪������mtllib�Ȃ�}�e���A��
		if (key == "mtllib")
		{
			//�}�e���A���̃t�@�C�����ǂݍ���
			std::string filename;
			line_stream >> filename;
			//�}�e���A���ǂݍ���
			LoadMaterial(filePath, filename, data);

		}
		//�擪������V�Ȃ璸�_���W
		if (key == "v")
		{
			//X,Y,Z���W�ǂݍ���
			myMath::Vector3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;

			position.x *= GetFlip(flipX) * -1;
			position.y *= GetFlip(flipY);
			position.z *= GetFlip(flipZ);
			//���W�f�[�^�ɒǉ�
			positions.emplace_back(position);
		}
		//�擪������vt�Ȃ�e�N�X�`��
		if (key == "vt")
		{
			//U,V�����ǂݍ���
			myMath::Vector2 texcoord;
			line_stream >> texcoord.x;
			line_stream >> texcoord.y;
			//V�������]
			texcoord.y = 1.0f - texcoord.y;
			//�e�N�X�`�����W�f�[�^�ɒǉ�
			texcoords.emplace_back(texcoord);
		}
		//�擪������vn�Ȃ�@���x�N�g��
		if (key == "vn")
		{
			//X,Y,Z�����ǂݍ���
			myMath::Vector3 normal{};
			line_stream >> normal.x;
			line_stream >> normal.y;
			line_stream >> normal.z;

			normal.x *= GetFlip(flipX) * -1;
			normal.y *= GetFlip(flipY);
			normal.z *= GetFlip(flipZ);
			//�@���x�N�g���f�[�^�ɒǉ�
			normals.emplace_back(normal);
		}
		//�擪�����Ȃ�|���S��(�O�p�`)
		if (key == "f")
		{
			uint8_t count = 0;
			//���p�X�y�[�X��؂�ōs�̑�����ǂݍ���
			std::string index_string;
			while (std::getline(line_stream, index_string, ' '))
			{
				//���_�C���f�b�N�X1����������X�g���[���ɕϊ����ĉ�͂��₷������
				std::istringstream index_stream(index_string);
				uint16_t indexPosition, indexTexcoord, indexNormal;
				index_stream >> indexPosition;
				//�X���b�V�����΂�
				index_stream.seekg(1, std::ios_base::cur);
				index_stream >> indexTexcoord;
				//�X���b�V�����΂�
				index_stream.seekg(1, std::ios_base::cur);
				index_stream >> indexNormal;

				//���_�f�[�^�̒ǉ�
				tmp.pos = positions[static_cast<size_t>(indexPosition) - 1];
				tmp.normal = normals[static_cast<size_t>(indexNormal) - 1];
				tmp.uv = texcoords[static_cast<size_t>(indexTexcoord) - 1];

				triangle[count] = tmp;
				count++;

				if (smoothing)
				{
					data->smoothData[static_cast<size_t>(indexPosition)].emplace_back(static_cast<uint32_t>(data->vertices.size() - 1));
				}

				//�C���f�b�N�X�f�[�^�̒ǉ�
				data->indices.emplace_back(static_cast<uint32_t>(data->indices.size()));
			}
			data->vertices.push_back(triangle[2]);
			data->vertices.push_back(triangle[1]);
			data->vertices.push_back(triangle[0]);
		}
	}

	//�t�@�C�������
	file.close();

	if (smoothing)
	{
		CalculateSmoothedVertexNormals(data);
	}

	data->maxVert = static_cast<uint32_t>(data->vertices.size());
	data->maxIndex = static_cast<uint32_t>(data->indices.size());

	//���_�o�b�t�@�E�C���f�b�N�X����
	data->vertexBuffer = std::make_unique<VertexBuffer>();
	data->vertexBuffer->Create(data->maxVert, sizeof(PosNormalUv));

	data->indexBuffer = std::make_unique<IndexBuffer>();
	data->indexBuffer->Create(data->maxIndex);

	//���_�o�b�t�@�ւ̃f�[�^�]��
	data->vertexBuffer->Update(data->vertices.data());

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	data->indexBuffer->Update(data->indices.data());

	data->constBuffMaterial = std::make_unique<ConstantBuffer>();
	data->constBuffMaterial->Create(sizeof(ConstBuffDataMaterial));
	ConstBuffDataMaterial tmpMaterial = data->modelMaterial.GetConstBuffMaterial();
	data->constBuffMaterial->Update(&tmpMaterial);
}

void Obj::LoadMaterial(const std::string& directoryPath, const std::string& filename, ModelData* data)
{
	std::ifstream file;

	std::string filePath = directoryPath + "/" + filename;

	file.open(filePath);
	if (file.fail())
	{
		assert(0);
	}

	std::string line;
	while (std::getline(file, line))
	{
		//1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		//���p�X�y�[�X��؂�ōs�̐擪�������擾
		std::string key;
		std::getline(line_stream, key, ' ');

		if (key[0] == '\t')
		{
			key.erase(key.begin());
		}

		if (key == "newmtl")
		{
			line_stream >> data->modelMaterial.name;
		}
		if (key == "Ka")
		{
			line_stream >> data->modelMaterial.ambient.x;
			line_stream >> data->modelMaterial.ambient.y;
			line_stream >> data->modelMaterial.ambient.z;
		}
		if (key == "Kd")
		{
			line_stream >> data->modelMaterial.diffuse.x;
			line_stream >> data->modelMaterial.diffuse.y;
			line_stream >> data->modelMaterial.diffuse.z;
		}
		if (key == "Ks")
		{
			line_stream >> data->modelMaterial.specular.x;
			line_stream >> data->modelMaterial.specular.y;
			line_stream >> data->modelMaterial.specular.z;
		}
		if (key == "map_Kd")
		{
			line_stream >> data->modelMaterial.textureFiename;
			LoadTexture(directoryPath, data->modelMaterial.textureFiename, data);
		}
	}

	//�t�@�C�������
	file.close();
}

void Obj::LoadTexture(const std::string& directoryPath, const std::string& filename, ModelData* data)
{
	std::string filepath = directoryPath + "/" + filename;

	uint32_t handl = TextureManager::Load(filepath);

	data->textureData = TextureManager::GetTextureData(handl);
}

void Obj::CalculateSmoothedVertexNormals(ModelData* data)
{
	auto itr = data->smoothData.begin();
	for (; itr != data->smoothData.end(); itr++)
	{
		//�e�ʗp�̋��ʓ_�R���N�V����
		std::vector<uint32_t>& v = itr->second;
		//�S���_�̖@���𕽋ς���
		myMath::Vector3 normal = {};
		for (uint32_t index : v)
		{
			normal += myMath::Vector3{ data->vertices[index].normal.x,  data->vertices[index].normal.y,  data->vertices[index].normal.z };
		}

		normal = normal / static_cast<float>(v.size());
		normal.normalization();
		//���ʖ@�����g�p����S�Ă̒��_�f�[�^�ɏ�������
		for (uint32_t index : v)
		{
			data->vertices[index].normal = { normal.x,normal.y,normal.z };
		}
	}
}

int8_t Obj::GetFlip(bool flip)
{
	if (flip == false)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}