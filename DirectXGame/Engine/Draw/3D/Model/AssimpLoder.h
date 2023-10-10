#pragma once
#include <unordered_map>
#include"DrawCommon.h"
#include"TextureManager.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"ConstantBuffer.h"
#include"myMath.h"
#include"Model.h"

struct aiMesh;
struct aiMaterial;

//struct Vertex
//{
//	myMath::Vector3 position; // 位置座標
//	myMath::Vector3 normal; // 法線
//	myMath::Vector2 uv; // uv座標
//	myMath::Vector3 tangent; // 接空間
//	myMath::Vector4 color; // 頂点色
//};

struct Mesh
{
	std::vector<PosNormalUv> vertices;	//頂点データ配列
	std::vector<uint32_t> indices;	//インデックス配列
	std::wstring diffuseMap;		//テクスチャのファイル
};

struct ImportSettings
{
	const wchar_t* filename = nullptr;	//ファイルパス
	std::vector<Mesh>& meshes;			//出力先のメッシュ配列
	bool inverseU = false;				//U座標を反転させるか
	bool inverseV = false;				//V座標を反転させるか
};

class AssimpLoder
{
public:

	static bool Load(ImportSettings setting, ModelData* data); // モデルをロードする

private:

	static void LoadMesh(Mesh& dst, const aiMesh* src, bool inverseU, bool inverseV, ModelData* data);
	static void LoadTexture(const wchar_t* filename, Mesh& dst, const aiMaterial* src, ModelData* data);
};