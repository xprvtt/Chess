
#include "FigureLocation.h"




FigureLocation::FigureLocation(size_t CountCellOnXPosition, size_t CountCellOnYPosition, int WindowHeight, path PathToEmptyTextureGameField , path PathToEmptyTextureEdge , float PrecentSizeFigure)
{
	if (CountCellOnXPosition < 3 || CountCellOnYPosition < 3)
	{
		return;
	}

	this->CountCellOnXPosition  = CountCellOnXPosition;
	this->CountCellOnYPosition  = CountCellOnYPosition;
	this->SizeCell              = float(WindowHeight / CountCellOnXPosition);
	this->PrecentSizeFigure     = PrecentSizeFigure;
	this->SizeRectangInCell     = SizeCell * PrecentSizeFigure;

	PrecentSizeFigure <= 0 ? this->PositionRectangInCell = 0 : this->PositionRectangInCell = (SizeCell - SizeRectangInCell) / 2;


	VectorLocationFigure.resize(CountCellOnXPosition, vector<pair<int,string>>(CountCellOnXPosition));

	/// размеры 

	//--//--//--//--//--//--//--//--//--//    ДЛЯ ФИГУР НА ДОСКЕ   //--//--//--//--//--//--//--//--//--//--//--//--//--//--//
																													
	LocationClassFigure.resize(   CountCellOnYPosition, vector<shared_ptr<Figure>> (CountCellOnXPosition));
	LocationTexture.resize(       CountCellOnYPosition, vector<shared_ptr<Texture>>(CountCellOnXPosition));
	LocationRectangleShape.resize(CountCellOnYPosition, vector<RectangleShape>     (CountCellOnXPosition));
																												    
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	


	//--//--//--//--//--//--//--//--//--//  ДЛЯ УНИКАЛЬНЫХ ФИГУР   //--//--//--//--//--//--//--//--//--//--//--//--//--//--//
																															
	UniqueFigureLocationRectangleShape.resize(CountCellOnYPosition,vector<pair<int, RectangleShape>>(CountCellOnXPosition));																																																									// 	// добавление уникальных фигур

	// нулевой элемент == край
	UniqueFigureLocationClassFigure.push_back(make_shared<Figure>(-1, true));
	//
	UniqueFigureLocationTexture.push_back(make_shared<Texture>(PathToEmptyTextureEdge));

	// первый элемент == пустая клетка
	UniqueFigureLocationClassFigure.push_back(make_shared<Figure>(NULL, false));
	UniqueFigureLocationTexture.push_back(make_shared<Texture>(PathToEmptyTextureGameField));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	for (int YPosition = 0; YPosition < CountCellOnYPosition; YPosition++)
	{
		for (int XPosition = 0; XPosition < CountCellOnXPosition; XPosition++)
		{
			int U; // итератор расположение уникального класса и уникальную текстуру в векторах

			// если край то используем фигуру-край == Side -1
			if (XPosition == 0 || YPosition == 0 || XPosition == CountCellOnXPosition - 1 || YPosition == CountCellOnYPosition - 1)
			{
				U = 0; // итератор на край

				LocationClassFigure[YPosition][XPosition] = UniqueFigureLocationClassFigure[U];
				LocationTexture[YPosition][XPosition] = UniqueFigureLocationTexture[U];

				LocationRectangleShape[YPosition][XPosition].setTexture(UniqueFigureLocationTexture[U].get(), true);

				UniqueFigureLocationRectangleShape[YPosition][XPosition].second.setTexture(UniqueFigureLocationTexture[U].get(), true);
				UniqueFigureLocationRectangleShape[YPosition][XPosition].first = U;
			}
			// в противном случае считаем как пустая клетка
			else

			{
				U = 1; // итератор на пустую клетку (фигуру)

				LocationClassFigure[YPosition][XPosition] = UniqueFigureLocationClassFigure[U];
				LocationTexture[YPosition][XPosition] = UniqueFigureLocationTexture[U];

				LocationRectangleShape[YPosition][XPosition].setTexture(UniqueFigureLocationTexture[U].get(), true);

				UniqueFigureLocationRectangleShape[YPosition][XPosition].second.setTexture(UniqueFigureLocationTexture[U].get(), true);
			}

			//--//--//--//--//--//--//--//--//--//   ДЛЯ ФИГУР НА ДОСКЕ  //--//--//--//--//--//--//--//--//--//--//--//--//--//-//
																																
			LocationRectangleShape[YPosition][XPosition].setSize(Vector2f(SizeCell, SizeCell));										
			LocationRectangleShape[YPosition][XPosition].setPosition(Vector2f(XPosition * SizeCell, YPosition * SizeCell));		

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			//--//--//--//--//--//--//--//--//--//     ДЛЯ УНИКАЛЬНЫХ ФИГУР   //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//

			UniqueFigureLocationRectangleShape[YPosition][XPosition].second.setSize(Vector2f(SizeCell * PrecentSizeFigure, SizeCell * PrecentSizeFigure));			
			UniqueFigureLocationRectangleShape[YPosition][XPosition].second.setPosition(Vector2f(XPosition * SizeCell * PrecentSizeFigure + WindowHeight, YPosition * SizeCell * PrecentSizeFigure + WindowHeight / 2 ));
			UniqueFigureLocationRectangleShape[YPosition][XPosition].second.setOutlineColor(Color::Black);

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			VectorLocationFigure[YPosition][XPosition].first = LocationClassFigure[YPosition][XPosition]->GetSIDE();
			VectorLocationFigure[YPosition][XPosition].second = LocationClassFigure[YPosition][XPosition]->Get_ID_FIGURE();
		}
	}
}

//--//--//--//--//--//--//--//--//--//    ДЛЯ ФИГУР НА ДОСКЕ   //--//--//--//--//--//--//--//--//--//--//--//--//


bool FigureLocation::SetFigure(int XPosition, int YPosition, string ID_Figure, int Side, bool invulnerable)
{

	if (LocationClassFigure[YPosition][XPosition]->GetSIDE() == -1)
	{
		OutputLog("ERROR -> Class -> FigureLocation -> SetFigure -> попытка установить за границу");
		return false;
	}

	for (int it = 0; it < UniqueFigureLocationClassFigure.size(); it++)
	{
		//находим итератор указанной финугы
		if (   UniqueFigureLocationClassFigure[it]->GetSIDE() == Side 
			&& UniqueFigureLocationClassFigure[it]->Get_ID_FIGURE() == ID_Figure
			&& UniqueFigureLocationClassFigure[it]->GetINVULNERABLE() == invulnerable
		   )
		{

			// станавливаем текстуру фигуры на поле
			LocationTexture[YPosition][XPosition] = UniqueFigureLocationTexture[it];

			// устанавливаем позицию и размер фигуры -> меньше чем пустая клетка или край
			LocationRectangleShape[YPosition][XPosition].setSize(Vector2f(SizeCell * PrecentSizeFigure, SizeCell * PrecentSizeFigure));
			LocationRectangleShape[YPosition][XPosition].setPosition(Vector2f(XPosition * SizeCell + PositionRectangInCell, YPosition * SizeCell + PositionRectangInCell));
			// передаем установленную текстуру
			LocationRectangleShape[YPosition][XPosition].setTexture(LocationTexture[YPosition][XPosition].get(), true);

			//ставим класс фигуры на поле
			LocationClassFigure[YPosition][XPosition] = UniqueFigureLocationClassFigure[it];

			return true;
		}
	}
	OutputLog("ERROR -> Class -> FigureLocation -> SetFigure -> фигура не найдена, сначала ее необходимо добавить -> AddUniqueFigure()");
	return false;
}

bool FigureLocation::PromoutionSelectFigure(string ID_Figure)
{
	// фигура может превратиться в указанную фигуру???.........
	if (LocationClassFigure[PositionSelectFigure.second][PositionSelectFigure.first]->GetPromoutionFigure(ID_Figure))
	{
		for (int it = 0; it < UniqueFigureLocationClassFigure.size(); it++)
		{
			if (UniqueFigureLocationClassFigure[it]->Get_ID_FIGURE() == ID_Figure && UniqueFigureLocationClassFigure[it]->GetSIDE() == LocationClassFigure[PositionSelectFigure.second][PositionSelectFigure.first]->GetSIDE())
			{
				// заменяем текстуру
				LocationTexture[PositionSelectFigure.second][PositionSelectFigure.first] = UniqueFigureLocationTexture[it];

				// передаем установленную текстуру
				LocationRectangleShape[PositionSelectFigure.second][PositionSelectFigure.first].setTexture(LocationTexture[PositionSelectFigure.second][PositionSelectFigure.first].get(), true);

				//ставим класс фигуры на поле
				LocationClassFigure[PositionSelectFigure.second][PositionSelectFigure.first] = UniqueFigureLocationClassFigure[it];

				return true;
			}
		}
		OutputLog("Error -> Class -> FigureLocation -> PromoutionSelectFigure() -> не найден итератор");
	}
	{
		OutputLog("Error -> Class -> FigureLocation -> PromoutionSelectFigure() -> невозможно превратиться в эту фигуру");
	}
	return false;
}

bool FigureLocation::AddUniqueFigure(shared_ptr<Figure> NewFigure, path CurrentTextureFigure)
{
	// изначально считаем что фигура уникальная 
	// проверяем есть ли такие фигуры у нас еще?
	// начинаем с 2 т.к. 0 и 1 слоты заняты заранее "краем" и пустой фигурой "клеткой" соответственно
	int Size = UniqueFigureLocationClassFigure.size();

	for (int it = 2; it < Size; it++)
	{
		// если поля совпадают значит не уникальна и не добавляем
		if ( UniqueFigureLocationClassFigure[it]->Get_ID_FIGURE()         == NewFigure->Get_ID_FIGURE() 
			 && UniqueFigureLocationClassFigure[it]->GetSIDE()            == NewFigure->GetSIDE()
			 && UniqueFigureLocationClassFigure[it]->GetINVULNERABLE()    == NewFigure->GetINVULNERABLE()
		   )
		{
			//не добавляем
			return false;
		}	
	}

	// иначе, если поля отличаются добавляем
	UniqueFigureLocationClassFigure.push_back(NewFigure);
	UniqueFigureLocationTexture.push_back(make_shared<Texture>(CurrentTextureFigure));

	for (int Row = 1; Row < CountCellOnYPosition - 1; Row++)
	{
		for (int Col = 1; Col < CountCellOnXPosition - 1; Col++)
		{
			// если клетка пустая то сразу же размещаем аникальную фигуру на поле уникальных фигур
			if (UniqueFigureLocationRectangleShape[Row][Col].first == 0)
			{
				size_t LatestElement = UniqueFigureLocationTexture.size() - 1;

				// ставим текстуру
				UniqueFigureLocationRectangleShape[Row][Col].second.setTexture(UniqueFigureLocationTexture[LatestElement].get(), true);
				UniqueFigureLocationRectangleShape[Row][Col].second.setOutlineThickness(-2);
				UniqueFigureLocationRectangleShape[Row][Col].second.setOutlineColor(Color::Black);

				// ставим итератор откуда привязали
				UniqueFigureLocationRectangleShape[Row][Col].first = LatestElement;
				return true;
			}
		}
	}	
	return false;
}


bool FigureLocation::MoveSelectFigure(int XPositionMove, int YPositionMove)
{
	vector<vector<bool>> AvailableMove = GetAvailableMovesForSelectFigure();

	if (!AvailableMove[YPositionMove][XPositionMove])
	{
		OutputLog("ход невозможен");
		return false;
	}

	if (LocationClassFigure[YPositionMove][XPositionMove]->GetSIDE() == 0)
	{
		swap(LocationClassFigure[PositionSelectFigure.second][PositionSelectFigure.first], LocationClassFigure[YPositionMove][XPositionMove]);
		swap(LocationTexture[PositionSelectFigure.second][PositionSelectFigure.first], LocationTexture[YPositionMove][XPositionMove]);


		//изменяем размер и положение
		LocationRectangleShape[PositionSelectFigure.second][PositionSelectFigure.first].setSize(Vector2f(SizeCell, SizeCell));
		LocationRectangleShape[PositionSelectFigure.second][PositionSelectFigure.first].setPosition(Vector2f(SizeCell * PositionSelectFigure.first, SizeCell * PositionSelectFigure.second));

		// установили тестуры т.к. они свапнуты
		LocationRectangleShape[PositionSelectFigure.second][PositionSelectFigure.first].setTexture(LocationTexture[PositionSelectFigure.second][PositionSelectFigure.first].get(), true);

		//изменяем размер и положение
		LocationRectangleShape[YPositionMove][XPositionMove].setSize(Vector2f(SizeCell * PrecentSizeFigure, SizeCell * PrecentSizeFigure));
		LocationRectangleShape[YPositionMove][XPositionMove].setPosition(Vector2f(SizeCell * XPositionMove + PositionRectangInCell, SizeCell * YPositionMove + PositionRectangInCell));

		// установили тестуры т.к. они свапнуты
		LocationRectangleShape[YPositionMove][XPositionMove].setTexture(LocationTexture[YPositionMove][XPositionMove].get(), true);

		return true;
	}
	// если клетка не пустая предполагается что там фигура другого игрока
	else
	{	
		// Фигура должна быть доступна для взятия т.е. Invulnerability = false		
		if (LocationClassFigure[YPositionMove][XPositionMove]->GetINVULNERABLE())
		{
			OutputLog("ERROR -> class -> FigureLocation -> MoveSelectFigure() -> фигура неуязвима");
			return false;
		}

		swap(LocationClassFigure[PositionSelectFigure.second][PositionSelectFigure.first], LocationClassFigure[YPositionMove][XPositionMove]);
		swap(LocationTexture[PositionSelectFigure.second][PositionSelectFigure.first], LocationTexture[YPositionMove][XPositionMove]);

		//
		LocationRectangleShape[YPositionMove][XPositionMove].setSize(Vector2f(SizeCell * PrecentSizeFigure, SizeCell * PrecentSizeFigure));
		LocationRectangleShape[YPositionMove][XPositionMove].setPosition(Vector2f(SizeCell * XPositionMove + PositionRectangInCell, SizeCell * YPositionMove + PositionRectangInCell));

		//
		LocationRectangleShape[YPositionMove][XPositionMove].setTexture(LocationTexture[YPositionMove][XPositionMove].get(), true);

		//
		LocationTexture[PositionSelectFigure.second][PositionSelectFigure.first] = UniqueFigureLocationTexture[1]; // 1 - пустая текстура

		//
		LocationClassFigure[PositionSelectFigure.second][PositionSelectFigure.first] = UniqueFigureLocationClassFigure[1]; // 1 - пустая фигура (клетка)

		//
		LocationRectangleShape[PositionSelectFigure.second][PositionSelectFigure.first].setSize(Vector2f(SizeCell, SizeCell));
		LocationRectangleShape[PositionSelectFigure.second][PositionSelectFigure.first].setPosition(Vector2f(SizeCell * PositionSelectFigure.first, SizeCell * PositionSelectFigure.second));
		//
		LocationRectangleShape[PositionSelectFigure.second][PositionSelectFigure.first].setTexture(LocationTexture[PositionSelectFigure.second][PositionSelectFigure.first].get(), true);

		return true;
	}

	return false;
}
/////////////////////////////////////////////////////////////////

pair<int, int> FigureLocation::GetPositionFigureWhenMousePressed(Vector2f PositonMouse)
{
	for (int YPosition = 0; YPosition < CountCellOnXPosition; YPosition++)
	{
		for (int XPosition = 0; XPosition < CountCellOnXPosition; XPosition++)
		{
			// если задели фигуру на игровом поле
			if (LocationRectangleShape[YPosition][XPosition].getGlobalBounds().contains(PositonMouse))
			{
				return make_pair(XPosition, YPosition);
			}
		}
	}
	return make_pair(NULL, NULL);
}
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////


bool FigureLocation::SeletcFigure(int XPositionFigure, int YpositionFigure)
{
	int SideFigure = LocationClassFigure[YpositionFigure][XPositionFigure]->GetSIDE();

	if (SideFigure == 0 || SideFigure == -1)
	{
		return false;
	}
	if (SelectFigure)
	{
		UnSeletcFigure();
	}

	LocationRectangleShape[YpositionFigure][XPositionFigure].setOutlineThickness(-3);
	LocationRectangleShape[YpositionFigure][XPositionFigure].setOutlineColor(Color::Red);

	PositionSelectFigure = make_pair(XPositionFigure, YpositionFigure);
	SelectFigure = true;

	return SelectFigure;
}

bool FigureLocation::UnSeletcFigure()
{
	for (int YPosition = 0; YPosition < CountCellOnXPosition; YPosition++)
	{
		for (int XPosition = 0; XPosition < CountCellOnXPosition; XPosition++)
		{
			LocationRectangleShape[YPosition][XPosition].setOutlineThickness(0);
		}
	}
	PositionSelectFigure = make_pair(0, 0);
	SelectFigure = false;

	return true;
}

bool FigureLocation::FiguresSelectedOrNot()
{
	return SelectFigure;
}
pair<int, int> FigureLocation::GetPositionSelectFigure()
{
	return PositionSelectFigure;
}
//////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////

vector<vector<bool>> FigureLocation::GetAvailableMovesForSelectFigure()
{
	pair<int, int> Position = GetPositionSelectFigure();
	return LocationClassFigure[Position.second][Position.first]->GetMoveForFigure(Position.first, Position.second, GetVectorLocationFigure());
}

bool FigureLocation::PromoutionFigureOnPosition(int XPositionFigure, int YpositionFigure)
{
	return LocationClassFigure[YpositionFigure][XPositionFigure]->GetPossibilityPromotion(XPositionFigure, YpositionFigure, GetVectorLocationFigure());
}

vector<vector<pair<int,string>>>  FigureLocation::GetVectorLocationFigure()
{
	UpdateVectorIntLocationFigure();
	return VectorLocationFigure;
}

void FigureLocation::UpdateVectorIntLocationFigure()
{
	for (int YPosition = 0; YPosition < CountCellOnXPosition; YPosition++)
	{
		for (int XPosition = 0; XPosition < CountCellOnXPosition; XPosition++)
		{
			VectorLocationFigure[YPosition][XPosition].first = LocationClassFigure[YPosition][XPosition]->GetSIDE();
			VectorLocationFigure[YPosition][XPosition].second = LocationClassFigure[YPosition][XPosition]->Get_ID_FIGURE();
		}
	}
}

//////////////////////////////////////////////////////////////////////

string FigureLocation::GetIDFigure(int XPosition, int Yposition)
{
	return LocationClassFigure[Yposition][XPosition]->Get_ID_FIGURE();
}

int FigureLocation::GetSideFigure(int XPosition, int Yposition)
{
	return LocationClassFigure[Yposition][XPosition]->GetSIDE();
}

const RectangleShape& FigureLocation::GetRectangleShapeFigure(int XPosition, int Yposition)
{
	return LocationRectangleShape[Yposition][XPosition];
}

bool FigureLocation::GetInvulnerableFigure(int XPosition, int Yposition)
{
	return LocationClassFigure[Yposition][XPosition]->GetINVULNERABLE();
}
//////////////////////////////////////////////////////////////////////








//--//--//--//--//--//--//--//--//--//      ДЛЯ ПОЛЕ УНИКАЛЬНЫХ ФИГУР     //--//--//--//--//--//--//--//--//--//--//--//-//

bool FigureLocation::GetInvulnerableUniqueFigure(int XPosition, int Yposition)
{
	int it = GetIteratorUniqueFigure(XPosition, Yposition);
	return UniqueFigureLocationClassFigure[it]->GetINVULNERABLE();
}

string FigureLocation::GetIDUniqueFigure(int XPosition, int Yposition)
{
	int it = GetIteratorUniqueFigure(XPosition, Yposition);
	return UniqueFigureLocationClassFigure[it]->Get_ID_FIGURE();
}

int FigureLocation::GetSideUniqueFigure(int XPosition, int Yposition)
{
	int it = GetIteratorUniqueFigure(XPosition, Yposition);
	return UniqueFigureLocationClassFigure[it]->GetSIDE();
}

const RectangleShape& FigureLocation::GetRectangleShapeUniqueFigure(int XPosition, int Yposition)
{
	return UniqueFigureLocationRectangleShape[Yposition][XPosition].second;
}

int FigureLocation::GetIteratorUniqueFigure(int XPosition, int Yposition)
{
	return UniqueFigureLocationRectangleShape[Yposition][XPosition].first;
}

bool FigureLocation::SeletcUniqueFigureForPromoution(int XPositionFigure, int YPositionFigure)
{
	// выделяем фигуры в которые может превратиться фигура
	int SideFigure = LocationClassFigure[YPositionFigure][XPositionFigure]->GetSIDE();

	for ( auto& VectorRectangleShape : UniqueFigureLocationRectangleShape)
	{
		for ( auto& RectangleShape : VectorRectangleShape)
		{
			int it = RectangleShape.first;

			// если фигура той же стороны.......
			if (UniqueFigureLocationClassFigure[it]->GetSIDE() == SideFigure)
			{
				// и может превратиться в указанную фигуру???... ......
				if (LocationClassFigure[YPositionFigure][XPositionFigure]->GetPromoutionFigure(UniqueFigureLocationClassFigure[it]->Get_ID_FIGURE()))
				{
					//подкрашиваем фигуру
					RectangleShape.second.setOutlineColor(Color::Red);
				}
			}
		}
	}
	return true;
}

bool FigureLocation::UnSeletcUniqueFigure()
{
	for (auto& VectorRectangleShape : UniqueFigureLocationRectangleShape)
	{
		for (auto& RectangleShape : VectorRectangleShape)
		{
			RectangleShape.second.setOutlineColor(Color::Black);
		}
	}
	return true;
}

pair<int, int> FigureLocation::GetPositionUniqueFigureWhenMousePressed(Vector2f PositonMouse)
{
	for (int YPosition = 0; YPosition < CountCellOnYPosition; YPosition++)
	{
		for (int XPosition = 0; XPosition < CountCellOnXPosition; XPosition++)
		{
			// если задели фигуру на поле уникальных фигур возвращаем позицию в минусе
			if (UniqueFigureLocationRectangleShape[YPosition][XPosition].second.getGlobalBounds().contains(PositonMouse))
			{
				return make_pair(XPosition, YPosition);
			}
		}
	}
	return make_pair(NULL, NULL);
}


