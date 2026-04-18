#include "GameField.h"


GameField::GameField(size_t countCell, int windowHeight, const sf::Font& font, sf::Color outerSide, sf::Color colorCellOne, sf::Color colorCellTwo) : m_gameFieldFont(font)
{
	m_sizeCell = static_cast<float>(windowHeight / countCell);

	for (int row = 0; row < countCell; row++)
	{
		std::vector<sf::RectangleShape> tempVectorRectangLeShape;
		std::vector<sf::Text> tempVectorText;

		for (int col = 0; col < countCell; col++)
		{
			sf::RectangleShape cell;
			cell.setSize(sf::Vector2f(m_sizeCell, m_sizeCell));
			cell.setPosition(sf::Vector2f(static_cast<float>(m_sizeCell * col), static_cast<float>(m_sizeCell * row)));
			cell.setOutlineColor(sf::Color::Black);
			cell.setOutlineThickness(-1);

			sf::Text textCoordinate(m_gameFieldFont, " ");
			textCoordinate.setCharacterSize(static_cast<unsigned int>(m_sizeCell / 5));
			textCoordinate.setFillColor(sf::Color::Black);
			textCoordinate.setPosition(sf::Vector2f(static_cast<float>(m_sizeCell * col + m_sizeCell / 1.6), static_cast<float>(m_sizeCell * row + m_sizeCell / 1.4)));

			if (row == 0 || row == countCell-1 || col == 0 || col == countCell-1)
			{
				cell.setFillColor(outerSide);

				if (col > 0 && col < countCell-1)
				{
					textCoordinate.setString(std::to_string(col));
				}
				else if (row > 0 && row < countCell-1)
				{
					textCoordinate.setString(char((int)'A' - 1 + row));
				}
			}
			else if (col % 2 == 0 && row % 2 == 0 || col % 2 != 0 && row % 2 != 0)
			{
				cell.setFillColor(colorCellOne);
				textCoordinate.setString(char((int)'A' - 1 + row) + std::to_string(col));
			}
			else
			{
				cell.setFillColor(colorCellTwo);
				textCoordinate.setString(char((int)'A' - 1 + row) + std::to_string(col));
			}
			tempVectorText.emplace_back(textCoordinate);
			tempVectorRectangLeShape.emplace_back(cell);
		}

		m_fieldCoordinate.emplace_back(tempVectorText);
		m_rectangleShapeOnField.emplace_back(tempVectorRectangLeShape);

	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

sf::RectangleShape GameField::getRectangleShapeOnField(Position::Coordinates position)
{
	try
	{
		return m_rectangleShapeOnField.at(position.inRow).at(position.inColum);
	}
	catch (const std::exception& err)
	{
		OUTPUT_LOG("ERROR -> Class -> GameField -> ошибка координат: " + std::string(err.what()) + ". yPosition: " + std::to_string(position.inRow) + ", xPosition: " + std::to_string(position.inRow));
		return sf::RectangleShape();
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------


sf::Text GameField::getFieldCoordinateOnField(Position::Coordinates position)
{
	try 
	{
		return m_fieldCoordinate.at(position.inRow).at(position.inColum);
	}
	catch (const std::exception& err)
	{	
		float temp = getSizeCell();
		sf::Text errText(m_gameFieldFont, "errorText Text: " + std::string(err.what()));
		errText.setPosition(sf::Vector2f(temp * position.inColum + temp / 2 , temp * position.inRow + temp / 2));
		errText.setFillColor(sf::Color::Black);
		errText.setCharacterSize(static_cast<unsigned int>(temp / 5));
		return errText;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

size_t GameField::getCounRow()
{
	return m_rectangleShapeOnField.size();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

size_t GameField::getCounColl(size_t numberColum)
{
	return m_rectangleShapeOnField[numberColum].size();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

float GameField::getSizeCell() const
{
	return m_sizeCell;
} 

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool GameField::selectCells(const Grid2x2Bool& coordinateToHighlight, sf::Color color)
{
	if (coordinateToHighlight.empty() || validGrid(coordinateToHighlight))
	{
		OUTPUT_LOG("ERROR -> Class -> GameField -> selectCell -> grid пуст, либо невалиден. Размер: " + std::to_string(coordinateToHighlight.size()));
		return false;
	}
	if (coordinateToHighlight.size() != m_rectangleShapeOnField.size() || coordinateToHighlight.begin()->size() != coordinateToHighlight.begin()->size())
	{
		OUTPUT_LOG( "ERROR -> Class -> GameField -> selectCell -> несовпадение размеров поля:");
		OUTPUT_LOG("Размер grid: " + std::to_string(coordinateToHighlight.size()) + " : " + std::to_string(coordinateToHighlight.front().size()));
		OUTPUT_LOG("Размер поля: " + std::to_string(m_rectangleShapeOnField.size()) + " : " + std::to_string(m_rectangleShapeOnField.front().size()));
		return false;
	}

	for (auto& colum : m_rectangleShapeOnField)
	{
		for (auto& cell : colum)
		{
			cell.setOutlineThickness(-5);
			cell.setOutlineColor(color);
		}
	}	
	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool GameField::selectCell(Position::Coordinates position, sf::Color color)
{
	size_t sizeRow = m_rectangleShapeOnField.size();
	size_t sizeColum = m_rectangleShapeOnField.front().size();

	// не выделяем разметку координат
	if (position.inColum < 1 || position.inRow < 1 || position.inColum > sizeColum - 1 || position.inRow > sizeRow - 1)
	{
		OUTPUT_LOG("ERROR -> Class -> GameField -> selectCell -> выход за игровое поле или выделение границы:");
		OUTPUT_LOG("Позиция: x: " + std::to_string(position.inColum) + " , y: " + std::to_string(position.inRow) + ". Размер доски: " + std::to_string(sizeRow) + " : " + std::to_string(sizeColum));
		return false;
	}

	m_rectangleShapeOnField[position.inRow][position.inColum].setOutlineThickness(-5);
	m_rectangleShapeOnField[position.inRow][position.inColum].setOutlineColor(color);
	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool GameField::unselectAllCell() noexcept
{
	for (auto& col : m_rectangleShapeOnField)
	{
		for (auto& cell : col)
		{
			cell.setOutlineThickness(-1);
			cell.setOutlineColor(sf::Color::Black);
		}
	}
	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
bool GameField::validGrid(const std::vector<std::vector<T>>& grid) const noexcept
{
	if (grid.empty()) { return false; }

	const size_t sz = grid.begin()->size();
	for (const auto& row : grid)
	{
		if (row.size() != sz)
			return false;
	}

	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
