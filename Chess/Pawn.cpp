#include "Pawn.h"


static bool customCheckMoveSideTop(const Position::Coordinates& positionCurrent, Position::Coordinates positionMove, const Grid<PropertiesFigure>& locationFigure);
static bool customCheckMoveSideDown(const Position::Coordinates& positionCurrent, Position::Coordinates positionMove, const Grid<PropertiesFigure>& locationFigure);

static std::vector<Position::Coordinates> availableMoveForFigureSideTop(const Position::Coordinates& positionCurrent, const Grid<PropertiesFigure>& locationFigure);
static std::vector<Position::Coordinates> availableMoveForFigureSideDown(const Position::Coordinates& positionCurrent, const Grid<PropertiesFigure>& locationFigure);

static bool possibilityPromotionSideTop(const Position::Coordinates& positionCurrent, const Grid<PropertiesFigure>& locationFigure);
static bool possibilityPromotionSideDown(const Position::Coordinates& positionCurrent, const Grid<PropertiesFigure>& locationFigure);

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool Pawn::checkMove(const Position::Coordinates& positionCurrent, const Position::Coordinates& positionMove, const Grid<PropertiesFigure>& locationFigure) const
{
	switch (m_side)
	{
	case 1:
		return customCheckMoveSideTop(positionCurrent, positionMove, locationFigure);
	case 2:
		return customCheckMoveSideDown(positionCurrent, positionMove, locationFigure);

	default:
		OUTPUT_LOG_ERROR("Не определенный Игрок проверьте линию -> Figure -> Pawn -> CheckMove -> case");
		return false;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<Position::Coordinates> Pawn::customMoveForFigure(const Position::Coordinates& position, const Grid<PropertiesFigure>& locationFigure) const
{
	// движение пешки в зависимости от стороны игрока
	switch (m_side)
	{
	case 1:
		return availableMoveForFigureSideTop(position, locationFigure);

	case 2:
		return availableMoveForFigureSideDown(position, locationFigure);

	default:
		OUTPUT_LOG_ERROR("Игрок не определен. [Figure] -> [Pawn] -> [GetMoveForFigure] -> [case]");
	}
	return std::vector<Position::Coordinates>();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool Pawn::getPossibilityPromotion(const Position::Coordinates& positionCurrent, const Grid<PropertiesFigure>& locationFigure) const
{
	switch (locationFigure[positionCurrent.inRow][positionCurrent.inColum].m_side)
	{
	case 1:
		return possibilityPromotionSideTop(positionCurrent, locationFigure); 
	case 2:
		return possibilityPromotionSideDown(positionCurrent, locationFigure); 
	default:
		OUTPUT_LOG_ERROR("Игрок не определен. [Figure] -> [Pawn] -> [getPossibilityPromotion] -> [case]");
		return false;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::wstring Pawn::setIdFigure() const noexcept
{
	return L"Pawn";
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<std::pair<inRowInt, inColInt>> Pawn::setAllMinimumMove() const
{
	return std::vector<std::pair<inRowInt, inColInt>>();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

static bool customCheckMoveSideTop(const Position::Coordinates& positionCurrent, Position::Coordinates positionMove, const Grid<PropertiesFigure>& locationFigure)
{
	std::vector<Position::Coordinates> availableMove = availableMoveForFigureSideTop(positionCurrent, locationFigure);

	for (const auto& move : availableMove)
	{
		if (move == positionMove) { return true; }
	}
	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

static bool customCheckMoveSideDown(const Position::Coordinates& positionCurrent, Position::Coordinates positionMove, const Grid<PropertiesFigure>& locationFigure)
{
	std::vector<Position::Coordinates> availableMove = availableMoveForFigureSideDown(positionCurrent, locationFigure);

	for (const auto& move : availableMove)
	{
		if (move == positionMove) { return true; }
	}
	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

static bool possibilityPromotionSideTop(const Position::Coordinates& positionCurrent, [[maybe_unused]] const Grid<PropertiesFigure>& locationFigure)
{
	// игрок 1 белый нижний
	return positionCurrent.inRow == 1 ? true : false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

static bool possibilityPromotionSideDown(const Position::Coordinates& positionCurrent, const Grid<PropertiesFigure>& locationFigure)
{
	// игрок 2 черный верхний
	return positionCurrent.inRow == locationFigure.size() - 2 ? true : false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

static std::vector<Position::Coordinates> availableMoveForFigureSideDown(const Position::Coordinates& positionCurrent, const Grid<PropertiesFigure>& locationFigure)
{
	// ИГРОК 2 ВЕРХНИЙ ЧЕРНЫЙ
	size_t row = locationFigure.size();
	size_t col = locationFigure.front().size();

	std::vector<Position::Coordinates> result;

	// если впереди пешки ничего нет
	if (locationFigure[(positionCurrent + Position::OffsetDownBy()).inRow][positionCurrent.inColum].m_side == 0)
	{
		result.emplace_back(positionCurrent + Position::OffsetDownBy());

		// высчитываем возможную начальную позицию пешки (2 ряд для игрока) тогда можно сходить еще на 1 клетку вперед если она не занята
		if (positionCurrent.inRow == 2 ) // на начальной позиции Side Down 
		{
			// добавляем возможный ход на 2 клетки вперед
			result.emplace_back(positionCurrent + Position::OffsetDownBy(2));
		}
	}

	// проситываем возможность взятие фигуры ПРОТИВНИКА справа и слева ИГРОКА 2
	// фигура на клетке не должна быть пустой ( side 0 ) не должна быть краем ( SIDE -1 ) и нельзя взять свою же фигуру 
	Position::Coordinates fictionPositionDownLeft = positionCurrent + Position::OffsetDiagDownLeftBy();
	if (locationFigure[fictionPositionDownLeft.inRow][fictionPositionDownLeft.inColum].m_side > 0 && locationFigure[fictionPositionDownLeft.inRow][fictionPositionDownLeft.inColum].m_side != locationFigure[positionCurrent.inRow][positionCurrent.inColum].m_side)
	{
		result.emplace_back(fictionPositionDownLeft);
	}

	Position::Coordinates fictionPositionDownRight = positionCurrent + Position::OffsetDiagDownRightBy();
	if (locationFigure[fictionPositionDownRight.inRow][fictionPositionDownRight.inColum].m_side > 0 && locationFigure[fictionPositionDownRight.inRow][fictionPositionDownRight.inColum].m_side != locationFigure[positionCurrent.inRow][positionCurrent.inColum].m_side)
	{
		result.emplace_back(fictionPositionDownRight);
	}
	return result;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

static std::vector<Position::Coordinates> availableMoveForFigureSideTop(const Position::Coordinates& positionCurrent, const Grid<PropertiesFigure>& locationFigure)
{
	// по умолчанию ИГРОК 1 НИЖНИЙ БЕЛЫЙ 
	size_t row = locationFigure.size();
	size_t col = locationFigure.front().size();

	std::vector<Position::Coordinates> result;

	// просчитываем ход на пустую клетку
	// если впереди пешки ничего нет то ход доступен

	if (locationFigure[(positionCurrent + Position::OffsetDownBy()).inRow][positionCurrent.inColum].m_side == 0)
	{
		result.emplace_back(positionCurrent + Position::OffsetDownBy());

		// высчитываем возможную начальную позицию пешки (2 ряд для игрока) тогда можно сходить еще на 1 клетку вперед если она не занята
		if (positionCurrent.inRow == row - 3) // на начальной позиции Side Down 
		{
			// добавляем возможный ход на 2 клетки вперед
			result.emplace_back(positionCurrent + Position::OffsetUpBy(2));
		}
	}

	// проситываем возможность взятие фигуры ПРОТИВНИКА справа и слева ИГРОКА 2
	// фигура на клетке не должна быть пустой ( side 0 ) не должна быть краем ( SIDE -1 ) и нельзя взять свою же фигуру 
	Position::Coordinates fictionPositionUpLeft = positionCurrent + Position::OffsetDiagUpLeftBy();
	if (locationFigure[fictionPositionUpLeft.inRow][fictionPositionUpLeft.inColum].m_side > 0 && locationFigure[fictionPositionUpLeft.inRow][fictionPositionUpLeft.inColum].m_side != locationFigure[positionCurrent.inRow][positionCurrent.inColum].m_side)
	{
		result.emplace_back(fictionPositionUpLeft);
	}

	Position::Coordinates fictionPositionUpRight = positionCurrent + Position::OffsetDiagUpRightBy();
	if (locationFigure[fictionPositionUpRight.inRow][fictionPositionUpRight.inColum].m_side > 0 && locationFigure[fictionPositionUpRight.inRow][fictionPositionUpRight.inColum].m_side != locationFigure[positionCurrent.inRow][positionCurrent.inColum].m_side)
	{
		result.emplace_back(fictionPositionUpRight);
	}
	return result;
}