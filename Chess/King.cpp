#include "King.h"


std::wstring King::setIdFigure() const noexcept
{
	return L"King";
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//std::vector<Position::Coordinates> King::getMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, const Grid<PropertiesFigure>& m_vectorLocationFigure)
//{
//	std::vector<Position::Coordinates> result;
//
//	size_t yPos;
//	size_t xPos;
//	 
//	for (size_t count = 0; count < 8; count++)
//	{
//		switch (count)
//		{
//		case 0:
//			// вправо от фигуры	
//			xPos = xPositionCurrent + 1;
//			yPos = yPositionCurrent;
//			break;
//
//		case 1:			
//			// влево от фигуры				
//			xPos = xPositionCurrent - 1;
//			yPos = yPositionCurrent;
//			break;
//
//		case 2:			
//			// вверх от фигуры	 
//			xPos = xPositionCurrent;
//			yPos = yPositionCurrent - 1;
//			break;
//
//		case 3:
//			/// вниз от фигуры	
//			xPos = xPositionCurrent;
//			yPos = yPositionCurrent + 1;
//			break;
//
//		case 4:
//			// диагональ
//			// в право вверх от фигуры 
//			xPos = xPositionCurrent + 1;
//			yPos = yPositionCurrent - 1;
//			break;
//		case 5:
//			//   в право вниз от фигуры 
//			xPos = xPositionCurrent + 1;
//			yPos = yPositionCurrent + 1;
//			break;
//		case 6:
//			//  влево вниз от фигуры 
//			xPos = xPositionCurrent - 1;
//			yPos = yPositionCurrent + 1;
//			break;
//		case 7:
//			//  влево вверх от фигуры 
//			xPos = xPositionCurrent - 1;
//			yPos = yPositionCurrent - 1;
//			break;
//
//		default:
//			break;
//		}
//
//		// продолжаем пока не встретим свою или чужую фигуру
//		if (m_vectorLocationFigure[yPos][xPos].m_side == 0)
//		{
//			result.emplace_back(xPos, yPos);
//		}
//
//		// если встретим фигуру противника добавляем возможность взятия и выходим
//		else if (m_vectorLocationFigure[yPos][xPos].m_side != getSide() && m_vectorLocationFigure[yPos][xPos].m_side > 0)
//		{
//			result.emplace_back(xPos, yPos);
//		}
//	}
//	return result;
//}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<std::pair<inRowInt, inColInt>> King::setAllMinimumMove() const
{
	/* * * * * * * * * * * * *
	*		|		 |
	* -1,-1 |  -1,0  | -1,1
	*		|		 |
	* -----------------------
	*		|		 |
	*  0,-1 |  King  |  0,1
	*		|		 |
	* -----------------------
	*		|		 |
	* 1, -1	|   1,0  |  1,1
	*		|		 |
	*/

	return { {-1,0}, {0,1}, {0,-1}, {1,0}, {-1,-1},{-1,1},{1,-1},{1,1} };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool King::getPossibilityPromotion([[maybe_unused]] const Position::Coordinates& positionCurrent, [[maybe_unused]] const Grid<PropertiesFigure>& locationFigure) const
{
	return false;
}
