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
/// Функция возвращает строку веремени 
/// </summary>
/// <returns>дата и время</returns>
string getCurrentTime();

/// <summary>
/// Функция выводит сообщение в файл Log/log.txt
/// </summary>
/// <param name="message">Сообщение которое необходимо вывести</param>
/// <returns>true если выведен</returns>
bool OutputMessage(string message);

/// <summary>
/// Функция Загружает шрифт по пути
/// </summary>
/// <param name="PathToFont">путь до шрифта</param>
/// <returns></returns>
Font LoadFont(path PathToFont);


/// <summary>
/// поиск файлов в директории
/// </summary>
/// <param name="SearchInPath">путь</param>
/// <param name="Extension">расширение файла(ов) / если не указано ищет всё </param>
/// <returns>вектор</returns>
vector<path> SearchFile(path SearchInPath, string Extension);
