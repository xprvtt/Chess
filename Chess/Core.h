#pragma once


#include "iostream"
#include "string"
#include "vector"
#include "ctime"
#include "fstream"
#include "filesystem"


#pragma warning(disable: 4275)
#include <SFML/Graphics.hpp>
#pragma warning(default: 4275)


#include "Define.h"



/// <summary>
/// Функция возвращает строку времени 
/// </summary>
/// <returns>дата и время</returns>
std::string getCurrentTime();

/// <summary>
/// Функция возвращает строку времени 
/// </summary>
/// <returns>дата и время</returns>
std::wstring getCurrentTimeWstring();


/// <summary>
/// Функция выводит сообщение в файл Log/log.txt
/// </summary>
/// <param name="message">Сообщение которое необходимо вывести</param>
/// <returns>true если выведен</returns>
bool outputMessage(std::string message);



/// <summary>
/// Функция Загружает шрифт из пути
/// </summary>
/// <param name="pathToFont">путь до шрифта</param>
/// <returns></returns>
sf::Font loadFont(std::filesystem::path pathToFont);



/// <summary>
/// поиск файлов в директории
/// </summary>
/// <param name="SearchInPath">путь</param>
/// <param name="Extension">расширение файла(ов) / если не указано ищет всё </param>
/// <returns>вектор</returns>
std::vector<std::filesystem::path> searchFile(std::filesystem::path searchInPath, std::string extension);

