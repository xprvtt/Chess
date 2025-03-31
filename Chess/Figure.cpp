#include "Figure.h"


////////////////////////////////////////////////////////////////////////////////////////////////////

// vector<vector<pair<int, string>>> VectorIntLocationFigure для int должен имееть структуру => 	  
// -1 == границы															  
// 0 == пустая клетка 														  
// 1+ == сторона игрока														  

////////////////////////////////////////////////////////////////////////////////////////////////////

Figure::Figure(int SIDE, bool INVULNERABLE)
{
	this->SIDE = SIDE;
	this->INVULNERABLE = INVULNERABLE; 
}


Figure::Figure(const Figure& OthreFigure)
{
	this->SIDE			  = OthreFigure.SIDE;
	this->ID_FIGURE		  = OthreFigure.ID_FIGURE;
	this->INVULNERABLE    = OthreFigure.INVULNERABLE;
}


bool Figure::CheckMoveForFigure(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
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


int Figure::GetSIDE()
{
	return SIDE;
}



/// ВИРТУАЛЬНЫЕ ФУНКЦИИ ТРЕБУЮТ ПЕРЕОПРЕДЕЛНИЯ В НАСЛЕДНИКАХ 


string Figure::Set_ID_FIGURE()
{
	//должна называться так же как и класс-наследник фигуры \\\\  требует переопределения
	return "Figure";
}


vector<vector<bool>> Figure::GetMoveForFigure(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	// виртуальный метод, всегда vector<vector<bool=false>>  \\\\  требует переопределения
	int Size = VectorLocationFigure.size();
	return vector<vector<bool>>(Size, vector<bool>(Size, false));
}


bool Figure::GetPossibilityPromotion(int XPositionCurrent, int YPositionCurrent, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	// виртуальный метод, всегда false   \\\\  требует переопределения
	// стандартная фигура не имеет условий для превращения в другую фигуру
	return false;
}

bool Figure::GetPromoutionFigure(string ID_Figure)
{
	// виртуальный метод, всегда false   \\\\  требует переопределения
	// не можем превратиться в любую указанную фигуру
	return false;
}


bool Figure::CheckMove(int XPositionCurrent, int YPositionCurrent, int XPositionMove, int YPositionMove, const vector<vector<pair<int, string>>>& VectorLocationFigure)
{
	// виртуальный метод, всегда false   \\\\  требует переопределения
	// проверка ходов
	return false;
}