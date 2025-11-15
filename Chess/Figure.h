#pragma once

#include "Core.h"
#include "PropertiesFigure.h"

class Figure
{
public:


	/// <summary>
	/// определяем сторону игрока фигуры и уязвимость при инициализации
	/// <para> если vectorPromoution is empty => promoution == false </para> 
	/// 
	/// </summary>
	/// <param name="side">сторона игрока</param>
	/// <param name="Inulnerability">true = неуязвимость \ false = фигуру можно взять (убить) \\ по умолчанию false</param>
	/// <param name="important">важная ли фигура? важные фигуры являются главными фигурами, по типу короля и определяют исход боя \\ по умолчанию - false</param>
	/// <param name="promoution">вектор с указанными фигурами, в которые может превратиться фигура \\ по умолчанию пустой = ни во что не может превратиться</param>
	Figure(int side, bool invulnerable = false, bool important = false, std::vector<PropertiesFigure> vectorPromoution = {});




	/// <summary>
	/// Конструктор копирования
	/// </summary>
	/// <param name="othreFigure"></param>
	Figure(const Figure& othreFigure);




	/// <summary>
	/// Проверяем доступен ли ход на указанные координаты
	/// </summary>
	/// <param name="xPositionCurrent"></param>
	/// <param name="yPositionCurrent"></param>
	/// <param name="xPositionMove"></param>
	/// <param name="yPositionMove"></param>
	/// <param name="vectorLocationFigure"></param>
	/// <returns></returns>
	bool checkMoveForFigureOnPosition(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const GridPropertiesFigure& vectorLocationFigure);













	/// <summary>
	/// Получить имя фигуры
	/// </summary>
	/// <returns>имя фигуры</returns>
	std::wstring getIdFigure();



	/// <summary>
	/// Получаем сторону игрока у фигуры
	/// </summary>
	/// <returns>сторона игрока</returns>
	int getSide() const noexcept;



	/// <summary>
	/// Неуязвима ли фигура?
	/// </summary>
	/// <returns>true = неуязвима \ false - можно убить</returns>
	bool getInvulnerable() const noexcept;



	/// <summary>
	/// важная ли фигура?
	/// </summary>
	/// <returns>true = важная \ false - не важная </returns>
	bool getImportant() const noexcept;



	/// <summary>
	/// имеет ли возможность фигура превращаться?
	/// </summary>
	/// <returns></returns>
	bool getPromoution() const noexcept;



	/// <summary>
	/// проверка ->  ли мы превратиться в другую указанную фигуру?
	/// </summary>
	/// <param name="side"></param>
	/// <param name="idFigure"></param>
	/// <param name="invulnerable"></param>
	/// <param name="important"></param>
	/// <returns></returns>
	bool getPromoutionFigure(int side, std::wstring idFigure, bool invulnerable, bool important, bool promoution) const;



	/// <summary>
	/// Получить доступные превращения для фигуры
	/// </summary>
	/// <returns></returns>
	std::vector<PropertiesFigure> getVectorPromoution() const;














	 
	//////////////////////////////     ФУНКЦИИ НИЖЕ ТРЕБУЮТ ПЕРЕОПРЕДЕЛНИЯ В НАСЛЕДНИКАХ     /////////////////////////////////
	
		
	/// <summary>
	/// получить доступные координаты для хода -> true - доступная координата
	/// </summary>
	/// <param name="xPositionCurrent"> текущая позиция фигуры Х</param>
	/// <param name="yPositionCurrent"> текущая позиция фигуры У</param>
	/// <param name="vectorLocationFigure">вектор с расположением фигур</param>
	/// <returns></returns>
	virtual std::vector<std::pair<size_t, size_t>> getMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, const GridPropertiesFigure& vectorLocationFigure) = 0;



	/// <summary>
	/// проверка -> возможно ли превращение фигуры на указанной позиции?
	/// </summary>
	/// <param name="xPositionCurrent"> текущая позиция фигуры Х</param>
	/// <param name="yPositionCurrent"> текущая позиция фигуры У</param>
	/// <param name="vectorLocationFigure">вектор с расположением фигур</param>
	/// <returns> логическое значение \ true - вревращение возможно</returns>
	virtual bool getPossibilityPromotion(size_t xPositionCurrent, size_t yPositionCurrent, const GridPropertiesFigure& vectorLocationFigure) = 0;





protected:

	//////////////////////////////     ФУНКЦИИ НИЖЕ ТРЕБУЮТ ПЕРЕОПРЕДЕЛНИЯ В НАСЛЕДНИКАХ     /////////////////////////////////


	/// <summary>
	/// Проверка -> доступен ли ход на указанные координаты, определяется для каждой фигуры
	/// </summary>
	/// <param name="xPositionCurrent">текущие координаты фигуры </param>
	/// <param name="yPositionCurrent">текущие координаты фигуры </param>
	/// <param name="xPositionMove"> координаты, на которые планируем переметиться</param>
	/// <param name="yPositionMove"> координаты, на которые планируем переметиться</param>
	/// <param name="vectorLocationFigure"></param>
	/// <returns></returns>
	virtual bool checkMove(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const GridPropertiesFigure& vectorLocationFigure) = 0;




	/// <summary>
	/// УСТАТАНАВЛИВАЕМ ID ДЛЯ ФИГУРЫ ДОЛЖНА БЫТЬ ПО НАЗВАНИЮ КЛАССА ДЛЯ УДОБСТВА
	/// </summary>
	virtual std::wstring setIdFigure() = 0;









private:

	/// <summary>
	/// единый id для фигур этого типа должен быть по названию класса для удобства например для class Figure -> ID_FIGURE = "Figure"
	/// </summary>
	std::wstring idFigure;


	/// <summary>
	/// сторона игрока 1 - белый \ 2 - черный и тд при наличии
	/// </summary>
	int side;


	/// <summary>
	/// фигуру можно убить? 
	/// </summary>
	bool invulnerable;
	

	/// <summary>
	/// важные фигуры являются главными фигурами, по типу короля и определяют исход боя
	/// </summary>
	bool important;


	/// <summary> 
	/// имеет ли фигура возможность превращения
	/// </summary>
	bool promoution;


	/// <summary>
	/// вектор "условий" фигур в которые может превратиться фигура
	/// </summary>
	std::vector<PropertiesFigure> vectorPromoution;




};

