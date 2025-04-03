#include "Figure.h"


////////////////////////////////////////////////////////////////////////////////////////////////////

// vector<vector<pair<int, string>>> VectorIntLocationFigure для int должен имееть структуру => 	  
// -1 == границы															  
// 0 == пустая клетка 														  
// 1+ == сторона игрока														  

////////////////////////////////////////////////////////////////////////////////////////////////////

Figure::Figure(int SIDE, bool INVULNERABLE, bool IMPORTANT, vector<tuple<int, string, bool, bool, bool>> VectorPROMOUTION )
{
	this->SIDE               = SIDE;
	this->INVULNERABLE       = INVULNERABLE; 
	this->IMPORTANT          = IMPORTANT;
	this->VectorPROMOUTION   = VectorPROMOUTION;
	
	VectorPROMOUTION.empty() ? PROMOUTION = false : PROMOUTION = true;
}


Figure::Figure(const Figure& OthreFigure)
{
	this->SIDE			   = OthreFigure.SIDE;
	this->ID_FIGURE		   = OthreFigure.ID_FIGURE;
	this->INVULNERABLE     = OthreFigure.INVULNERABLE;
	this->IMPORTANT		   = OthreFigure.IMPORTANT;
	this->VectorPROMOUTION = OthreFigure.VectorPROMOUTION;
	this->PROMOUTION       = OthreFigure.PROMOUTION;
}

bool Figure::CheckMoveForFigure(size_t XPositionCurrent, size_t YPositionCurrent, size_t XPositionMove, size_t YPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	return CheckMove(XPositionCurrent, YPositionCurrent, XPositionMove, YPositionMove, VectorLocationFigure);
}


string Figure::Get_ID_FIGURE()
{
	if (ID_FIGURE.empty()) 
	{ 
		ID_FIGURE = Set_ID_FIGURE();
	}
	return ID_FIGURE;
}

bool Figure::GetINVULNERABLE()
{
	return INVULNERABLE;
}

bool Figure::GetIMPORTANT()
{
	return IMPORTANT;
}

bool Figure::GetPROMOUTION()
{
	return PROMOUTION;
}

int Figure::GetSIDE()
{
	return SIDE;
}

vector<tuple<int, string, bool, bool, bool>> Figure::GetVectorPROMOUTION()
{
	return VectorPROMOUTION;
} 

bool Figure::GetPromoutionFigure(int SIDE, string ID_FIGURE,  bool INVULNERABLE, bool IMPORTANT, bool PROMOUTION)
{
	for (int it = 0; it < VectorPROMOUTION.size(); it++)
	{
		// если находим такую фигуру, в которую можем превратиться
		if (   get<0>(VectorPROMOUTION[it]) == SIDE
			&& get<1>(VectorPROMOUTION[it]) == ID_FIGURE
			&& get<2>(VectorPROMOUTION[it]) == INVULNERABLE
			&& get<3>(VectorPROMOUTION[it]) == IMPORTANT
			&& get<4>(VectorPROMOUTION[it]) == PROMOUTION
			)
		{
			return true;
		}
	}
	return false;
}








/// ВИРТУАЛЬНЫЕ ФУНКЦИИ ТРЕБУЮТ ПЕРЕОПРЕДЕЛНИЯ В НАСЛЕДНИКАХ 


string Figure::Set_ID_FIGURE()
{
	//должна называться так же как и класс-наследник фигуры \\\\  требует переопределения
	return "Figure";
}


vector<pair<size_t, size_t>> Figure::GetMoveForFigure(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	// виртуальный метод, для фигуры Figure всегда vector<vector<bool=false>> = нет условий, не может превратиться
	int Size = VectorLocationFigure.size();
	int Size2 = VectorLocationFigure[0].size();
	return vector<pair<size_t, size_t>>();
}


bool Figure::GetPossibilityPromotion(size_t XPositionCurrent, size_t YPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	// виртуальный метод, всегда false для фигуры Figure
	// стандартная фигура не имеет условий для превращения в другую фигуру
	return false;
}


bool Figure::CheckMove(size_t XPositionCurrent, size_t YPositionCurrent, size_t XPositionMove, size_t YPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	// виртуальный метод, всегда false для фигуры Figure
	// проверка ходов
	return false;
}
