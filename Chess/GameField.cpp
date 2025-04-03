#include "GameField.h"


GameField::GameField(size_t CountCell, int WindowHeight, const Font& font, Color OuterSide, Color ColorCellOne, Color ColorCellTwo)
{
	SizeCell = static_cast<float>(WindowHeight / CountCell);

	GameFieldFont = font;

	for (int Row = 0; Row < CountCell; Row++)
	{
		vector<RectangleShape> TempVectorRectangLeShape;
		vector<Text> TempVectorText;

		for (int Col = 0; Col < CountCell; Col++)
		{
			RectangleShape Cell;
			Cell.setSize(Vector2f(SizeCell, SizeCell));
			Cell.setPosition(Vector2f(static_cast<float>(SizeCell * Col), static_cast<float>(SizeCell * Row)));
			Cell.setOutlineColor(Color::Black);
			Cell.setOutlineThickness(-1);

			Text TextCoordinate(GameFieldFont, " ");
			TextCoordinate.setCharacterSize(static_cast<unsigned int>(SizeCell / 5));
			TextCoordinate.setFillColor(Color::Black);
			TextCoordinate.setPosition(Vector2f(static_cast<float>(SizeCell * Col + SizeCell / 1.6), static_cast<float>(SizeCell * Row + SizeCell / 1.4)));

			if (Row == 0 || Row == CountCell-1 || Col == 0 || Col == CountCell-1)
			{
				Cell.setFillColor(OuterSide);

				if (Col > 0 && Col < CountCell-1)
				{
					TextCoordinate.setString(to_string(Col));
				}
				else if (Row > 0 && Row < CountCell-1)
				{
					TextCoordinate.setString(char((int)'A' - 1 + Row));
				}
			}
			else if (Col % 2 == 0 && Row % 2 == 0 || Col % 2 != 0 && Row % 2 != 0)
			{
				Cell.setFillColor(ColorCellOne);
				TextCoordinate.setString(char((int)'A' - 1 + Row) + to_string(Col));
			}
			else
			{
				Cell.setFillColor(ColorCellTwo);
				TextCoordinate.setString(char((int)'A' - 1 + Row) + to_string(Col));
			}
			TempVectorText.push_back(TextCoordinate);
			TempVectorRectangLeShape.push_back(Cell);
		}

		FieldCoordinate.push_back(TempVectorText);
		RectangleShapeOnField.push_back(TempVectorRectangLeShape);

	}
}

RectangleShape GameField::GetRectangleShapeOnField(size_t XPosition, size_t YPosition)
{
	if (XPosition < RectangleShapeOnField[YPosition].size() && YPosition < RectangleShapeOnField.size() && XPosition >= 0 && YPosition >= 0)
	{
		return RectangleShapeOnField[YPosition][XPosition];
	}
	else
	{
		OutputLog("Class -> GameField -> Error XPosition or YPosition");
		return RectangleShape();
	}

}

Text GameField::GetFieldCoordinateOnField(size_t XPosition, size_t YPosition)
{
	if (XPosition < FieldCoordinate[YPosition].size() && YPosition < FieldCoordinate.size() && XPosition >= 0 && YPosition >= 0)
	{
		return FieldCoordinate[YPosition][XPosition];
	}
	else
	{	
		float temp = GetSizeCell();
		Text Error(GameFieldFont, "Error Text");
		Error.setPosition(Vector2f(temp * XPosition + temp / 2 , temp * YPosition + temp / 2));
		Error.setFillColor(Color::Black);
		Error.setCharacterSize(static_cast<unsigned int>(temp / 5));
		return Error;
	}
}

size_t GameField::GetCounRow()
{
	return RectangleShapeOnField.size();
}

size_t GameField::GetCounColl(size_t No)
{
	return RectangleShapeOnField[No].size();
}

float GameField::GetSizeCell()
{
	return SizeCell;
} 

bool GameField::SelectCell(const vector<vector<bool>>& Coordinate, Color color)
{
	size_t SizeCoordinate = Coordinate.size();
	size_t SizeRectangleShapeOnField = RectangleShapeOnField.size();

	if (SizeCoordinate != SizeRectangleShapeOnField)
	{
		OutputLog( "ERROR -> Class -> GameField -> SelectCell -> несовпадение размеров поля:");
		OutputLog(to_string(SizeCoordinate) + "\\" + to_string(SizeRectangleShapeOnField));
		return false;
	}

	for (size_t Row = 0; Row < Coordinate.size(); Row++)
	{
		for (size_t Col = 0; Col < Coordinate[0].size(); Col++)
		{
			if (Coordinate[Row][Col] == true)
			{
				RectangleShapeOnField[Row][Col].setOutlineThickness(-5); 
				RectangleShapeOnField[Row][Col].setOutlineColor(color);
			}
		}
	}	
	return true;
}
bool GameField::SelectCell(size_t XPosition, size_t YPosition, Color color)
{
	size_t SizeV = RectangleShapeOnField.size();
	size_t SizeVV = RectangleShapeOnField[0].size();

	if (XPosition < 1 || YPosition < 1 || XPosition > SizeVV - 1 || YPosition > SizeV - 1)
	{
		OutputLog("ERROR -> Class -> GameField -> SelectCell -> выход за игровое поле или выделение границы:");
		OutputLog(to_string(SizeV) + "\\" + to_string(SizeVV));
		return false;
	}

	RectangleShapeOnField[YPosition][XPosition].setOutlineThickness(-5);
	RectangleShapeOnField[YPosition][XPosition].setOutlineColor(color);

	return true;
}



bool GameField::UnSelectCell()
{
	for (int Row = 0; Row < RectangleShapeOnField.size(); Row++)
	{
		for (int Col = 0; Col < RectangleShapeOnField[0].size(); Col++)
		{
			RectangleShapeOnField[Row][Col].setOutlineThickness(-1);
			RectangleShapeOnField[Row][Col].setOutlineColor(Color::Black);
		}
	}
	return true;
}