#include "FigureLocation.h"

FigureLocation::FigureLocation(size_t countCellOninColum, size_t countCellOninRow, int windowHeight, std::filesystem::path pathToEmptyTextureGameField, std::filesystem::path pathToEmptyTextureEdge, float precentSizeFigure) : m_countColum(countCellOninColum), m_countRow(countCellOninRow), m_sizeCell(float(windowHeight / countCellOninColum)), m_precentSizeFigure(precentSizeFigure), m_sizeRectangInCell(m_sizeCell* precentSizeFigure)
{
	if (countCellOninColum < 3 || countCellOninRow < 3)	
	{ 
		OUTPUT_LOG_WARNING("[FigureLocation] -> конструктор -> неверный размер поля (<3)");
		return;
	}	

	precentSizeFigure <= 0 ? this->m_positionRectangInCell = 0 : this->m_positionRectangInCell = (m_sizeCell - m_sizeRectangInCell) / 2;

	// РАЗМЕРЫ 	
	m_dataLocalFigure.resize(countCellOninRow, std::vector<DataFigure>(countCellOninColum)); // ДЛЯ ФИГУР НА ДОСКЕ 

	// FIXME: 
	// потенциальная проблема когда уникальных фигур может быть больше чем игровая доска 
	m_uniqueFigureLocationRectangleShape.resize(countCellOninRow, std::vector< std::pair<size_t, sf::RectangleShape >>(countCellOninColum)); // ДЛЯ УНИКАЛЬНЫХ ФИГУР

	// край - уникальная фигура
	m_dataUniqueFigure.emplace_back(std::make_shared<Space>(-1, true, false), std::make_shared<sf::Texture>(pathToEmptyTextureEdge));
	// пустая клетка - уникальная фигура
	m_dataUniqueFigure.emplace_back(std::make_shared<Space>(0), std::make_shared<sf::Texture>(pathToEmptyTextureGameField));

	for (size_t inRow = 0; inRow < countCellOninRow; inRow++)
	{
		for (size_t inColum = 0; inColum < countCellOninColum; inColum++)
		{
			auto& dataLocal = m_dataLocalFigure[inRow][inColum];
			auto& dataUniqLocation = m_uniqueFigureLocationRectangleShape[inRow][inColum];

			// если край то используем фигуру-край == Side -1
			if (inColum == 0 || inRow == 0 || inColum == countCellOninColum - 1 || inRow == countCellOninRow - 1)
			{
				const auto& dataUniqueFigure = m_dataUniqueFigure[0]; // итератор на фигуру - край 

				dataLocal.m_locationClassFigure = dataUniqueFigure.m_uniqueFigureLocationClassFigure;
				dataLocal.m_locationTexture = dataUniqueFigure.m_uniqueFigureLocationTexture;
				dataLocal.m_locationRectangleShape.setTexture(dataUniqueFigure.m_uniqueFigureLocationTexture.get(), true);
				dataLocal.m_locationRectangleShape.setTexture(dataUniqueFigure.m_uniqueFigureLocationTexture.get(), true);

				dataUniqLocation.second.setTexture(dataUniqueFigure.m_uniqueFigureLocationTexture.get(), true);
				dataUniqLocation.first = 0;
			}
			else // в противном случае считаем как пустая клетка == Side 0
			{
				const auto& dataUniqueFigure = m_dataUniqueFigure[1]; // итератор на пустую фигуру space

				dataLocal.m_locationClassFigure = dataUniqueFigure.m_uniqueFigureLocationClassFigure;
				dataLocal.m_locationTexture = dataUniqueFigure.m_uniqueFigureLocationTexture;
				dataLocal.m_locationRectangleShape.setTexture(dataUniqueFigure.m_uniqueFigureLocationTexture.get(), true);

				dataUniqLocation.second.setTexture(dataUniqueFigure.m_uniqueFigureLocationTexture.get(), true);
			}
			
			//--//--//--//--//--//--//--//--//--//   ДЛЯ ФИГУР НА ДОСКЕ  //--//--//--//--//--//--//--//--//--//--//--//--//--//-//
			dataLocal.m_locationRectangleShape.setSize(sf::Vector2f(m_sizeCell, m_sizeCell));
			dataLocal.m_locationRectangleShape.setPosition(sf::Vector2f(inColum * m_sizeCell, inRow * m_sizeCell));


			//--//--//--//--//--//--//--//--//--//     ДЛЯ УНИКАЛЬНЫХ ФИГУР   //--//--//--//--//--//--//--//--//--//--//--//--//--//
			dataUniqLocation.second.setSize(sf::Vector2f(m_sizeCell * precentSizeFigure, m_sizeCell * precentSizeFigure));
			dataUniqLocation.second.setPosition(sf::Vector2f(inColum * m_sizeCell * precentSizeFigure + windowHeight, inRow * m_sizeCell * precentSizeFigure + windowHeight / 2 ));
			dataUniqLocation.second.setOutlineColor(sf::Color::Black);

			m_vectorLocationFigure[inRow][inColum].m_side = dataLocal.m_locationClassFigure->getSide();
			m_vectorLocationFigure[inRow][inColum].m_idFigure = dataLocal.m_locationClassFigure->getIdFigure();
			m_vectorLocationFigure[inRow][inColum].m_invulnerable = dataLocal.m_locationClassFigure->isInvulnerable();
			m_vectorLocationFigure[inRow][inColum].m_important = dataLocal.m_locationClassFigure->isImportant();
			m_vectorLocationFigure[inRow][inColum].m_promoution = dataLocal.m_locationClassFigure->isPromoution();
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------


//--//--//--//--//--//--//--//--//--//    ДЛЯ ФИГУР НА ДОСКЕ   //--//--//--//--//--//--//--//--//--//--//--//--//

// установка по сухим параметрам устаревает => апнуть полноценную замену =>
// bool FigureLocation::setFigure(Position::Coordinates position, PropertiesFigure pF)
//[[deprecated]]
bool FigureLocation::setFigure(Position::Coordinates position, std::wstring idFigure, int side, bool invulnerable, bool important, [[maybe_unused]] std::vector<PropertiesFigure> vectorPromoution /* нет проверки (!) */)
{
	if (m_dataLocalFigure.size() <= position.inRow || m_dataLocalFigure[position.inRow].size() <= position.inColum)
	{
		OUTPUT_LOG_ERROR("Class -> FigureLocation -> SetFigure -> попытка установить ЗА границу");
		return false;		
	}

	if (m_dataLocalFigure[position.inRow][position.inColum].m_locationClassFigure->getSide() == -1)
	{
		OUTPUT_LOG_ERROR("Class -> FigureLocation -> SetFigure -> попытка установить НА границу");
		return false;
	}

	for (int it = 0; it < m_dataUniqueFigure.size(); it++)
	{
		// находим итератор указанной финугы
		if (   m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->getSide()         == side
			&& m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->getIdFigure()     == idFigure
			&& m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->isInvulnerable()  == invulnerable
			&& m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->isImportant()     == important
		   )
		{
			// станавливаем текстуру фигуры на поле
			m_dataLocalFigure[position.inRow][position.inColum].m_locationTexture = m_dataUniqueFigure[it].m_uniqueFigureLocationTexture;

			// устанавливаем позицию и размер фигуры -> меньше чем пустая клетка или край
			m_dataLocalFigure[position.inRow][position.inColum].m_locationRectangleShape.setSize(sf::Vector2f(m_sizeCell * m_precentSizeFigure, m_sizeCell * m_precentSizeFigure));
			m_dataLocalFigure[position.inRow][position.inColum].m_locationRectangleShape.setPosition(sf::Vector2f(position.inColum * m_sizeCell + m_positionRectangInCell, position.inRow * m_sizeCell + m_positionRectangInCell));

			// передаем установленную текстуру
			m_dataLocalFigure[position.inRow][position.inColum].m_locationRectangleShape.setTexture(m_dataLocalFigure[position.inRow][position.inColum].m_locationTexture.get());

			// ставим класс фигуры на поле
			m_dataLocalFigure[position.inRow][position.inColum].m_locationClassFigure = m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure;

			return true;
		}
	}
	OUTPUT_LOG_ERROR("Class -> FigureLocation -> SetFigure -> фигура не найдена, сначала ее необходимо добавить -> AddUniqueFigure()");
	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool FigureLocation::setFigure(Position::Coordinates position, PropertiesFigure pF, const std::vector<PropertiesFigure>& vectorPromoution)
{
	return setFigure(position, pF.m_idFigure, pF.m_side, pF.m_invulnerable, pF.m_important, vectorPromoution);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool FigureLocation::setFigureVector(const std::vector<PositionAndPropertiesFigure>& locationFigure)
{
	bool result = true;

	for (const auto& currentFigure : locationFigure)
	{		
		if (!setFigure( currentFigure.m_position, currentFigure.m_propertions, currentFigure.m_gridPromoution  )
		   )
		{
			std::wstring ws = currentFigure.m_propertions.m_idFigure;			
			OUTPUT_LOG("ERROR -> Class -> FigureLocation -> setFigureVector -> фигура не размещена или размещена с ошибкой координат: \t" + std::filesystem::path(ws).string() + "\tряд " + std::to_string(currentFigure.m_position.inRow) + ", столбец " + std::to_string(currentFigure.m_position.inColum));

			result = false;
		}
		
	}

	return result;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool FigureLocation::promoutionSelectFigure(const PropertiesFigure& properties)
{
	// фигура может превратиться в указанную фигуру?.........
	if (m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationClassFigure->getPromoutionFigure(properties))
	{
		for (int it = 0; it < m_dataLocalFigure.size(); it++)
		{
			if ( m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->getIdFigure() == properties.m_idFigure &&
				 m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->getSide() == m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationClassFigure->getSide()
			   )
			{
				// заменяем текстуру
				m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationTexture = m_dataUniqueFigure[it].m_uniqueFigureLocationTexture;

				// передаем установленную текстуру
				m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationRectangleShape.setTexture(m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationTexture.get());

				// ставим класс фигуры на поле
				m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationClassFigure = m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure;

				return true;
			}
		}
		OUTPUT_LOG("Error -> Class -> FigureLocation -> promoutionSelectFigure() -> не найден итератор");
	}
	else
	{
		OUTPUT_LOG("Error -> Class -> FigureLocation -> promoutionSelectFigure() -> невозможно превратиться в эту фигуру");
	}

	return false;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------

bool FigureLocation::addUniqueFigure(std::shared_ptr<Figure> newFigureOrHeirs, std::filesystem::path currentTextureFigure)
{
	// изначально считаем что фигура уникальная 
	// проверяем есть ли такие фигуры у нас еще?
	// начинаем с 2 т.к. 0 и 1 слоты заняты заранее "краем" и пустой фигурой (видимой как пустая клетка) соответственно
	for (int it = 2; it < m_dataUniqueFigure.size(); it++)
	{
		// если поля совпадают значит не уникальна и не добавляем
		if (   m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure.get()->getIdFigure()          == newFigureOrHeirs.get()->getIdFigure()
			&& m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure.get()->getSide()              == newFigureOrHeirs.get()->getSide()
			&& m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure.get()->isInvulnerable()      == newFigureOrHeirs.get()->isInvulnerable()
			&& m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure.get()->isImportant()         == newFigureOrHeirs.get()->isImportant()
			&& m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure.get()->getVectorPromoution()  == newFigureOrHeirs.get()->getVectorPromoution()
		   )
		{			
			return false;
		}	
	}
	// иначе, если поля отличаются добавляем
	m_dataUniqueFigure.emplace_back(newFigureOrHeirs, std::make_shared<sf::Texture>(currentTextureFigure));

	for (size_t row = 1; row < m_countRow - 1; row++)
	{
		for (size_t col = 1; col < m_countColum - 1; col++)
		{
			// если клетка пустая то сразу же размещаем никальную фигуру на поле уникальных фигур
			if (m_uniqueFigureLocationRectangleShape[row][col].first == 0)
			{
				size_t latestElement = m_dataUniqueFigure.size() - 1;

				// ставим текстуру
				m_uniqueFigureLocationRectangleShape[row][col].second.setTexture(m_dataUniqueFigure[latestElement].m_uniqueFigureLocationTexture.get());
				m_uniqueFigureLocationRectangleShape[row][col].second.setOutlineThickness(-2);
				m_uniqueFigureLocationRectangleShape[row][col].second.setOutlineColor(sf::Color::Black);

				// ставим итератор откуда привязали
				m_uniqueFigureLocationRectangleShape[row][col].first = latestElement;
				return true;
			}
		}
	}	
	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool FigureLocation::addUniqueVectorFigure(std::vector<std::pair<std::shared_ptr<Figure>, std::filesystem::path>> vectorUniqueFigure)
{
	bool result = true;

	for (const auto& [figure, path] : vectorUniqueFigure)
	{
		if (!addUniqueFigure(figure, path))
		{
			std::string id = std::filesystem::path(figure.get()->getIdFigure()).string();
			OUTPUT_LOG("Error -> Class -> FigureLocation -> addUniqueVectorFigure -> фигура не добавлена:\t" + id);
			result = false;
		}
	}

	return result;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool FigureLocation::moveSelectFigure(Position::Coordinates position)
{
	auto availableMove = getAvailableMovesForFigure(m_positionSelectFigure);

	bool exists = false;

	for (const auto& move : availableMove)
	{ 
		if (move.inColum == position.inColum && move.inRow == position.inRow)
		{
			exists = true;
		}
	}

	if (!exists)
	{
		OUTPUT_LOG("ход невозможен");
		return false;
	}

	if (m_dataLocalFigure[position.inRow][position.inColum].m_locationClassFigure->getSide() == 0)
	{
		swap(m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationClassFigure, m_dataLocalFigure[position.inRow][position.inColum].m_locationClassFigure);
		swap(m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationTexture, m_dataLocalFigure[position.inRow][position.inColum].m_locationTexture);

		// изменяем размер и положение
		m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationRectangleShape.setSize(sf::Vector2f(m_sizeCell, m_sizeCell));
		m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationRectangleShape.setPosition(sf::Vector2f(m_sizeCell * m_positionSelectFigure.inColum, m_sizeCell * m_positionSelectFigure.inRow));

		// установили тестуры т.к. они свапнуты
		m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationRectangleShape.setTexture(m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationTexture.get());

		// изменяем размер и положение
		m_dataLocalFigure[position.inRow][position.inColum].m_locationRectangleShape.setSize(sf::Vector2f(m_sizeCell * m_precentSizeFigure, m_sizeCell * m_precentSizeFigure));
		m_dataLocalFigure[position.inRow][position.inColum].m_locationRectangleShape.setPosition(sf::Vector2f(m_sizeCell * position.inColum + m_positionRectangInCell, m_sizeCell * position.inRow + m_positionRectangInCell));

		// установили тестуры т.к. они свапнуты
		m_dataLocalFigure[position.inRow][position.inColum].m_locationRectangleShape.setTexture(m_dataLocalFigure[position.inRow][position.inColum].m_locationTexture.get());

		return true;
	}
	else
	{	
		// если клетка не пустая предполагается что там фигура другого игрока

		// Фигура должна быть доступна для взятия т.е. Invulnerability = false
		if (m_dataLocalFigure[position.inRow][position.inColum].m_locationClassFigure->isInvulnerable())
		{
			OUTPUT_LOG("ERROR -> class -> FigureLocation -> moveSelectFigure() -> фигура неуязвима");
			return false;
		}

		swap(m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationClassFigure, m_dataLocalFigure[position.inRow][position.inColum].m_locationClassFigure);
		swap(m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationTexture, m_dataLocalFigure[position.inRow][position.inColum].m_locationTexture);
		
		m_dataLocalFigure[position.inRow][position.inColum].m_locationRectangleShape.setSize(sf::Vector2f(m_sizeCell * m_precentSizeFigure, m_sizeCell * m_precentSizeFigure));
		m_dataLocalFigure[position.inRow][position.inColum].m_locationRectangleShape.setPosition(sf::Vector2f(m_sizeCell * position.inColum + m_positionRectangInCell, m_sizeCell * position.inRow + m_positionRectangInCell));

		m_dataLocalFigure[position.inRow][position.inColum].m_locationRectangleShape.setTexture(m_dataLocalFigure[position.inRow][position.inColum].m_locationTexture.get());
		
		// 1 - пустая текстура		
		m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationTexture = m_dataUniqueFigure[1].m_uniqueFigureLocationTexture;

		// 1 - пустая фигура (клетка)
		m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationClassFigure = m_dataUniqueFigure[1].m_uniqueFigureLocationClassFigure;
		
		m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationRectangleShape.setSize(sf::Vector2f(m_sizeCell, m_sizeCell));
		m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationRectangleShape.setPosition(sf::Vector2f(m_sizeCell * m_positionSelectFigure.inColum, m_sizeCell * m_positionSelectFigure.inRow));
		
		m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationRectangleShape.setTexture(m_dataLocalFigure[m_positionSelectFigure.inRow][m_positionSelectFigure.inColum].m_locationTexture.get());

		return true;
	}

	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

Position::Coordinates FigureLocation::getPositionFigureWhenMousePressed(sf::Vector2f positonMouse)  const
{
	for (size_t row = 0; row < m_countColum; row++)
	{
		for (size_t colum = 0; colum < m_countColum; colum++)
		{
			// если задели фигуру на игровом поле
			if (m_dataLocalFigure[row][colum].m_locationRectangleShape.getGlobalBounds().contains(positonMouse))
			{
				return { row, colum };
			}
		}
	}
	return {0, 0};
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool FigureLocation::seletcFigure(Position::Coordinates position)
{
	int sideFigure = m_dataLocalFigure[position.inRow][position.inColum].m_locationClassFigure->getSide();

	if (sideFigure == 0 || sideFigure == -1)
	{
		return false;
	}
	if (m_selectFigure)
	{
		unseletcAllFigure();
	}

	m_dataLocalFigure[position.inRow][position.inColum].m_locationRectangleShape.setOutlineThickness(-3);
	m_dataLocalFigure[position.inRow][position.inColum].m_locationRectangleShape.setOutlineColor(sf::Color::Red);

	m_positionSelectFigure = position; 
	m_selectFigure = true;

	return m_selectFigure;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool FigureLocation::unseletcAllFigure()
{
	for (auto& row : m_dataLocalFigure)
	{
		for (auto& cell : row)
		{
			cell.m_locationRectangleShape.setOutlineThickness(0);
		}
	}

	m_positionSelectFigure = { 0, 0 };
	m_selectFigure = false;

	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool FigureLocation::figuresSelectedOrNot() const noexcept
{
	return m_selectFigure;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

Position::Coordinates FigureLocation::getPositionSelectFigure() const
{
	return m_positionSelectFigure;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<Position::Coordinates> FigureLocation::getAvailableMovesForFigure(Position::Coordinates position)
{
	return m_dataLocalFigure[position.inRow][position.inColum].m_locationClassFigure->getMoveForFigure(position, getLocationFigure());
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool FigureLocation::isPromoutionFigureOnPosition(Position::Coordinates position)
{
	return m_dataLocalFigure[position.inRow][position.inColum].m_locationClassFigure->getPossibilityPromotion(position, getLocationFigure());
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

Grid<PropertiesFigure> FigureLocation::getLocationFigure()
{
	updateLocationFigure();
	return m_vectorLocationFigure;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void FigureLocation::updateLocationFigure()
{
	for (size_t inRow = 0; inRow < m_countColum; inRow++)
	{
		for (size_t inColum = 0; inColum < m_countColum; inColum++)
		{
			m_vectorLocationFigure[inRow][inColum].m_side         = m_dataLocalFigure[inRow][inColum].m_locationClassFigure->getSide();
			m_vectorLocationFigure[inRow][inColum].m_idFigure     = m_dataLocalFigure[inRow][inColum].m_locationClassFigure->getIdFigure();
			m_vectorLocationFigure[inRow][inColum].m_invulnerable = m_dataLocalFigure[inRow][inColum].m_locationClassFigure->isInvulnerable();
			m_vectorLocationFigure[inRow][inColum].m_important    = m_dataLocalFigure[inRow][inColum].m_locationClassFigure->isImportant();
			m_vectorLocationFigure[inRow][inColum].m_promoution   = m_dataLocalFigure[inRow][inColum].m_locationClassFigure->isPromoution();
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::wstring FigureLocation::getIdFigure(Position::Coordinates position) const
{
	return m_dataLocalFigure[position.inRow][position.inColum].m_locationClassFigure->getIdFigure();
}

int FigureLocation::getSideFigure(Position::Coordinates position) const
{
	return m_dataLocalFigure[position.inRow][position.inColum].m_locationClassFigure->getSide();
}

const sf::RectangleShape& FigureLocation::getRectangleShapeFigure(Position::Coordinates position) const
{
	return m_dataLocalFigure[position.inRow][position.inColum].m_locationRectangleShape;
}

bool FigureLocation::getInvulnerableFigure(Position::Coordinates position) const
{
	return m_dataLocalFigure[position.inRow][position.inColum].m_locationClassFigure->isInvulnerable();
}

bool FigureLocation::getImportantFigure(Position::Coordinates position) const
{
	return m_dataLocalFigure[position.inRow][position.inColum].m_locationClassFigure->isImportant();
}

PropertiesFigure FigureLocation::getPropertiesFigure(Position::Coordinates position)
{	
	return { getIdFigure(position), getSideFigure(position), getInvulnerableFigure(position), getImportantFigure(position), isPromoutionUniqueFigire(position) };
}


//--//--//--//--//--//--//--//--//--//      ДЛЯ ПОЛЕ УНИКАЛЬНЫХ ФИГУР     //--//--//--//--//--//--//--//--//--//--//--//-//

bool FigureLocation::isInvulnerableUniqueFigire(const Position::Coordinates& position)
{
	size_t it = getIteratorUniqueFigure(position);
	return m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->isInvulnerable();
}

std::wstring FigureLocation::geIdUniqueFigure(const Position::Coordinates& position)
{
	size_t it = getIteratorUniqueFigure(position);
	return m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->getIdFigure();
}

int FigureLocation::getSideUniqueFigure(const Position::Coordinates& position)
{
	size_t it = getIteratorUniqueFigure(position);
	return m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->getSide();
}

bool FigureLocation::isImportantUniqueFigire(const Position::Coordinates& position)
{
	size_t it = getIteratorUniqueFigure(position);
	return m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->isImportant();
}

bool FigureLocation::isPromoutionUniqueFigire(const Position::Coordinates& position)const
{
	size_t it = getIteratorUniqueFigure(position);
	return m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->isPromoution();
}

const sf::RectangleShape& FigureLocation::getRectangleShapeUniqueFigure(const Position::Coordinates& position)const
{
	return m_uniqueFigureLocationRectangleShape[position.inRow][position.inColum].second;
}

size_t FigureLocation::getIteratorUniqueFigure(Position::Coordinates position)const
{
	return m_uniqueFigureLocationRectangleShape[position.inRow][position.inColum].first;
}

size_t FigureLocation::getIteratorUniqueFigure(PropertiesFigure otherFigure) const
{
	for (size_t it = 0; it < m_dataUniqueFigure.size(); it++)
	{
		// если находим такую фигуру то возвращаем итератор
		if (m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->getIdFigure() == otherFigure.m_idFigure
			&& m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->getSide() == otherFigure.m_side
			&& m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->isInvulnerable() == otherFigure.m_invulnerable
			&& m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->isImportant() == otherFigure.m_important
			&& m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->isPromoution() == otherFigure.m_promoution
			)
		{
			return it;
		}
	}
	return -1;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//bool FigureLocation::checkMoveForFigure(size_t inColumCurrent, size_t inRowCurrent, size_t inColumMove, size_t inRowMove, const GridPropertiesFigure& m_vectorLocationFigure)
//{
//	return false;
//}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool FigureLocation::selectForPromoutionUniqueFigure(const Position::Coordinates& position)
{
	// выделяем фигуры в которые может превратиться фигура

	const auto& localFigure = m_dataLocalFigure[position.inRow][position.inColum].m_locationClassFigure;

	for ( auto& vectorRectangleShape : m_uniqueFigureLocationRectangleShape)
	{
		for ( auto& rectangleShape : vectorRectangleShape)
		{
			size_t it = rectangleShape.first;
			const auto& uniqueFigure = m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure;

			// если фигура той же стороны
			if (uniqueFigure->getSide() == localFigure->getSide())
			{
				// и может превратиться в указанную фигуру???...
				if (localFigure->getPromoutionFigure({ uniqueFigure->getIdFigure(),uniqueFigure->getSide(),uniqueFigure->isInvulnerable(),uniqueFigure->isImportant(),uniqueFigure->isPromoution() }) )
				{
					// подсвечиваем фигуру
					rectangleShape.second.setOutlineColor(sf::Color::Red);
				}
			}
		}
	}
	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool FigureLocation::unselectUniqueFigure()
{
	for (auto& vectorRectangleShape : m_uniqueFigureLocationRectangleShape)
	{
		for (auto& rectangleShape : vectorRectangleShape)
		{
			rectangleShape.second.setOutlineColor(sf::Color::Black);
		}
	}
	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

Position::Coordinates FigureLocation::getPositionOnMousePositionUniqueFigire(const sf::Vector2f& positonMouse)
{
	for (size_t inRow = 0; inRow < m_countRow; inRow++)
	{
		for (size_t inColum = 0; inColum < m_countColum; inColum++)
		{
			// если задели фигуру на поле уникальных фигур возвращаем позицию в минусе
			if (m_uniqueFigureLocationRectangleShape[inRow][inColum].second.getGlobalBounds().contains(positonMouse))
			{
				return  { inRow, inColum };
			}
		}
	}
	return { 0, 0 };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<Position::Coordinates> FigureLocation::checkThreatForFigure(const Position::Coordinates position, const  Grid<PropertiesFigure>& m_vectorLocationFigure)
{
	const auto sideCurrentFigure = m_vectorLocationFigure[position.inRow][position.inColum].m_side;

	size_t maxSize = m_countRow * m_countColum;

	//std::vector<std::future<std::vector<Position::Coordinates>>> threadForCalculate;
	//threadForCalculate.reserve(maxSize);

	//size_t maxThread = std::thread::hardware_concurrency(); 
	//if (!maxThread) { maxThread = 1; }

	//const size_t countOpcOnThread = static_cast<size_t>(maxSize / maxThread); // колличество операций на поток

	std::vector<Position::Coordinates> resultPositionEnemyFigure;

	// проверяем все фигуры на переданном игровом поле у других игроков, которые могу "угрожать взятием"
	for (size_t rowPosition = 0; rowPosition < m_countRow; rowPosition++)
	{
		//threadForCalculate.emplace_back(std::thread(std::launch::deferred, [=] {
		for (size_t colPosition = 0; colPosition < m_countColum; colPosition++)
		{			
			const auto figure = m_vectorLocationFigure[rowPosition][colPosition];

			//std::vector<Position::Coordinates>  resultThreadPos;
			//resultThreadPos.reserve(m_countColum);

			// если у фигуры на позиции другая сторона, то проверяем далее....
			if (figure.m_side != sideCurrentFigure && figure.m_side > 0)
			{
				size_t it = getIteratorUniqueFigure({ figure.m_idFigure, figure.m_side,figure.m_invulnerable,figure.m_important,figure.m_promoution });

				// ходы на которые может сходить фигура
				auto allMovePosFigure = m_dataUniqueFigure[it].m_uniqueFigureLocationClassFigure->getMoveForFigure({ rowPosition, colPosition }, m_vectorLocationFigure);

				for (const auto& movePosFigure : allMovePosFigure) {
					if (movePosFigure == position)
					{
						resultPositionEnemyFigure.emplace_back(rowPosition, colPosition);
					}
				}
			}

		}
	}

	//for (const auto& allMove : distribAllMove)
	//{
	//	for (const auto& move :  allMove)
	//	{
	//		resultPositionEnemyFigure.push_back(move);
	//	}
	//}	

	return resultPositionEnemyFigure;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<Position::Coordinates> FigureLocation::getPositionFigure(int side, std::wstring idFigure, bool invulnerable, bool important, bool promoution)
{
	return positionFigure(side, idFigure, invulnerable, important, promoution);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<Position::Coordinates> FigureLocation::getPositionFigure(int side, std::wstring idFigure)
{
	return positionFigure(side, idFigure, m_numException, m_numException, m_numException);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<Position::Coordinates> FigureLocation::getPositionFigure(int side)
{
	return positionFigure(side, m_wsExceprion, m_numException, m_numException, m_numException);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<Position::Coordinates> FigureLocation::getPositionsFigure(int side, bool invulnerableOrImportantOrPromoution , char IMP )
{
	switch (IMP)
	{
	case 'I':
		return positionFigure(side, m_wsExceprion, invulnerableOrImportantOrPromoution, m_numException, m_numException);

	case 'M':
		return positionFigure(side, m_wsExceprion, m_numException, invulnerableOrImportantOrPromoution, m_numException);

	case 'P':
		return positionFigure(side, m_wsExceprion, m_numException, m_numException, invulnerableOrImportantOrPromoution);

	default:
		return std::vector<Position::Coordinates>();
	}	
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<Position::Coordinates> FigureLocation::positionFigure(int side, std::wstring idFigure, int invulnerable, int important, int promoution)
{
	std::vector<Position::Coordinates> position;

	for (size_t yPos = 0; yPos < m_countRow; yPos++)
	{
		for (size_t xPos = 0; xPos < m_countColum; xPos++)
		{
			// если поля совпадают то добавляем

			// если передан параметр numException значение не учитывается, так же и wsExceprion 
			if (    (  idFigure     == m_wsExceprion  || ( m_dataLocalFigure[yPos][xPos].m_locationClassFigure->getIdFigure()                       == idFigure     && idFigure != m_wsExceprion) )
				 && (  side         == m_numException || ( static_cast<int>(m_dataLocalFigure[yPos][xPos].m_locationClassFigure->getSide())         == side         && side != m_numException   ) )
				 && (  invulnerable == m_numException || ( static_cast<int>(m_dataLocalFigure[yPos][xPos].m_locationClassFigure->isInvulnerable()) == invulnerable && side != m_numException   ) )
				 && (  important    == m_numException || ( static_cast<int>(m_dataLocalFigure[yPos][xPos].m_locationClassFigure->isImportant())    == important    && side != m_numException   ) )
				 && (  promoution   == m_numException || ( static_cast<int>(m_dataLocalFigure[yPos][xPos].m_locationClassFigure->isPromoution())   == promoution   && side != m_numException   ) )
			   )
			{
				position.emplace_back(xPos, yPos);
			}
		}
	}
	return position;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool FigureLocation::isCheckmateForFigure(const Position::Coordinates& position, const Grid<PropertiesFigure>& m_vectorLocationFigure)
{
	auto tempResult = getPositionFigureCanProtectedIndicatedFigure(position, m_vectorLocationFigure);

	if (tempResult.size() == 1 && tempResult.front() == Position::Coordinates( 0, 0 ))
	{
		return true;
	}

	return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<Position::Coordinates> FigureLocation::getPositionFigureCanProtectedIndicatedFigure(const Position::Coordinates& position, const Grid<PropertiesFigure>& m_vectorLocationFigure)
{
	int currentSideFigure = m_dataLocalFigure[position.inRow][position.inColum].m_locationClassFigure->getSide();
	
	// край и пустую клетку не проверяем, нет смысла
	if (currentSideFigure == 0 || currentSideFigure == -1) 
	{		
		return std::vector<Position::Coordinates>(); // возвращаем пустой ничего не угрожает
	}

	// если фигур, которые угрожают == 0, то логично, что ничего ему не угрожает
	if (checkThreatForFigure(position, m_vectorLocationFigure).empty())
	{		
		return std::vector<Position::Coordinates>(); // возвращаем пустой ничего не угрожает
	}

	// позиции всех фигур текущего игрока
	auto positionAllFigureForPlayer = getPositionFigure(currentSideFigure);


	
	// позиции фигур которые могут защитить
	std::vector<Position::Coordinates> resultPositionFigure;


	// проверяем может ли какая-то фигура текущего игрока куда-то передвинуться, чтобы исключить шах 
	// проходимся по каждой фигуре 
	for (const auto& curentPosFigure : positionAllFigureForPlayer)
	{
		// получаем доступные ходы для текущей фигуры
		auto moveForFigure = m_dataLocalFigure[curentPosFigure.inRow][curentPosFigure.inColum].m_locationClassFigure->getMoveForFigure(curentPosFigure, m_vectorLocationFigure);

		// проходимся по всему вектору ходов
		for (const auto& move : moveForFigure)
		{
			// создаем фиктивное расположение фигур
			auto imaginaryLocation = m_vectorLocationFigure;
			
			// создаем фиктивный ход 
			// свапаем "передвигая" фигуру
			PropertiesFigure tempPropertiesFigure = imaginaryLocation[curentPosFigure.inRow][curentPosFigure.inColum];
			imaginaryLocation[curentPosFigure.inRow][curentPosFigure.inColum] = imaginaryLocation[move.inRow][move.inColum];
			imaginaryLocation[move.inRow][move.inColum] = tempPropertiesFigure;

			//swap(imaginaryLocation[curentPosFigure.second][curentPosFigure.first], imaginaryLocation[move.second][move.first]);

			// устанавливаем пустую фигуру (клетку) на бывшую позицию 
			imaginaryLocation[curentPosFigure.inRow][curentPosFigure.inColum] = { L"Figure", 0, false, false, false };

			// начальная позиция проверяемой фигуры х \ у
			Position::Coordinates currentPositionCheckedFigure = position;

			// если мы дошли до проверки ходов у изначально проверяемой фигуры
			if (currentPositionCheckedFigure == curentPosFigure)
			{
				// устанавливаем новое фиктивное положение для ПРОВЕРЯЕМОЙ фигуры
				currentPositionCheckedFigure = move;
			}
			// проверяем угрозу с фиктивным расположением
			auto thFigure = checkThreatForFigure(currentPositionCheckedFigure, imaginaryLocation);
		
			// считаем колличество фигур которые могут угрожать на этом ходу
			// если колличество угрожающих фигур == 0, то мата нет, фигура может закрыть важную фигуру или убить своим ходом
			if (thFigure.size() == 0)
			{
				resultPositionFigure.emplace_back(curentPosFigure);
			}			
		}		
	}

	// возвращаем 0,0 позицию, если угрозу не избежать // пустой если угроз не найдено // или заполенный фигурами, которые могут задефать
	return resultPositionFigure.empty() ? std::vector<Position::Coordinates>(1, { 0, 0 } ) : resultPositionFigure;
}
