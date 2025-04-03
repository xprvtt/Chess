#include "Pawn.h"

bool CustomCheckMove1(size_t XPositionCurrent, size_t YPositionCurrent, size_t XPositionMove, size_t YPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);
bool CustomCheckMove2(size_t XPositionCurrent, size_t YPositionCurrent, size_t XPositionMove, size_t YPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);

vector<pair<size_t, size_t>> AvailableMoveForFigure1(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);
vector<pair<size_t, size_t>> AvailableMoveForFigure2(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);

bool PossibilityPromotion1(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);
bool PossibilityPromotion2(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure);


//////////////////////////////////////////////////////////////////////////////////////////////////
//
// vector<vector<tuple<int, string, bool, bool, bool>>> VectorIntLocationFigure для int должен имееть структуру => 	  
// -1 == границы															  
// 0 == пустая клетка 														  
// 1+ == сторона игрока	 													  
//
//////////////////////////////////////////////////////////////////////////////////////////////////

//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//


bool Pawn::CheckMove(size_t XPositionCurrent, size_t YPositionCurrent, size_t XPositionMove, size_t YPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{

	switch (GetSIDE())
	{
	case 1:
		return CustomCheckMove1(XPositionCurrent, YPositionCurrent, XPositionMove, YPositionMove, VectorLocationFigure);
	case 2:
		return CustomCheckMove2(XPositionCurrent, YPositionCurrent, XPositionMove, YPositionMove, VectorLocationFigure);

	default:
		OutputLog("Игрок не определен проверьте линию -> Figure -> Pawn -> CheckMove() -> case");
		return false;
	}
}
bool CustomCheckMove1(size_t XPositionCurrent, size_t YPositionCurrent, size_t XPositionMove, size_t YPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{

	vector<pair<size_t, size_t>> VMove = AvailableMoveForFigure1(XPositionCurrent, YPositionCurrent, VectorLocationFigure);

	for (const auto& Move : VMove)
	{
		if (Move.first == XPositionMove && Move.second == YPositionMove)
		{
			return true;
		}
	}
	return false;
}

bool CustomCheckMove2(size_t XPositionCurrent, size_t YPositionCurrent, size_t XPositionMove, size_t YPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	vector<pair<size_t, size_t>> VMove = AvailableMoveForFigure2(XPositionCurrent, YPositionCurrent, VectorLocationFigure);

	for (const auto& Move : VMove)
	{
		if (Move.first == XPositionMove && Move.second == YPositionMove)
		{
			return true;
		}
	}
	return false;
}

//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//



//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//

vector<pair<size_t, size_t>> Pawn::GetMoveForFigure(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{

	// движение пешки в зависимости от стороны игрока
	switch (GetSIDE())
	{
	case 1:
		return AvailableMoveForFigure1(XPositionCurrent, YPositionCurrent, VectorLocationFigure);
	case 2:
		return AvailableMoveForFigure2(XPositionCurrent, YPositionCurrent, VectorLocationFigure);


	default:
		OutputLog("Игрок не определен проверьте линию -> Figure -> Pawn -> GetMoveForFigure() -> case");
		return vector<pair<size_t, size_t>>();
	}
}



vector<pair<size_t, size_t>> AvailableMoveForFigure1(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{

	/// ИГРОК 1 НИЖНИЙ БЕЛЫЙ 

	size_t Row = VectorLocationFigure.size();
	size_t Col = VectorLocationFigure[0].size();

	//изначально считаем что ходов доступных нет
	vector<pair<size_t, size_t>> result;


	// просчитываем ход на пустую клетку
	// 
	//если впереди пешки ничего нет то ход доступен
	if (get<0>(VectorLocationFigure[YPositionCurrent - 1][XPositionCurrent]) == 0)
	{
		result.push_back(make_pair(XPositionCurrent, YPositionCurrent - 1));


		//высчитываем возможную начальную позицию пешки (2 ряд для игрока) тогда можно сходить еще на 1 клетку вперед, т.е. сразу на 2
		if (YPositionCurrent == Row - 3 && get<0>(VectorLocationFigure[YPositionCurrent - 2][XPositionCurrent]) == 0)
		{
			// добавляем возможный ход на 2 клетки вперед
			result.push_back(make_pair(XPositionCurrent, YPositionCurrent - 2));
		}
	}

	// проситываем возможность взятие фигуры ПРОТИВНИКА справа и слева ИГРОКА 2
	// фигура на клетке не должна быть пустой ( SIDE 0 ) не должна быть краем ( SIDE -1 ) и нельзя взять свою же фигуру 
	if (get<0>(VectorLocationFigure[YPositionCurrent - 1][XPositionCurrent - 1]) > 0 && get<0>(VectorLocationFigure[YPositionCurrent - 1][XPositionCurrent - 1]) != get<0>(VectorLocationFigure[YPositionCurrent][XPositionCurrent]))
	{
		result.push_back(make_pair(XPositionCurrent - 1, YPositionCurrent - 1));

	}
	if (get<0>(VectorLocationFigure[YPositionCurrent - 1][XPositionCurrent + 1]) > 0 && get<0>(VectorLocationFigure[YPositionCurrent - 1][XPositionCurrent + 1]) != get<0>(VectorLocationFigure[YPositionCurrent][XPositionCurrent]))
	{
		result.push_back(make_pair(XPositionCurrent + 1, YPositionCurrent - 1));
	}


	return result;
}

vector<pair<size_t, size_t>> AvailableMoveForFigure2(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	/// ИГРОК 2 ВЕРХНИЙ ЧЕРНЫЙ

	size_t Row = VectorLocationFigure.size();
	size_t Col = VectorLocationFigure[0].size();

	vector<pair<size_t, size_t>> result;


	//если впереди пешки ничего нет
	if (get<0>(VectorLocationFigure[YPositionCurrent + 1][XPositionCurrent]) == 0)
	{
		result.push_back(make_pair(XPositionCurrent, YPositionCurrent + 1));

		//высчитываем возможную начальную позицию пешки (2 ряд для игрока) тогда можно сходить еще на 1 клетку вперед если она не занята
		if (YPositionCurrent == 2 && get<0>(VectorLocationFigure[YPositionCurrent + 2][XPositionCurrent]) == 0)
		{
			// добавляем возможный ход на 2 клетки вперед
			result.push_back(make_pair(XPositionCurrent, YPositionCurrent + 2));
		}
	}

	// проситываем возможность взятие фигуры ПРОТИВНИКА справа и слева ИГРОКА 2
	// фигура на клетке не должна быть пустой ( SIDE 0 ) не должна быть краем ( SIDE -1 ) и нельзя взять свою же фигуру 
	if (get<0>(VectorLocationFigure[YPositionCurrent + 1][XPositionCurrent - 1]) > 0 && get<0>(VectorLocationFigure[YPositionCurrent + 1][XPositionCurrent - 1]) != get<0>(VectorLocationFigure[YPositionCurrent][XPositionCurrent]))
	{
		result.push_back(make_pair(XPositionCurrent - 1, YPositionCurrent + 1));
	}
	if (get<0>(VectorLocationFigure[YPositionCurrent + 1][XPositionCurrent + 1]) > 0 && get<0>(VectorLocationFigure[YPositionCurrent + 1][XPositionCurrent + 1]) != get<0>(VectorLocationFigure[YPositionCurrent][XPositionCurrent]))
	{ 
		result.push_back(make_pair(XPositionCurrent + 1, YPositionCurrent + 1));
	}


	return result;
}


//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//






//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//


bool Pawn::GetPossibilityPromotion(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	switch (GetSIDE())
	{
	case 1:
		return PossibilityPromotion1(XPositionCurrent, YPositionCurrent, VectorLocationFigure);
	case 2:
		return PossibilityPromotion2(XPositionCurrent, YPositionCurrent, VectorLocationFigure);

	default:
		OutputLog("Игрок не определен проверьте линию -> Figure -> Pawn -> GetPossibilityPromotion() -> case");
		return false;
	}
}

bool PossibilityPromotion1(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	/// игрок 1 белый нижний

	return YPositionCurrent == 1 ? true : false;


}


bool PossibilityPromotion2(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	/// игрок 2 черный верхний
	return YPositionCurrent == VectorLocationFigure.size() - 2 ? true : false;

}


//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//





//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//

string Pawn::Set_ID_FIGURE()
{
	return "Pawn";
}
//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//

