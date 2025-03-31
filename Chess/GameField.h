#pragma once

#include "Core.h"

class GameField
{
private:

	/// <summary>
	/// вектор с размещени€ми клеток (доска)
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
	/// <param name="CountCell">колличество клеток, по умолчанию 10х10 т.к. 2 строки и 2 столбца уход€т на стандартную разметку</param>
	/// <param name="SizeWindow">разрешение окна</param>
	GameField(int CountCell, int WindowHeight, const Font& font, Color OuterSide, Color ColorCellOne, Color ColorCellTwo);

	/// <summary>
	/// получаем текущий квадрат дл€ отрисовки
	/// </summary>
	/// <returns>текуший квадрат</returns>
	RectangleShape GetRectangleShapeOnField(int XPosition, int YPosition);


	/// <summary>
	/// ѕолучает текстовый вид координаты
	/// </summary>
	/// <param name="XPosition">позици€ ’</param>
	/// <param name="YPosition">позици€ Y</param>
	/// <param name="font">Ўрифт</param>
	/// <returns></returns>
	Text GetFieldCoordinateOnField(int XPosition, int YPosition);

	/// <summary>
	/// ѕолучаем колличество р€дов в поле
	/// </summary>
	/// <returns>колличество р€дов</returns>
	int GetCounRowRectangleShape();

	/// <summary>
	/// получаем колличество столбцов в р€ду
	/// </summary>
	/// <param name="No"></param>
	/// <returns></returns>
	int GetCounCollRectangleShape(int No = 0);

	/// <summary>
	/// получаем колличество координат в р€ду
	/// </summary>
	/// <returns></returns>
	int GetCounRowFieldCoordinate();

	/// <summary>
	/// получаем полличество столбцов в р€ду
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
	/// ¬ыдел€ем клетки указанные в векторе
	/// </summary>
	/// <param name="Coordinate">вектор координат</param>
	bool SelectCell(const vector<vector<bool>>& Coordinate);

	/// <summary>
	/// сн€ть выделение с клеток
	/// </summary>
	/// <returns></returns>
	bool UnSelectCell();
};

