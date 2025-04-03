#include "King.h"

string King::Set_ID_FIGURE()
{
	return "King";
}

vector<pair<size_t, size_t>> King::GetMoveForFigure(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	vector<pair<size_t, size_t>> result;

	size_t Row = VectorLocationFigure.size();
	size_t Col = VectorLocationFigure[0].size();


	size_t YPos;
	size_t XPos;

	for (size_t count = 0; count < 8; count++)
	{
		switch (count)
		{
		case 0:
			XPos = XPositionCurrent + 1;
			YPos = YPositionCurrent;
			break;
		case 1:
			//влево от фигуры
			XPos = XPositionCurrent - 1;
			YPos = YPositionCurrent;
			break;
		case 2:
			//вверх от фигуры
			XPos = XPositionCurrent;
			YPos = YPositionCurrent - 1;
			break;
		case 3:
			//вниз от фигуры
			XPos = XPositionCurrent;
			YPos = YPositionCurrent + 1;
			break;
		case 4:
			///// диагональ
			//в право вверх от фигуры
			XPos = XPositionCurrent + 1;
			YPos = YPositionCurrent - 1;
			break;
		case 5:
			//  в право вниз от фигуры
			XPos = XPositionCurrent + 1;
			YPos = YPositionCurrent + 1;
			break;
		case 6:
			// влево вниз от фигуры
			XPos = XPositionCurrent - 1;
			YPos = YPositionCurrent + 1;
			break;
		case 7:
			// влево вверх от фигуры
			XPos = XPositionCurrent - 1;
			YPos = YPositionCurrent - 1;
			break;
		default:
			break;
		}
		// продолжаем пока не встретим свою или чужую фигуру
		if (get<0>(VectorLocationFigure[YPos][XPos]) == 0)
		{
			result.push_back(make_pair(XPos, YPos));

		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (get<0>(VectorLocationFigure[YPos][XPos]) != GetSIDE() && get<0>(VectorLocationFigure[YPos][XPos]) > 0)
		{
			result.push_back(make_pair(XPos, YPos));

		}
	}
	return result;
}

bool King::CheckMove(size_t XPositionCurrent, size_t YPositionCurrent, size_t XPositionMove, size_t YPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
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

bool King::GetPossibilityPromotion(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	return false;
}
