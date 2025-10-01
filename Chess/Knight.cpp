#include "Knight.h"

string Knight::set_ID_FIGURE()
{
	return "Knight";
}

vector<pair<size_t, size_t>> Knight::getMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	vector<pair<size_t, size_t>> result;

	size_t row = vectorLocationFigure.size();
	size_t col = vectorLocationFigure[0].size();

	size_t xPos;
	size_t yPos;

	for (size_t count = 0; count < 8; count++)
	{

		switch (count)
		{
		case 0:
			xPos = xPositionCurrent - 2;
			yPos = yPositionCurrent - 1;
			break;
		case 1:
			xPos = xPositionCurrent - 1;
			yPos = yPositionCurrent - 2;
			break;
		case 2:
			xPos = xPositionCurrent + 1;
			yPos = yPositionCurrent - 2;
			break;
		case 3:
			xPos = xPositionCurrent + 2;
			yPos = yPositionCurrent - 1;
			break;
		case 4:
			xPos = xPositionCurrent + 2;
			yPos = yPositionCurrent + 1;
			break;
		case 5:
			xPos = xPositionCurrent + 1;
			yPos = yPositionCurrent + 2;
			break;
		case 6:
			xPos = xPositionCurrent - 1;
			yPos = yPositionCurrent + 2;
			break;
		case 7:
			xPos = xPositionCurrent - 2;
			yPos = yPositionCurrent + 1;
			break;

		default:
			break;
		}

		if (xPos >= col || yPos >= row || xPos < 0 || yPos < 0)
		{
			continue;
		}

		// пока не встретим свою или чужую фигуру 
		if (get<0>(vectorLocationFigure[yPos][xPos]) == 0)
		{
			result.push_back(make_pair(xPos, yPos));

		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (get<0>(vectorLocationFigure[yPos][xPos]) != get_SIDE() && get<0>(vectorLocationFigure[yPos][xPos]) > 0)
		{
			result.push_back(make_pair(xPos, yPos));
		}
		// иначе предполагаем что встретили фигуру своей стороны
	}
	return result;
}
 
bool Knight::checkMove(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
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

bool Knight::getPossibilityPromotion(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	return false;
}
