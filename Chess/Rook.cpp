#include "Rook.h"
static bool checkCell(size_t xPos, size_t yPos, int side, vector<pair<size_t, size_t>>& result, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure);

string Rook::set_ID_FIGURE()
{
	return "Rook";
}

vector<pair<size_t, size_t>> Rook::getMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{

	size_t row = vectorLocationFigure.size();
	size_t col = vectorLocationFigure[0].size();

	vector<pair<size_t, size_t>> result;

	int side = this->get_SIDE();

	//проходимся по горизонтали

	// вправо от фигуры (ладьи)
	for (size_t xPos = xPositionCurrent + 1; xPos < col; xPos++)
	{
		if (!checkCell(xPos, yPositionCurrent, side, result, vectorLocationFigure))	{	break;	}
	}
	// влево от фигуры
	for (size_t xPos = xPositionCurrent - 1; xPos > 0; xPos--)
	{
		if (!checkCell(xPos, yPositionCurrent, side, result, vectorLocationFigure))	{	break;	}
	}
	//вверх от фигуры
	for (size_t yPos = yPositionCurrent - 1; yPos > 0; yPos--)
	{
		if (!checkCell(xPositionCurrent, yPos, side, result, vectorLocationFigure)) {	break; }
	}
	//вниз от фигуры
	for (size_t yPos = yPositionCurrent + 1; yPos < row; yPos++)
	{
		if (!checkCell(xPositionCurrent, yPos, side, result, vectorLocationFigure))	{	break;	}
	}
	return result;
}
static bool checkCell(size_t xPos, size_t yPos, int side, vector<pair<size_t, size_t>>& result, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	// продолжаем пока не встретим свою или чужую фигуру
	if (get<0>(vectorLocationFigure[yPos][xPos]) == 0)
	{
		result.push_back(make_pair(xPos, yPos));
		return true;

	}
	// если встретим фигуру противника добавляем возможность взятия и выходим
	else if (get<0>(vectorLocationFigure[yPos][xPos]) != side && get<0>(vectorLocationFigure[yPos][xPos]) > 0)
	{
		result.push_back(make_pair(xPos, yPos));
		return false;
	}
	// иначе предполагаем что встретили фигуру своей стороны и та же выходим
	else
	{
		return false;
	}
}

bool Rook::checkMove(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	vector<pair<size_t, size_t>> vMove = getMoveForFigure(xPositionCurrent, yPositionCurrent, vectorLocationFigure);

	for (const auto& move : vMove)
	{
		if (move.first == xPositionMove && move.second == yPositionMove)
		{
			return true;
		}
	}
	return false;
}

bool Rook::getPossibilityPromotion(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	return false;
}
