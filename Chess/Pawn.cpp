#include "Pawn.h"

bool CustomCheckMove1(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure);
bool CustomCheckMove2(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure);

vector<vector<bool>> AvailableMoveForFigure1(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure);
vector<vector<bool>> AvailableMoveForFigure2(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure);

bool PossibilityPromotion1(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>&VectorLocationFigure);
bool PossibilityPromotion2(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>&VectorLocationFigure);


//////////////////////////////////////////////////////////////////////////////////////////////////
//
// vector<vector<pair<int, string>>> VectorIntLocationFigure для int должен имееть структуру => 	  
// -1 == границы															  
// 0 == пустая клетка 														  
// 1+ == сторона игрока	 													  
//
//////////////////////////////////////////////////////////////////////////////////////////////////

//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//


bool Pawn::CheckMove(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
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
bool CustomCheckMove1(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	vector<vector<bool>> temp = AvailableMoveForFigure1(XPositionCurrent, YPositionCurrent, VectorLocationFigure);

	if (temp[XPositionMove][YPositionMove] == true)
	{
		return true;
	}

	return false;
}

bool CustomCheckMove2(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	vector<vector<bool>> temp = AvailableMoveForFigure2(XPositionCurrent, YPositionCurrent, VectorLocationFigure);

	if (temp[XPositionMove][YPositionMove] == true)
	{
		return true;
	}

	return false;
}

//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//



//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//

vector<vector<bool>> Pawn::GetMoveForFigure(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
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
		return vector<vector<bool>>(VectorLocationFigure.size(), vector<bool>(VectorLocationFigure[0].size(), false));
	}
}



vector<vector<bool>> AvailableMoveForFigure1(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{

	/// ИГРОК 1 НИЖНИЙ БЕЛЫЙ

	int Row = VectorLocationFigure.size();
	int Col = VectorLocationFigure[0].size();

	//изначально считаем что ходов доступных нет
	vector<vector<bool>> result(Row, vector<bool>(Col, false));
	



	// просчитываем ход на пустую клетку
	// 
	//если впереди пешки ничего нет то ход доступен
	if (VectorLocationFigure[YPositionCurrent - 1][XPositionCurrent].first == 0)
	{
		result[YPositionCurrent-1][XPositionCurrent] = true;

		//высчитываем возможную начальную позицию пешки (2 ряд для игрока) тогда можно сходить еще на 1 клетку вперед, т.е. сразу на 2
		if (YPositionCurrent == Row - 3 && VectorLocationFigure[YPositionCurrent - 2][XPositionCurrent].first == 0)
		{
			// добавляем возможный ход на 2 клетки вперед
			result[YPositionCurrent-2][XPositionCurrent] = true;
		}
	}

	// проситываем возможность взятие фигуры ПРОТИВНИКА справа и слева ИГРОКА 2
	// фигура на клетке не должна быть пустой ( SIDE 0 ) не должна быть краем ( SIDE -1 ) и нельзя взять свою же фигуру 
	if (VectorLocationFigure[YPositionCurrent - 1][XPositionCurrent - 1].first > 0 && VectorLocationFigure[YPositionCurrent - 1][XPositionCurrent - 1].first != VectorLocationFigure[YPositionCurrent][XPositionCurrent].first)
	{
		result[YPositionCurrent - 1][XPositionCurrent - 1] = true;
	}
	if (VectorLocationFigure[YPositionCurrent - 1][XPositionCurrent + 1].first > 0 && VectorLocationFigure[YPositionCurrent - 1][XPositionCurrent + 1].first != VectorLocationFigure[YPositionCurrent][XPositionCurrent].first)
	{
		result[YPositionCurrent - 1][XPositionCurrent + 1] = true;
	}


	return result;
}

vector<vector<bool>> AvailableMoveForFigure2(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	/// ИГРОК 2 ВЕРХНИЙ ЧЕРНЫЙ

	int Row = VectorLocationFigure.size();
	int Col = VectorLocationFigure[0].size();

	vector<vector<bool>> result(Row, vector<bool>(Col, false));

	//если впереди пешки ничего нет
	if (VectorLocationFigure[YPositionCurrent + 1][XPositionCurrent].first == 0)
	{
		result[YPositionCurrent + 1][XPositionCurrent] = true;

		//высчитываем возможную начальную позицию пешки (2 ряд для игрока) тогда можно сходить еще на 1 клетку вперед если она не занята
		if (YPositionCurrent == 2 && VectorLocationFigure[YPositionCurrent + 2][XPositionCurrent].first == 0)
		{
			// добавляем возможный ход на 2 клетки вперед
			result[YPositionCurrent + 2][XPositionCurrent] = true;
		}
	}

	// проситываем возможность взятие фигуры ПРОТИВНИКА справа и слева ИГРОКА 2
    // фигура на клетке не должна быть пустой ( SIDE 0 ) не должна быть краем ( SIDE -1 ) и нельзя взять свою же фигуру 
	if (VectorLocationFigure[YPositionCurrent + 1][XPositionCurrent - 1].first > 0 && VectorLocationFigure[YPositionCurrent + 1][XPositionCurrent - 1].first != VectorLocationFigure[YPositionCurrent][XPositionCurrent].first)
	{
		result[YPositionCurrent + 1][XPositionCurrent - 1] = true;
	}
	if (VectorLocationFigure[YPositionCurrent + 1][XPositionCurrent + 1].first > 0 && VectorLocationFigure[YPositionCurrent + 1][XPositionCurrent + 1].first != VectorLocationFigure[YPositionCurrent][XPositionCurrent].first)
	{
		result[YPositionCurrent + 1][XPositionCurrent + 1] = true;
	}


	return result;
}


//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//






//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//


bool Pawn::GetPossibilityPromotion(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	switch (GetSIDE())
	{
	case 1:
		return PossibilityPromotion1(XPositionCurrent,  YPositionCurrent,  VectorLocationFigure);
	case 2:
		return PossibilityPromotion2(XPositionCurrent,  YPositionCurrent, VectorLocationFigure);

	default:
		OutputLog("Игрок не определен проверьте линию -> Figure -> Pawn -> GetPossibilityPromotion() -> case");
		return false;
	}
}

bool PossibilityPromotion1(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	/// игрок 1 белый нижний

	return YPositionCurrent == 1 ? true : false;

	
}


bool PossibilityPromotion2(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
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



//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//-----------//

bool Pawn::GetPromoutionFigure(string ID_Figure)
{
	//по умолчанию пешка может превратиться в 4 другие стандартные фигуры, но можно добавить и другие
	if (ID_Figure == "Rook" || ID_Figure == "Queen" || ID_Figure == "Knight" || ID_Figure == "Bishop" )
	{
		return true;
	}

	return false;
}
