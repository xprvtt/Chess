#include "Pawn.h"

static bool customCheckMoveSideTop(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure);
static bool customCheckMoveSideDown(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure);

static vector<pair<size_t, size_t>> availableMoveForFigureSideTop(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);
static vector<pair<size_t, size_t>> availableMoveForFigureSideDown(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);

static bool possibilityPromotionSideTop(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure);
static bool possibilityPromotionSideDown(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure);














//////////////////////////////////////////////////////////////////////////////////////////////////
//
// vector<vector<tuple<int, string, bool, bool, bool>>> VectorIntLocationFigure для int должен имееть структуру => 	  
// -1 == границы															  
// 0 == пустая клетка 														  
// 1+ == сторона игрока	 													  
//
//////////////////////////////////////////////////////////////////////////////////////////////////

//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//


bool Pawn::checkMove(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{

	switch (get_SIDE())
	{
	case 1:
		return customCheckMoveSideTop(xPositionCurrent, yPositionCurrent, xPositionMove, yPositionMove, vectorLocationFigure);
	case 2:
		return customCheckMoveSideDown(xPositionCurrent, yPositionCurrent, xPositionMove, yPositionMove, vectorLocationFigure);

	default:
		OutputLog("Игрок не определен проверьте линию -> Figure -> Pawn -> CheckMove() -> case");
		return false;
	}
}
static bool customCheckMoveSideTop(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{

	vector<pair<size_t, size_t>> vMove = availableMoveForFigureSideTop(xPositionCurrent, yPositionCurrent, vectorLocationFigure);

	for (const auto& move : vMove)
	{
		if (move.first == xPositionMove && move.second == yPositionMove)
		{
			return true;
		}
	}
	return false;
}

static bool customCheckMoveSideDown(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	vector<pair<size_t, size_t>> vMove = availableMoveForFigureSideDown(xPositionCurrent, yPositionCurrent, vectorLocationFigure);

	for (const auto& move : vMove)
	{
		if (move.first == xPositionMove && move.second == yPositionMove)
		{
			return true;
		}
	}
	return false;
}

//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//























//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//

vector<pair<size_t, size_t>> Pawn::getMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{

	// движение пешки в зависимости от стороны игрока
	switch (get_SIDE())
	{
	case 1:
		return availableMoveForFigureSideTop(xPositionCurrent, yPositionCurrent, vectorLocationFigure);
	case 2:
		return availableMoveForFigureSideDown(xPositionCurrent, yPositionCurrent, vectorLocationFigure);


	default:
		OutputLog("Игрок не определен проверьте линию -> Figure -> Pawn -> GetMoveForFigure() -> case");
		return vector<pair<size_t, size_t>>();
	}
}



static vector<pair<size_t, size_t>> availableMoveForFigureSideTop(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{

	/// ИГРОК 1 НИЖНИЙ БЕЛЫЙ 

	size_t row = vectorLocationFigure.size();
	size_t col = vectorLocationFigure[0].size();

	vector<pair<size_t, size_t>> result;


	// просчитываем ход на пустую клетку
	 
	//если впереди пешки ничего нет то ход доступен
	if (get<0>(vectorLocationFigure[yPositionCurrent - 1][xPositionCurrent]) == 0)
	{
		result.push_back(make_pair(xPositionCurrent, yPositionCurrent - 1));

		//высчитываем возможную начальную позицию пешки (2 ряд для игрока) тогда можно сходить еще на 1 клетку вперед, т.е. сразу на 2
		if (yPositionCurrent == row - 3 && get<0>(vectorLocationFigure[yPositionCurrent - 2][xPositionCurrent]) == 0)
		{
			// добавляем возможный ход на 2 клетки вперед
			result.push_back(make_pair(xPositionCurrent, yPositionCurrent - 2));
		}
	}

	// проситываем возможность взятие фигуры ПРОТИВНИКА справа и слева ИГРОКА 2
	// фигура на клетке не должна быть пустой ( SIDE 0 ) не должна быть краем ( SIDE -1 ) и нельзя взять свою же фигуру 
	if (get<0>(vectorLocationFigure[yPositionCurrent - 1][xPositionCurrent - 1]) > 0 && get<0>(vectorLocationFigure[yPositionCurrent - 1][xPositionCurrent - 1]) != get<0>(vectorLocationFigure[yPositionCurrent][xPositionCurrent]))
	{
		result.push_back(make_pair(xPositionCurrent - 1, yPositionCurrent - 1));
	}
	if (get<0>(vectorLocationFigure[yPositionCurrent - 1][xPositionCurrent + 1]) > 0 && get<0>(vectorLocationFigure[yPositionCurrent - 1][xPositionCurrent + 1]) != get<0>(vectorLocationFigure[yPositionCurrent][xPositionCurrent]))
	{
		result.push_back(make_pair(xPositionCurrent + 1, yPositionCurrent - 1));
	}
	return result;
}





static vector<pair<size_t, size_t>> availableMoveForFigureSideDown(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	/// ИГРОК 2 ВЕРХНИЙ ЧЕРНЫЙ
	size_t row = vectorLocationFigure.size();
	size_t col = vectorLocationFigure[0].size();

	vector<pair<size_t, size_t>> result;

	//если впереди пешки ничего нет
	if (get<0>(vectorLocationFigure[yPositionCurrent + 1][xPositionCurrent]) == 0)
	{
		result.push_back(make_pair(xPositionCurrent, yPositionCurrent + 1));

		//высчитываем возможную начальную позицию пешки (2 ряд для игрока) тогда можно сходить еще на 1 клетку вперед если она не занята
		if (yPositionCurrent == 2 && get<0>(vectorLocationFigure[yPositionCurrent + 2][xPositionCurrent]) == 0)
		{
			// добавляем возможный ход на 2 клетки вперед
			result.push_back(make_pair(xPositionCurrent, yPositionCurrent + 2));
		}
	}
	// проситываем возможность взятие фигуры ПРОТИВНИКА справа и слева ИГРОКА 2
	// фигура на клетке не должна быть пустой ( SIDE 0 ) не должна быть краем ( SIDE -1 ) и нельзя взять свою же фигуру 
	if (get<0>(vectorLocationFigure[yPositionCurrent + 1][xPositionCurrent - 1]) > 0 && get<0>(vectorLocationFigure[yPositionCurrent + 1][xPositionCurrent - 1]) != get<0>(vectorLocationFigure[yPositionCurrent][xPositionCurrent]))
	{
		result.push_back(make_pair(xPositionCurrent - 1, yPositionCurrent + 1));
	}
	if (get<0>(vectorLocationFigure[yPositionCurrent + 1][xPositionCurrent + 1]) > 0 && get<0>(vectorLocationFigure[yPositionCurrent + 1][xPositionCurrent + 1]) != get<0>(vectorLocationFigure[yPositionCurrent][xPositionCurrent]))
	{ 
		result.push_back(make_pair(xPositionCurrent + 1, yPositionCurrent + 1));
	}
	return result;
}
//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//













//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//
bool Pawn::getPossibilityPromotion(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	switch (get_SIDE())
	{
	case 1:
		return possibilityPromotionSideTop(xPositionCurrent, yPositionCurrent, vectorLocationFigure);
	case 2:
		return possibilityPromotionSideDown(xPositionCurrent, yPositionCurrent, vectorLocationFigure);

	default:
		OutputLog("Игрок не определен проверьте линию -> Figure -> Pawn -> GetPossibilityPromotion() -> case");
		return false;
	}
}


static bool possibilityPromotionSideTop(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	/// игрок 1 белый нижний
	return yPositionCurrent == 1 ? true : false;
}


static bool possibilityPromotionSideDown(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	/// игрок 2 черный верхний
	return yPositionCurrent == vectorLocationFigure.size() - 2 ? true : false;
}
//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//
















//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//
string Pawn::set_ID_FIGURE()
{
	return "Pawn";
}
//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//

