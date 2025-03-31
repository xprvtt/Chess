#include "Rook.h"

string Rook::Set_ID_FIGURE()
{
	return "Rook";
}

vector<vector<bool>> Rook::GetMoveForFigure(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{

	int Row = VectorLocationFigure.size();
	int Col = VectorLocationFigure[0].size();

	//изначально считаем что ходов доступных нет
	vector<vector<bool>> result(Row, vector<bool>(Col, false));

	//проходимся по горизонтали

	// вправо от фигуры (ладьи)
	for (int XPos = XPositionCurrent + 1; XPos < Col; XPos++)
	{
		// продолжаем пока не встретим свою или чужую фигуру
		if (VectorLocationFigure[YPositionCurrent][XPos].first == 0)
		{
			result[YPositionCurrent][XPos] = true;
		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (VectorLocationFigure[YPositionCurrent][XPos].first != GetSIDE() && VectorLocationFigure[YPositionCurrent][XPos].first > 0)
		{
			result[YPositionCurrent][XPos] = true;
			break;
		}
		// иначе предполагаем что встретили фигуру своей стороны и та же выходим
		else
		{
			result[YPositionCurrent][XPos] = false;
			break;
		}
	}
	// влево от фигуры
	for (int XPos = XPositionCurrent - 1; XPos > 0; XPos--)
	{
		// продолжаем пока не встретим свою или чужую фигуру
		if (VectorLocationFigure[YPositionCurrent][XPos].first == 0)
		{
			result[YPositionCurrent][XPos] = true;
		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (VectorLocationFigure[YPositionCurrent][XPos].first != GetSIDE() && VectorLocationFigure[YPositionCurrent][XPos].first > 0)
		{
			result[YPositionCurrent][XPos] = true;
			break;
		}
		// иначе предполагаем что встретили фигуру своей стороны и та же выходим
		else
		{
			result[YPositionCurrent][XPos] = false;
			break;
		}
	}

	//вверх от фигуры
	for (int YPos = YPositionCurrent - 1; YPos > 0; YPos--)
	{
		// продолжаем пока не встретим свою или чужую фигуру
		if (VectorLocationFigure[YPos][XPositionCurrent].first == 0)
		{
			result[YPos][XPositionCurrent] = true;
		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (VectorLocationFigure[YPos][XPositionCurrent].first != GetSIDE() && VectorLocationFigure[YPos][XPositionCurrent].first > 0)
		{
			result[YPos][XPositionCurrent] = true;
			break;
		}
		// иначе предполагаем что встретили фигуру своей стороны и та же выходим
		else
		{
			result[YPos][XPositionCurrent] = false; 
			break;
		}
	}
	//вниз от фигуры
	for (int YPos = YPositionCurrent + 1; YPos < Row; YPos++)
	{
		// продолжаем пока не встретим свою или чужую фигуру
		if (VectorLocationFigure[YPos][XPositionCurrent].first == 0)
		{
			result[YPos][XPositionCurrent] = true;
		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (VectorLocationFigure[YPos][XPositionCurrent].first != GetSIDE() && VectorLocationFigure[YPos][XPositionCurrent].first > 0)
		{
			result[YPos][XPositionCurrent] = true;
			break;
		}
		// иначе предполагаем что встретили фигуру своей стороны и та же выходим
		else
		{
			result[YPos][XPositionCurrent] = false;
			break;
		}
	}
	return result;
}

bool Rook::CheckMove(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	vector<vector<bool>> temp = GetMoveForFigure(XPositionCurrent, YPositionCurrent, VectorLocationFigure);

	return temp[XPositionMove][YPositionMove] ? true : false;
}

bool Rook::GetPossibilityPromotion(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	return false;
}

bool Rook::GetPromoutionFigure(string ID_Figure)
{
	return false;
}
