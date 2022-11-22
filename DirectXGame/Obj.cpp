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
//	//ファイルストリーム
//	std::ifstream file;
//	//.objファイルを開く
//	file.open("Resources/triangle.obj");
//	//ファイルオープン失敗をチェック
//	assert(!file.fail());
//
//	std::vector<myMath::Vector3>positions;//頂点座標
//	std::vector<myMath::Vector3>normals;//法線ベクトル
//	std::vector<myMath::Vector2>texcoords;//テクスチャUV
//
//	//1行ずつ読み込む
//	std::string line;
//	while (std::getline(file, line))
//	{
//		//1行分の文字列をストリームに変換して解析しやすくする
//		std::istringstream line_stream(line);
//
//		//半角スペース区切りで行の先頭文字列を取得
//		std::string key;
//		std::getline(line_stream, key,' ');
//
//		UINT sizeVB = static_cast<UINT>(sizeof(PosNormalUv) * vertices.size());
//		UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * indices.size());
//
//		//頂点バッファビュー生成処理の一部
//		vbView.SizeInBytes = sizeVB;
//
//		//インデックスバッファビュー生成処理の一部
//		ibView.SizeInBytes = sizeIB;
//
//		//頂点バッファへのデータ転送の一部
//		std::copy(vertices.begin(), vertices.end(), vertMap);
//
//		//インデックスバッファへのデータ転送の一部
//		std::copy(indices.begin(), indices.end(), indexMap);
//
//		//先頭文字列がvなら頂点座標
//		if (key == "v")
//		{
//			//x,y,z座標読み込み
//			myMath::Vector3 position;
//			line_stream >> position.x;
//			line_stream >> position.y;
//			line_stream >> position.z;
//
//			//座標データに追加
//			positions.emplace_back(position);
//
//			//頂点データに追加
//			PosNormalUv vertex;
//			vertex.pos = position;
//			vertices.emplace_back(vertex);
//		}
//
//		//先頭文字列がfならポリゴン(三角形)
//		if (key == "f")
//		{
//			//半角スペース区切りで行の続きを読み込む
//			std::string index_string;
//			while (std::getline(line_stream, index_string, ' '))
//			{
//				//頂点インデックス1個分の文字列をストリームに変換して解析しやすくする
//				std::istringstream index_stream(index_string);
//				uint16_t indexPosition;
//				index_stream >> indexPosition;
//				//頂点インデックスに追加
//				indices.emplace_back(indexPosition - 1);
//			}
//		}
//	}
//	//ファイルを閉じる
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