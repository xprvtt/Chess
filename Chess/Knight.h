#pragma once

#include "Figure.h"

class Knight : public Figure
{
	///
	/// наследуем все конструкторы
	/// 
	using Figure::Figure;


	/// <summary>
	/// получить доступные координаты для хода -> true - доступная координата
	/// </summary>
	/// <param name="xPositionCurrent"> текущая позиция фигуры Х</param>
	/// <param name="yPositionCurrent"> текущая позиция фигуры У</param>
	/// <param name="vectorLocationFigure">вектор с расположением фигур</param>
	/// <returns></returns>
	std::vector<std::pair<size_t, size_t>> getMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, const GridPropertiesFigure& vectorLocationFigure) override;

	/// <summary>
	/// проверка -> возможно ли превращение фигуры на указанной позиции?
	/// </summary>
	/// <param name="xPositionCurrent"> текущая позиция фигуры Х</param>
	/// <param name="yPositionCurrent"> текущая позиция фигуры У</param>
	/// <param name="vectorLocationFigure">вектор с расположением фигур</param>
	/// <returns> логическое значение \ true - вревращение возможно</returns>
	bool getPossibilityPromotion(size_t xPositionCurrent, size_t yPositionCurrent, const GridPropertiesFigure& vectorLocationFigure) override;


	/// <summary>
	/// Проверка -> доступен ли ход на указанные координаты, определяется для каждой фигуры
	/// </summary>
	/// <param name="xPositionCurrent">текущие координаты фигуры </param>
	/// <param name="yPositionCurrent">текущие координаты фигуры </param>
	/// <param name="xPositionMove"> координаты, на которые планируем переметиться</param>
	/// <param name="yPositionMove"> координаты, на которые планируем переметиться</param>
	/// <param name="vectorLocationFigure"></param>
	/// <returns></returns>
	bool checkMove(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const GridPropertiesFigure& vectorLocationFigure) override;

	/// <summary>
	/// УСТАТАНАВЛИВАЕМ ID ДЛЯ ФИГУРЫ ДОЛЖНА БЫТЬ ПО НАЗВАНИЮ КЛАССА ДЛЯ УДОБСТВА
	/// </summary>
	std::wstring setIdFigure() override;

};