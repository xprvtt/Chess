#include "Knight.h"

string Knight::Set_ID_FIGURE()
{
	return "Knight";
}

vector<vector<bool>> Knight::GetMoveForFigure(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	/// ИГРОК 1 НИЖНИЙ БЕЛЫЙ

	int Row = VectorLocationFigure.size();
	int Col = VectorLocationFigure[0].size();

	//изначально считаем что ходов доступных нет
	vector<vector<bool>> result(Row, vector<bool>(Col, false));

	//вправо  вверх

	int XPos;
	int YPos;

	for (int count = 0; count < 8; count++)
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
		if (VectorLocationFigure[YPos][XPos].first == 0)
		{
			result[YPos][XPos] = true;
		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (VectorLocationFigure[YPos][XPos].first != GetSIDE() && VectorLocationFigure[YPos][XPos].first > 0)
		{
			result[YPos][XPos] = true;
		}
		// иначе предполагаем что встретили фигуру своей стороны и та же выходим
		else
		{
			result[YPos][XPos] = false;
		}
		
	}
	return result;
}

bool Knight::CheckMove(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	vector<vector<bool>> temp = GetMoveForFigure(XPositionCurrent, YPositionCurrent, VectorLocationFigure);

	return temp[XPositionMove][YPositionMove] ? true : false;
}

bool Knight::GetPossibilityPromotion(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	return false;
}

bool Knight::GetPromoutionFigure(string ID_Figure)
{
	return false;
}