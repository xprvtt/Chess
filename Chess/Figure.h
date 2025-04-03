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
	vector<tuple<int, string, bool, bool, bool >> VectorPROMOUTION;

public:

	/// <summary>
	/// определяем сторону игрока фигуры и уязвимость при инициализации
	/// </summary>
	/// <param name="SIDE">сторона игрока</param>
	/// <param name="Inulnerability">true = неуязвимость \ false = фигуру можно взять (убить) \\ по умолчанию false</param>
	/// <param name="IMPORTANT">важная ли фигура? важные фигуры являются главными фигурами, по типу короля и определяют исход боя \\ по умолчанию - false</param>
	/// <param name="PROMOUTION">вектор с указанными фигурами, в которые может превратиться фигура \\ по умолчанию пустой = ни во что не может превратиться</param>
	Figure(int SIDE, bool INVULNERABLE = false, bool IMPORTANT = false, vector<tuple<int, string, bool, bool, bool>> VectorPROMOUTION = {});

	/// <summary>
	/// Конструктор копирования
	/// </summary>
	/// <param name="OthreFigure"></param>
	Figure(const Figure &OthreFigure);
	
	/// <summary>
	/// Проверяем доступен ли ход на указанные координаты
	/// </summary>
	/// <param name="XPositionCurrent"></param>
	/// <param name="YPositionCurrent"></param>
	/// <param name="XPositionMove"></param>
	/// <param name="YPositionMove"></param>
	/// <param name="VectorLocationFigure"></param>
	/// <returns></returns>
	bool CheckMoveForFigure(size_t XPositionCurrent, size_t YPositionCurrent, size_t XPositionMove, size_t YPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);

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

	/// <summary>
	/// важная ли фигура?
	/// </summary>
	/// <returns>true = важная \ false - не важная </returns>
	bool GetIMPORTANT();

	/// <summary>
	/// имеет ли возможность фигура превращаться?
	/// </summary>
	/// <returns></returns>
	bool GetPROMOUTION();


	/// <summary>
	/// проверка ->  ли мы превратиться в другую указанную фигуру?
	/// </summary>
	/// <param name="SIDE"></param>
	/// <param name="ID_FIGURE"></param>
	/// <param name="INVULNERABLE"></param>
	/// <param name="IMPORTANT"></param>
	/// <returns></returns>
	bool GetPromoutionFigure(int SIDE, string ID_FIGURE, bool INVULNERABLE, bool IMPORTANT, bool PROMOUTION);


	/// <summary>
	/// Получить доступные превращения для фигуры
	/// </summary>
	/// <returns></returns>
	vector<tuple<int, string, bool, bool, bool >> GetVectorPROMOUTION();


	///////////////////////////////////////////////////////////////////////////////////////////////
	//																			  
	// VectorLocationFigure -> для int должен имееть структуру =>
	// -1 == границы															  
	// 0 == пустая клетка 														  
	// 1+ == сторона игрока														  
	//																	  
	///////////////////////////////////////////////////////////////////////////////////////////////



	/// ВСЕ ВИРТУАЛЬНЫЕ ФУНКЦИИ ТРЕБУЮТ ПЕРЕОПРЕДЕЛНИЯ В НАСЛЕДНИКАХ 

	
	/// <summary>
	/// получить доступные координаты для хода -> true - доступная координата
	/// </summary>
	/// <param name="XPositionCurrent"> текущая позиция фигуры Х</param>
	/// <param name="YPositionCurrent"> текущая позиция фигуры У</param>
	/// <param name="VectorLocationFigure">вектор с расположением фигур</param>
	/// <returns></returns>
	virtual vector<pair<size_t, size_t>> GetMoveForFigure(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);


	/// <summary>
	/// проверка -> возможно ли превращение фигуры на указанной позиции?
	/// </summary>
	/// <param name="XPositionCurrent"> текущая позиция фигуры Х</param>
	/// <param name="YPositionCurrent"> текущая позиция фигуры У</param>
	/// <param name="VectorLocationFigure">вектор с расположением фигур</param>
	/// <returns> логическое значение \ true - вревращение возможно</returns>
	virtual bool GetPossibilityPromotion(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);


protected:

	/// <summary>
	/// Проверка -> доступен ли ход на указанные координаты, определяется для каждой фигуры
	/// </summary>
	/// <param name="XPositionCurrent">текущие координаты фигуры </param>
	/// <param name="YPositionCurrent">текущие координаты фигуры </param>
	/// <param name="XPositionMove"> координаты, на которые планируем переметиться</param>
	/// <param name="YPositionMove"> координаты, на которые планируем переметиться</param>
	/// <param name="VectorLocationFigure"></param>
	/// <returns></returns>
	virtual bool CheckMove(size_t XPositionCurrent, size_t YPositionCurrent, size_t XPositionMove, size_t YPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);

	/// <summary>
	/// УСТАТАНАВЛИВАЕМ ID ДЛЯ ФИГУРЫ ДОЛЖНА БЫТЬ ПО НАЗВАНИЮ КЛАССА ДЛЯ УДОБСТВА
	/// ФИГУРА НЕ ДОЛЖНА НАЗЫВАТЬСЯ "ALL"
	/// </summary>
	virtual string Set_ID_FIGURE();
};

