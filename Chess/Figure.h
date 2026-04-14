#pragma once

#include "Core.h"
#include "PropertiesFigure.h"

using inRowInt = int;
using inColInt = int;

class Figure
{
public:
	/// <summary>
	/// определяем сторону игрока фигуры и уязвимость при инициализации
	/// <para> если vectorPromoution is empty => promoution == false </para>  
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
	/// <param name="locationFigure"></param>
	/// <returns></returns>
	bool  checkMoveForFigureOnPosition(const Position::Coordinates& positionCurrent, const Position::Coordinates& positionMove, const Grid<PropertiesFigure>& m_vectorLocationFigure) const;

	/// <summary>
	/// Получить имя фигуры
	/// </summary>
	/// <returns>имя фигуры</returns>
	std::wstring getIdFigure() noexcept;

	/// <summary>
	/// Получаем сторону игрока у фигуры
	/// </summary>
	/// <returns>сторона игрока</returns>
	int getSide() const noexcept;

	/// <summary>
	/// Неуязвима ли фигура?
	/// </summary>
	/// <returns>true = неуязвима \ false - можно убить</returns>
	bool isInvulnerable() const noexcept;

	/// <summary>
	/// важная ли фигура?
	/// </summary>
	/// <returns>true = важная \ false - не важная </returns>
	bool isImportant() const noexcept;

	/// <summary>
	/// имеет ли возможность фигура превращаться?
	/// </summary>
	/// <returns></returns>
	bool isPromoution() const noexcept;

	/// <summary>
	/// проверка ->  ли мы превратиться в другую указанную фигуру?
	/// </summary>
	/// <param name="side"></param>
	/// <param name="idFigure"></param>
	/// <param name="invulnerable"></param>
	/// <param name="important"></param>
	/// <returns></returns>
	bool getPromoutionFigure(const PropertiesFigure& properties) const;

	/// <summary>
	/// Получить доступные фигуры для превращения
	/// </summary>
	/// <returns></returns>
	std::vector<PropertiesFigure> getVectorPromoution() const;
		
	/// <summary>
	/// получить доступные координаты для хода, метод должен содержать описание передвижения фигуры
	/// </summary>
	/// <param name="xPositionCurrent"> текущая позиция фигуры Х</param>
	/// <param name="yPositionCurrent"> текущая позиция фигуры У</param>
	/// <param name="locationFigure">вектор с расположением фигур</param>
	/// <returns></returns>
	std::vector<Position::Coordinates> getMoveForFigure(const Position::Coordinates& position, const Grid<PropertiesFigure>& m_vectorLocationFigure) const;

	/// <summary>
	/// проверка -> возможно ли превращение фигуры на указанной позиции, с учетом расположения фигур на доске с их свойствами?
	/// </summary>
	/// <param name="xPositionCurrent"> текущая позиция фигуры Х</param>
	/// <param name="yPositionCurrent"> текущая позиция фигуры У</param>
	/// <param name="locationFigure">вектор с расположением фигур</param>
	/// <returns> логическое значение \ true - вревращение возможно</returns>
	virtual bool getPossibilityPromotion(const Position::Coordinates& position, const Grid<PropertiesFigure>& m_vectorLocationFigure) const = 0;

protected:

	/// <summary>
	/// единый id для фигур этого типа должен быть по названию класса для удобства например для class Figure -> ID_FIGURE = "Figure"
	/// </summary>
	std::wstring m_idFigure = L"";

	/// <summary>
	/// минимально возможный ход, для каждого направления с координаты
	/// например король или ферзь имеют минимальный ход на 1 в любую сторону от себя следовательно 8 разных минимальных позиций от ( -1,-1 ) до ( 1, 1 )
	/// пешка имеет специфический характер движения -> если не передвинута то может сходить на 2 клетки вперед иначе на 1
	/// в связи с этим заполнение allMinimumMove бессмыслено, и требуется кастомное переопределение customMoveForFigure()
	/// минимальные ходы не ограничиваются 1, 4 или 8 разными движениями, 
	/// метод getMoveForFigure() проходится с каждым минимальным передвижением m_allMinimumMove до конца доски
	/// после этого он добавляет результат из customMoveForFigure()
	/// </summary>
	std::vector<std::pair<inRowInt, inColInt>> m_allMinimumMove = {};

	/// <summary>
	/// вектор свойств фигур в которые может превратиться фигура
	/// </summary>
	std::vector<PropertiesFigure> m_allPromoution = {};

	/// <summary>
	/// сторона игрока 1 - белый \ 2 - черный, возможны и другие игроки
	/// </summary>
	int m_side = -2;

	/// <summary>
	/// фигуру можно убить? 
	/// </summary>
	bool m_invulnerable = false;

	/// <summary>
	/// важные фигуры являются главными фигурами, по типу короля и определяют исход боя
	/// </summary>
	bool m_important = false;

	/// <summary> 
	/// имеет ли фигура возможность превращения
	/// </summary>
	bool m_promoution = false;

	/// <summary>
	/// устанавливаем id для фигуры должна быть по названию класса для удобства
	/// </summary>
	virtual std::wstring setIdFigure() const noexcept = 0;

	/// <summary>
	/// метод проверки возможности передвижения
	/// </summary>
	/// <param name="positionCurrent">текущие координаты</param>
	/// <param name="positionMove">координаты, на которые планируем переметиться</param>
	/// <param name="m_vectorLocationFigure"></param>
	/// <returns></returns>
	virtual bool checkMove(const Position::Coordinates& positionCurrent, const Position::Coordinates& positionMove, const Grid<PropertiesFigure>& m_vectorLocationFigure) const;

	/// <summary>
	/// кастомная реализация возможных движений с указанной позиции
	/// </summary>
	/// <param name="position"></param>
	/// <param name="locationFigure"></param>
	/// <param name="sumResultMove"></param>
	virtual std::vector<Position::Coordinates> customMoveForFigure(const Position::Coordinates& position, const Grid<PropertiesFigure>& locationFigure) const;

	/// <summary>
	/// установить все возможные минимальные ходы в любую сторону
	/// </summary>
	virtual std::vector<std::pair<inRowInt, inColInt>> setAllMinimumMove() const = 0;
};



