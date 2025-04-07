#include "Knight.h"

string Knight::Set_ID_FIGURE()
{
	return "Knight";
}

vector<pair<size_t, size_t>> Knight::GetMoveForFigure(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{

	size_t Row = VectorLocationFigure.size();
	size_t Col = VectorLocationFigure[0].size();

	//изначально считаем что ходов доступных нет
	vector<pair<size_t, size_t>> result;


	//вправо  вверх

	size_t XPos;
	size_t YPos;

	for (size_t count = 0; count < 8; count++)
	{

		switch (count)
		{
		case 0:
			XPos = XPositionCurrent - 2;
			YPos = YPositionCurrent - 1;
			break;
		case 1:
			XPos = XPositionCurrent - 1;
			YPos = YPositionCurrent - 2;
			break;
		case 2:
			XPos = XPositionCurrent + 1;
			YPos = YPositionCurrent - 2;
			break;
		case 3:
			XPos = XPositionCurrent + 2;
			YPos = YPositionCurrent - 1;
			break;
		case 4:
			XPos = XPositionCurrent + 2;
			YPos = YPositionCurrent + 1;
			break;
		case 5:
			XPos = XPositionCurrent + 1;
			YPos = YPositionCurrent + 2;
			break;
		case 6:
			XPos = XPositionCurrent - 1;
			YPos = YPositionCurrent + 2;
			break;
		case 7:
			XPos = XPositionCurrent - 2;
			YPos = YPositionCurrent + 1;
			break;

		default:
			break;
		}

		if (XPos >= Col || YPos >= Row || XPos < 0 || YPos < 0)
		{
			continue;
		}

		// пока не встретим свою или чужую фигуру 
		if (get<0>(VectorLocationFigure[YPos][XPos]) == 0)
		{
			result.push_back(make_pair(XPos, YPos));

		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (get<0>(VectorLocationFigure[YPos][XPos]) != GetSIDE() && get<0>(VectorLocationFigure[YPos][XPos]) > 0)
		{
			result.push_back(make_pair(XPos, YPos));
		}
		// иначе предполагаем что встретили фигуру своей стороны
	}
	return result;
}
 
bool Knight::CheckMove(size_t XPositionCurrent, size_t YPositionCurrent, size_t XPositionMove, size_t YPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
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

bool Knight::GetPossibilityPromotion(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	return false;
}
