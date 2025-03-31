#include "GameField.h"


GameField::GameField(int CountCell, int WindowHeight, const Font& font, Color OuterSide, Color ColorCellOne, Color ColorCellTwo)
{
	SizeCell = WindowHeight / CountCell;

	GameFieldFont = font;

	for (int Row = 0; Row < CountCell; Row++)
	{
		vector<RectangleShape> TempVectorRectangLeShape;
		vector<Text> TempVectorText;

		for (int Col = 0; Col < CountCell; Col++)
		{
			RectangleShape Cell;
			Cell.setSize(Vector2f(SizeCell, SizeCell));
			Cell.setPosition(Vector2f(SizeCell * Col, SizeCell * Row));
			Cell.setOutlineColor(Color::Black);
			Cell.setOutlineThickness(-1);

			Text TextCoordinate(GameFieldFont, " ");
			TextCoordinate.setCharacterSize(SizeCell / 5);
			TextCoordinate.setFillColor(Color::Black);
			TextCoordinate.setPosition(Vector2f(SizeCell * Col + SizeCell / 1.6 , SizeCell * Row + SizeCell / 1.4));

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

RectangleShape GameField::GetRectangleShapeOnField(int XPosition, int YPosition)
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

Text GameField::GetFieldCoordinateOnField(int XPosition, int YPosition)
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
		Error.setCharacterSize(temp / 5);
		return Error;
	}
}

int GameField::GetCounRowRectangleShape()
{
	return RectangleShapeOnField.size();
}

int GameField::GetCounCollRectangleShape(int No)
{
	return RectangleShapeOnField[No].size();
}

int GameField::GetCounRowFieldCoordinate()
{
	return FieldCoordinate.size();
}

int GameField::GetCounCollFieldCoordinate(int No)
{
	return FieldCoordinate[No].size();
}

float GameField::GetSizeCell()
{
	return SizeCell;
}

bool GameField::SelectCell(const vector<vector<bool>>& Coordinate)
{
	int SizeCoordinate = Coordinate.size();
	int SizeRectangleShapeOnField = RectangleShapeOnField.size();

	if (SizeCoordinate != SizeRectangleShapeOnField)
	{
		OutputLog( "ERROR -> Class -> GameField -> SelectCell -> несовпадение размеров поля:");
		OutputLog(to_string(SizeCoordinate) + "\\" + to_string(SizeRectangleShapeOnField));
		return false;
	}

	for (int Row = 0; Row < Coordinate.size(); Row++)
	{
		for (int Col = 0; Col < Coordinate[0].size(); Col++)
		{
			if (Coordinate[Row][Col] == true)
			{
				RectangleShapeOnField[Row][Col].setOutlineThickness(-5);
				RectangleShapeOnField[Row][Col].setOutlineColor(Color::Red);
			}
		}
	}	
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