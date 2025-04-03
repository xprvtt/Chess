#pragma once

#include "Figure.h"

class Queen : public Figure
{
	//наследуем все конструкторы
	using Figure::Figure;

	/// <summary>
	/// получить доступные координаты для хода -> true - доступная координата
	/// </summary>
	/// <param name="XPositionCurrent"> текущая позиция фигуры Х</param>
	/// <param name="YPositionCurrent"> текущая позиция фигуры У</param>
	/// <param name="VectorLocationFigure">вектор с расположением фигур</param>
	/// <returns></returns>
	vector<pair<size_t, size_t>> GetMoveForFigure(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure) override;

	/// <summary>
	/// проверка -> возможно ли превращение фигуры на указанной позиции?
	/// </summary>
	/// <param name="XPositionCurrent"> текущая позиция фигуры Х</param>
	/// <param name="YPositionCurrent"> текущая позиция фигуры У</param>
	/// <param name="VectorLocationFigure">вектор с расположением фигур</param>
	/// <returns> логическое значение \ true - вревращение возможно</returns>
	bool GetPossibilityPromotion(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure) override;


	/// <summary>
	/// Проверка -> доступен ли ход на указанные координаты, определяется для каждой фигуры
	/// </summary>
	/// <param name="XPositionCurrent">текущие координаты фигуры </param>
	/// <param name="YPositionCurrent">текущие координаты фигуры </param>
	/// <param name="XPositionMove"> координаты, на которые планируем переметиться</param>
	/// <param name="YPositionMove"> координаты, на которые планируем переметиться</param>
	/// <param name="VectorLocationFigure"></param>
	/// <returns></returns>
	bool CheckMove(size_t XPositionCurrent, size_t YPositionCurrent, size_t XPositionMove, size_t YPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure) override;

	/// <summary>
	/// УСТАТАНАВЛИВАЕМ ID ДЛЯ ФИГУРЫ ДОЛЖНА БЫТЬ ПО НАЗВАНИЮ КЛАССА ДЛЯ УДОБСТВА
	/// ФИГУРА НЕ ДОЛЖНА НАЗЫВАТЬСЯ "ALL"
	/// </summary>
	string Set_ID_FIGURE() override;

};