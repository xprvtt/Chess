#pragma once

#include "Core.h"

#include "GameEngine.h"

#include "CountdownTimer.h" 

#include "propertiesGame.h"


/// <summary>
/// начинаем новую игру после выхода из цикла startGameCycle() ?
/// </summary>
extern bool nextGame;



/// <summary>
/// основной цикл игры
/// </summary>
/// <param name="rWindow"></param>
bool startGameCycle(std::unique_ptr<GameEngine> Game);




/// <summary>
/// <para> НЕ РЕАЛИЗОВАНО (!) </para> 
/// получить расположение фигур
/// <para> если не указан путь, получаем стандартное расположение фигур для шахмат, со стандартным размером доски</para>
/// <para> если путь  указан, получаем расположение фигур из файла</para>
/// </summary>
/// <param name="pathToSave">путь до файла</param>
/// <returns>вектор</returns>
std::vector<PositionAndPropertiesFigure> getVectorLocationFigure(std::filesystem::path pathToSave);




/// <summary>
/// 
/// </summary>
/// <param name="pathToSave"></param>
/// <param name="numberSave"></param>
/// <returns></returns>
bool importSave(std::filesystem::path pathToSave, int numberSave);




/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool exportSave();
