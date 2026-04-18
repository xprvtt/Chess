#pragma once

#include "Core.h"

#include "Figure.h"
#include "Space.h"

#include "PropertiesFigure.h"

/// <summary>
/// Класс с расположением фигур 
/// </summary>
class FigureLocation
{
public:

	///////////////////////////////////////////////////  ОСНОВНЫЕ - НАЧАЛЬНЫЕ  ///////////////////////////////////////////////////
	
	///  инициализирующаяся структура поля, зависимая countCellOnLengthWindow \ countCellOnHeightWindow
	///	
	///	| -1 | -1 | -1 | -1 |
	/// 
	///	| -1 | 0+ | 0+ | -1 |
	/// 
	///	| -1 | 0+ | 0+ | -1 |
	/// 
	///	| -1 | -1 | -1 | -1 |
	/// 
	/// поставить фигуру на -1 не получится => считается краем
	/// 0 - фигура - пустая клетка, должна быть указана
	/// 1+ сторона игрока, должна быть указана

	/// <summary>
	/// инициализация игрового поля \ квадрат X на X 	/// 
	/// </summary>
	/// <param name="countCellOnLengthWindow">колличество клеток в длину</param>
	/// <param name="countCellOnHeightWindow">колличество клеток в высоту</param>
	/// <param name="windowHeight"></param>
	/// <param name="pathToEmptyImage">путь до пустой текстуры</param>
	/// <param name="pathToEmptyTextureEdge">путь до пустой текстуры (край)</param>
	/// <param name="precentSizeFigure">размер фигуры от максимального размера клетки</param>
	FigureLocation(size_t countCellOnLengthWindow, size_t countCellOnHeightWindow, int windowHeight, std::filesystem::path pathToEmptyImage, std::filesystem::path pathToEmptyTextureEdge, float precentSizeFigure);

	/// <summary>
	/// метод расположения фигуры на доске
	/// <para> ВОЗМОЖНЫЙ БАГ => НЕ СРАВНИВАЕТ vectorPromoution, А ЛИШЬ НАХОДИТ ПО ПАРАМЕТРАМ ИТЕРАТОР И РАЗМЕЩАЕТ ФИГУРУ  </para>
	/// <para> ВЕРНУТЬСЯ добавить vectorPromoution в PropertiesFigure и проверку (!) доделать замену перегрузку </para>
	/// </summary>
	/// <param name="xPosition">позиция Х на которую будет установлена фигура</param>
	/// <param name="yPosition">позиция У на которую будет установлена фигура</param>
	/// <param name="idFigure">название фигуры</param>
	/// <param name="side"></param>
	/// <param name="invulnerable"></param>
	/// <param name="important"></param>
	/// <param name="vectorPromoution"></param>
	/// <returns></returns>
	bool setFigure(Position::Coordinates position, std::wstring idFigure, int side, bool invulnerable = false, bool important = false, std::vector<PropertiesFigure> vectorPromoution = {});

	/// <summary>
	/// метод расположения фигуры на доске
	/// <para> ВОЗМОЖНЫЙ БАГ => НЕ СРАВНИВАЕТ vectorPromoution, А ЛИШЬ НАХОДИТ ПО ПАРАМЕТРАМ ИТЕРАТОР И РАЗМЕЩАЕТ ФИГУРУ  </para>
	/// <para> ВЕРНУТЬСЯ добавить vectorPromoution в PropertiesFigure и проверку (!) доделать замену перегрузку </para>
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <param name="pF"></param>
	/// <returns></returns>
	bool setFigure(Position::Coordinates position, PropertiesFigure pF, const std::vector<PropertiesFigure>& vectorPromoution);

	/// <summary>
	/// разместить на доску готовый вектор с расположением фигур
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool setFigureVector(const  std::vector<PositionAndPropertiesFigure>& locationFigure);

	/// <summary>
	/// Добавить уникальную фигуру
	/// </summary>
	/// <param name="NewFigure">класс-наследник Figure</param>
	/// <param name="currentTextureFigure">текстура фигуры</param>
	/// <returns></returns>
	bool addUniqueFigure(std::shared_ptr<Figure> newFigureOrheirs, std::filesystem::path currentTextureFigure);

	/// <summary>
	/// добавить уникальные фигуры из вектора
	/// </summary>
	/// <param name="vectorUniqueFigure"></param>
	/// <returns></returns>
	bool addUniqueVectorFigure(std::vector<std::pair<std::shared_ptr<Figure>, std::filesystem::path>> vectorUniqueFigure);

	///--///--///--///--///--///--///--///--///--///--///--///       ДЛЯ ФИГУР НА ДОСКЕ       ///--///--///--///--///--///--///--///--///--///--///--///	

	///////////////////////////////////////////////////  ИНФОРМАЦИЯ О ФИГУРЕ  ///////////////////////////////////////////////////

	/// <summary>
	/// Получаем название фигуры на позиции
	/// </summary>
	/// <param name="xPosition">позиция Х фигуры</param>
	/// <param name="yPosition">позиция У фигуры</param>
	/// <returns>название фигуры</returns>
	std::wstring getIdFigure(Position::Coordinates position) const;

	/// <summary>
	/// Получаем сторону игрока фигуры на позиции
	/// </summary>
	/// <param name="xPosition">позиция Х фигуры</param>
	/// <param name="yPosition">позиция У фигуры</param>
	/// <returns>сторона игрока у фигуры</returns>
	int getSideFigure(Position::Coordinates position)  const;

	/// <summary>
	/// Получаем координаты фигуры на позиции мышки
	/// </summary>
	/// <param name="positon">позиция в окне</param>
	/// <returns>пара координатов X , Y </returns>
	Position::Coordinates getPositionFigureWhenMousePressed(sf::Vector2f positon)  const;

	/// <summary>
	/// Если есть выделеная фигура, получаем ее позицию x \ y 
	/// </summary>
	/// <returns></returns>
	Position::Coordinates getPositionSelectFigure() const;

	/// <summary>
	/// Уязвима ли фигура на позиции?
	/// 
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	bool getInvulnerableFigure(Position::Coordinates position) const;

	/// <summary>
	/// Важная ли фигура на указанной позиции? от нее может зависить исход боя
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	bool getImportantFigure(Position::Coordinates position) const;

	/// <summary>
	/// получить все свойства фигуры
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	PropertiesFigure getPropertiesFigure(Position::Coordinates position);

	/// <summary>
	/// получаем указатель на спрайт фигуры, расположенной на позиции Х\У
	/// </summary>
	/// <param name="xPosition">позиция Х фигуры</param>
	/// <param name="yPosition">позиция У фигуры</param>
	/// <returns>указатель на RectangleShape  фигуры</returns>
	const sf::RectangleShape& getRectangleShapeFigure(Position::Coordinates position)  const;

	///////////////////////////////////////////////////  ВЗАИМОДЕЙСТВИЕ С ФИГУРОЙ  ///////////////////////////////////////////////////

	/// <summary>
	/// передвижение выделенной фигуры на указанную позицию
	/// </summary>
	/// <param name="xPositionMove">позиция Х на которую нужно передвинуть</param>
	/// <param name="YPositionMove">позиция У на которую нужно передвинуть</param>
	/// <returns>true - фигуры передвинута</returns>
	bool moveSelectFigure(Position::Coordinates position);

	/// <summary>
	/// Выделить фигуру на позиции
	/// </summary>
	/// <param name="xPositionFigure">позиция Х фигуры</param>
	/// <param name="yPositionFigure">позиция У фигуры</param>
	/// <returns>true - если фигура на позиции есть и была выделена</returns>
	bool seletcFigure(Position::Coordinates position);

	/// <summary>
	/// отменить выделение
	/// </summary>
	/// <returns>true - если выделение снято</returns>
	bool unseletcAllFigure();

	/// <summary>
	/// Есть ли хоть одна выделеная фигура?
	/// </summary>
	/// <returns>true - если фигура выделена</returns>
	bool hasSelectedFigure() const noexcept;

	/// <summary>
	/// получаем вектор доступных ходов для выделенной фигуры
	/// </summary>
	/// <returns></returns>
	std::vector<Position::Coordinates> getAvailableMovesForFigure(Position::Coordinates position);

	/// <summary>
	/// доступно ли какое-либо превращение для фигуры на указанной позиции? /// обычно используется сразу после передвижения фигуры
	/// </summary>
	/// <param name="xPositionFigure"></param>
	/// <param name="yPositionFigure"></param>
	/// <returns>true - если доступно </returns>
	bool isPromoutionFigureOnPosition(Position::Coordinates position);

	/// <summary>
	/// Превратиться в выбранную фигуру если доступно
	/// </summary>
	/// <param name="pF"></param>
	/// <returns></returns>
	bool promoutionSelectFigure(const PropertiesFigure& pF);

	///////////////////////////////////////////////////  ВЗАИМОДЕЙСТВИЕ С ИГРОВЫМ ПОЛЕМ   ///////////////////////////////////////////////////

	/// <summary>
	/// обновить вектор с расположение фигурами на игровом поле
	/// </summary>
	void updateLocationFigure();

	/// <summary>
	/// Получить вектор с расположением фигур на игровом поле
	/// </summary>
	/// <returns></returns>
	Grid<PropertiesFigure> getLocationFigure();

	/// <summary>
	/// проверить какие другие фигуры могут угрожать фигуре на указанной позиции || 
	/// работает с так же с фиктивным VectorLocationFigure
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <param name="m_vectorLocationFigure"></param>
	/// <returns>позиции фигур Х \ У</returns>
	std::vector<Position::Coordinates> checkThreatForFigure(Position::Coordinates position, const Grid<PropertiesFigure>& m_vectorLocationFigure);

	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойcтвам
	/// </summary>
	/// <param name="idFigure"></param>
	/// <param name="side"></param>
	/// <param name="invulnerable"></param>
	/// <param name="important"></param>
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	std::vector<Position::Coordinates> getPositionFigure(int side, std::wstring idFigure, bool invulnerable, bool important, bool promoution);

	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойcтвам 
	/// </summary>
	/// <param name="idFigure"></param>
	/// <param name="side"></param>
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	std::vector<Position::Coordinates> getPositionFigure(int side, std::wstring idFigure);

	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойcтвам 
	/// </summary>
	/// <param name="side"></param>
	/// <param name="invulnerableOrImportantOrPromoution">invulnerable или important или promoution</param>
	/// <param name="IMP">к чему относится указанный bool \\ I - invulnerable \\ M - important \\  P - PROMOUTION</param> 
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	std::vector<Position::Coordinates> getPositionsFigure(int side, bool invulnerableOrImportantOrPromoution, char IMP);

	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойтвам
	/// </summary>
	/// <param name="side"></param>
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	std::vector<Position::Coordinates> getPositionFigure(int side);

	/// <summary>
	/// поставлен ли мат указанной фигуре?
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <param name="m_vectorLocationFigure"></param>
	/// <returns></returns>
	bool isCheckmateForFigure(const Position::Coordinates& position, const Grid<PropertiesFigure>& m_vectorLocationFigure);

	/// <summary>
	/// получаем позиции других фигур, которые могут защитить ( от мата или взятия ) указанную фигуру
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <param name="m_vectorLocationFigure"></param>
	/// <returns></returns>
	std::vector<Position::Coordinates> getPositionFigureCanProtectedIndicatedFigure(const Position::Coordinates& position, const Grid<PropertiesFigure>& m_vectorLocationFigure);

	///--///--///--///--///--///--///--///--///--///--///--///     ДЛЯ УНИКАЛЬНЫХ ФИГУР   ///--///--///--///--///--///--///--///--///--///--///--///

	/// <summary>
	/// PropertiesFigure уникальной фигуры с поля уникальных фигур
	/// </summary>
	/// <param name="position">position</param>
	/// <returns>PropertiesFigure</returns>
	PropertiesFigure getPropertiesUniqueFigure(const Position::Coordinates& position);

	/// <summary>
	/// Получить ID уникальной фигуры с поля уникальных фигур
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	std::wstring getIdUniqueFigure(const Position::Coordinates& position);

	/// <summary>
	/// Получить Сторону у уникальной фигуры
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	int getSideUniqueFigure(const Position::Coordinates& position);

	/// <summary>
	/// получить "текстуру" поля уникальных фигур
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	const sf::RectangleShape& getRectangleShapeUniqueFigure(const Position::Coordinates& position)const;

	/// <summary>
	/// выделить фигуру на поле уникальных фигур
	/// </summary>
	/// <param name="xPositionFigure"></param>
	/// <param name="YPositionFigure"></param>
	/// <returns></returns>
	bool selectForPromoutionUniqueFigure(const Position::Coordinates& position);

	/// <summary>
	/// отменить выделение всех фигур на поле уникальных фигур
	/// </summary>
	/// <returns></returns>
	bool unselectUniqueFigure();

	/// <summary>
	/// получить позицию фигуры, информация с поле уникальных фигур
	/// </summary>
	/// <param name="positonMouse"></param>
	/// <returns></returns>
	Position::Coordinates getPositionOnMousePositionUniqueFigire(const sf::Vector2f& positonMouse);

	/// <summary>
	/// Уязвима ли фигура на поле уникальных фигур
	/// </summary>
	bool isInvulnerableUniqueFigire(const Position::Coordinates& position);

	/// <summary>
	/// важная ли фигура, информация с поле уникальных фигур
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	bool isImportantUniqueFigire(const Position::Coordinates& position);

	/// <summary>
	/// может ли фигура превращаться? информация с поле уникальных фигур, по координатам доски
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	bool isPromoutionUniqueFigire(const Position::Coordinates& position)const;

private:

	struct DataFigure
	{
		std::shared_ptr<Figure>      m_locationClassFigure;
		std::shared_ptr<sf::Texture> m_locationTexture;
		sf::RectangleShape           m_locationRectangleShape;

		DataFigure() = default;

		DataFigure(std::shared_ptr<Figure> locationClassFigure, std::shared_ptr<sf::Texture> locationTexture, sf::RectangleShape locationRectangleShape, PropertiesFigure vectorLocationFigure)
			:m_locationClassFigure(locationClassFigure), m_locationTexture(locationTexture), m_locationRectangleShape(locationRectangleShape) {};

		bool operator=(const DataFigure& other) = delete; // maybe later
	};

	struct DataUnique
	{
		std::shared_ptr<Figure>				                m_uniqueFigureLocationClassFigure;
		std::shared_ptr<sf::Texture>				        m_uniqueFigureLocationTexture;

		DataUnique() = default;

		DataUnique(std::shared_ptr<Figure> uniqueFigureLocationClassFigure, std::shared_ptr<sf::Texture> uniqueFigureLocationTexture)
			:m_uniqueFigureLocationClassFigure(uniqueFigureLocationClassFigure), m_uniqueFigureLocationTexture(uniqueFigureLocationTexture) {};

		bool operator=(const DataUnique& other) = delete; // maybe later
	};

	/// <summary>
	/// номер-исключение используется в positionFigure() и GetPositionFigure(), чтобы отбросить условия
	/// </summary>
	std::wstring m_wsExceprion = L"None";

	/// <summary>
	/// информация о фигурах на доске
	/// </summary>
	Grid<DataFigure> m_dataLocalFigure = {} ;

	Grid<PropertiesFigure> m_vectorLocationFigure;

	/// <summary>
	/// информация о уникальных фигурах
	/// </summary>
	std::vector<DataUnique> m_dataUniqueFigure = {};

	//std::vector<std::vector<std::shared_ptr<figure>>> m_locationclassfigure;
	//std::vector<std::vector<std::shared_ptr<sf::texture>>> m_locationtexture;
	//std::vector<std::vector<sf::rectangleshape>> m_locationrectangleshape;

	//std::vector<std::shared_ptr<figure>>				             m_uniquefigurelocationclassfigure;
	//std::vector<std::shared_ptr<sf::texture>>				         m_uniquefigurelocationtexture;
	//std::vector<std::vector<std::pair<size_t, sf::rectangleshape>>>  m_uniquefigurelocationrectangleshape;

	Grid<std::pair<size_t, sf::RectangleShape>>  m_uniqueFigureLocationRectangleShape;

	/// <summary>
	/// координаты выделенной фигуры
	/// </summary>
	Position::Coordinates m_positionSelectFigure = { 0, 0 };

	/// <summary>
	/// колличество столбцов (клеток в одном ряду)
	/// </summary>
	size_t m_countColum = 0;

	/// <summary>
	/// колличество рядов
	/// </summary>
	size_t m_countRow = 0;

	/// <summary>
	/// номер-исключение используется в positionFigure() и GetPositionFigure(), чтобы отбросить условия
	/// </summary>
	int m_numException = -2288;

	/// <summary>
	/// размер одной клетки
	/// </summary>
	float m_sizeCell = 0.f;

	/// <summary>
	///  процент размера одной клетки от максимального размера SizeCell
	/// </summary>
	float m_precentSizeFigure = 0.f;

	/// <summary>
	/// размер клетки фигуры, расчитывается от процента Precent
	/// </summary>
	float m_sizeRectangInCell = 0.f;

	/// <summary>
	/// позиция клетки фигуры
	/// </summary>
	float m_positionRectangInCell = 0.f;
	
	/// <summary>
	/// выделить можно только одну фигуру, поэтому если выделили = true;
	/// </summary>
	bool m_selectFigure = false;

	/// <summary>
	/// получить итератор в векторах уникальных классов фигур и текстур, по позиции
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	size_t getIteratorUniqueFigure(Position::Coordinates position)const;

	/// <summary>
	/// получить итератор в векторах уникальных классов фигур и текстур, по параметрам
	/// </summary>
	/// <returns></returns>
	size_t getIteratorUniqueFigure(PropertiesFigure otherFigure)const;

	/// <summary>
	/// проверить доступен ли ход на указанные координаты	
	/// </summary>
	/// <param name="xPositionCurrent"></param>
	/// <param name="yPositionCurrent"></param>
	/// <param name="xPositionMove"></param>
	/// <param name="yPositionMove"></param>
	/// <param name="m_vectorLocationFigure"></param>
	/// <returns></returns>
	/// bool checkMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const GridPropertiesFigure& m_vectorLocationFigure);

	/// <summary>
	/// найти позиции фигур 
	/// </summary>
	/// <param name="side"></param>
	/// <param name="idFigure"></param>
	/// <param name="invulnerable"></param>
	/// <param name="important"></param>
	/// <param name="promoution"></param>
	/// <returns></returns>
	std::vector<Position::Coordinates> positionFigure(int side, std::wstring idFigure, int invulnerable, int important, int promoution);
};