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
////ボーン構造体
//struct Bone;
//
//struct Node
//{
//	//名前
//	std::string name;
//	//ローカルスケール
//	myMath::Vector3 scaling = { 1,1,1 };
//	//ローカル回転角
//	myMath::Vector3 rotation = { 0,0,0 };
//	//ローカル移動
//	myMath::Vector3 translation = { 0,0,0 };
//	//ローカル変形行列
//	myMath::Matrix4 transform;
//	//グローバル変形行列
//	myMath::Matrix4 globalTransform;
//	//親ノード
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
//	std::vector<Mesh>& meshes; // 出力先のメッシュ配列
//
//	bool inverseU = false; // U座標を反転させるか
//
//	bool inverseV = false; // V座標を反転させるか
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