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
	
	
	//  инициализирующаяся структура поля, зависимая countCellOnLengthWindow \ countCellOnHeightWindow
	//	
	//	| -1 | -1 | -1 | -1 |
	// 
	//	| -1 | 0+ | 0+ | -1 |
	// 
	//	| -1 | 0+ | 0+ | -1 |
	// 
	//	| -1 | -1 | -1 | -1 |
	// 
	// поставить фигуру на -1 не получится => считается краем
	// 0 - фигура - пустая клетка, должна быть указана
	// 1+ сторона игрока, должна быть указана



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
	bool setFigure(size_t xPosition, size_t yPosition, std::wstring idFigure, int side, bool invulnerable = false, bool important = false, std::vector<PropertiesFigure> vectorPromoution = {});

	/// <summary>
	/// метод расположения фигуры на доске
	/// <para> ВОЗМОЖНЫЙ БАГ => НЕ СРАВНИВАЕТ vectorPromoution, А ЛИШЬ НАХОДИТ ПО ПАРАМЕТРАМ ИТЕРАТОР И РАЗМЕЩАЕТ ФИГУРУ  </para>
	/// <para> ВЕРНУТЬСЯ добавить vectorPromoution в PropertiesFigure и проверку (!) доделать замену перегрузку </para>
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <param name="pF"></param>
	/// <returns></returns>
	bool setFigure(size_t xPosition, size_t yPosition, PropertiesFigure pF);










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




















	//--//--//--//--//--//--//--//--//--//--//--//       ДЛЯ ФИГУР НА ДОСКЕ       //--//--//--//--//--//--//--//--//--//--//--//	




	///////////////////////////////////////////////////  ИНФОРМАЦИЯ О ФИГУРЕ  ///////////////////////////////////////////////////

	/// <summary>
	/// Получаем название фигуры на позиции
	/// </summary>
	/// <param name="xPosition">позиция Х фигуры</param>
	/// <param name="yPosition">позиция У фигуры</param>
	/// <returns>название фигуры</returns>
	std::wstring getIdFigure(size_t xPosition, size_t yPosition)  const;



	/// <summary>
	/// Получаем сторону игрока фигуры на позиции
	/// </summary>
	/// <param name="xPosition">позиция Х фигуры</param>
	/// <param name="yPosition">позиция У фигуры</param>
	/// <returns>сторона игрока у фигуры</returns>
	int getSideFigure(size_t xPosition, size_t yPosition)  const;



	/// <summary>
	/// Получаем координаты фигуры на позиции мышки
	/// </summary>
	/// <param name="positon">позиция в окне</param>
	/// <returns>пара координатов X , Y </returns>
	std::pair<size_t, size_t> getPositionFigureWhenMousePressed(sf::Vector2f positon)  const;




	/// <summary>
	/// Если есть выделеная фигура, получаем ее позицию x \ y 
	/// </summary>
	/// <returns></returns>
	std::pair<size_t, size_t> getPositionSelectFigure() const;



	/// <summary>
	/// Уязвима ли фигура на позиции?
	/// 
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	bool getInvulnerableFigure(size_t xPosition, size_t yPosition) const;




	/// <summary>
	/// Важная ли фигура на указанной позиции? от нее может зависить исход боя
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	bool getImportantFigure(size_t xPosition, size_t yPosition) const;




	/// <summary>
	/// получить все свойства фигуры
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	PropertiesFigure getPropertiesFigure(size_t xPosition, size_t yPosition);





	/// <summary>
	/// получаем указатель на спрайт фигуры, расположенной на позиции Х\У
	/// </summary>
	/// <param name="xPosition">позиция Х фигуры</param>
	/// <param name="yPosition">позиция У фигуры</param>
	/// <returns>указатель на RectangleShape  фигуры</returns>
	const sf::RectangleShape& getRectangleShapeFigure(size_t xPosition, size_t yPosition)  const;























	///////////////////////////////////////////////////  ВЗАИМОДЕЙСТВИЕ С ФИГУРОЙ  ///////////////////////////////////////////////////



	/// <summary>
	/// передвижение выделенной фигуры на указанную позицию
	/// </summary>
	/// <param name="xPositionMove">позиция Х на которую нужно передвинуть</param>
	/// <param name="YPositionMove">позиция У на которую нужно передвинуть</param>
	/// <returns>true - фигуры передвинута</returns>
	bool moveSelectFigure(size_t xPositionMove, size_t yPositionMove);




	/// <summary>
	/// Выделить фигуру на позиции
	/// </summary>
	/// <param name="xPositionFigure">позиция Х фигуры</param>
	/// <param name="yPositionFigure">позиция У фигуры</param>
	/// <returns>true - если фигура на позиции есть и была выделена</returns>
	bool seletcFigure(size_t xPositionFigure, size_t yPositionFigure);





	/// <summary>
	/// отменить выделение
	/// </summary>
	/// <returns>true - если выделение снято</returns>
	bool unseletcAllFigure();





	/// <summary>
	/// Есть ли хоть одна выделеная фигура?
	/// </summary>
	/// <returns>true - если фигура выделена</returns>
	bool figuresSelectedOrNot() const noexcept;





	/// <summary>
	/// получаем вектор доступных ходов для выделенной фигуры
	/// </summary>
	/// <returns></returns>
	std::vector<std::pair<size_t, size_t>> getAvailableMovesForFigure(size_t xPositionFigure, size_t yPositionFigure);





	/// <summary>
	/// доступно ли какое-либо превращение для фигуры на указанной позиции? // обычно используется сразу после передвижения фигуры
	/// </summary>
	/// <param name="xPositionFigure"></param>
	/// <param name="yPositionFigure"></param>
	/// <returns>true - если доступно </returns>
	bool promoutionFigureOnPosition(size_t xPositionFigure, size_t yPositionFigure);





	/// <summary>
	/// Превратиться в выбранную фигуру если доступно
	/// </summary>
	/// <param name="side"></param>
	/// <param name="idFigure"></param>
	/// <param name="invulnerable"></param>
	/// <param name="important"></param>
	/// <returns>true - превращение выполнено</returns>
	bool PromoutionSelectFigure(int side, std::wstring idFigure, bool invulnerable, bool important, bool Promoution);





	/// <summary>
	/// 
	/// </summary>
	/// <param name="pF"></param>
	/// <returns></returns>
	bool PromoutionSelectFigure(PropertiesFigure pF);





















	///////////////////////////////////////////////////  ВЗАИМОДЕЙСТВИЕ С ИГРОВЫМ ПОЛЕМ   ///////////////////////////////////////////////////



	/// <summary>
	/// обновить вектор с расположение фигурами на игровом поле
	/// </summary>
	void updateVectorLocationFigure();




	/// <summary>
	/// Получить вектор с расположением фигур на игровом поле
	/// </summary>
	/// <returns></returns>
	GridPropertiesFigure getVectorLocationFigure();




	/// <summary>
	/// проверить какие другие фигуры могут угрожать фигуре на указанной позиции || 
	/// работает с так же с фиктивным VectorLocationFigure
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <param name="vectorLocationFigure"></param>
	/// <returns>позиции фигур Х \ У</returns>
	std::vector<std::pair<size_t, size_t>> checkThreatFigure(size_t xPositionOnVectorLocationFigure, size_t yPositionOnVectorLocationFigure, const GridPropertiesFigure& vectorLocationFigure);




	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойcтвам
	/// </summary>
	/// <param name="idFigure"></param>
	/// <param name="side"></param>
	/// <param name="invulnerable"></param>
	/// <param name="important"></param>
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	std::vector<std::pair<size_t, size_t>> getPositionFigure(int side, std::wstring idFigure, bool invulnerable, bool important, bool promoution);




	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойтвам позция X \ Y
	/// </summary>
	/// <param name="idFigure"></param>
	/// <param name="side"></param>
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	std::vector<std::pair<size_t, size_t>> getPositionFigure(int side, std::wstring idFigure);




	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойтвам позция X \ Y
	/// </summary>
	/// <param name="side"></param>
	/// <param name="invulnerableOrImportantOrPromoution">invulnerable или important или promoution</param>
	/// <param name="IMP">к чему относится указанный bool \\ I - invulnerable \\ M - important \\  P - PROMOUTION</param> 
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	std::vector<std::pair<size_t, size_t>> getPositionsFigure(int side, bool invulnerableOrImportantOrPromoution, char IMP);




	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойтвам позция X \ Y
	/// </summary>
	/// <param name="side"></param>
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	std::vector<std::pair<size_t, size_t>> getPositionFigure(int side);






	/// <summary>
	/// поставлен ли мат указанной фигуре?
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <param name="vectorLocationFigure"></param>
	/// <returns></returns>
	bool checkmateForFigure(size_t xPosition, size_t yPosition, const GridPropertiesFigure& vectorLocationFigure);




	/// <summary>
	/// получаем позиции других фигур, которые могут защитить ( от мата или взятия ) указанную фигуру
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <param name="vectorLocationFigure"></param>
	/// <returns></returns>
	std::vector<std::pair<size_t, size_t>> figureCanProtectenCheckmateForFigure(size_t xPosition, size_t yPosition, const GridPropertiesFigure& vectorLocationFigure);

	

























	//--//--//--//--//--//--//--//--//--//--//--//     ДЛЯ УНИКАЛЬНЫХ ФИГУР   //--//--//--//--//--//--//--//--//--//--//--//




	/// <summary>
	/// Получить ID уникальной фигуры с поля уникальных фигур
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	std::wstring getUniqueIdFigure(size_t xPosition, size_t yPosition);



	/// <summary>
	/// Получить Сторону у уникальной фигуры
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	int getUniqueSideFigure(size_t xPosition, size_t yPosition);




	/// <summary>
	/// получить "текстуру" поля уникальных фигур
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	const sf::RectangleShape& getUniqueRectangleShapeFigure(size_t xPosition, size_t yPosition);




	/// <summary>
	/// выделить фигуру на поле уникальных фигур
	/// </summary>
	/// <param name="xPositionFigure"></param>
	/// <param name="YPositionFigure"></param>
	/// <returns></returns>
	bool seletcUniqueFigureForPromoution(size_t xPositionFigure, size_t yPositionFigure);



	/// <summary>
	/// отменить выделение всех фигур на поле уникальных фигур
	/// </summary>
	/// <returns></returns>
	bool unseletcUniqueFigure();



	/// <summary>
	/// получить позицию фигуры, информация с поле уникальных фигур
	/// </summary>
	/// <param name="positonMouse"></param>
	/// <returns></returns>
	std::pair<int, int> getUniquePositionFigureWhenMousePressed(sf::Vector2f positonMouse);



	/// <summary>
	/// Уязвима ли фигура на поле уникальных фигур
	/// </summary>
	bool getUniqueInvulnerableFigure(size_t xPosition, size_t yPosition);



	/// <summary>
	/// важная ли фигура, информация с поле уникальных фигур
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	bool getUniqueImportantFigure(size_t xPosition, size_t yPosition);



	/// <summary>
	/// может ли фигура превращаться? информация с поле уникальных фигур, по координатам доски
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	bool getUniquePromoutionFigure(size_t xPositionField, size_t yPositionField);




















private:



	//--//--//--//--//--//--//--//   ДЛЯ ФИГУР НА ИГРОВОМ ПОЛЕ  //--//--//--//--//--//--//--//--//--//--//--//
	
	std::vector<std::vector<std::shared_ptr<Figure>>>				locationClassFigure;
																	
	std::vector<std::vector<std::shared_ptr<sf::Texture>>>			locationTexture;
																	
	std::vector<std::vector<sf::RectangleShape>>					locationRectangleShape;
	




	//--//--//--//--//--//--//--//--//   ДЛЯ УНИКАЛЬНЫХ ФИГУР   //--//--//--//--//--//--//--//--//--//--//--//

	std::vector<std::shared_ptr<Figure>>				             uniqueFigureLocationClassFigure;
																     
	std::vector<std::shared_ptr<sf::Texture>>				         uniqueFigureLocationTexture;

	std::vector<std::vector<std::pair<size_t, sf::RectangleShape>>>  uniqueFigureLocationRectangleShape;








	///////////////////////////////////////////////////////////////////////////////////////////////////
	/// 
	///  int в VectorIntLocationFigure должен имееть структуру => 	              
	///  -1 == границы														  
	///  0 == пустая клетка 												  
	///  1+ == сторона игрока 
	/// 
	///////////////////////////////////////////////////////////////////////////////////////////////////

	GridPropertiesFigure vectorLocationFigure;
	
	





	///////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// колличество клеток в 1 ряду
	/// </summary>
	size_t countCellOnXPosition = 0;

	/// <summary>
	/// колличество рядов
	/// </summary>
	size_t countCellOnYPosition = 0;

	/// <summary>
	/// размер одной клетки
	/// </summary>
	float sizeCell = 0.f;

	/// <summary>
	///  процент размера одной клетки от максимального размера SizeCell
	/// </summary>
	float precentSizeFigure = 0.f;

	/// <summary>
	/// размер клетки фигуры, расчитывается от процента Precent
	/// </summary>
	float sizeRectangInCell = 0.f;

	/// <summary>
	/// позиция клетки фигуры
	/// </summary>
	float positionRectangInCell = 0.f;
	
	/// <summary>
	/// выделить можно только одну фигуру, поэтому если выделили = true;
	/// </summary>
	bool selectFigure = false;

	/// <summary>
	/// координаты выделенной фигуры Х \ У 
	/// </summary>
	std::pair<size_t, size_t> positionSelectFigure = { 0, 0 };

	/// <summary>
	/// номер-исключение используется в positionFigure() и GetPositionFigure(), чтобы отбросить условия
	/// </summary>
	int numException = -2288;

	/// <summary>
	/// 
	/// </summary>
	std::wstring wsExceprion = L"None";














	///////////////////////////////////////////////////////////////////////////////////////////


	/// <summary>
	/// получаем итератор в векторах уникальных классов фигур и текстур, по позиции
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	size_t getIteratorUniqueFigure(size_t xPosition, size_t yPosition);




	/// <summary>
	/// получаем итератор в векторах уникальных классов фигур и текстур, по параметрам
	/// </summary>
	/// <returns></returns>
	size_t getIteratorUniqueFigure(PropertiesFigure otherFigure);

	



	/// <summary>
	/// проверяем доступен ли ход на указанные координаты	
	/// </summary>
	/// <param name="xPositionCurrent"></param>
	/// <param name="yPositionCurrent"></param>
	/// <param name="xPositionMove"></param>
	/// <param name="yPositionMove"></param>
	/// <param name="vectorLocationFigure"></param>
	/// <returns></returns>
	/// bool checkMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const GridPropertiesFigure& vectorLocationFigure);

	



	/// <summary>
	/// найти позиции фигур 
	/// </summary>
	/// <param name="side"></param>
	/// <param name="idFigure"></param>
	/// <param name="invulnerable"></param>
	/// <param name="important"></param>
	/// <param name="promoution"></param>
	/// <returns></returns>
	std::vector<std::pair<size_t, size_t>> positionFigure(int side, std::wstring idFigure, int invulnerable, int important, int promoution);



};