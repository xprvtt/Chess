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


	//--//--//--//--//--//--//--//   ДЛЯ ФИГУР НА ДОСКЕ  //--//--//--//--//--//--//--//--//--//--//--//
	
	vector< vector< shared_ptr<Figure>>>   LocationClassFigure;
	vector< vector< shared_ptr<Texture>>>  LocationTexture;
	vector< vector< RectangleShape >>      LocationRectangleShape;
	
	//--//--//--//--//--//--//--//     ДЛЯ УНИКАЛЬНЫХ ФИГУР   //--//--//--//--//--//--//--//--//--//--//

	vector<shared_ptr<Figure>>				   UniqueFigureLocationClassFigure;
	vector<shared_ptr<Texture>>				   UniqueFigureLocationTexture;
	vector<vector<pair<int, RectangleShape>>>  UniqueFigureLocationRectangleShape;


	///////////////////////////////////////////////////////////////////////////////////////////////////



	////////////////////////////////////////////////////////////////////////////////
																				  //
	// vector<vector<int>> VectorIntLocationFigure должен имееть структуру => 	  //
	// -1 == границы															  //
	// 0 == пустая клетка 														  //
	// 1+ == сторона игрока														  //
																				  //
	////////////////////////////////////////////////////////////////////////////////
	
	vector<vector<pair<int, string>>> VectorLocationFigure;
	
	
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
	/// получаем итератор в векторах уникальных классов фигур и текстур
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <returns></returns>
	int GetIteratorUniqueFigure(int XPosition, int Yposition);

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
	bool SetFigure(int XPosition, int YPosition, string NameFigure_ID_Figure, int Side, bool invulnerable);


	/// <summary>
	/// Добавить уникальную фигуру
	/// </summary>
	/// <param name="NewFigure">класс-наследник Figure</param>
	/// <param name="CurrentTextureFigure">текстура фигуры</param>
	/// <returns></returns>
	bool AddUniqueFigure(shared_ptr<Figure> NewFigure, path CurrentTextureFigure);
	








	//////////////////////////////  Текстуры фигуры  ///////////////////////////////////////////////////

	/// <summary>
	/// получаем указатель на "квадрат" (спрайт) фигуры, расположенной на позиции Х\У
	/// </summary>
	/// <param name="XPosition">позиция Х фигуры</param>
	/// <param name="Yposition">позиция У фигуры</param>
	/// <returns>указатель на RectangleShape  фигуры</returns>
	const RectangleShape& GetRectangleShapeFigure(int XPosition, int Yposition);








	//////////////////////////////  информация о фигуре  ///////////////////////////////////////////////////

	/// <summary>
	/// Получаем название фигуры на позиции
	/// </summary>
	/// <param name="XPosition">позиция Х фигуры</param>
	/// <param name="Yposition">позиция У фигуры</param>
	/// <returns>название фигуры</returns>
	string GetIDFigure(int XPosition, int Yposition);

	/// <summary>
	/// Получаем сторону игрока фигуры
	/// </summary>
	/// <param name="XPosition">позиция Х фигуры</param>
	/// <param name="Yposition">позиция У фигуры</param>
	/// <returns>сторона игрока у фигуры</returns>
	int GetSideFigure(int XPosition, int Yposition);

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
	bool GetInvulnerableFigure(int XPosition, int Yposition);





		
	//////////////////////////////  Взаимодействие с фигурой  ///////////////////////////////////////////////////

	/// <summary>
	/// передвижение выделенной фигуры на указанную позицию
	/// </summary>
	/// <param name="XPositionFigure">текущая позиция Х фигуры</param>
	/// <param name="YpositionFigure">текущая позиция У фигуры</param>
	/// <param name="XPositionMove">позиция Х на которую нужно передвинуть</param>
	/// <param name="YPositionMove">позиция У на которую нужно передвинуть</param>
	/// <returns>true - фигуры передвинута</returns>
	bool MoveSelectFigure (int XPositionMove, int YPositionMove);

	/// <summary>
	/// Выделить фигуру на позиции
	/// </summary>
	/// <param name="XPositionFigure">позиция Х фигуры</param>
	/// <param name="YpositionFigure">позиция У фигуры</param>
	/// <returns>true - если фигура на позиции есть и была выделена</returns>
	bool SeletcFigure(int XPositionFigure, int YpositionFigure);

	/// <summary>
	/// отменить выделение
	/// </summary>
	/// <param name="XPositionFigure">позиция Х фигуры</param>
	/// <param name="YpositionFigure">позиция У фигуры</param>
	/// <returns>true - если выделение снято</returns>
	bool UnSeletcFigure();

	/// <summary>
	/// Есть ли хоть одна выделеная фигура?
	/// </summary>
	/// <returns>true - если фигура выделена</returns>
	bool FiguresSelectedOrNot();

	/// <summary>
	/// получаем вектор доступных ходов для выделенной фигуры
	/// </summary>
	/// <returns></returns>
	vector<vector<bool>> GetAvailableMovesForSelectFigure();


	/// <summary>
	/// доступно ли какое-либо превращение для фигуры на указанной позиции // обычно используется сразу после передвижения фигуры
	/// </summary>
	/// <param name="XPositionFigure"></param>
	/// <param name="YpositionFigure"></param>
	/// <returns>true - если доступно </returns>
	bool PromoutionFigureOnPosition(int XPositionFigure, int YpositionFigure);


	/// <summary>
	/// Превратиться в выбранную фигуру если доступно
	/// </summary>
	/// <param name="ID_Figure"></param>
	/// <returns></returns>
	bool PromoutionSelectFigure(string ID_Figure);





	//////////////////////////////  Взаимодействие с игровым полем фигур  ///////////////////////////////////////////////////

	/// <summary>
	/// обновить вектор с расположение фигурами на игровом поле
	/// </summary>
	void UpdateVectorIntLocationFigure();


	/// <summary>
	/// Получить вектор с расположением фигур на игровом поле
	/// </summary>
	/// <returns></returns>
	vector<vector<pair<int,string>>> GetVectorLocationFigure();







	//--//--//--//--//--//--//--//     ДЛЯ Уникальных ФИГУР   //--//--//--//--//--//--//--//--//--//--//--//

	/// <summary>
	/// Получить ID уникальной фигуры с поля уникальных фигур
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <returns></returns>
	string GetIDUniqueFigure(int XPosition, int Yposition);

	/// <summary>
	/// Получить Сторону у уникальной фигуры
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <returns></returns>
	int GetSideUniqueFigure(int XPosition, int Yposition);

	/// <summary>
	/// получить "текстуру" поля уникальных фигур
	/// </summary>
	/// <param name="XPosition"></param>
	/// <param name="Yposition"></param>
	/// <returns></returns>
	const RectangleShape& GetRectangleShapeUniqueFigure(int XPosition, int Yposition);

	/// <summary>
	/// выделить фигуру на поле уникальных фигур
	/// </summary>
	/// <param name="XPositionFigure"></param>
	/// <param name="YPositionFigure"></param>
	/// <returns></returns>
	bool SeletcUniqueFigureForPromoution(int XPositionFigure, int YPositionFigure);

	/// <summary>
	/// отменить выделение всех фигур на поле уникальных фигур
	/// </summary>
	/// <returns></returns>
	bool UnSeletcUniqueFigure();


	/// <summary>
	/// получить позицию фигуры, на поле уникальных фигур
	/// </summary>
	/// <param name="PositonMouse"></param>
	/// <returns></returns>
	pair<int, int> GetPositionUniqueFigureWhenMousePressed(Vector2f PositonMouse);

	/// <summary>
	/// Уязвима ли фигура на поле уникальных фигур
	/// </summary>
	bool GetInvulnerableUniqueFigure(int XPosition, int Yposition);


};
