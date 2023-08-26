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

	//ファイルストリーム
	std::ifstream file;
	//objファイルを開く
	file.open(fileName);
	//ファイルオープン失敗をチェック
	if (file.fail())
	{
		assert(0);
	}

	//頂点座標
	std::vector<myMath::Vector3> positions;
	//法線ベクトル
	std::vector<myMath::Vector3> normals;
	//テクスチャUV
	std::vector<myMath::Vector2> texcoords;

	PosNormalUv tmp = { {},{},{} };
	PosNormalUv triangle[3];

	//1行ずつ読み込む
	std::string line;
	while (std::getline(file, line))
	{
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		//半角スペース区切りで行の先頭文字を取得
		std::string key;
		std::getline(line_stream, key, ' ');

		//先頭文字列がmtllibならマテリアル
		if (key == "mtllib")
		{
			//マテリアルのファイル名読み込み
			std::string filename;
			line_stream >> filename;
			//マテリアル読み込み
			LoadMaterial(filePath, filename, data);

		}
		//先頭文字列がVなら頂点座標
		if (key == "v")
		{
			//X,Y,Z座標読み込み
			myMath::Vector3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;

			position.x *= GetFlip(flipX) * -1;
			position.y *= GetFlip(flipY);
			position.z *= GetFlip(flipZ);
			//座標データに追加
			positions.emplace_back(position);
		}
		//先頭文字列がvtならテクスチャ
		if (key == "vt")
		{
			//U,V成分読み込み
			myMath::Vector2 texcoord;
			line_stream >> texcoord.x;
			line_stream >> texcoord.y;
			//V方向反転
			texcoord.y = 1.0f - texcoord.y;
			//テクスチャ座標データに追加
			texcoords.emplace_back(texcoord);
		}
		//先頭文字列がvnなら法線ベクトル
		if (key == "vn")
		{
			//X,Y,Z成分読み込み
			myMath::Vector3 normal{};
			line_stream >> normal.x;
			line_stream >> normal.y;
			line_stream >> normal.z;

			normal.x *= GetFlip(flipX) * -1;
			normal.y *= GetFlip(flipY);
			normal.z *= GetFlip(flipZ);
			//法線ベクトルデータに追加
			normals.emplace_back(normal);
		}
		//先頭文字ならポリゴン(三角形)
		if (key == "f")
		{
			uint8_t count = 0;
			//半角スペース区切りで行の続きを読み込む
			std::string index_string;
			while (std::getline(line_stream, index_string, ' '))
			{
				//頂点インデックス1個分文字列をストリームに変換して解析しやすくする
				std::istringstream index_stream(index_string);
				uint16_t indexPosition, indexTexcoord, indexNormal;
				index_stream >> indexPosition;
				//スラッシュを飛ばす
				index_stream.seekg(1, std::ios_base::cur);
				index_stream >> indexTexcoord;
				//スラッシュを飛ばす
				index_stream.seekg(1, std::ios_base::cur);
				index_stream >> indexNormal;

				//頂点データの追加
				tmp.pos = positions[static_cast<size_t>(indexPosition) - 1];
				tmp.normal = normals[static_cast<size_t>(indexNormal) - 1];
				tmp.uv = texcoords[static_cast<size_t>(indexTexcoord) - 1];

				triangle[count] = tmp;
				count++;

				if (smoothing)
				{
					data->smoothData[static_cast<size_t>(indexPosition)].emplace_back(static_cast<uint32_t>(data->vertices.size() - 1));
				}

				//インデックスデータの追加
				data->indices.emplace_back(static_cast<uint32_t>(data->indices.size()));
			}
			data->vertices.push_back(triangle[2]);
			data->vertices.push_back(triangle[1]);
			data->vertices.push_back(triangle[0]);
		}
	}

	//ファイルを閉じる
	file.close();

	if (smoothing)
	{
		CalculateSmoothedVertexNormals(data);
	}

	data->maxVert = static_cast<uint32_t>(data->vertices.size());
	data->maxIndex = static_cast<uint32_t>(data->indices.size());

	//頂点バッファ・インデックス生成
	data->vertexBuffer = std::make_unique<VertexBuffer>();
	data->vertexBuffer->Create(data->maxVert, sizeof(PosNormalUv));

	data->indexBuffer = std::make_unique<IndexBuffer>();
	data->indexBuffer->Create(data->maxIndex);

	//頂点バッファへのデータ転送
	data->vertexBuffer->Update(data->vertices.data());

	//インデックスバッファへのデータ転送
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
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		//半角スペース区切りで行の先頭文字を取得
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

	//ファイルを閉じる
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
		//各面用の共通点コレクション
		std::vector<uint32_t>& v = itr->second;
		//全頂点の法線を平均する
		myMath::Vector3 normal = {};
		for (uint32_t index : v)
		{
			normal += myMath::Vector3{ data->vertices[index].normal.x,  data->vertices[index].normal.y,  data->vertices[index].normal.z };
		}

		normal = normal / static_cast<float>(v.size());
		normal.normalization();
		//共通法線を使用する全ての頂点データに書き込む
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