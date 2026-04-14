#include "Bishop.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::wstring Bishop::setIdFigure() const noexcept
{
	return L"Bishop";
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//std::vector<Position::Coordinates> Bishop::getMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, const Grid<PropertiesFigure>& m_vectorLocationFigure) const
//{
//	std::vector<Position::Coordinates> result;
//
//	size_t row = m_vectorLocationFigure.size();
//	size_t col = m_vectorLocationFigure[0].size(); 
//
//	int side = this->getSide();
//
//	// по диагонали 
//	// в правый низ от фигуры
//	for (size_t yPos = yPositionCurrent + 1, xPos = xPositionCurrent + 1; yPos < row || xPos < col; yPos++, xPos++)
//	{
//		if (!checkCell(xPos, yPos, side, result, m_vectorLocationFigure))	{	break;	}
//	}
//
//	// в правый верх от фигуры
//	for (size_t yPos = yPositionCurrent - 1, xPos = xPositionCurrent + 1; yPos > 0 || xPos < col; yPos--, xPos++)
//	{
//		if (!checkCell(xPos, yPos, side, result, m_vectorLocationFigure))	{	break;	}
//	}
//
//	// левый верх от фигуры 
//	for (size_t yPos = yPositionCurrent - 1, xPos = xPositionCurrent - 1; yPos > 0 || xPos > 0; yPos--, xPos--)
//	{
//		if (!checkCell(xPos, yPos, side, result, m_vectorLocationFigure))	{	break;	}
//	}
//
//	// левый низ от фигуры
//	for (size_t yPos = yPositionCurrent + 1, xPos = xPositionCurrent - 1; yPos < row || xPos > 0; yPos++, xPos--)
//	{
//		if (!checkCell(xPos, yPos, side, result, m_vectorLocationFigure))	{	break;	}
//	}
//	return result;
//}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<std::pair<inRowInt, inColInt>> Bishop::setAllMinimumMove() const
{
	return { {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool Bishop::getPossibilityPromotion([[maybe_unused]] const Position::Coordinates& positionCurrent, [[maybe_unused]] const Grid<PropertiesFigure>& locationFigure) const 
{
	return false;
}
