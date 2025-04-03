
#include "FigureLocation.h"




FigureLocation::FigureLocation(size_t CountCellOnXPosition, size_t CountCellOnYPosition, int WindowHeight, path PathToEmptyTextureGameField, path PathToEmptyTextureEdge, float PrecentSizeFigure)
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


	VectorLocationFigure.resize(CountCellOnXPosition, vector<tuple<int, string, bool, bool, bool>>(CountCellOnXPosition));

	/// размеры 

	//--//--//--//--//--//--//--//--//--//    ДЛЯ ФИГУР НА ДОСКЕ   //--//--//--//--//--//--//--//--//--//--//--//--//--//--//
																													
	LocationClassFigure.resize(   CountCellOnYPosition, vector<shared_ptr<Figure>> (CountCellOnXPosition));
	LocationTexture.resize(       CountCellOnYPosition, vector<shared_ptr<Texture>>(CountCellOnXPosition));
	LocationRectangleShape.resize(CountCellOnYPosition, vector<RectangleShape>     (CountCellOnXPosition));
																												    
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	 
	//--//--//--//--//--//--//--//--//--//  ДЛЯ УНИКАЛЬНЫХ ФИГУР   //--//--//--//--//--//--//--//--//--//--//--//--//--//--//
																															
	UniqueFigureLocationRectangleShape.resize(CountCellOnYPosition,vector<pair<size_t, RectangleShape>>(CountCellOnXPosition));																																																									// 	// добавление уникальных фигур

	// нулевой элемент == край
	UniqueFigureLocationClassFigure.push_back(make_shared<Figure>(-1, true, false));
	//
	UniqueFigureLocationTexture.push_back(make_shared<Texture>(PathToEmptyTextureEdge));

	// первый элемент == пустая клетка
	UniqueFigureLocationClassFigure.push_back(make_shared<Figure>(0));
	UniqueFigureLocationTexture.push_back(make_shared<Texture>(PathToEmptyTextureGameField));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	for (size_t YPosition = 0; YPosition < CountCellOnYPosition; YPosition++)
	{
		for (size_t XPosition = 0; XPosition < CountCellOnXPosition; XPosition++)
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
			// в противном случае считаем как пустая клетка == Side 0
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

			get<0>(VectorLocationFigure[YPosition][XPosition]) = LocationClassFigure[YPosition][XPosition]->GetSIDE();
			get<1>(VectorLocationFigure[YPosition][XPosition]) = LocationClassFigure[YPosition][XPosition]->Get_ID_FIGURE();
			get<2>(VectorLocationFigure[YPosition][XPosition]) = LocationClassFigure[YPosition][XPosition]->GetINVULNERABLE();
			get<3>(VectorLocationFigure[YPosition][XPosition]) = LocationClassFigure[YPosition][XPosition]->GetIMPORTANT();
			get<4>(VectorLocationFigure[YPosition][XPosition]) = LocationClassFigure[YPosition][XPosition]->GetPROMOUTION();
		}
	}
}

//--//--//--//--//--//--//--//--//--//    ДЛЯ ФИГУР НА ДОСКЕ   //--//--//--//--//--//--//--//--//--//--//--//--//


bool FigureLocation::SetFigure(size_t XPosition, size_t YPosition, string ID_FIGURE, int SIDE, bool INVULNERABLE, bool IMPORTANT, vector<tuple<int, string, bool, bool, bool>> VectorPROMOUTION)
{

	if (LocationClassFigure[YPosition][XPosition]->GetSIDE() == -1)
	{
		OutputLog("ERROR -> Class -> FigureLocation -> SetFigure -> попытка установить за границу");
		return false;
	}

	for (int it = 0; it < UniqueFigureLocationClassFigure.size(); it++)
	{
		//находим итератор указанной финугы
		if (   UniqueFigureLocationClassFigure[it]->GetSIDE()          == SIDE
			&& UniqueFigureLocationClassFigure[it]->Get_ID_FIGURE()    == ID_FIGURE
			&& UniqueFigureLocationClassFigure[it]->GetINVULNERABLE()  == INVULNERABLE
			&& UniqueFigureLocationClassFigure[it]->GetIMPORTANT()     == IMPORTANT
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

bool FigureLocation::PromoutionSelectFigure(int SIDE, string ID_Figure, bool INVULNERABLE, bool IMPORTANT, bool PROMOUTION)
{

	// фигура может превратиться в указанную фигуру???.........
	if (LocationClassFigure[PositionSelectFigure.second][PositionSelectFigure.first]->GetPromoutionFigure(SIDE, ID_Figure, INVULNERABLE, IMPORTANT, PROMOUTION))
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

bool FigureLocation::AddUniqueFigure(shared_ptr<Figure> NewFigureOrheirs, path CurrentTextureFigure)
{
	// изначально считаем что фигура уникальная 
	// проверяем есть ли такие фигуры у нас еще?
	// начинаем с 2 т.к. 0 и 1 слоты заняты заранее "краем" и пустой фигурой (видимой как пустая клетка) соответственно
	size_t Size = UniqueFigureLocationClassFigure.size();

	for (int it = 2; it < Size; it++)
	{
		// если поля совпадают значит не уникальна и не добавляем
		if (    UniqueFigureLocationClassFigure[it]->Get_ID_FIGURE()       == NewFigureOrheirs->Get_ID_FIGURE() 
			 && UniqueFigureLocationClassFigure[it]->GetSIDE()             == NewFigureOrheirs->GetSIDE()
			 && UniqueFigureLocationClassFigure[it]->GetINVULNERABLE()     == NewFigureOrheirs->GetINVULNERABLE()
			 && UniqueFigureLocationClassFigure[it]->GetIMPORTANT()        == NewFigureOrheirs->GetIMPORTANT()
			 && UniqueFigureLocationClassFigure[it]->GetVectorPROMOUTION() == NewFigureOrheirs->GetVectorPROMOUTION()
		   )
		{
			//не добавляем
			return false;
		}	
	}

	// иначе, если поля отличаются добавляем
	UniqueFigureLocationClassFigure.push_back(NewFigureOrheirs);
	UniqueFigureLocationTexture.push_back(make_shared<Texture>(CurrentTextureFigure));

	for (size_t Row = 1; Row < CountCellOnYPosition - 1; Row++)
	{
		for (size_t Col = 1; Col < CountCellOnXPosition - 1; Col++)
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


bool FigureLocation::MoveSelectFigure(size_t XPositionMove, size_t YPositionMove)
{
	auto AvailableMove = GetAvailableMovesForFigure(PositionSelectFigure.first, PositionSelectFigure.second);

	bool exists = false;

	for (const auto& Move : AvailableMove)
	{
		if (Move.first == XPositionMove && Move.second == YPositionMove)
		{
			exists = true;
		}
	}
	if (!exists)
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
	for (size_t YPosition = 0; YPosition < CountCellOnXPosition; YPosition++)
	{
		for (size_t XPosition = 0; XPosition < CountCellOnXPosition; XPosition++)
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

bool FigureLocation::SeletcFigure(size_t XPositionFigure, size_t YpositionFigure)
{
	int SideFigure = LocationClassFigure[YpositionFigure][XPositionFigure]->GetSIDE();

	if (SideFigure == 0 || SideFigure == -1)
	{
		return false;
	}
	if (SelectFigure)
	{
		UnSeletcAllFigure();
	}

	LocationRectangleShape[YpositionFigure][XPositionFigure].setOutlineThickness(-3);
	LocationRectangleShape[YpositionFigure][XPositionFigure].setOutlineColor(Color::Red);

	PositionSelectFigure = make_pair(XPositionFigure, YpositionFigure);
	SelectFigure = true;

	return SelectFigure;
}

bool FigureLocation::UnSeletcAllFigure()
{
	for (size_t YPosition = 0; YPosition < CountCellOnXPosition; YPosition++)
	{
		for (size_t XPosition = 0; XPosition < CountCellOnXPosition; XPosition++)
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

vector<pair<size_t, size_t>> FigureLocation::GetAvailableMovesForFigure(size_t XPositionFigure, size_t YpositionFigure)
{
	return LocationClassFigure[YpositionFigure][XPositionFigure]->GetMoveForFigure(XPositionFigure, YpositionFigure, GetVectorLocationFigure());
}

bool FigureLocation::PromoutionFigureOnPosition(size_t XPositionFigure, size_t YpositionFigure)
{
	return LocationClassFigure[YpositionFigure][XPositionFigure]->GetPossibilityPromotion(XPositionFigure, YpositionFigure, GetVectorLocationFigure());
}

vector<vector<tuple<int, string, bool, bool, bool>>>  FigureLocation::GetVectorLocationFigure()
{
	UpdateVectorLocationFigure();
	return VectorLocationFigure;
}

void FigureLocation::UpdateVectorLocationFigure()
{
	for (size_t YPosition = 0; YPosition < CountCellOnXPosition; YPosition++)
	{
		for (size_t XPosition = 0; XPosition < CountCellOnXPosition; XPosition++)
		{
			get<0>(VectorLocationFigure[YPosition][XPosition]) = LocationClassFigure[YPosition][XPosition]->GetSIDE();
			get<1>(VectorLocationFigure[YPosition][XPosition]) = LocationClassFigure[YPosition][XPosition]->Get_ID_FIGURE();
			get<2>(VectorLocationFigure[YPosition][XPosition]) = LocationClassFigure[YPosition][XPosition]->GetINVULNERABLE();
			get<3>(VectorLocationFigure[YPosition][XPosition]) = LocationClassFigure[YPosition][XPosition]->GetIMPORTANT();
			get<4>(VectorLocationFigure[YPosition][XPosition]) = LocationClassFigure[YPosition][XPosition]->GetPROMOUTION();
		}
	}
}

//////////////////////////////////////////////////////////////////////

string FigureLocation::GetIDFigure(size_t XPosition, size_t Yposition)
{
	return LocationClassFigure[Yposition][XPosition]->Get_ID_FIGURE();
}

int FigureLocation::GetSideFigure(size_t XPosition, size_t Yposition)
{
	return LocationClassFigure[Yposition][XPosition]->GetSIDE();
}

const RectangleShape& FigureLocation::GetRectangleShapeFigure(size_t XPosition, size_t Yposition)
{
	return LocationRectangleShape[Yposition][XPosition];
}

bool FigureLocation::GetInvulnerableFigure(size_t XPosition, size_t Yposition)
{
	return LocationClassFigure[Yposition][XPosition]->GetINVULNERABLE();
}

bool FigureLocation::GetImportantFigure(size_t XPosition, size_t Yposition)
{
	return LocationClassFigure[Yposition][XPosition]->GetIMPORTANT();
}
//////////////////////////////////////////////////////////////////////








//--//--//--//--//--//--//--//--//--//      ДЛЯ ПОЛЕ УНИКАЛЬНЫХ ФИГУР     //--//--//--//--//--//--//--//--//--//--//--//-//

bool FigureLocation::GetInvulnerableUniqueFigure(size_t XPosition, size_t Yposition)
{
	int it = GetIteratorUniqueFigure(XPosition, Yposition);
	return UniqueFigureLocationClassFigure[it]->GetINVULNERABLE();
}


string FigureLocation::GetIDUniqueFigure(size_t XPosition, size_t Yposition)
{
	int it = GetIteratorUniqueFigure(XPosition, Yposition);
	return UniqueFigureLocationClassFigure[it]->Get_ID_FIGURE();
}


int FigureLocation::GetSideUniqueFigure(size_t XPosition, size_t Yposition)
{
	int it = GetIteratorUniqueFigure(XPosition, Yposition);
	return UniqueFigureLocationClassFigure[it]->GetSIDE();
}

bool FigureLocation::GetImportantUniqueFigure(size_t XPosition, size_t Yposition)
{
	int it = GetIteratorUniqueFigure(XPosition, Yposition);	
	return UniqueFigureLocationClassFigure[it]->GetIMPORTANT();
}

bool FigureLocation::GetPromoutionUniqueFigure(size_t XPosition, size_t Yposition)
{
	int it = GetIteratorUniqueFigure(XPosition, Yposition);
	return UniqueFigureLocationClassFigure[it]->GetPROMOUTION();
}

const RectangleShape& FigureLocation::GetRectangleShapeUniqueFigure(size_t XPosition, size_t Yposition)
{
	return UniqueFigureLocationRectangleShape[Yposition][XPosition].second;
}


int FigureLocation::GetIteratorUniqueFigure(size_t XPosition, size_t Yposition)
{
	return UniqueFigureLocationRectangleShape[Yposition][XPosition].first;
}
int FigureLocation::GetIteratorUniqueFigure(int SIDE, string ID_FIGURE, bool INVULNERABLE, bool IMPORTANT, bool PROMOUTION)
{
	for (int it = 0; it < UniqueFigureLocationClassFigure.size(); it++)
	{
		// если находим такую фигуру то возвращаем итератор
		if (   UniqueFigureLocationClassFigure[it]->Get_ID_FIGURE()       == ID_FIGURE
			&& UniqueFigureLocationClassFigure[it]->GetSIDE()             == SIDE
			&& UniqueFigureLocationClassFigure[it]->GetINVULNERABLE()     == INVULNERABLE
			&& UniqueFigureLocationClassFigure[it]->GetIMPORTANT()        == IMPORTANT
			&& UniqueFigureLocationClassFigure[it]->GetPROMOUTION()       == PROMOUTION
			)
		{
			return it;
		}
	}
	return -1;
}


bool FigureLocation::SeletcUniqueFigureForPromoution(size_t XPositionFigure, size_t YpositionFigure)
{
	// выделяем фигуры в которые может превратиться фигура

	//получаем сторону текущего игрока
	int SideFigure = LocationClassFigure[YpositionFigure][XPositionFigure]->GetSIDE();

	for ( auto& VectorRectangleShape : UniqueFigureLocationRectangleShape)
	{
		for ( auto& RectangleShape : VectorRectangleShape)
		{
			int it = RectangleShape.first;

			// если фигура той же стороны
			if (UniqueFigureLocationClassFigure[it]->GetSIDE() == SideFigure)
			{
				// и может превратиться в указанную фигуру???... ......
				if (LocationClassFigure[YpositionFigure][XPositionFigure]->GetPromoutionFigure(UniqueFigureLocationClassFigure[it]->GetSIDE(),
					                                                                           UniqueFigureLocationClassFigure[it]->Get_ID_FIGURE(),
					                                                                           UniqueFigureLocationClassFigure[it]->GetINVULNERABLE(),
					                                                                           UniqueFigureLocationClassFigure[it]->GetIMPORTANT(),
																							   UniqueFigureLocationClassFigure[it]->GetPROMOUTION()
																							  )
				)
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
	for (size_t YPosition = 0; YPosition < CountCellOnYPosition; YPosition++)
	{
		for (size_t XPosition = 0; XPosition < CountCellOnXPosition; XPosition++)
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




vector<pair<size_t, size_t>> FigureLocation::CheckThreatFigure(size_t XPositionOnVectorLocationFigure, size_t YPositionOnVectorLocationFigure, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	vector<pair<size_t, size_t>> ResultPositionEnemyFigure;

	// получаем сторону текущего игрока, у которого будет проверяться фигура
	int  SideCurrentFigure;

	SideCurrentFigure = get<0>(VectorLocationFigure[YPositionOnVectorLocationFigure][XPositionOnVectorLocationFigure]);
	
	// проверяем все фигуры на переданном игровом поле у других игроков, которые могу "угрожать взятием"
	for (size_t Ypos = 0; Ypos < CountCellOnYPosition; Ypos++)
	{
		for (size_t Xpos = 0; Xpos < CountCellOnXPosition; Xpos++)
		{
			// если у фигуры на позиции другая сторона, то проверяем далее....
			if (   get<0>(VectorLocationFigure[Ypos][Xpos]) != SideCurrentFigure	
				&& get<0>(VectorLocationFigure[Ypos][Xpos]) != -1                    // не учитываем край 
				&& get<0>(VectorLocationFigure[Ypos][Xpos]) != 0	                 // не учитываем пустые клетки (фигуры)
			   )
			{
				
				int it = GetIteratorUniqueFigure(
					                              get<0>(VectorLocationFigure[Ypos][Xpos]),
					                              get<1>(VectorLocationFigure[Ypos][Xpos]),
					                              get<2>(VectorLocationFigure[Ypos][Xpos]),
					                              get<3>(VectorLocationFigure[Ypos][Xpos]),
					                              get<4>(VectorLocationFigure[Ypos][Xpos])
												);
				// получаем ходы на которые может сходить фигура
				auto MoveForFigure = UniqueFigureLocationClassFigure[it]->GetMoveForFigure(Xpos, Ypos, VectorLocationFigure);

				// если фигура может сходить на позицию проверяемой фигуры ("угрожать взятием"), то добавляем эту фигуру в вектор, она угрожает
				for (const auto& Move : MoveForFigure)
				{
					if (Move.first == XPositionOnVectorLocationFigure && Move.second == YPositionOnVectorLocationFigure)
					{
						ResultPositionEnemyFigure.push_back(make_pair(Xpos, Ypos));
					}
				}
			}
		}
	}	
	return ResultPositionEnemyFigure;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<pair<size_t, size_t>> FigureLocation::GetPositionFigure(int SIDE, string ID_Figure, bool INVULNERABLE, bool IMPORTANT, bool PROMOUTION)
{
	return PositionFigure(SIDE, ID_Figure, INVULNERABLE, IMPORTANT, PROMOUTION);
}



vector<pair<size_t, size_t>> FigureLocation::GetPositionFigure(int SIDE, string ID_Figure)
{
	return PositionFigure(SIDE, ID_Figure, NUM_exception, NUM_exception, NUM_exception);
}



vector<pair<size_t, size_t>> FigureLocation::GetPositionFigure(int SIDE)
{
	return PositionFigure(SIDE, "ALL", NUM_exception, NUM_exception, NUM_exception);
}



vector<pair<size_t, size_t>> FigureLocation::GetPositionsFigure(int SIDE, bool _INVULNERABLE_or_IMPORTANT_or_PROMOUTION_ , char _I_M_P_ )
{
	switch (_I_M_P_)
	{
	case 'I':
		return PositionFigure(SIDE, "ALL", _INVULNERABLE_or_IMPORTANT_or_PROMOUTION_, NUM_exception, NUM_exception);

	case 'M':
		return PositionFigure(SIDE, "ALL", NUM_exception, _INVULNERABLE_or_IMPORTANT_or_PROMOUTION_, NUM_exception);

	case 'P':
		return PositionFigure(SIDE, "ALL", NUM_exception, NUM_exception, _INVULNERABLE_or_IMPORTANT_or_PROMOUTION_);



	default:
		return vector<pair<size_t, size_t>>();
	}	
}



vector<pair<size_t, size_t>> FigureLocation::PositionFigure(int SIDE, string ID_Figure, int INVULNERABLE, int IMPORTANT, int PROMOUTION)
{
	vector<pair<size_t, size_t>> Position;

	for (size_t Ypos = 0; Ypos < CountCellOnYPosition; Ypos++)
	{
		for (size_t Xpos = 0; Xpos < CountCellOnXPosition; Xpos++)
		{
			// если поля совпадают то добавляем

			// если передан параметр NUM_exception значение не учитывается, так же и "ALL" 
			if (   (  ID_Figure    == "ALL"         || ( LocationClassFigure[Ypos][Xpos]->Get_ID_FIGURE()   == ID_Figure    && ID_Figure != "ALL"     ) )
				&& (  SIDE         == NUM_exception || ( LocationClassFigure[Ypos][Xpos]->GetSIDE()         == SIDE         && SIDE != NUM_exception  ) )
				&& (  INVULNERABLE == NUM_exception || ( LocationClassFigure[Ypos][Xpos]->GetINVULNERABLE() == INVULNERABLE && SIDE != NUM_exception  ) )
				&& (  IMPORTANT    == NUM_exception || ( LocationClassFigure[Ypos][Xpos]->GetIMPORTANT()    == IMPORTANT    && SIDE != NUM_exception  ) )
				&& (  PROMOUTION   == NUM_exception || ( LocationClassFigure[Ypos][Xpos]->GetPROMOUTION()   == PROMOUTION   && SIDE != NUM_exception  ) )
			   )
			{
				Position.push_back(make_pair(Xpos, Ypos));
			}
		}
	}
	return Position;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



bool FigureLocation::CheckmateForFigure(size_t XPosition, size_t Yposition, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	auto TempResult = FigureCanProtectenCheckmateForFigure(XPosition, Yposition, VectorLocationFigure);

	if (TempResult.size() == 1 && TempResult[0].first == NULL && TempResult[0].second == NULL)
	{
		return true;
	}

	return false;
}

vector<pair<size_t, size_t>> FigureLocation::FigureCanProtectenCheckmateForFigure(size_t XPosition, size_t Yposition, const vector<vector<tuple<int, string, bool, bool, bool>>>& VectorLocationFigure)
{
	
	int SIDECurrent = LocationClassFigure[Yposition][XPosition]->GetSIDE();


	/// позиции фигур которые могут защитить
	vector<pair<size_t, size_t>> ResultPositionFigure;

	// край и пустую клетку не проверяем, нет смысла
	if (SIDECurrent == 0 || SIDECurrent == -1)
	{
		// возвращаем пустой ничего не угрожает
		return vector<pair<size_t, size_t>>();
	}

	// получаем расположение фигур на игровом поле, которые урожают этой фигуре
	auto LocationThreatFigure = CheckThreatFigure(XPosition, Yposition, VectorLocationFigure);


	// если фигур, которые угрожают == 0, то логично, что ничего ему не угрожает
	if (LocationThreatFigure.empty())
	{
		// возвращаем пустой ничего не угрожает
		return vector<pair<size_t, size_t>>();
	}

	// позиции всех фигур текущего игрока Х / У
	auto PositionAllFigureForPlayer = GetPositionFigure(SIDECurrent);





	// проверяем может ли какая-то фигура текущего игрока куда-то передвинуться, чтобы исключить шах 
	// проходимся по каждой фигуре 
	
	// позиция фигуры  Х / У
	for (const auto& CurentPosFigure : PositionAllFigureForPlayer)
	{
		// получаем доступные ходы для текущей фигуры
		auto MoveForFigure = LocationClassFigure[CurentPosFigure.second][CurentPosFigure.first]->GetMoveForFigure(CurentPosFigure.first, CurentPosFigure.second, VectorLocationFigure);


		// проходимся по всему вектору ходов

		for (const auto& Move : MoveForFigure)
		{

			// создаем фиктивное расположение фигур
			auto ImaginaryLocation = VectorLocationFigure;
			
			// создаем фиктивный ход 
			// свапаем "передвигая" фигуру
			swap(ImaginaryLocation[CurentPosFigure.second][CurentPosFigure.first], ImaginaryLocation[Move.second][Move.first]);

			// устанавливаем пустую фигуру (клетку) на бывшую позицию 
			ImaginaryLocation[CurentPosFigure.second][CurentPosFigure.first] = make_tuple(0, "Figure", false, false, false);




			// начальная позиция проверяемой фигуры х \ у
			pair <size_t, size_t> CurrentPositionCheckedFigure = make_pair(XPosition, Yposition);

			// если мы дошли до проверки ходов у изначально проверяемой фигуры
			if (CurrentPositionCheckedFigure == CurentPosFigure)
			{
				// устанавливаем новое фиктивное положение для ПРОВЕРЯЕМОЙ фигуры
				CurrentPositionCheckedFigure = Move;
			}

		

			// проверяем угрозу с фиктивным расположением
			auto ThFigure = CheckThreatFigure(CurrentPositionCheckedFigure.first, CurrentPositionCheckedFigure.second, ImaginaryLocation);
		
			// считаем колличество фигур которые могут угрожать на этом ходу
			// если колличество угрожающих фигур == 0, то мата нет, фигура может закрыть важную фигуру или убить своим ходом
			if (ThFigure.size() == 0)
			{
				ResultPositionFigure.push_back(make_pair(CurentPosFigure.first, CurentPosFigure.second));
			}
			
		}
		
	}
	//возвращаем 0,0 позицию, если угрозу не избежать // пустой если угроз не найдено // или заполенный фигурами, которые могут задефать
	return ResultPositionFigure.empty() ? vector<pair<size_t, size_t>>(1, make_pair(NULL, NULL)) : ResultPositionFigure;
}
