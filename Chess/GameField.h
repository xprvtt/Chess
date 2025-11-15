#pragma once

#include "Core.h"

using GridBoolCoordinate = std::vector<std::vector<bool>>;

using GridRectangleShape = std::vector<std::vector<sf::RectangleShape> >;

using GridText = std::vector<std::vector<sf::Text>>;


class GameField
{

public:
	
	/// <summary>
	/// определение класса
	/// </summary>
	/// <param name="CountCell">колличество клеток, по умолчанию 10х10 т.к. 2 строки и 2 столбца уходят на стандартную разметку</param>
	/// <param name="SizeWindow">разрешение окна</param>
	GameField(size_t CountCell, int WindowHeight, const sf::Font& font, sf::Color OuterSide, sf::Color ColorCellOne, sf::Color ColorCellTwo);


	/// <summary>
	/// получаем текущий квадрат для отрисовки
	/// </summary>
	/// <returns>текуший квадрат</returns>
	sf::RectangleShape getRectangleShapeOnField(size_t XPosition, size_t YPosition);


	/// <summary>
	/// Получает текстовый вид координаты
	/// </summary>
	/// <param name="xPosition">позиция Х</param>
	/// <param name="yPosition">позиция Y</param>
	/// <param name="font">Шрифт</param>
	/// <returns></returns>
	sf::Text getFieldCoordinateOnField(size_t xPosition, size_t yPosition);

	/// <summary>
	/// Получаем колличество рядов
	/// </summary>
	/// <returns>колличество рядов</returns>
	size_t getCounRow();

	/// <summary>
	/// получаем колличество столбцов в ряду
	/// </summary>
	/// <param name="No"></param>
	/// <returns></returns>
	size_t getCounColl(size_t no = 0);

	/// <summary>
	/// размер клетки тип float
	/// </summary>
	/// <returns></returns>
	float getSizeCell() const;

	/// <summary>
	/// Выделяем клетки указанные в векторе
	/// </summary>
	/// <param name="coordinate">вектор координат</param>
	bool selectCell(const GridBoolCoordinate& coordinate, sf::Color color);

	/// <summary>
	/// выделяем клетку на позиции
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	bool selectCell(size_t xPosition, size_t yPosition, sf::Color color);


	/// <summary>
	/// снять выделение с клеток
	/// </summary>
	/// <returns></returns>
	bool unselectAllCell();


private:

	/// <summary>
	/// вектор с размещениями клеток (доска) 
	/// </summary>
	GridRectangleShape rectangleShapeOnField;

	/// <summary>
	/// вектор с отображением координат 
	/// </summary>
	GridText fieldCoordinate;

	/// <summary>
	/// размер одной клетки на поле
	/// </summary>
	float sizeCell = 0.f;

	/// <summary>
	/// шрифт
	/// </summary>
	sf::Font gameFieldFont;
};