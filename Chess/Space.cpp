#include "Space.h"


std::wstring Space::setIdFigure()
{
	return L"Space";
}


std::vector<std::pair<size_t, size_t>> Space::getMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, const GridPropertiesFigure& vectorLocationFigure)
{
	return std::vector<std::pair<size_t, size_t>>();
}


bool Space::getPossibilityPromotion(size_t xPositionCurrent, size_t yPositionCurrent, const GridPropertiesFigure& vectorLocationFigure)
{
	return false;
}


bool Space::checkMove(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const GridPropertiesFigure& vectorLocationFigure)
{
	return false;
}