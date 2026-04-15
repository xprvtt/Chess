#include "Knight.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------

std::wstring Knight::setIdFigure() const noexcept
{
	return L"Knight";
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<std::pair<int, int>> Knight::setAllMinimumMove() const
{
	return { { -2, -1 }, { -2, 1 }, { -1, -2 }, { -1, 2 }, { 1, -2 }, { 1, 2 }, { 2, -1 }, { 2, 1 } };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//std::vector<Position::Coordinates> Knight::customMoveForFigure(const Position::Coordinates& position, const Grid<PropertiesFigure>& m_vectorLocationFigure) const
//{
//	Position::Coordinates maxPosition = { m_vectorLocationFigure.size(),  m_vectorLocationFigure.front().size() };
//
//	std::vector<Position::Coordinates> result;
//
//	Position::Coordinates coordinates;
//	size_t xPos;
//	size_t yPos;
//
//	for (size_t count = 0; count < 8; count++)
//	{
//		switch (count)
//		{
//		case 0:
//			coordinates = position + Position::offsetLeftBy(2) + Position::OffsetUpBy(1);
//			break;
//		case 1:
//			xPos = xPositionCurrent - 1;
//			yPos = yPositionCurrent - 2;
//			break;
//		case 2:
//			xPos = xPositionCurrent + 1;
//			yPos = yPositionCurrent - 2;
//			break;
//		case 3:
//			xPos = xPositionCurrent + 2;
//			yPos = yPositionCurrent - 1;
//			break;
//		case 4:
//			xPos = xPositionCurrent + 2;
//			yPos = yPositionCurrent + 1;
//			break;
//		case 5:
//			xPos = xPositionCurrent + 1;
//			yPos = yPositionCurrent + 2;
//			break;
//		case 6:
//			xPos = xPositionCurrent - 1;
//			yPos = yPositionCurrent + 2;
//			break;
//		case 7:
//			xPos = xPositionCurrent - 2;
//			yPos = yPositionCurrent + 1;
//			break;
//
//		default:
//			break;
//		}
//
//		if (xPos >= col || yPos >= row || xPos < 0 || yPos < 0)
//		{
//			continue;
//		}
//		// пока не встретим свою или чужую фигуру 
//		if (m_vectorLocationFigure[yPos][xPos].m_side == 0)
//		{
//			result.emplace_back(xPos, yPos);
//
//		}
//
//		// если встретим фигуру противника добавляем возможность взятия и выходим
//		else if (m_vectorLocationFigure[yPos][xPos].m_side != getSide() && m_vectorLocationFigure[yPos][xPos].m_side > 0)
//		{
//			result.emplace_back(xPos, yPos);
//		}
//
//	}
//	return result;
//}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool Knight::getPossibilityPromotion([[maybe_unused]] const Position::Coordinates& positionCurrent, [[maybe_unused]] const Grid<PropertiesFigure>& locationFigure) const
{
	return false;
}
