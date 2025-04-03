#include "Bishop.h"

string Bishop::Set_ID_FIGURE()
{
	return "Bishop";
}

vector<pair<size_t, size_t>> Bishop::GetMoveForFigure(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	vector<pair<size_t, size_t>> result;

	size_t Row = VectorLocationFigure.size();
	size_t Col = VectorLocationFigure[0].size(); 


	int Side = GetSIDE();
	//// по диагонали 

	//в правый низ от фигуры
	for (size_t YPos = YPositionCurrent + 1, XPos = XPositionCurrent + 1; YPos < Row || XPos < Col; YPos++, XPos++)
	{
		// продолжаем пока не встретим свою или чужую фигуру
		if (get<0>(VectorLocationFigure[YPos][XPos]) == 0)
		{
			result.push_back(make_pair(XPos, YPos));
		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (get<0>(VectorLocationFigure[YPos][XPos]) != Side && get<0>(VectorLocationFigure[YPos][XPos]) > 0)
		{
			result.push_back(make_pair(XPos, YPos));
			break;
		}
		// иначе предполагаем что встретили фигуру своей стороны и та же выходим
		else
		{
			break;
		}
	}

	// в правый верх от фигуры
	for (size_t YPos = YPositionCurrent - 1, XPos = XPositionCurrent + 1; YPos > 0 || XPos < Col; YPos--, XPos++)
	{
		// продолжаем пока не встретим свою или чужую фигуру
		if (get<0>(VectorLocationFigure[YPos][XPos]) == 0)
		{
			result.push_back(make_pair(XPos, YPos));

		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (get<0>(VectorLocationFigure[YPos][XPos]) != Side && get<0>(VectorLocationFigure[YPos][XPos]) > 0)
		{
			result.push_back(make_pair(XPos, YPos));

			break;
		}
		// иначе предполагаем что встретили фигуру своей стороны и та же выходим
		else
		{
			break;
		}
	}


	//левый верх от фигуры 
	for (size_t YPos = YPositionCurrent - 1, XPos = XPositionCurrent - 1; YPos > 0 || XPos > 0; YPos--, XPos--)
	{
		// продолжаем пока не встретим свою или чужую фигуру
		if (get<0>(VectorLocationFigure[YPos][XPos]) == 0)
		{
			result.push_back(make_pair(XPos, YPos));

		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (get<0>(VectorLocationFigure[YPos][XPos]) != Side && get<0>(VectorLocationFigure[YPos][XPos]) > 0)
		{
			result.push_back(make_pair(XPos, YPos));

			break;
		}
		// иначе предполагаем что встретили фигуру своей стороны и та же выходим
		else
		{
			break;
		}
	}
	//левый низ от фигуры
	for (size_t YPos = YPositionCurrent + 1, XPos = XPositionCurrent - 1; YPos < Row || XPos > 0; YPos++, XPos--)
	{
		// продолжаем пока не встретим свою или чужую фигуру
		if (get<0>(VectorLocationFigure[YPos][XPos]) == 0)
		{
			result.push_back(make_pair(XPos, YPos));

		}
		// если встретим фигуру противника добавляем возможность взятия и выходим
		else if (get<0>(VectorLocationFigure[YPos][XPos]) != Side && get<0>(VectorLocationFigure[YPos][XPos]) > 0)
		{
			result.push_back(make_pair(XPos, YPos));

			break;
		}
		// иначе предполагаем что встретили фигуру своей стороны и та же выходим
		else
		{
			break;
		}
	}

	return result;
}

bool Bishop::CheckMove(size_t XPositionCurrent, size_t YPositionCurrent, size_t XPositionMove, size_t YPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
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

bool Bishop::GetPossibilityPromotion(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	return false;
}
