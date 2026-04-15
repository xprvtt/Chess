#pragma once

#include "Figure.h"

class Pawn : public Figure
{
	/// наследуем все конструкторы
	using Figure::Figure;

	/// <summary>
	/// проверка -> возможно ли превращение фигуры на указанной позиции?
	/// </summary>
	/// <param name="positionCurrent">текущая позиция фигуры</param>
	/// <param name="locationFigure"></param>
	/// <returns>true - превращение возможно</returns>
	bool getPossibilityPromotion(const Position::Coordinates& positionCurrent, const Grid<PropertiesFigure>& locationFigure) const override;

	/// <summary>
	/// устанавливаем id для фигуры должна быть по названию класса для удобства
	/// </summary>
	std::wstring setIdFigure() const noexcept override;

	/// <summary>
	/// кастомная реализация возможных движений с указанной позиции
	/// </summary>
	/// <param name="position"></param>
	/// <param name="locationFigure"></param>
	/// <param name="sumResultMove"></param>
	std::vector<Position::Coordinates> customMoveForFigure(const Position::Coordinates& position, const Grid<PropertiesFigure>& locationFigure) const override;


	/// <summary>
	/// установить все возможные минимальные ходы в любую сторону
	/// </summary>
	std::vector<std::pair<int, int>> setAllMinimumMove() const override;
};