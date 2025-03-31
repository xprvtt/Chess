#pragma once

#include "Core.h"


class Figure
{
private:

	/// <summary>
	/// единый id для фигур этого типа
	/// </summary>
	string ID_FIGURE;

	/// <summary>
	/// сторока игрока 1 - белый \ 2 - черный
	/// </summary>
	int SIDE;

	/// <summary>
	/// фигуру можно убить? 
	/// </summary>
	bool INVULNERABLE;

public:


	
	/// <summary>
	/// определяем сторону игрока фигуры и уязвимость при инициализации
	/// </summary>
	/// <param name="SIDE">сторона игрока</param>
	/// <param name="Inulnerability">true = неуязвимость \ false = пешку можно взять (убить) </param>
	Figure(int SIDE, bool INVULNERABLE);

	/// <summary>
	/// Конструктор копирования
	/// </summary>
	/// <param name="OthreFigure"></param>
	Figure(const Figure &OthreFigure);

	/// <summary>
	/// Проверяем доступен ли ход на указанные координаты
	/// </summary>
	/// <param name="MoveCoordinate"> передаем конечные координаты</param>
	/// <returns>логическое значение</returns>
	bool CheckMoveForFigure(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure);

	/// <summary>
	/// Получить имя фигуры
	/// </summary>
	/// <returns>имя фигуры</returns>
	string Get_ID_FIGURE();

	/// <summary>
	/// Получаем сторону игрока у фигуры
	/// </summary>
	/// <returns>сторона игрока</returns>
	int GetSIDE();


	/// <summary>
	/// Неуязвима ли фигура?
	/// </summary>
	/// <returns>true = неуязвима \ false - можно убить</returns>
	bool GetINVULNERABLE();


	///////////////////////////////////////////////////////////////////////////////////////////////
	//																			  
	// vector<vector<pair<int, string>>> VectorLocationFigure для int должен имееть структуру =>
	// -1 == границы															  
	// 0 == пустая клетка 														  
	// 1+ == сторона игрока														  
	//																	  
	///////////////////////////////////////////////////////////////////////////////////////////////


	/// ВСЕ ВИРТУАЛЬНЫЕ ФУНКЦИИ ТРЕБУЮТ ПЕРЕОПРЕДЕЛНИЯ В НАСЛЕДНИКАХ 

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


protected:

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

