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
	
	vector< vector< shared_ptr<Figure>>>   LocationClassFigure;
	vector< vector< shared_ptr<Texture>>>  LocationTexture;
	vector< vector< RectangleShape >>      LocationRectangleShape;
	
	//--//--//--//--//--//--//--//     ДЛЯ УНИКАЛЬНЫХ ФИГУР   //--//--//--//--//--//--//--//--//--//--//

	vector<shared_ptr<Figure>>				   UniqueFigureLocationClassFigure;
	vector<shared_ptr<Texture>>				   UniqueFigureLocationTexture;
	vector<vector<pair<size_t, RectangleShape>>>  UniqueFigureLocationRectangleShape;


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
	vector<vector<tuple<int, string, bool, bool, bool>>> VectorLocationFigure;
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// колличество клеток в 1 ряду
	/// </summary>
	size_t CountCellOnXPosition;


	/// <summary>
	/// колличество рядов
	/// </summary>
	size_t CountCellOnYPosition;

	/// <summary>
	/// размер одной клетки
	/// </summary>
	float SizeCell;

	/// <summary>
	///  процент размера одной клетки от максимального размера SizeCell
	/// </summary>
	float PrecentSizeFigure;

	/// <summary>
	/// размер клетки фигуры, расчитывается от процента Precent
	/// </summary>
	float SizeRectangInCell;

	/// <summary>
	/// позиция клетки фигуры
	/// </summary>
	float PositionRectangInCell;
	
	/// <summary>
	/// выделить можно только одну фигуру, поэтому если выделили = true;
	/// </summary>
	bool SelectFigure = false;

	/// <summary>
	/// координаты выделенной фигуры Х \ У 
	/// </summary>
	pair<int, int> PositionSelectFigure = make_pair(0, 0);

	/// <summary>
	/// номер-исключение используется в PositionFigure() и GetPositionFigure(), чтобы отбросить условия
	/// </summary>
	int NUM_exception = -228322999;

	///////////////////////////////////////////////////////////////////////////////////////////


	/// <summary>
	/// получаем итератор в векторах уникальных классов фигур и текстур, по позиции
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <returns></returns>
	int GetIteratorUniqueFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// получаем итератор в векторах уникальных классов фигур и текстур, по параметрам
	/// </summary>
	/// <param name="SIDE"></param>
	/// <param name="ID_FIGURE"></param>
	/// <param name="INVULNERABLE"></param>
	/// <param name="IMPORTANT"></param>
	/// <param name="PROMOUTION"></param>
	/// <returns></returns>
	int GetIteratorUniqueFigure(int SIDE, string ID_FIGURE, bool INVULNERABLE, bool IMPORTANT, bool PROMOUTION);

	
	/// <summary>
	/// проверяем доступен ли ход на указанные координаты
	/// </summary>
	/// <param name="XPositionCurrent"></param>
	/// <param name="YPositionCurrent"></param>
	/// <param name="XPositionMove"></param>
	/// <param name="YPositionMove"></param>
	/// <param name="VectorLocationFigure"></param>
	/// <returns></returns>
	bool CheckMoveForFigure(size_t XPositionCurrent, size_t YpositionCurrent, size_t XPositionMove, size_t YpositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);


	/// <summary>
	/// найти позиции фигур
	/// </summary>
	/// <param name="ID_Figure"></param>
	/// <param name="SIDE"></param>
	/// <param name="INVULNERABLE"></param>
	/// <param name="IMPORTANT"></param>
	/// <returns></returns>
	vector<pair<size_t, size_t>> PositionFigure(int SIDE, string ID_Figure, int INVULNERABLE, int IMPORTANT, int PROMOUTION);


	///////////////////////////////////////////////////////////////////////////////////////////

public:


	//--//--//--//--//--//--//--//   ДЛЯ ФИГУР НА ДОСКЕ  //--//--//--//--//--//--//--//--//--//--//--//

	/// <summary>
	/// инициализация игрового поля \ квадрат X на X
	/// </summary>
	/// <param name="CountCellOnSideWindow">колличество клеток на сторону </param>
	/// <param name="WindowHeight">высота окна</param>
	/// <param name="PathToEmptyImage">путь до пустой текстуры</param>
	FigureLocation(size_t CountCellOnLengthWindow, size_t CountCellOnHeightWindow,  int WindowHeight, path PathToEmptyImage, path PathToEmptyTextureEdge , float PrecentSizeFigure);

	/// <summary>
	/// метод расположения фигуры на поле
	/// </summary>
	/// <param name="XPosition">позиция Х на которую будет установлена фигура</param>
	/// <param name="Yposition">позиция У на которую будет установлена фигура</param>
	/// <param name="NameFigure">название фигуры</param>
	/// <param name="Side">сторона игрока для фигуры</param>
	/// <param name="CurrentTextureFigure">пусть до текстуры фигуры</param>
	/// <returns>true - фигуры установлена</returns>
	bool SetFigure(size_t XPosition, size_t Yposition, string ID_FIGURE, int SIDE, bool INVULNERABLE = false, bool IMPORTANT = false, vector<tuple<int, string, bool, bool, bool>> VectorPROMOUTION = {});


	/// <summary>
	/// Добавить уникальную фигуру
	/// </summary>
	/// <param name="NewFigure">класс-наследник Figure</param>
	/// <param name="CurrentTextureFigure">текстура фигуры</param>
	/// <returns></returns>
	bool AddUniqueFigure(shared_ptr<Figure> NewFigureOrheirs, path CurrentTextureFigure);
	








	//////////////////////////////  Текстуры фигуры  ///////////////////////////////////////////////////

	/// <summary>
	/// получаем указатель на "квадрат" (спрайт) фигуры, расположенной на позиции Х\У
	/// </summary>
	/// <param name="XPosition">позиция Х фигуры</param>
	/// <param name="Yposition">позиция У фигуры</param>
	/// <returns>указатель на RectangleShape  фигуры</returns>
	const RectangleShape& GetRectangleShapeFigure(size_t XPosition, size_t Yposition);








	//////////////////////////////  информация о фигуре  ///////////////////////////////////////////////////

	/// <summary>
	/// Получаем название фигуры на позиции
	/// </summary>
	/// <param name="XPosition">позиция Х фигуры</param>
	/// <param name="Yposition">позиция У фигуры</param>
	/// <returns>название фигуры</returns>
	string GetIDFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// Получаем сторону игрока фигуры
	/// </summary>
	/// <param name="XPosition">позиция Х фигуры</param>
	/// <param name="Yposition">позиция У фигуры</param>
	/// <returns>сторона игрока у фигуры</returns>
	int GetSideFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// Получаем координаты фигуры по расположению на игровом поле
	/// </summary>
	/// <param name="Positon">позиция в окне</param>
	/// <returns>пара координатов X , Y </returns>
	pair<int, int> GetPositionFigureWhenMousePressed(Vector2f Positon);


	/// <summary>
	/// Если есть выделеная фигура, получаем ее позицию x \ y 
	/// </summary>
	/// <returns></returns>
	pair<int, int> GetPositionSelectFigure();


	/// <summary>
	/// Уязвима ли фигура на позиции
	/// </summary>
	bool GetInvulnerableFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// важная ли фигура на указанной позиции? от нее может зависить исход боя
	/// </summary>
	bool GetImportantFigure(size_t XPosition, size_t Yposition);






		
	//////////////////////////////  Взаимодействие с фигурой  ///////////////////////////////////////////////////

	/// <summary>
	/// передвижение выделенной фигуры на указанную позицию
	/// </summary>
	/// <param name="XPositionMove">позиция Х на которую нужно передвинуть</param>
	/// <param name="YPositionMove">позиция У на которую нужно передвинуть</param>
	/// <returns>true - фигуры передвинута</returns>
	bool MoveSelectFigure (size_t XPositionMove, size_t YpositionMove);

	/// <summary>
	/// Выделить фигуру на позиции
	/// </summary>
	/// <param name="XPositionFigure">позиция Х фигуры</param>
	/// <param name="YpositionFigure">позиция У фигуры</param>
	/// <returns>true - если фигура на позиции есть и была выделена</returns>
	bool SeletcFigure(size_t XPositionFigure, size_t YpositionFigure); 

	/// <summary>
	/// отменить выделение
	/// </summary>
	/// <param name="XPositionFigure">позиция Х фигуры</param>
	/// <param name="YpositionFigure">позиция У фигуры</param>
	/// <returns>true - если выделение снято</returns>
	bool UnSeletcAllFigure();

	/// <summary>
	/// Есть ли хоть одна выделеная фигура?
	/// </summary>
	/// <returns>true - если фигура выделена</returns>
	bool FiguresSelectedOrNot();

	/// <summary>
	/// получаем вектор доступных ходов для выделенной фигуры
	/// </summary>
	/// <returns></returns>
	vector<pair<size_t, size_t>> GetAvailableMovesForFigure(size_t XPositionFigure, size_t YpositionFigure);


	/// <summary>
	/// доступно ли какое-либо превращение для фигуры на указанной позиции // обычно используется сразу после передвижения фигуры
	/// </summary>
	/// <param name="XPositionFigure"></param>
	/// <param name="YpositionFigure"></param>
	/// <returns>true - если доступно </returns>
	bool PromoutionFigureOnPosition(size_t XPositionFigure, size_t YpositionFigure);

	
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
	void UpdateVectorLocationFigure();


	/// <summary>
	/// Получить вектор с расположением фигур на игровом поле
	/// </summary>
	/// <returns></returns>
	vector<vector<tuple<int, string, bool, bool, bool>>> GetVectorLocationFigure();

	/// <summary>
	/// проверить какие другие фигуры могут угрожать фигуре на указанной позиции || 
	/// работает с так же с фиктивным VectorLocationFigure
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <param name="VectorLocationFigure"></param>
	/// <returns>позиции фигур Х \ У</returns>
	vector<pair<size_t, size_t>> CheckThreatFigure(size_t XPositionOnVectorLocationFigure, size_t YpositionOnVectorLocationFigure, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);




	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойтвам позция X \ Y
	/// </summary>
	/// <param name="ID_Figure"></param>
	/// <param name="SIDE"></param>
	/// <param name="INVULNERABLE"></param>
	/// <param name="IMPORTANT"></param>
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	vector<pair<size_t, size_t>> GetPositionFigure(int SIDE, string ID_Figure,  bool INVULNERABLE, bool IMPORTANT, bool PROMOUTION);

	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойтвам позция X \ Y
	/// </summary>
	/// <param name="ID_Figure"></param>
	/// <param name="SIDE"></param>
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	vector<pair<size_t, size_t>> GetPositionFigure(int SIDE, string ID_Figure);

	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойтвам позция X \ Y
	/// </summary>
	/// <param name="SIDE"></param>
	/// <param name="_INVULNERABLE_or_IMPORTANT_or_PROMOUTION_">INVULNERABLE или IMPORTANT или PROMOUTION</param>
	/// <param name="_I_M_P_">к чему относится указанный bool \\ I - INVULNERABLE \\ M - IMPORTANT \\  P - PROMOUTION</param> 
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	vector<pair<size_t, size_t>> GetPositionsFigure(int SIDE, bool _INVULNERABLE_or_IMPORTANT_or_PROMOUTION_, char _I_M_P_);

	/// <summary>
	/// получить позицию фигуры (или фигур если их несколько) по свойтвам позция X \ Y
	/// </summary>
	/// <param name="SIDE"></param>
	/// <returns>возвращает пустой вектор если фигур не найдено</returns>
	vector<pair<size_t, size_t>> GetPositionFigure(int SIDE);





	
	/// <summary>
	/// поставлен ли мат указанной фигуре?
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <param name="VectorLocationFigure"></param>
	/// <returns></returns>
	bool CheckmateForFigure(size_t XPosition, size_t Yposition, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure );




	/// <summary>
	/// получаем позиции других фигур, которые могут защитить ( от мата или взятия ) указанную фигуру
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <param name="VectorLocationFigure"></param>
	/// <returns></returns>
	vector<pair<size_t, size_t>> FigureCanProtectenCheckmateForFigure(size_t XPosition, size_t Yposition, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







	//--//--//--//--//--//--//--//     ДЛЯ Уникальных ФИГУР   //--//--//--//--//--//--//--//--//--//--//--//

	/// <summary>
	/// Получить ID уникальной фигуры с поля уникальных фигур
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <returns></returns>
	string GetIDUniqueFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// Получить Сторону у уникальной фигуры
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <returns></returns>
	int GetSideUniqueFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// получить "текстуру" поля уникальных фигур
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <returns></returns>
	const RectangleShape& GetRectangleShapeUniqueFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// выделить фигуру на поле уникальных фигур
	/// </summary>
	/// <param name="XPositionFigure"></param>
	/// <param name="YPositionFigure"></param>
	/// <returns></returns>
	bool SeletcUniqueFigureForPromoution(size_t XPositionFigure, size_t YpositionFigure);

	/// <summary>
	/// отменить выделение всех фигур на поле уникальных фигур
	/// </summary>
	/// <returns></returns>
	bool UnSeletcUniqueFigure();


	/// <summary>
	/// получить позицию фигуры, информация с поле уникальных фигур
	/// </summary>
	/// <param name="PositonMouse"></param>
	/// <returns></returns>
	pair<int, int> GetPositionUniqueFigureWhenMousePressed(Vector2f PositonMouse);

	/// <summary>
	/// Уязвима ли фигура на поле уникальных фигур
	/// </summary>
	bool GetInvulnerableUniqueFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// важная ли фигура, информация с поле уникальных фигур
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <returns></returns>
	bool GetImportantUniqueFigure(size_t XPosition, size_t Yposition);

	/// <summary>
	/// может ли фигура превращаться? информация с поле уникальных фигур
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <returns></returns>
	bool GetPromoutionUniqueFigure(size_t XPosition, size_t Yposition);
};
