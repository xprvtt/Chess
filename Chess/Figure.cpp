#include "Figure.h"



///////////////////////////////////////////////////////////////
// 
// PropertiesFigure.side должен имееть структуру => 	  
// -1 == границы															  
// 0 == пустая клетка 														  
// 1+ == сторона игрока										  
// 
///////////////////////////////////////////////////////////////

Figure::Figure(int side, bool invulnerable, bool important, std::vector<PropertiesFigure> vectorPromoution) :
	side(side),
	invulnerable(invulnerable),
	important(important),
	vectorPromoution(vectorPromoution)
{
	vectorPromoution.empty() ? promoution = false : promoution = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Figure::Figure(const Figure& othreFigure) :
	side(othreFigure.side),
	idFigure(othreFigure.idFigure),
	invulnerable(othreFigure.invulnerable),
	important(othreFigure.important),
	vectorPromoution(othreFigure.vectorPromoution),
	promoution(othreFigure.promoution)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool  Figure::checkMoveForFigureOnPosition(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const GridPropertiesFigure& vectorLocationFigure)
{
	return checkMove(xPositionCurrent, yPositionCurrent, xPositionMove, yPositionMove, vectorLocationFigure);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::wstring Figure::getIdFigure()
{
	if (idFigure.empty())
	{
		idFigure = setIdFigure();
	}
	return idFigure;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool Figure::getInvulnerable() const noexcept
{
	return invulnerable;
}


bool Figure::getImportant() const noexcept
{
	return important;
}


bool Figure::getPromoution() const noexcept
{
	return promoution;
}


int Figure::getSide() const noexcept
{
	return side;
}


std::vector<PropertiesFigure> Figure::getVectorPromoution() const
{
	return vectorPromoution;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool Figure::getPromoutionFigure(int side, std::wstring idFigure, bool invulnerable, bool important, bool promoution) const
{
	for (int it = 0; it < vectorPromoution.size(); it++)
	{
		///
		/// если находим такую фигуру, в которую можем превратиться
		/// 
		if (   vectorPromoution[it].side         == side
			&& vectorPromoution[it].idFigure     == idFigure
			&& vectorPromoution[it].invulnerable == invulnerable
			&& vectorPromoution[it].important    == important
			&& vectorPromoution[it].promoution   == promoution
			)
		{
			return true;
		}
	}
	return false;
}
