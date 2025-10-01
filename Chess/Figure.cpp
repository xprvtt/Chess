#include "Figure.h"


////////////////////////////////////////////////////////////////////////////////////////////////////

// vector<vector<pair<int, string>>> VectorIntLocationFigure для int должен имееть структуру => 	  
// -1 == границы															  
// 0 == пустая клетка 														  
// 1+ == сторона игрока														  

////////////////////////////////////////////////////////////////////////////////////////////////////

Figure::Figure(int SIDE, bool INVULNERABLE, bool IMPORTANT, vector<tuple<int, string, bool, bool, bool>> vectorPROMOUTION )
{
	this->SIDE               = SIDE;
	this->INVULNERABLE       = INVULNERABLE; 
	this->IMPORTANT          = IMPORTANT;
	this->VECTOR_PROMOUTION   = vectorPROMOUTION;
	
	vectorPROMOUTION.empty() ? PROMOUTION = false : PROMOUTION = true;
}


Figure::Figure(const Figure& othreFigure)
{
	this->SIDE			   = othreFigure.SIDE;
	this->ID_FIGURE		   = othreFigure.ID_FIGURE;
	this->INVULNERABLE     = othreFigure.INVULNERABLE;
	this->IMPORTANT		   = othreFigure.IMPORTANT;
	this->VECTOR_PROMOUTION = othreFigure.VECTOR_PROMOUTION;
	this->PROMOUTION       = othreFigure.PROMOUTION;
}

bool Figure::checkMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	return checkMove(xPositionCurrent, yPositionCurrent, xPositionMove, yPositionMove, vectorLocationFigure);
}


string Figure::get_ID_FIGURE()
{
	if (ID_FIGURE.empty()) 
	{ 
		ID_FIGURE = set_ID_FIGURE();
	}
	return ID_FIGURE;
}

bool Figure::get_INVULNERABLE()
{
	return INVULNERABLE;
}

bool Figure::get_IMPORTANT()
{
	return IMPORTANT;
}

bool Figure::get_PROMOUTION()
{
	return PROMOUTION;
}

int Figure::get_SIDE()
{
	return SIDE;
}

vector<tuple<int, string, bool, bool, bool>> Figure::get_VECTOR_PROMOUTION()
{
	return VECTOR_PROMOUTION;
} 

bool Figure::getPromoutionFigure(int SIDE, string ID_FIGURE,  bool INVULNERABLE, bool IMPORTANT, bool PROMOUTION)
{
	for (int it = 0; it < VECTOR_PROMOUTION.size(); it++)
	{
		// если находим такую фигуру, в которую можем превратиться
		if (   get<0>(VECTOR_PROMOUTION[it]) == SIDE
			&& get<1>(VECTOR_PROMOUTION[it]) == ID_FIGURE
			&& get<2>(VECTOR_PROMOUTION[it]) == INVULNERABLE
			&& get<3>(VECTOR_PROMOUTION[it]) == IMPORTANT
			&& get<4>(VECTOR_PROMOUTION[it]) == PROMOUTION
			)
		{
			return true;
		}
	}
	return false;
}



/// ВИРТУАЛЬНЫЕ ФУНКЦИИ ТРЕБУЮТ ПЕРЕОПРЕДЕЛНИЯ В НАСЛЕДНИКАХ 


string Figure::set_ID_FIGURE()
{
	//должна называться так же как и класс-наследник фигуры \\\\  требует переопределения
	return "Figure";
}


vector<pair<size_t, size_t>> Figure::getMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	// виртуальный метод, для фигуры Figure - нет условий, не может превратиться
	return vector<pair<size_t, size_t>>();
}


bool Figure::getPossibilityPromotion(size_t xPositionCurrent, size_t yPositionCurrent, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	// виртуальный метод, всегда false для фигуры Figure
	// стандартная фигура не имеет условий для превращения в другую фигуру
	return false;
}


bool Figure::checkMove(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	// виртуальный метод, всегда false для фигуры Figure
	// проверка ходов
	return false;
}
