#include "Obj.h"
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include <cassert>
#include"myMath.h"

//void Object::Initialize()
//{
//	cmdList = DirectX_::GetInstance()->GetCommandList();
//
//	//�t�@�C���X�g���[��
//	std::ifstream file;
//	//.obj�t�@�C�����J��
//	file.open("Resources/triangle.obj");
//	//�t�@�C���I�[�v�����s���`�F�b�N
//	assert(!file.fail());
//
//	std::vector<myMath::Vector3>positions;//���_���W
//	std::vector<myMath::Vector3>normals;//�@���x�N�g��
//	std::vector<myMath::Vector2>texcoords;//�e�N�X�`��UV
//
//	//1�s���ǂݍ���
//	std::string line;
//	while (std::getline(file, line))
//	{
//		//1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
//		std::istringstream line_stream(line);
//
//		//���p�X�y�[�X��؂�ōs�̐擪��������擾
//		std::string key;
//		std::getline(line_stream, key,' ');
//
//		UINT sizeVB = static_cast<UINT>(sizeof(PosNormalUv) * vertices.size());
//		UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * indices.size());
//
//		//���_�o�b�t�@�r���[���������̈ꕔ
//		vbView.SizeInBytes = sizeVB;
//
//		//�C���f�b�N�X�o�b�t�@�r���[���������̈ꕔ
//		ibView.SizeInBytes = sizeIB;
//
//		//���_�o�b�t�@�ւ̃f�[�^�]���̈ꕔ
//		std::copy(vertices.begin(), vertices.end(), vertMap);
//
//		//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]���̈ꕔ
//		std::copy(indices.begin(), indices.end(), indexMap);
//
//		//�擪������v�Ȃ璸�_���W
//		if (key == "v")
//		{
//			//x,y,z���W�ǂݍ���
//			myMath::Vector3 position;
//			line_stream >> position.x;
//			line_stream >> position.y;
//			line_stream >> position.z;
//
//			//���W�f�[�^�ɒǉ�
//			positions.emplace_back(position);
//
//			//���_�f�[�^�ɒǉ�
//			PosNormalUv vertex;
//			vertex.pos = position;
//			vertices.emplace_back(vertex);
//		}
//
//		//�擪������f�Ȃ�|���S��(�O�p�`)
//		if (key == "f")
//		{
//			//���p�X�y�[�X��؂�ōs�̑�����ǂݍ���
//			std::string index_string;
//			while (std::getline(line_stream, index_string, ' '))
//			{
//				//���_�C���f�b�N�X1���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
//				std::istringstream index_stream(index_string);
//				uint16_t indexPosition;
//				index_stream >> indexPosition;
//				//���_�C���f�b�N�X�ɒǉ�
//				indices.emplace_back(indexPosition - 1);
//			}
//		}
//	}
//	//�t�@�C�������
//	file.close();
//}
//
//void Object::Update()
//{
//}
//
//void Object::Draw()
//{
//	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);
//}