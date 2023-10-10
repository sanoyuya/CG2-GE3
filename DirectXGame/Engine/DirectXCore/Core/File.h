#pragma once
#include <vector>
#include <string>
#include<fstream>
#include<filesystem>

/// <summary>
/// ディレクトリからファイル名一覧を所得
/// </summary>
/// <param name="folderPath">ディレクトリパス</param>
/// <returns>ファイル名一覧</returns>
std::vector<std::string> GetFileNames(const std::string& folderPath);