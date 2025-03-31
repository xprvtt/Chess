#pragma once

#include "Core.h"

class GameField
{
private:

	/// <summary>
	/// вектор с размещениями клеток (доска) 
	/// </summary>
	vector<vector<RectangleShape>> RectangleShapeOnField;

	/// <summary>
	/// вектор с отображением координат 
	/// </summary>
	vector<vector<Text>> FieldCoordinate;

	/// <summary>
	/// размер одной клетки на поле
	/// </summary>
	float SizeCell = 0.f;

	Font GameFieldFont;

public:
	
	/// <summary>
	/// определение класса
	/// </summary>
	/// <param name="CountCell">колличество клеток, по умолчанию 10х10 т.к. 2 строки и 2 столбца уходят на стандартную разметку</param>
	/// <param name="SizeWindow">разрешение окна</param>
	GameField(int CountCell, int WindowHeight, const Font& font, Color OuterSide, Color ColorCellOne, Color ColorCellTwo);

	/// <summary>
	/// получаем текущий квадрат для отрисовки
	/// </summary>
	/// <returns>текуший квадрат</returns>
	RectangleShape GetRectangleShapeOnField(int XPosition, int YPosition);


	/// <summary>
	/// Получает текстовый вид координаты
	/// </summary>
	/// <param name="XPosition">позиция Х</param>
	/// <param name="YPosition">позиция Y</param>
	/// <param name="font">Шрифт</param>
	/// <returns></returns>
	Text GetFieldCoordinateOnField(int XPosition, int YPosition);

	/// <summary>
	/// Получаем колличество рядов в поле
	/// </summary>
	/// <returns>колличество рядов</returns>
	int GetCounRowRectangleShape();

	/// <summary>
	/// получаем колличество столбцов в ряду
	/// </summary>
	/// <param name="No"></param>
	/// <returns></returns>
	int GetCounCollRectangleShape(int No = 0);

	/// <summary>
	/// получаем колличество координат в ряду
	/// </summary>
	/// <returns></returns>
	int GetCounRowFieldCoordinate();

	/// <summary>
	/// получаем полличество столбцов в ряду
	/// </summary>
	/// <param name="No"></param>
	/// <returns></returns>
	int GetCounCollFieldCoordinate(int No = 0);

	/// <summary>
	/// размер клетки тип float
	/// </summary>
	/// <returns></returns>
	float GetSizeCell();

	/// <summary>
	/// Выделяем клетки указанные в векторе
	/// </summary>
	/// <param name="Coordinate">вектор координат</param>
	bool SelectCell(const vector<vector<bool>>& Coordinate);

	/// <summary>
	/// снять выделение с клеток
	/// </summary>
	/// <returns></returns>
	bool UnSelectCell();
};

