#include "Queen.h"




static bool checkCell(size_t xPos, size_t yPos, int side, std::vector<std::pair<size_t, size_t>>& result, const GridPropertiesFigure& vectorLocationFigure);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::wstring Queen::setIdFigure()
{
	return L"Queen";
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::pair<size_t, size_t>> Queen::getMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, const GridPropertiesFigure& vectorLocationFigure)
{
	size_t row = vectorLocationFigure.size();
	size_t col = vectorLocationFigure[0].size();

	std::vector<std::pair<size_t, size_t>> result;


	int side = getSide();

	///
	/// вправо от фигуры
	/// 
	for (size_t xPos = xPositionCurrent + 1; xPos < col; xPos++)
	{
		if (!checkCell(xPos, yPositionCurrent, side, result, vectorLocationFigure))	{	break;	}
	}

	///
	/// влево от фигуры
	/// 
	for (size_t xPos = xPositionCurrent - 1; xPos > 0; xPos--)
	{
		if (!checkCell(xPos, yPositionCurrent, side, result, vectorLocationFigure))	{	break;	}
	}

	///
	/// вверх от фигуры
	/// 
	for (size_t yPos = yPositionCurrent - 1; yPos > 0; yPos--)
	{
		if (!checkCell(xPositionCurrent, yPos, side, result, vectorLocationFigure))	{	break;	}
	}

	///
	/// вниз от фигуры
	/// 
	for (size_t yPos = yPositionCurrent + 1; yPos < row; yPos++)
	{
		if (!checkCell(xPositionCurrent, yPos, side, result, vectorLocationFigure))	{	break;	}
	}





	///
	/// по диагонали
	/// 	

	/// 
	/// в правый низ от фигуры
	/// 
	for (size_t yPos = yPositionCurrent + 1, xPos = xPositionCurrent + 1; yPos < row || xPos < col; yPos++, xPos++)
	{
		if (!checkCell(xPos, yPos, side, result, vectorLocationFigure))	{	break;	}
	}

	///
	/// в правый верх от фигуры
	/// 
	for (size_t yPos = yPositionCurrent - 1, xPos = xPositionCurrent + 1; yPos > 0 || xPos < col; yPos--, xPos++)
	{
		if (!checkCell(xPos, yPos, side, result, vectorLocationFigure))	{	break;	}
	}

	///
	/// левый верх от фигуры
	/// 
	for (size_t yPos = yPositionCurrent - 1, xPos = xPositionCurrent - 1; yPos > 0 || xPos > 0; yPos--, xPos--)
	{
		if (!checkCell(xPos, yPos, side, result, vectorLocationFigure)) {	break;	}
	}

	///
	///левый низ от фигуры
	/// 
	for (size_t yPos = yPositionCurrent + 1, xPos = xPositionCurrent - 1; yPos < row || xPos > 0; yPos++, xPos--)
	{
		if (!checkCell(xPos, yPos, side, result, vectorLocationFigure))	{	break;	}
	}

	return result;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static bool checkCell(size_t xPos, size_t yPos, int side, std::vector<std::pair<size_t, size_t>>& result, const GridPropertiesFigure& vectorLocationFigure)
{
	///
	/// продолжаем пока не встретим свою или чужую фигуру
	/// 
	if (vectorLocationFigure[yPos][xPos].side == 0)
	{
		result.emplace_back(xPos, yPos);
		return true;

	}
	///
	/// если встретим фигуру противника добавляем возможность взятия и выходим
	/// 
	else if (vectorLocationFigure[yPos][xPos].side != side && vectorLocationFigure[yPos][xPos].side > 0)
	{
		result.emplace_back(xPos, yPos);
		return false;
	}
	///
	/// иначе предполагаем, что встретили фигуру своей стороны и так же выходим
	/// 
	else
	{
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Queen::checkMove(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const GridPropertiesFigure& vectorLocationFigure)
{
	std::vector<std::pair<size_t, size_t>> VMove = getMoveForFigure(xPositionCurrent, yPositionCurrent, vectorLocationFigure);

	for (const auto& Move : VMove)
	{
		if (Move.first == xPositionMove && Move.second == yPositionMove)
		{
			return true;
		}
	} 
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Queen::getPossibilityPromotion(size_t xPositionCurrent, size_t yPositionCurrent, const GridPropertiesFigure& vectorLocationFigure)
{
	return false;
}
