//#pragma once
//#include <unordered_map>
//#include"DrawCommon.h"
//#include"TextureManager.h"
//#include"VertexBuffer.h"
//#include"IndexBuffer.h"
//#include"ConstantBuffer.h"
//
//struct Mesh;
//
//struct Vertex
//{
//	myMath::Vector3 position;
//	myMath::Vector3 normal;
//	myMath::Vector2 uv;
//};
//
////�{�[���\����
//struct Bone;
//
//struct Node
//{
//	//���O
//	std::string name;
//	//���[�J���X�P�[��
//	myMath::Vector3 scaling = { 1,1,1 };
//	//���[�J����]�p
//	myMath::Vector3 rotation = { 0,0,0 };
//	//���[�J���ړ�
//	myMath::Vector3 translation = { 0,0,0 };
//	//���[�J���ό`�s��
//	myMath::Matrix4 transform;
//	//�O���[�o���ό`�s��
//	myMath::Matrix4 globalTransform;
//	//�e�m�[�h
//	Node* parent = nullptr;
//
//};
//
//class AssimpModelData
//{
//private:
//
//	std::string filePath;
//
//	uint32_t modelHandle;
//
//	std::vector<Mesh>& meshes; // �o�͐�̃��b�V���z��
//
//	bool inverseU = false; // U���W�𔽓]�����邩
//
//	bool inverseV = false; // V���W�𔽓]�����邩
//
//	
//};
//
//class AssimpLoder
//{
//private:
//
//	static Microsoft::WRL::ComPtr<ID3D12Device> device;
//
//	static std::vector<std::string>filePaths;
//
//	static std::unordered_map<std::string, std::unique_ptr<AssimpModelData>> modelDatas;
//
//	static uint32_t modelCount;
//
//public:
//
//	bool LoadModelData(const char* filePath)
//};