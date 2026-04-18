#include "Figure.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------

Figure::Figure(int side, bool invulnerable, bool important, std::vector<PropertiesFigure> vectorPromoution) :	m_side(side),	m_invulnerable(invulnerable),	m_important(important),	m_allPromoution(vectorPromoution)
{
	vectorPromoution.empty() ? m_promoution = false : m_promoution = true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

Figure::Figure(const Figure& othreFigure) : m_side(othreFigure.m_side),	m_idFigure(othreFigure.m_idFigure),	m_invulnerable(othreFigure.m_invulnerable),	m_important(othreFigure.m_important),	m_allPromoution(othreFigure.m_allPromoution),	m_promoution(othreFigure.m_promoution) {}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool  Figure::checkMoveForFigureOnPosition(const Position::Coordinates& positionCurrent, const Position::Coordinates& positionMove, const Grid<PropertiesFigure>& m_vectorLocationFigure)
{
	return checkMove(positionCurrent, positionMove, m_vectorLocationFigure);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::wstring Figure::getIdFigure() noexcept
{
	if(m_idFigure.empty())
	{
		m_idFigure = setIdFigure();
	}
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
	if (m_allPromoution.empty())
	{
		OUTPUT_LOG_ERROR("Class -> Figure -> getPromoutionFigure() -> невозможно превратиться в эту фигуру: причина m_allPromoution пустой");
		return false;
	}
	for (const auto& properties : m_allPromoution)
	{
		// если находим такую фигуру, в которую можем превратиться
		if (properties == propertiesOther)
		{
			return true;
		}
	}
	OUTPUT_LOG_ERROR("Class -> Figure -> getPromoutionFigure() -> невозможно превратиться в эту фигуру: причина отсутствует подходящие properties в m_allPromoution");

	DEBUG_CODE(
		OUTPUT_LOG_ERROR("Свойства фигур для превращения: ");
		int i = 0;
		for (const auto& property : m_allPromoution)
		{
			OUTPUT_LOG_ERROR("Свойство #" + std::to_string(i++));
			OUTPUT_LOG_ERROR("m_idFigure " + std::filesystem::path(property.m_idFigure).string());
			OUTPUT_LOG_ERROR("m_side " + std::to_string(property.m_side));
			OUTPUT_LOG_ERROR("m_invulnerable " + std::to_string(property.m_invulnerable));
			OUTPUT_LOG_ERROR("m_important " + std::to_string(property.m_important));
			OUTPUT_LOG_ERROR("m_promoution " + std::to_string(property.m_promoution));
		 }
	);
	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<Position::Coordinates> Figure::getMoveForFigure(const Position::Coordinates& position, const Grid<PropertiesFigure>& vectorLocationFigure) 
{
	const Position::Coordinates max = { vectorLocationFigure.size(), vectorLocationFigure.front().size() };
	const Position::Coordinates min = { 0, 0 };

	const auto currentSideFigure = vectorLocationFigure[position.inRow][position.inColum].m_side;

	std::vector<Position::Coordinates> result;
	result.reserve((max.inColum * 4)); // приблизительное колличество возможных ходов на основе ферьзя стоящего в центе доски

	if (m_allMinimumMove.empty())
	{
		m_allMinimumMove = setAllMinimumMove();
	}
	for (const auto& [minMove, howMany] : m_allMinimumMove)
	{
		auto positionMove = position + minMove;

		HowMany currentNumMove = 0;
		HowMany maxCount = !howMany ? std::numeric_limits<HowMany>::max() : howMany;

		while ((currentNumMove < maxCount) && /* не выход за границы доски */
			   (positionMove.inRow < max.inRow && positionMove.inColum < max.inColum) && (positionMove.inRow > min.inRow && positionMove.inColum > min.inColum))			   
		{
			auto sideFigureOnCell = vectorLocationFigure[positionMove.inRow][positionMove.inColum].m_side;

			if (sideFigureOnCell == 0)
			{
				result.push_back(positionMove);
			}
			else if (sideFigureOnCell > 0 && sideFigureOnCell != currentSideFigure) // фигура противника добавляем возможность взятия и выходим
			{
				result.push_back(positionMove);
				break;
			}
			else // фигура своей стороны или край
			{
				break;
			}
			positionMove = positionMove + minMove;
			currentNumMove++;
		}
	}
	auto customMove = customMoveForFigure(position, vectorLocationFigure);
	result.insert(result.end(), customMove.begin(), customMove.end());
	return result;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::wstring Figure::setIdFigure() const noexcept
{
	return L"Figure";
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool Figure::checkMove(const Position::Coordinates& positionCurrent, const Position::Coordinates& positionMove, const Grid<PropertiesFigure>& vectorLocationFigure)
{
	const auto allMove = getMoveForFigure(positionCurrent, vectorLocationFigure);

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

std::vector<std::pair<MinimumMoveRowColInt, HowMany>> Figure::setAllMinimumMove() const
{
	return std::vector<std::pair<MinimumMoveRowColInt, HowMany>>();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
