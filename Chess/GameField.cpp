#include "GameField.h"


GameField::GameField(size_t countCell, int windowHeight, const sf::Font& font, sf::Color outerSide, sf::Color colorCellOne, sf::Color colorCellTwo)
{
	sizeCell = static_cast<float>(windowHeight / countCell);

	gameFieldFont = font;

	for (int row = 0; row < countCell; row++)
	{
		std::vector<sf::RectangleShape> tempVectorRectangLeShape;
		std::vector<sf::Text> tempVectorText;

		for (int col = 0; col < countCell; col++)
		{
			sf::RectangleShape cell;
			cell.setSize(sf::Vector2f(sizeCell, sizeCell));
			cell.setPosition(sf::Vector2f(static_cast<float>(sizeCell * col), static_cast<float>(sizeCell * row)));
			cell.setOutlineColor(sf::Color::Black);
			cell.setOutlineThickness(-1);

			sf::Text textCoordinate(gameFieldFont, " ");
			textCoordinate.setCharacterSize(static_cast<unsigned int>(sizeCell / 5));
			textCoordinate.setFillColor(sf::Color::Black);
			textCoordinate.setPosition(sf::Vector2f(static_cast<float>(sizeCell * col + sizeCell / 1.6), static_cast<float>(sizeCell * row + sizeCell / 1.4)));

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

		fieldCoordinate.emplace_back(tempVectorText);
		rectangleShapeOnField.emplace_back(tempVectorRectangLeShape);

	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


sf::RectangleShape GameField::getRectangleShapeOnField(size_t xPosition, size_t yPosition)
{
	if (xPosition < rectangleShapeOnField[yPosition].size() && yPosition < rectangleShapeOnField.size() && xPosition >= 0 && yPosition >= 0)
	{
		return rectangleShapeOnField[yPosition][xPosition];
	}
	else
	{
		OutputLog("Class -> GameField -> errorText xPosition or yPosition");
		return sf::RectangleShape();
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



sf::Text GameField::getFieldCoordinateOnField(size_t xPosition, size_t yPosition)
{
	if (xPosition < fieldCoordinate[yPosition].size() && yPosition < fieldCoordinate.size() && xPosition >= 0 && yPosition >= 0)
	{
		return fieldCoordinate[yPosition][xPosition];
	}
	else
	{	
		float temp = getSizeCell();
		sf::Text errorText(gameFieldFont, "errorText Text");
		errorText.setPosition(sf::Vector2f(temp * xPosition + temp / 2 , temp * yPosition + temp / 2));
		errorText.setFillColor(sf::Color::Black);
		errorText.setCharacterSize(static_cast<unsigned int>(temp / 5));
		return errorText;
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

size_t GameField::getCounRow()
{
	return rectangleShapeOnField.size();
}


size_t GameField::getCounColl(size_t no)
{
	return rectangleShapeOnField[no].size();
}


float GameField::getSizeCell() const
{
	return sizeCell;
} 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool GameField::selectCell(const GridBoolCoordinate& coordinate, sf::Color color)
{
	size_t sizeCoordinate = coordinate.size();
	size_t sizeRectangleShapeOnField = rectangleShapeOnField.size();

	if (sizeCoordinate != sizeRectangleShapeOnField)
	{
		OutputLog( "ERROR -> Class -> GameField -> selectCell -> несовпадение размеров поля:");
		OutputLog(std::to_string(sizeCoordinate) + "\\" + std::to_string(sizeRectangleShapeOnField));
		return false;
	}

	for (size_t row = 0; row < coordinate.size(); row++)
	{
		for (size_t col = 0; col < coordinate[0].size(); col++)
		{
			if (coordinate[row][col] == true)
			{
				rectangleShapeOnField[row][col].setOutlineThickness(-5); 
				rectangleShapeOnField[row][col].setOutlineColor(color);
			}
		}
	}	
	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



bool GameField::selectCell(size_t xPosition, size_t yPosition, sf::Color color)
{
	size_t sizeV = rectangleShapeOnField.size();
	size_t sizeVV = rectangleShapeOnField[0].size();

	if (xPosition < 1 || yPosition < 1 || xPosition > sizeVV - 1 || yPosition > sizeV - 1)
	{
		OutputLog("ERROR -> Class -> GameField -> selectCell -> выход за игровое поле или выделение границы:");
		OutputLog(std::to_string(sizeV) + "\\" + std::to_string(sizeVV));
		return false;
	}

	rectangleShapeOnField[yPosition][xPosition].setOutlineThickness(-5);
	rectangleShapeOnField[yPosition][xPosition].setOutlineColor(color);

	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool GameField::unselectAllCell()
{
	for (int Row = 0; Row < rectangleShapeOnField.size(); Row++)
	{
		for (int Col = 0; Col < rectangleShapeOnField[0].size(); Col++)
		{
			rectangleShapeOnField[Row][Col].setOutlineThickness(-1);
			rectangleShapeOnField[Row][Col].setOutlineColor(sf::Color::Black);
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////