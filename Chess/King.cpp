#include "King.h"

string King::set_ID_FIGURE()
{
	return "King";
}

vector<pair<size_t, size_t>> King::getMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	vector<pair<size_t, size_t>> result;

	size_t yPos;
	size_t xPos;
	 
	for (size_t count = 0; count < 8; count++)
	{
		switch (count)
		{
		case 0:
			xPos = xPositionCurrent + 1;
			yPos = yPositionCurrent;
			break;
		case 1:
			//влево от фигуры
			xPos = xPositionCurrent - 1;
			yPos = yPositionCurrent;
			break;
		case 2:
			//вверх от фигуры
			xPos = xPositionCurrent;
			yPos = yPositionCurrent - 1;
			break;
		case 3:
			//вниз от фигуры
			xPos = xPositionCurrent;
			yPos = yPositionCurrent + 1;
			break;
		case 4:
			///// диагональ
			//в право вверх от фигуры
			xPos = xPositionCurrent + 1;
			yPos = yPositionCurrent - 1;
			break;
		case 5:
			//  в право вниз от фигуры
			xPos = xPositionCurrent + 1;
			yPos = yPositionCurrent + 1;
			break;
		case 6:
			// влево вниз от фигуры
			xPos = xPositionCurrent - 1;
			yPos = yPositionCurrent + 1;
			break;
		case 7:
			// влево вверх от фигуры
			xPos = xPositionCurrent - 1;
			yPos = yPositionCurrent - 1;
			break;
		default:
			break;
		}
		// продолжаем пока не встретим свою или чужую фигуру
		if (get<0>(vectorLocationFigure[yPos][xPos]) == 0)
		{
			result.push_back(make_pair(xPos, yPos));
		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (get<0>(vectorLocationFigure[yPos][xPos]) != get_SIDE() && get<0>(vectorLocationFigure[yPos][xPos]) > 0)
		{
			result.push_back(make_pair(xPos, yPos));
		}
	}
	return result;
}

bool King::checkMove(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
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

bool King::getPossibilityPromotion(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	return false;
}
