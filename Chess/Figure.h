#pragma once

#include "Core.h"


class Figure
{
private:

	/// <summary>
	/// единый id для фигур этого типа должен быть по названию класса для удобства например для class Figure -> ID_FIGURE = "Figure"
	/// </summary>
	string ID_FIGURE;

	/// <summary>
	/// сторона игрока 1 - белый \ 2 - черный
	/// </summary>
	int SIDE;

	/// <summary>
	/// фигуру можно убить? 
	/// </summary>
	bool INVULNERABLE;
	
	/// <summary>
	/// важные фигуры являются главными фигурами, по типу короля и определяют исход боя
	/// </summary>
	bool IMPORTANT;

	/// <summary> 
	/// имеет ли фигура возможность превращения
	/// </summary>
	bool PROMOUTION;

	/// <summary>
	/// вектор "условий" фигур в которые может превратиться фигура
	/// </summary>
	vector<tuple<int, string, bool, bool, bool >> VECTOR_PROMOUTION;

public:

	/// <summary>
	/// определяем сторону игрока фигуры и уязвимость при инициализации
	/// </summary>
	/// <param name="SIDE">сторона игрока</param>
	/// <param name="Inulnerability">true = неуязвимость \ false = фигуру можно взять (убить) \\ по умолчанию false</param>
	/// <param name="IMPORTANT">важная ли фигура? важные фигуры являются главными фигурами, по типу короля и определяют исход боя \\ по умолчанию - false</param>
	/// <param name="PROMOUTION">вектор с указанными фигурами, в которые может превратиться фигура \\ по умолчанию пустой = ни во что не может превратиться</param>
	Figure(int SIDE, bool INVULNERABLE = false, bool IMPORTANT = false, vector<tuple<int, string, bool, bool, bool>> VECTOR_PROMOUTION = {});

	/// <summary>
	/// Конструктор копирования
	/// </summary>
	/// <param name="othreFigure"></param>
	Figure(const Figure &othreFigure);
	
	/// <summary>
	/// Проверяем доступен ли ход на указанные координаты
	/// </summary>
	/// <param name="xPositionCurrent"></param>
	/// <param name="yPositionCurrent"></param>
	/// <param name="xPositionMove"></param>
	/// <param name="yPositionMove"></param>
	/// <param name="vectorLocationFigure"></param>
	/// <returns></returns>
	bool checkMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure);

	/// <summary>
	/// Получить имя фигуры
	/// </summary>
	/// <returns>имя фигуры</returns>
	string get_ID_FIGURE();

	/// <summary>
	/// Получаем сторону игрока у фигуры
	/// </summary>
	/// <returns>сторона игрока</returns>
	int get_SIDE();

	/// <summary>
	/// Неуязвима ли фигура?
	/// </summary>
	/// <returns>true = неуязвима \ false - можно убить</returns>
	bool get_INVULNERABLE();

	/// <summary>
	/// важная ли фигура?
	/// </summary>
	/// <returns>true = важная \ false - не важная </returns>
	bool get_IMPORTANT();

	/// <summary>
	/// имеет ли возможность фигура превращаться?
	/// </summary>
	/// <returns></returns>
	bool get_PROMOUTION();


	/// <summary>
	/// проверка ->  ли мы превратиться в другую указанную фигуру?
	/// </summary>
	/// <param name="SIDE"></param>
	/// <param name="ID_FIGURE"></param>
	/// <param name="INVULNERABLE"></param>
	/// <param name="IMPORTANT"></param>
	/// <returns></returns>
	bool getPromoutionFigure(int SIDE, string ID_FIGURE, bool INVULNERABLE, bool IMPORTANT, bool PROMOUTION);


	/// <summary>
	/// Получить доступные превращения для фигуры
	/// </summary>
	/// <returns></returns>
	vector<tuple<int, string, bool, bool, bool >> get_VECTOR_PROMOUTION();


	///////////////////////////////////////////////////////////////////////////////////////////////
	//																			  
	// vectorLocationFigure -> для int должен имееть структуру =>
	// -1 == границы															  
	// 0 == пустая клетка 														  
	// 1+ == сторона игрока														  
	//																	  
	///////////////////////////////////////////////////////////////////////////////////////////////



	/// ВСЕ ВИРТУАЛЬНЫЕ ФУНКЦИИ ТРЕБУЮТ ПЕРЕОПРЕДЕЛНИЯ В НАСЛЕДНИКАХ 

	
	/// <summary>
	/// получить доступные координаты для хода -> true - доступная координата
	/// </summary>
	/// <param name="xPositionCurrent"> текущая позиция фигуры Х</param>
	/// <param name="yPositionCurrent"> текущая позиция фигуры У</param>
	/// <param name="vectorLocationFigure">вектор с расположением фигур</param>
	/// <returns></returns>
	virtual vector<pair<size_t, size_t>> getMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure);


	/// <summary>
	/// проверка -> возможно ли превращение фигуры на указанной позиции?
	/// </summary>
	/// <param name="xPositionCurrent"> текущая позиция фигуры Х</param>
	/// <param name="yPositionCurrent"> текущая позиция фигуры У</param>
	/// <param name="vectorLocationFigure">вектор с расположением фигур</param>
	/// <returns> логическое значение \ true - вревращение возможно</returns>
	virtual bool getPossibilityPromotion(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure);


protected:

	/// <summary>
	/// Проверка -> доступен ли ход на указанные координаты, определяется для каждой фигуры
	/// </summary>
	/// <param name="xPositionCurrent">текущие координаты фигуры </param>
	/// <param name="yPositionCurrent">текущие координаты фигуры </param>
	/// <param name="xPositionMove"> координаты, на которые планируем переметиться</param>
	/// <param name="yPositionMove"> координаты, на которые планируем переметиться</param>
	/// <param name="vectorLocationFigure"></param>
	/// <returns></returns>
	virtual bool checkMove(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure);

	/// <summary>
	/// УСТАТАНАВЛИВАЕМ ID ДЛЯ ФИГУРЫ ДОЛЖНА БЫТЬ ПО НАЗВАНИЮ КЛАССА ДЛЯ УДОБСТВА
	/// ФИГУРА НЕ ДОЛЖНА НАЗЫВАТЬСЯ "ALL"
	/// </summary>
	virtual string set_ID_FIGURE();
};

