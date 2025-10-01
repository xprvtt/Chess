#include "Bishop.h"

static bool checkCell(size_t xPos, size_t yPos, int side, vector<pair<size_t, size_t>>& result, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure);



string Bishop::set_ID_FIGURE()
{
	return "Bishop";
}

vector<pair<size_t, size_t>> Bishop::getMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	vector<pair<size_t, size_t>> result;

	size_t row = vectorLocationFigure.size();
	size_t col = vectorLocationFigure[0].size(); 

	int side = this->get_SIDE();




	//// по диагонали 

	//в правый низ от фигуры
	for (size_t yPos = yPositionCurrent + 1, xPos = xPositionCurrent + 1; yPos < row || xPos < col; yPos++, xPos++)
	{
		if (!checkCell(xPos, yPos, side, result, vectorLocationFigure))	{	break;	}
	}
	// в правый верх от фигуры
	for (size_t yPos = yPositionCurrent - 1, xPos = xPositionCurrent + 1; yPos > 0 || xPos < col; yPos--, xPos++)
	{
		if (!checkCell(xPos, yPos, side, result, vectorLocationFigure))	{	break;	}
	}
	//левый верх от фигуры 
	for (size_t yPos = yPositionCurrent - 1, xPos = xPositionCurrent - 1; yPos > 0 || xPos > 0; yPos--, xPos--)
	{
		if (!checkCell(xPos, yPos, side, result, vectorLocationFigure))	{	break;	}
	}
	//левый низ от фигуры
	for (size_t yPos = yPositionCurrent + 1, xPos = xPositionCurrent - 1; yPos < row || xPos > 0; yPos++, xPos--)
	{
		if (!checkCell(xPos, yPos, side, result, vectorLocationFigure))	{	break;	}
	}
	return result;
}

static bool checkCell(size_t xPos, size_t yPos, int side,  vector<pair<size_t, size_t>>& result, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
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
	// иначе предполагаем что встретили фигуру своей стороны и так же выходим
	else
	{
		return false;
	}
}

bool Bishop::checkMove(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
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

bool Bishop::getPossibilityPromotion(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	return false;
}
