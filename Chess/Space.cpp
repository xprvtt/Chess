#include "Space.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------

std::wstring Space::setIdFigure() const noexcept
{
	return L"Space";
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool Space::getPossibilityPromotion([[maybe_unused]]  const Position::Coordinates& positionCurrent, [[maybe_unused]] const Grid<PropertiesFigure>& locationFigure) const
{
	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool Space::checkMove([[maybe_unused]] const Position::Coordinates& positionCurrent, [[maybe_unused]] const Position::Coordinates& positionMove, [[maybe_unused]] const Grid<PropertiesFigure>& locationFigure) const
{
	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<std::pair<inRowInt, inColInt>> Space::setAllMinimumMove() const
{
	return std::vector<std::pair<inRowInt, inColInt>>();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
