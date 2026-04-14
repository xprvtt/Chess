#include "Figure.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------

Figure::Figure(int side, bool invulnerable, bool important, std::vector<PropertiesFigure> vectorPromoution) :	m_side(side),	m_invulnerable(invulnerable),	m_important(important),	m_allPromoution(vectorPromoution)
{
	vectorPromoution.empty() ? m_promoution = false : m_promoution = true;
	m_idFigure = setIdFigure();
	m_allMinimumMove = setAllMinimumMove();	
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

Figure::Figure(const Figure& othreFigure) : m_side(othreFigure.m_side),	m_idFigure(othreFigure.m_idFigure),	m_invulnerable(othreFigure.m_invulnerable),	m_important(othreFigure.m_important),	m_allPromoution(othreFigure.m_allPromoution),	m_promoution(othreFigure.m_promoution) {}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool  Figure::checkMoveForFigureOnPosition(const Position::Coordinates& positionCurrent, const Position::Coordinates& positionMove, const Grid<PropertiesFigure>& m_vectorLocationFigure) const
{
	return checkMove(positionCurrent, positionMove, m_vectorLocationFigure);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::wstring Figure::getIdFigure() noexcept
{
	return m_idFigure;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool Figure::isInvulnerable() const noexcept
{
	return m_invulnerable;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool Figure::isImportant() const noexcept
{
	return m_important;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool Figure::isPromoution() const noexcept
{
	return m_promoution;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

int Figure::getSide() const noexcept
{
	return m_side;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<PropertiesFigure> Figure::getVectorPromoution() const
{
	return m_allPromoution;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool Figure::getPromoutionFigure(const PropertiesFigure& propertiesOther) const
{
	for (const auto& properties : m_allPromoution)
	{
		// если находим такую фигуру, в которую можем превратиться
		if (properties == propertiesOther)
		{	
			return true;
		}
	}
	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

/// <summary>
/// функция проверки позиции, проверяет можно ли идти на позицию, и(или) идти дальше по траектории
/// </summary>
/// <param name="position">позиция</param>
/// <param name="side"></param>
/// <param name="mediumResult"></param>
/// <param name="figure"></param>
/// <returns> можем ли мы продолжать идти дальше?</returns>
__forceinline static bool checkCell(const Position::Coordinates& position, int side, std::vector<Position::Coordinates>& result, const PropertiesFigure& figure)
{
	if (figure.m_side == 0) [[likely]]
	{
		result.emplace_back(position);
		return true;
	}
	else if (figure.m_side > 0 && figure.m_side != side) // фигура противника добавляем возможность взятия и выходим
	{
		result.emplace_back(position);
		return false;
	}
	// фигура своей стороны или край
	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<Position::Coordinates> Figure::getMoveForFigure(const Position::Coordinates& position, const Grid<PropertiesFigure>& m_vectorLocationFigure) const
{
	Position::Coordinates maxMoveCoordinate = { m_vectorLocationFigure.size(), m_vectorLocationFigure.front().size() };
	Position::Coordinates minMoveCoordinate = { 0, 0 };

	std::vector<Position::Coordinates> result;
	result.reserve((maxMoveCoordinate.inColum + maxMoveCoordinate.inColum) * 2); // приблизительное колличество возможных ходов на основе ферьзя стоящего в центе доски

	for (const auto& minMove : m_allMinimumMove)
	{
		for (auto positionMove = position + minMove; positionMove < maxMoveCoordinate || positionMove > minMoveCoordinate; positionMove + minMove)
		{
			checkCell(positionMove, m_side, result, m_vectorLocationFigure[positionMove.inRow][positionMove.inColum]);
		}
	}
	auto customMove = customMoveForFigure(position, m_vectorLocationFigure);
	result.insert(result.end(), customMove.begin(), customMove.end());
	return result;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool Figure::checkMove(const Position::Coordinates& positionCurrent, const Position::Coordinates& positionMove, const Grid<PropertiesFigure>& m_vectorLocationFigure) const
{
	const std::vector<Position::Coordinates> allMove = getMoveForFigure(positionCurrent, m_vectorLocationFigure);

	for (const auto& move : allMove)
	{
		if (move == positionMove) { return true; }
	}
	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<Position::Coordinates> Figure::customMoveForFigure(const Position::Coordinates& position, const Grid<PropertiesFigure>& locationFigure) const
{
	// Ваша реализация ходов если проверка по минимальному ходу вам не подходит (рассмотрен пример с пешкой m_allMinimumMove) 
	// position изначальная позиция 
	// locationFigure полное расположение фигур на доске с их свойствами

	return std::vector<Position::Coordinates>();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
