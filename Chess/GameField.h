#pragma once

#include "Core.h"


/// <summary>
/// матрица используемая для хранения информации о том какие клетки подлежат подсветке, а какие нет -> должна содержать все координаты текущей доски { x, y }
/// </summary>
using Grid2x2Bool = std::vector<std::vector<bool>>;

/// <summary>
/// матрица используемая для хранения информации о свойствах клеток на доске ( RectangleShape ) { x, y }
/// </summary>
using Grid2x2RectangleShape = std::vector<std::vector<sf::RectangleShape>>;

/// <summary>
/// матрица используемая для хранения информации о переменной Text { x, y }
/// </summary>
using Grid2x2Text = std::vector<std::vector<sf::Text>>;


class GameField
{
public:
	
	/// <summary>
	/// конструктор создающий игровое поле исходя из параметров, поле создается всегда в виде соразмерной матрицы 2х2. Цвет клеток для игры окракшивается в виде мазайки из цветов ColorCellOne и ColorCellTwo
	/// </summary>
	/// <param name="CountCell">колличество клеток на одной из любой стороны, по умолчанию 10 т.к. 2 строки и 2 столбца уходят на стандартную разметку позиции</param></param>
	/// <param name="WindowHeight">длина окна</param>
	/// <param name="font">шрифт который будет использоваться для отображения текста</param>
	/// <param name="OuterSide">цвет клеток разметки</param>
	/// <param name="ColorCellOne">первый цвет непосредственно игровой клетки</param>
	/// <param name="ColorCellTwo">второй цвет непосредственно игровой клетки </param>
	GameField(size_t CountCell, int WindowHeight, const sf::Font& font, sf::Color OuterSide, sf::Color ColorCellOne, sf::Color ColorCellTwo);
	
	/// <summary>
	/// получить клетку на игровом поле
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	sf::RectangleShape getRectangleShapeOnField(Position::Coordinates position);

	/// <summary>
	/// Получить Text координаты
	/// </summary>
	/// <param name="xPosition">позиция Х</param>
	/// <param name="yPosition">позиция Y</param>
	/// <param name="font">Шрифт</param>
	/// <returns></returns>
	sf::Text getFieldCoordinateOnField(Position::Coordinates position);

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
	size_t getCounColl(size_t numberColum = 0);

	/// <summary>
	/// получить длину клетки
	/// </summary>
	/// <returns></returns>
	float getSizeCell() const;

	/// <summary>
	/// Выделить клетки указанные в векторе
	/// </summary>
	/// <param name="coordinate">вектор координат</param>
	bool selectCells(const Grid2x2Bool& coordinate, sf::Color color);

	/// <summary>
	/// выделяем клетку на позиции
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	bool selectCell(Position::Coordinates position, sf::Color color);

	/// <summary>
	/// снять выделение с клеток
	/// </summary>
	/// <returns></returns>
	bool unselectAllCell() noexcept;

private:

	/// <summary>
	/// шрифт используемый для отрисовки текста
	/// </summary>
	sf::Font m_gameFieldFont = {};

	/// <summary>
	/// матрица 2x2 с размещениями клеток -> игровая доска
	/// гарантированно валидный -> row == colum
	/// </summary>
	Grid2x2RectangleShape m_rectangleShapeOnField = {};

	/// <summary>
	/// матрица 2х2 с отображением координат 
	/// гарантированно валидный -> row == colum
	/// </summary>
	Grid2x2Text m_fieldCoordinate = {};

	/// <summary>
	/// размер одной клетки на поле
	/// </summary>
	float m_sizeCell = 0.f;

	/// <summary>
	/// Проверка соразмерности кол-ва рядов и столбцов матрицы 2х2 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="v">grid</param>
	/// <returns>Возвращает true если колво рядов == колличеству столбцов. Возвращает false если не равно, либо если пустой</returns>
	template<typename T>
	bool validGrid(const std::vector<std::vector<T>>& grid) const noexcept;

};