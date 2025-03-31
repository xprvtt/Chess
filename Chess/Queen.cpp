#include "Queen.h"

string Queen::Set_ID_FIGURE()
{
	return "Queen";
}

vector<vector<bool>> Queen::GetMoveForFigure(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	/// ИГРОК 1 НИЖНИЙ БЕЛЫЙ

	int Row = VectorLocationFigure.size();
	int Col = VectorLocationFigure[0].size();

	//изначально считаем что ходов доступных нет
	vector<vector<bool>> result(Row, vector<bool>(Col, false));


	// вправо от фигуры
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
	//// по диагонали

	//в правый низ от фигуры
	for (int YPos = YPositionCurrent + 1, XPos = XPositionCurrent + 1; YPos < Row || XPos < Col; YPos++, XPos++)
	{
		// продолжаем пока не встретим свою или чужую фигуру
		if (VectorLocationFigure[YPos][XPos].first == 0)
		{
			result[YPos][XPos] = true;
		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (VectorLocationFigure[YPos][XPos].first != GetSIDE() && VectorLocationFigure[YPos][XPos].first > 0)
		{
			result[YPos][XPos] = true;
			break;
		}
		// иначе предполагаем что встретили фигуру своей стороны и та же выходим
		else
		{
			result[YPos][XPos] = false;
			break;
		}
	}

	// в правый верх от фигуры
	for (int YPos = YPositionCurrent - 1, XPos = XPositionCurrent + 1; YPos > 0 || XPos < Col; YPos--, XPos++)
	{
		// продолжаем пока не встретим свою или чужую фигуру
		if (VectorLocationFigure[YPos][XPos].first == 0)
		{
			result[YPos][XPos] = true;
		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (VectorLocationFigure[YPos][XPos].first != GetSIDE() && VectorLocationFigure[YPos][XPos].first > 0)
		{
			result[YPos][XPos] = true;
			break;
		}
		// иначе предполагаем что встретили фигуру своей стороны и та же выходим
		else
		{
			result[YPos][XPos] = false;
			break;
		}
	}


	//левый верх от фигуры
	for (int YPos = YPositionCurrent - 1, XPos = XPositionCurrent - 1; YPos > 0 || XPos > 0; YPos--, XPos--)
	{
		// продолжаем пока не встретим свою или чужую фигуру
		if (VectorLocationFigure[YPos][XPos].first == 0)
		{
			result[YPos][XPos] = true;
		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (VectorLocationFigure[YPos][XPos].first != GetSIDE() && VectorLocationFigure[YPos][XPos].first > 0)
		{
			result[YPos][XPos] = true;
			break;
		}
		// иначе предполагаем что встретили фигуру своей стороны и та же выходим
		else
		{
			result[YPos][XPos] = false;
			break;
		}
	}
	//левый низ от фигуры
	for (int YPos = YPositionCurrent + 1, XPos = XPositionCurrent - 1; YPos < Row || XPos > 0; YPos++, XPos--)
	{
		// продолжаем пока не встретим свою или чужую фигуру
		if (VectorLocationFigure[YPos][XPos].first == 0)
		{
			result[YPos][XPos] = true;
		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (VectorLocationFigure[YPos][XPos].first != GetSIDE() && VectorLocationFigure[YPos][XPos].first > 0)
		{
			result[YPos][XPos] = true;
			break;
		}
		// иначе предполагаем что встретили фигуру своей стороны и та же выходим
		else
		{
			result[YPos][XPos] = false; 
			break;
		}
	}

	return result;
}

bool Queen::CheckMove(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	vector<vector<bool>> temp = GetMoveForFigure(XPositionCurrent, YPositionCurrent, VectorLocationFigure);

	return temp[XPositionMove][YPositionMove] ? true : false;
}

bool Queen::GetPossibilityPromotion(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	return false;
}

bool Queen::GetPromoutionFigure(string ID_Figure)
{
	return false;
}
