#pragma once


#include "iostream"
#include "string"
#include "vector"
#include "ctime"
#include "fstream"
#include "filesystem"

#include <SFML\Graphics.hpp>

#include "Define.h"

using namespace std;
using namespace sf;
using namespace filesystem;

/// <summary>
/// ������� ���������� ������ �������� 
/// </summary>
/// <returns>���� � �����</returns>
string getCurrentTime();

/// <summary>
/// ������� ������� ��������� � ���� Log/log.txt
/// </summary>
/// <param name="message">��������� ������� ���������� �������</param>
/// <returns>true ���� �������</returns>
bool OutputMessage(string message);

/// <summary>
/// ������� ��������� ����� �� ����
/// </summary>
/// <param name="PathToFont">���� �� ������</param>
/// <returns></returns>
Font LoadFont(path PathToFont);


/// <summary>
/// ����� ������ � ����������
/// </summary>
/// <param name="SearchInPath">����</param>
/// <param name="Extension">���������� �����(��) / ���� �� ������� ���� �� </param>
/// <returns>������</returns>
vector<path> SearchFile(path SearchInPath, string Extension);
