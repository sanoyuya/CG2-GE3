#pragma once
#include <vector>
#include <string>
#include<fstream>
#include<filesystem>

/// <summary>
/// �f�B���N�g������t�@�C�����ꗗ������
/// </summary>
/// <param name="folderPath">�f�B���N�g���p�X</param>
/// <returns>�t�@�C�����ꗗ</returns>
std::vector<std::string> GetFileNames(const std::string& folderPath);