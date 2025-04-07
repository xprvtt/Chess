#include "Queen.h"
static bool CheckCell(size_t XPos, size_t YPos, int Side, vector<pair<size_t, size_t>>& result, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);

string Queen::Set_ID_FIGURE()
{
	return "Queen";
}

vector<pair<size_t, size_t>> Queen::GetMoveForFigure(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	size_t Row = VectorLocationFigure.size();
	size_t Col = VectorLocationFigure[0].size();

	//изначально считаем что ходов доступных нет
	vector<pair<size_t, size_t>> result;


	int Side = GetSIDE();
	// вправо от фигуры
	for (size_t XPos = XPositionCurrent + 1; XPos < Col; XPos++)
	{
		if (!CheckCell(XPos, YPositionCurrent, Side, result, VectorLocationFigure))	{	break;	}
	}
	// влево от фигуры
	for (size_t XPos = XPositionCurrent - 1; XPos > 0; XPos--)
	{
		if (!CheckCell(XPos, YPositionCurrent, Side, result, VectorLocationFigure))	{	break;	}
	}
	//вверх от фигуры
	for (size_t YPos = YPositionCurrent - 1; YPos > 0; YPos--)
	{
		if (!CheckCell(XPositionCurrent, YPos, Side, result, VectorLocationFigure))	{	break;	}
	}
	//вниз от фигуры
	for (size_t YPos = YPositionCurrent + 1; YPos < Row; YPos++)
	{
		if (!CheckCell(XPositionCurrent, YPos, Side, result, VectorLocationFigure))	{	break;	}
	}
	//// по диагонали

	//в правый низ от фигуры
	for (size_t YPos = YPositionCurrent + 1, XPos = XPositionCurrent + 1; YPos < Row || XPos < Col; YPos++, XPos++)
	{
		if (!CheckCell(XPos, YPos, Side, result, VectorLocationFigure))	{	break;	}
	}
	// в правый верх от фигуры
	for (size_t YPos = YPositionCurrent - 1, XPos = XPositionCurrent + 1; YPos > 0 || XPos < Col; YPos--, XPos++)
	{
		if (!CheckCell(XPos, YPos, Side, result, VectorLocationFigure))	{	break;	}
	}
	//левый верх от фигуры
	for (size_t YPos = YPositionCurrent - 1, XPos = XPositionCurrent - 1; YPos > 0 || XPos > 0; YPos--, XPos--)
	{
		if (!CheckCell(XPos, YPos, Side, result, VectorLocationFigure)) {	break;	}
	}
	//левый низ от фигуры
	for (size_t YPos = YPositionCurrent + 1, XPos = XPositionCurrent - 1; YPos < Row || XPos > 0; YPos++, XPos--)
	{
		if (!CheckCell(XPos, YPos, Side, result, VectorLocationFigure))	{	break;	}
	}

	return result;
}

static bool CheckCell(size_t XPos, size_t YPos, int Side, vector<pair<size_t, size_t>>& result, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	// продолжаем пока не встретим свою или чужую фигуру
	if (get<0>(VectorLocationFigure[YPos][XPos]) == 0)
	{
		result.push_back(make_pair(XPos, YPos));
		return true;

	}
	// если встретим фигуру противника добавляем возможность взятия и выходим
	else if (get<0>(VectorLocationFigure[YPos][XPos]) != Side && get<0>(VectorLocationFigure[YPos][XPos]) > 0)
	{
		result.push_back(make_pair(XPos, YPos));
		return false;
	}
	// иначе предполагаем что встретили фигуру своей стороны и та же выходим
	else
	{
		return false;
	}
}

bool Queen::CheckMove(size_t XPositionCurrent, size_t YPositionCurrent, size_t XPositionMove, size_t YPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	vector<pair<size_t, size_t>> VMove = GetMoveForFigure(XPositionCurrent, YPositionCurrent, VectorLocationFigure);

	for (const auto& Move : VMove)
	{
		if (Move.first == XPositionMove && Move.second == YPositionMove)
		{
			return true;
		}
	} 
	return false;
}

bool Queen::GetPossibilityPromotion(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	return false;
}
