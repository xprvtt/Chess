#pragma once

#include "Core.h"
#include "Figure.h"

/// <summary>
/// Класс с расположением фигур 
/// </summary>
class FigureLocation
{

private:

	///////////////////////////////////////////////////////////////////////////////////////////////////


	//--//--//--//--//--//--//--//   ДЛЯ ФИГУР НА ИГРОВОМ ПОЛЕ  //--//--//--//--//--//--//--//--//--//--//--//
	
	vector< vector< shared_ptr<Figure>>>   locationClassFigure;
	vector< vector< shared_ptr<Texture>>>  locationTexture;
	vector< vector< RectangleShape >>      locationRectangleShape;
	
	//--//--//--//--//--//--//--//     ДЛЯ УНИКАЛЬНЫХ ФИГУР   //--//--//--//--//--//--//--//--//--//--//

	vector<shared_ptr<Figure>>				   uniqueFigureLocationClassFigure;
	vector<shared_ptr<Texture>>				   uniqueFigureLocationTexture;
	vector<vector<pair<size_t, RectangleShape>>>  uniqueFigureLocationRectangleShape;


	///////////////////////////////////////////////////////////////////////////////////////////////////



	////////////////////////////////////////////////////////////////////////////////
																				  //
	// int в VectorIntLocationFigure должен имееть структуру => 	              //
	// -1 == границы															  //
	// 0 == пустая клетка 														  //
	// 1+ == сторона игрока														  //
																				  //
	////////////////////////////////////////////////////////////////////////////////
	
	/// <summary>
	/// get<0> int-SIDE ||| get<1> string-ID_FIGURE ||| get<2> bool-INVULNERABLE ||| get<3> bool- IMPORTANT ||| get<4> bool- PROMOUTION 
	/// </summary>
	vector<vector<tuple<int, string, bool, bool, bool>>> vectorLocationFigure;
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// колличество клеток в 1 ряду
	/// </summary>
	size_t countCellOnXPosition;


	/// <summary>
	/// колличество рядов
	/// </summary>
	size_t countCellOnYPosition;

	/// <summary>
	/// размер одной клетки
	/// </summary>
	float sizeCell;

	/// <summary>
	///  процент размера одной клетки от максимального размера SizeCell
	/// </summary>
	float precentSizeFigure;

	/// <summary>
	/// размер клетки фигуры, расчитывается от процента Precent
	/// </summary>
	float sizeRectangInCell;

	/// <summary>
	/// позиция клетки фигуры
	/// </summary>
	float positionRectangInCell;
	
	/// <summary>
	/// выделить можно только одну фигуру, поэтому если выделили = true;
	/// </summary>
	bool selectFigure = false;

	/// <summary>
	/// координаты выделенной фигуры Х \ У 
	/// </summary>
	pair<int, int> positionSelectFigure = make_pair(0, 0);

	/// <summary>
	/// номер-исключение используется в positionFigure() и GetPositionFigure(), чтобы отбросить условия
	/// </summary>
	int NUM_exception = -2288;

	///////////////////////////////////////////////////////////////////////////////////////////


	/// <summary>
	/// получаем итератор в векторах уникальных классов фигур и текстур, по позиции
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	int getIteratorUniqueFigure(size_t xPosition, size_t yPosition);

	/// <summary>
	/// получаем итератор в векторах уникальных классов фигур и текстур, по параметрам
	/// </summary>
	/// <param name="SIDE"></param>
	/// <param name="ID_FIGURE"></param>
	/// <param name="INVULNERABLE"></param>
	/// <param name="IMPORTANT"></param>
	/// <param name="PROMOUTION"></param>
	/// <returns></returns>
	int getIteratorUniqueFigure(int SIDE, string ID_FIGURE, bool INVULNERABLE, bool IMPORTANT, bool PROMOUTION);

	
	/// <summary>
	/// проверяем доступен ли ход на указанные координаты
	/// </summary>
	/// <param name="xPositionCurrent"></param>
	/// <param name="YPositionCurrent"></param>
	/// <param name="xPositionMove"></param>
	/// <param name="YPositionMove"></param>
	/// <param name="vectorLocationFigure"></param>
	/// <returns></returns>
	bool checkMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure);


	/// <summary>
	/// найти позиции фигур
	/// </summary>
	/// <param name="ID_Figure"></param>
	/// <param name="SIDE"></param>
	/// <param name="INVULNERABLE"></param>
	/// <param name="IMPORTANT"></param>
	/// <returns></returns>
	vector<pair<size_t, size_t>> positionFigure(int SIDE, string ID_Figure, int INVULNERABLE, int IMPORTANT, int PROMOUTION);


	///////////////////////////////////////////////////////////////////////////////////////////

public:


	//--//--//--//--//--//--//--//   ДЛЯ ФИГУР НА ДОСКЕ  //--//--//--//--//--//--//--//--//--//--//--//

	/// <summary>
	/// инициализация игрового поля \ квадрат X на X
	/// </summary>
	/// <param name="CountCellOnSideWindow">колличество клеток на сторону </param>
	/// <param name="WindowHeight">высота окна</param>
	/// <param name="PathToEmptyImage">путь до пустой текстуры</param>
	FigureLocation(size_t CountCellOnLengthWindow, size_t CountCellOnHeightWindow,  int WindowHeight, path PathToEmptyImage, path PathToEmptyTextureEdge , float precentSizeFigure);

	/// <summary>
	/// метод расположения фигуры на поле
	/// </summary>
	/// <param name="xPosition">позиция Х на которую будет установлена фигура</param>
	/// <param name="yPosition">позиция У на которую будет установлена фигура</param>
	/// <param name="NameFigure">название фигуры</param>
	/// <param name="Side">сторона игрока для фигуры</param>
	/// <param name="CurrentTextureFigure">пусть до текстуры фигуры</param>
	/// <returns>true - фигуры установлена</returns>
	bool setFigure(size_t XPosition, size_t Yposition, string ID_FIGURE, int SIDE, bool INVULNERABLE = false, bool IMPORTANT = false, vector<tuple<int, string, bool, bool, bool>> VECTOR_PROMOUTION = {});


	/// <summary>
	/// Добавить уникальную фигуру
	/// </summary>
	/// <param name="NewFigure">класс-наследник Figure</param>
	/// <param name="CurrentTextureFigure">текстура фигуры</param>
	/// <returns></returns>
	bool addUniqueFigure(shared_ptr<Figure> NewFigureOrheirs, path CurrentTextureFigure);
	








	//////////////////////////////  Текстуры фигуры  ///////////////////////////////////////////////////

	/// <summary>
	/// получаем указатель на "квадрат" (спрайт) фигуры, расположенной на позиции Х\У
	/// </summary>
	/// <param name="xPosition">позиция Х фигуры</param>
	/// <param name="yPosition">позиция У фигуры</param>
	/// <returns>указатель на RectangleShape  фигуры</returns>
	const RectangleShape& getRectangleShapeFigure(size_t XPosition, size_t Yposition);








	//////////////////////////////  информация о фигуре  ///////////////////////////////////////////////////

	/// <summary>
	/// Получаем название фигуры на позиции
	/// </summary>
	/// <param name="xPosition">позиция Х фигуры</param>
	/// <param name="yPosition">позиция У фигуры</param>
	/// <returns>название фигуры</returns>
	string getIDFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// Получаем сторону игрока фигуры
	/// </summary>
	/// <param name="xPosition">позиция Х фигуры</param>
	/// <param name="yPosition">позиция У фигуры</param>
	/// <returns>сторона игрока у фигуры</returns>
	int getSideFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// Получаем координаты фигуры по расположению на игровом поле
	/// </summary>
	/// <param name="Positon">позиция в окне</param>
	/// <returns>пара координатов X , Y </returns>
	pair<int, int> getPositionFigureWhenMousePressed(Vector2f Positon);


	/// <summary>
	/// Если есть выделеная фигура, получаем ее позицию x \ y 
	/// </summary>
	/// <returns></returns>
	pair<int, int> getPositionSelectFigure();


	/// <summary>
	/// Уязвима ли фигура на позиции
	/// </summary>
	bool getInvulnerableFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// важная ли фигура на указанной позиции? от нее может зависить исход боя
	/// </summary>
	bool getImportantFigure(size_t XPosition, size_t Yposition);






		
	//////////////////////////////  Взаимодействие с фигурой  ///////////////////////////////////////////////////

	/// <summary>
	/// передвижение выделенной фигуры на указанную позицию
	/// </summary>
	/// <param name="xPositionMove">позиция Х на которую нужно передвинуть</param>
	/// <param name="YPositionMove">позиция У на которую нужно передвинуть</param>
	/// <returns>true - фигуры передвинута</returns>
	bool moveSelectFigure (size_t XPositionMove, size_t YpositionMove);

	/// <summary>
	/// Выделить фигуру на позиции
	/// </summary>
	/// <param name="XPositionFigure">позиция Х фигуры</param>
	/// <param name="YpositionFigure">позиция У фигуры</param>
	/// <returns>true - если фигура на позиции есть и была выделена</returns>
	bool seletcFigure(size_t XPositionFigure, size_t YpositionFigure); 

	/// <summary>
	/// отменить выделение
	/// </summary>
	/// <param name="XPositionFigure">позиция Х фигуры</param>
	/// <param name="YpositionFigure">позиция У фигуры</param>
	/// <returns>true - если выделение снято</returns>
	bool unSeletcAllFigure();

	/// <summary>
	/// Есть ли хоть одна выделеная фигура?
	/// </summary>
	/// <returns>true - если фигура выделена</returns>
	bool figuresSelectedOrNot();

	/// <summary>
	/// получаем вектор доступных ходов для выделенной фигуры
	/// </summary>
	/// <returns></returns>
	vector<pair<size_t, size_t>> getAvailableMovesForFigure(size_t XPositionFigure, size_t YpositionFigure);


	/// <summary>
	/// доступно ли какое-либо превращение для фигуры на указанной позиции // обычно используется сразу после передвижения фигуры
	/// </summary>
	/// <param name="XPositionFigure"></param>
	/// <param name="YpositionFigure"></param>
	/// <returns>true - если доступно </returns>
	bool promoutionFigureOnPosition(size_t XPositionFigure, size_t YpositionFigure);

	
	/// <summary>
	/// Превратиться в выбранную фигуру если доступно
	/// </summary>
	/// <param name="SIDE"></param>
	/// <param name="ID_Figure"></param>
	/// <param name="INVULNERABLE"></param>
	/// <param name="IMPORTANT"></param>
	/// <returns>true - превращение выполнено</returns>
	bool PromoutionSelectFigure(int SIDE, string ID_Figure, bool INVULNERABLE, bool IMPORTANT, bool PROMOUTION);






	//////////////////////////////  Взаимодействие с игровым полем фигур  ///////////////////////////////////////////////////

	/// <summary>
	/// обновить вектор с расположение фигурами на игровом поле
	/// </summary>
	void updateVectorLocationFigure();


	/// <summary>
	/// Получить вектор с расположением фигур на игровом поле
	/// </summary>
	/// <returns></returns>
	vector<vector<tuple<int, string, bool, bool, bool>>> getVectorLocationFigure();

	/// <summary>
	/// проверить какие другие фигуры могут угрожать фигуре на указанной позиции || 
	/// работает с так же с фиктивным VectorLocationFigure
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <param name="vectorLocationFigure"></param>
	/// <returns>позиции фигур Х \ У</returns>
	vector<pair<size_t, size_t>> checkThreatFigure(size_t XPositionOnVectorLocationFigure, size_t YpositionOnVectorLocationFigure, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure);




	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойтвам позция X \ Y
	/// </summary>
	/// <param name="ID_Figure"></param>
	/// <param name="SIDE"></param>
	/// <param name="INVULNERABLE"></param>
	/// <param name="IMPORTANT"></param>
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	vector<pair<size_t, size_t>> getPositionFigure(int SIDE, string ID_Figure,  bool INVULNERABLE, bool IMPORTANT, bool PROMOUTION);

	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойтвам позция X \ Y
	/// </summary>
	/// <param name="ID_Figure"></param>
	/// <param name="SIDE"></param>
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	vector<pair<size_t, size_t>> getPositionFigure(int SIDE, string ID_Figure);

	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойтвам позция X \ Y
	/// </summary>
	/// <param name="SIDE"></param>
	/// <param name="_INVULNERABLE_or_IMPORTANT_or_PROMOUTION_">INVULNERABLE или IMPORTANT или PROMOUTION</param>
	/// <param name="_I_M_P_">к чему относится указанный bool \\ I - INVULNERABLE \\ M - IMPORTANT \\  P - PROMOUTION</param> 
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	vector<pair<size_t, size_t>> getPositionsFigure(int SIDE, bool _INVULNERABLE_or_IMPORTANT_or_PROMOUTION_, char _I_M_P_);

	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойтвам позция X \ Y
	/// </summary>
	/// <param name="SIDE"></param>
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	vector<pair<size_t, size_t>> getPositionFigure(int SIDE);





	
	/// <summary>
	/// поставлен ли мат указанной фигуре?
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <param name="vectorLocationFigure"></param>
	/// <returns></returns>
	bool checkmateForFigure(size_t XPosition, size_t Yposition, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure );




	/// <summary>
	/// получаем позиции других фигур, которые могут защитить ( от мата или взятия ) указанную фигуру
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <param name="vectorLocationFigure"></param>
	/// <returns></returns>
	vector<pair<size_t, size_t>> figureCanProtectenCheckmateForFigure(size_t XPosition, size_t Yposition, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







	//--//--//--//--//--//--//--//     ДЛЯ Уникальных ФИГУР   //--//--//--//--//--//--//--//--//--//--//--//

	/// <summary>
	/// Получить ID уникальной фигуры с поля уникальных фигур
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	string getIDUniqueFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// Получить Сторону у уникальной фигуры
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	int getSideUniqueFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// получить "текстуру" поля уникальных фигур
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	const RectangleShape& getRectangleShapeUniqueFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// выделить фигуру на поле уникальных фигур
	/// </summary>
	/// <param name="XPositionFigure"></param>
	/// <param name="YPositionFigure"></param>
	/// <returns></returns>
	bool seletcUniqueFigureForPromoution(size_t XPositionFigure, size_t YpositionFigure);

	/// <summary>
	/// отменить выделение всех фигур на поле уникальных фигур
	/// </summary>
	/// <returns></returns>
	bool unSeletcUniqueFigure();


	/// <summary>
	/// получить позицию фигуры, информация с поле уникальных фигур
	/// </summary>
	/// <param name="PositonMouse"></param>
	/// <returns></returns>
	pair<int, int> getPositionUniqueFigureWhenMousePressed(Vector2f PositonMouse);

	/// <summary>
	/// Уязвима ли фигура на поле уникальных фигур
	/// </summary>
	bool getInvulnerableUniqueFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// важная ли фигура, информация с поле уникальных фигур
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	bool getImportantUniqueFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// может ли фигура превращаться? информация с поле уникальных фигур
	/// </summary>
	/// <param name="xPosition"></param>
	/// <param name="yPosition"></param>
	/// <returns></returns>
	bool getPromoutionUniqueFigure(size_t XPosition, size_t Yposition);
};
