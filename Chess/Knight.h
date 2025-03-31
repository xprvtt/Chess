#pragma once
#pragma once
#include "Figure.h"

class Knight : public Figure
{
	//наследуем все конструторы
	using Figure::Figure;

	/// <summary>
	/// получаем доступные координаты для хода
	/// </summary>
	/// <param name="Coordiante">Координаты на которые мы хочем сходить</param>
	/// <returns>логическое значение</returns>
	virtual vector<vector<bool>> GetMoveForFigure(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure);

	/// <summary>
	/// возможность превращения пешки если выполнены условия
	/// </summary>
	/// <returns></returns>
	virtual bool GetPossibilityPromotion(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure);

	/// <summary>
	/// можем ли мы превратиться в другую указанную фигуру?
	/// </summary>
	/// <returns></returns>
	virtual bool GetPromoutionFigure(string ID_Figure);

	/// <summary>
	/// Проверяем доступен ли ход на указанные координаты, определяется для каждой фигуры
	/// </summary>
	/// <param name="Coordiante">Координаты на которые мы хочем сходить</param>
	/// <returns>логическое значение</returns>
	virtual bool CheckMove(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure);

	/// <summary>
	/// УСТАТАНАВЛИВАЕМ ID ДЛЯ ФИГУРЫ ДОЛЖНА БЫТЬ ПО НАЗВАНИЮ КЛАССА ДЛЯ УДОБСТВА
	/// </summary>
	virtual string Set_ID_FIGURE();

};