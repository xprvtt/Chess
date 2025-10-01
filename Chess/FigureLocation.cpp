
#include "FigureLocation.h"




FigureLocation::FigureLocation(size_t countCellOnXPosition, size_t countCellOnYPosition, int windowHeight, path pathToEmptyTextureGameField, path pathToEmptyTextureEdge, float precentSizeFigure)
{
	if (countCellOnXPosition < 3 || countCellOnYPosition < 3)
	{
		return;
	}

	this->countCellOnXPosition  = countCellOnXPosition;
	this->countCellOnYPosition  = countCellOnYPosition;
	this->sizeCell              = float(windowHeight / countCellOnXPosition);
	this->precentSizeFigure     = precentSizeFigure;
	this->sizeRectangInCell     = sizeCell * precentSizeFigure;

	precentSizeFigure <= 0 ? this->positionRectangInCell = 0 : this->positionRectangInCell = (sizeCell - sizeRectangInCell) / 2;


	vectorLocationFigure.resize(countCellOnXPosition, vector<tuple<int, string, bool, bool, bool>>(countCellOnXPosition));

	/// размеры 

	//--//--//--//--//--//--//--//--//--//    ДЛЯ ФИГУР НА ДОСКЕ   //--//--//--//--//--//--//--//--//--//--//--//--//--//--//
																													
	locationClassFigure.resize(   countCellOnYPosition, vector<shared_ptr<Figure>> (countCellOnXPosition));
	locationTexture.resize(       countCellOnYPosition, vector<shared_ptr<Texture>>(countCellOnXPosition));
	locationRectangleShape.resize(countCellOnYPosition, vector<RectangleShape>     (countCellOnXPosition));
																												    
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	 
	//--//--//--//--//--//--//--//--//--//  ДЛЯ УНИКАЛЬНЫХ ФИГУР   //--//--//--//--//--//--//--//--//--//--//--//--//--//--//
																															
	uniqueFigureLocationRectangleShape.resize(countCellOnYPosition,vector<pair<size_t, RectangleShape>>(countCellOnXPosition));																																																									// 	// добавление уникальных фигур

	// нулевой элемент == край
	uniqueFigureLocationClassFigure.push_back(make_shared<Figure>(-1, true, false));
	//
	uniqueFigureLocationTexture.push_back(make_shared<Texture>(pathToEmptyTextureEdge));

	// первый элемент == пустая клетка
	uniqueFigureLocationClassFigure.push_back(make_shared<Figure>(0));
	uniqueFigureLocationTexture.push_back(make_shared<Texture>(pathToEmptyTextureGameField));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	for (size_t yPosition = 0; yPosition < countCellOnYPosition; yPosition++)
	{
		for (size_t xPosition = 0; xPosition < countCellOnXPosition; xPosition++)
		{
			int U; // итератор расположение уникального класса и уникальную текстуру в векторах

			// если край то используем фигуру-край == Side -1
			if (xPosition == 0 || yPosition == 0 || xPosition == countCellOnXPosition - 1 || yPosition == countCellOnYPosition - 1)
			{
				U = 0; // итератор на край 

				locationClassFigure[yPosition][xPosition] = uniqueFigureLocationClassFigure[U];
				locationTexture[yPosition][xPosition] = uniqueFigureLocationTexture[U];

				locationRectangleShape[yPosition][xPosition].setTexture(uniqueFigureLocationTexture[U].get(), true);

				uniqueFigureLocationRectangleShape[yPosition][xPosition].second.setTexture(uniqueFigureLocationTexture[U].get(), true);
				uniqueFigureLocationRectangleShape[yPosition][xPosition].first = U;
			}
			// в противном случае считаем как пустая клетка == Side 0
			else

			{
				U = 1; // итератор на пустую клетку (фигуру)

				locationClassFigure[yPosition][xPosition] = uniqueFigureLocationClassFigure[U];
				locationTexture[yPosition][xPosition] = uniqueFigureLocationTexture[U];

				locationRectangleShape[yPosition][xPosition].setTexture(uniqueFigureLocationTexture[U].get(), true);

				uniqueFigureLocationRectangleShape[yPosition][xPosition].second.setTexture(uniqueFigureLocationTexture[U].get(), true);
			}

			//--//--//--//--//--//--//--//--//--//   ДЛЯ ФИГУР НА ДОСКЕ  //--//--//--//--//--//--//--//--//--//--//--//--//--//-//
																																
			locationRectangleShape[yPosition][xPosition].setSize(Vector2f(sizeCell, sizeCell));										
			locationRectangleShape[yPosition][xPosition].setPosition(Vector2f(xPosition * sizeCell, yPosition * sizeCell));		

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			//--//--//--//--//--//--//--//--//--//     ДЛЯ УНИКАЛЬНЫХ ФИГУР   //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//

			uniqueFigureLocationRectangleShape[yPosition][xPosition].second.setSize(Vector2f(sizeCell * precentSizeFigure, sizeCell * precentSizeFigure));			
			uniqueFigureLocationRectangleShape[yPosition][xPosition].second.setPosition(Vector2f(xPosition * sizeCell * precentSizeFigure + windowHeight, yPosition * sizeCell * precentSizeFigure + windowHeight / 2 ));
			uniqueFigureLocationRectangleShape[yPosition][xPosition].second.setOutlineColor(Color::Black);

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			get<0>(vectorLocationFigure[yPosition][xPosition]) = locationClassFigure[yPosition][xPosition]->get_SIDE();
			get<1>(vectorLocationFigure[yPosition][xPosition]) = locationClassFigure[yPosition][xPosition]->get_ID_FIGURE();
			get<2>(vectorLocationFigure[yPosition][xPosition]) = locationClassFigure[yPosition][xPosition]->get_INVULNERABLE();
			get<3>(vectorLocationFigure[yPosition][xPosition]) = locationClassFigure[yPosition][xPosition]->get_IMPORTANT();
			get<4>(vectorLocationFigure[yPosition][xPosition]) = locationClassFigure[yPosition][xPosition]->get_PROMOUTION();
		}
	}
}

//--//--//--//--//--//--//--//--//--//    ДЛЯ ФИГУР НА ДОСКЕ   //--//--//--//--//--//--//--//--//--//--//--//--//


bool FigureLocation::setFigure(size_t xPosition, size_t yPosition, string ID_FIGURE, int SIDE, bool INVULNERABLE, bool IMPORTANT, vector<tuple<int, string, bool, bool, bool>> VECTOR_PROMOUTION)
{

	if (locationClassFigure[yPosition][xPosition]->get_SIDE() == -1)
	{
		OutputLog("ERROR -> Class -> FigureLocation -> SetFigure -> попытка установить за границу");
		return false;
	}

	for (int it = 0; it < uniqueFigureLocationClassFigure.size(); it++)
	{
		//находим итератор указанной финугы
		if (   uniqueFigureLocationClassFigure[it]->get_SIDE()          == SIDE
			&& uniqueFigureLocationClassFigure[it]->get_ID_FIGURE()     == ID_FIGURE
			&& uniqueFigureLocationClassFigure[it]->get_INVULNERABLE()  == INVULNERABLE
			&& uniqueFigureLocationClassFigure[it]->get_IMPORTANT()     == IMPORTANT
		   )
		{

			// станавливаем текстуру фигуры на поле
			locationTexture[yPosition][xPosition] = uniqueFigureLocationTexture[it];

			// устанавливаем позицию и размер фигуры -> меньше чем пустая клетка или край
			locationRectangleShape[yPosition][xPosition].setSize(Vector2f(sizeCell * precentSizeFigure, sizeCell * precentSizeFigure));
			locationRectangleShape[yPosition][xPosition].setPosition(Vector2f(xPosition * sizeCell + positionRectangInCell, yPosition * sizeCell + positionRectangInCell));
			// передаем установленную текстуру
			locationRectangleShape[yPosition][xPosition].setTexture(locationTexture[yPosition][xPosition].get(), true);

			//ставим класс фигуры на поле
			locationClassFigure[yPosition][xPosition] = uniqueFigureLocationClassFigure[it];

			return true;
		}
	}
	OutputLog("ERROR -> Class -> FigureLocation -> SetFigure -> фигура не найдена, сначала ее необходимо добавить -> AddUniqueFigure()");
	return false;
}

bool FigureLocation::PromoutionSelectFigure(int SIDE, string ID_FIGURE, bool INVULNERABLE, bool IMPORTANT, bool PROMOUTION)
{

	// фигура может превратиться в указанную фигуру???.........
	if (locationClassFigure[positionSelectFigure.second][positionSelectFigure.first]->getPromoutionFigure(SIDE, ID_FIGURE, INVULNERABLE, IMPORTANT, PROMOUTION))
	{
		for (int it = 0; it < uniqueFigureLocationClassFigure.size(); it++)
		{
			if (
				uniqueFigureLocationClassFigure[it]->get_ID_FIGURE() == ID_FIGURE && 
				uniqueFigureLocationClassFigure[it]->get_SIDE() == locationClassFigure[positionSelectFigure.second][positionSelectFigure.first]->get_SIDE()
			   )
			{
				// заменяем текстуру
				locationTexture[positionSelectFigure.second][positionSelectFigure.first] = uniqueFigureLocationTexture[it];

				// передаем установленную текстуру
				locationRectangleShape[positionSelectFigure.second][positionSelectFigure.first].setTexture(locationTexture[positionSelectFigure.second][positionSelectFigure.first].get(), true);

				//ставим класс фигуры на поле
				locationClassFigure[positionSelectFigure.second][positionSelectFigure.first] = uniqueFigureLocationClassFigure[it];

				return true;
			}
		}

		OutputLog("Error -> Class -> FigureLocation -> PromoutionSelectFigure() -> не найден итератор");
	}
	else
	{
		OutputLog("Error -> Class -> FigureLocation -> PromoutionSelectFigure() -> невозможно превратиться в эту фигуру");
	}
	return false;
}

bool FigureLocation::addUniqueFigure(shared_ptr<Figure> newFigureOrheirs, path currentTextureFigure)
{
	// изначально считаем что фигура уникальная 
	// проверяем есть ли такие фигуры у нас еще?
	// начинаем с 2 т.к. 0 и 1 слоты заняты заранее "краем" и пустой фигурой (видимой как пустая клетка) соответственно

	size_t Size = uniqueFigureLocationClassFigure.size();

	for (int it = 2; it < Size; it++)
	{
		// если поля совпадают значит не уникальна и не добавляем
		if (    
			 uniqueFigureLocationClassFigure[it]->get_ID_FIGURE()         == newFigureOrheirs->get_ID_FIGURE()    &&
			 uniqueFigureLocationClassFigure[it]->get_SIDE()              == newFigureOrheirs->get_SIDE()         &&
			 uniqueFigureLocationClassFigure[it]->get_INVULNERABLE()      == newFigureOrheirs->get_INVULNERABLE() &&
			 uniqueFigureLocationClassFigure[it]->get_IMPORTANT()         == newFigureOrheirs->get_IMPORTANT()	  &&
			 uniqueFigureLocationClassFigure[it]->get_VECTOR_PROMOUTION() == newFigureOrheirs->get_VECTOR_PROMOUTION()
		   )
		{
			//не добавляем
			return false;
		}	
	}

	// иначе, если поля отличаются добавляем
	uniqueFigureLocationClassFigure.push_back(newFigureOrheirs);
	uniqueFigureLocationTexture.push_back(make_shared<Texture>(currentTextureFigure));

	for (size_t row = 1; row < countCellOnYPosition - 1; row++)
	{
		for (size_t col = 1; col < countCellOnXPosition - 1; col++)
		{
			// если клетка пустая то сразу же размещаем аникальную фигуру на поле уникальных фигур
			if (uniqueFigureLocationRectangleShape[row][col].first == 0)
			{
				size_t latestElement = uniqueFigureLocationTexture.size() - 1;

				// ставим текстуру
				uniqueFigureLocationRectangleShape[row][col].second.setTexture(uniqueFigureLocationTexture[latestElement].get(), true);
				uniqueFigureLocationRectangleShape[row][col].second.setOutlineThickness(-2);
				uniqueFigureLocationRectangleShape[row][col].second.setOutlineColor(Color::Black);

				// ставим итератор откуда привязали
				uniqueFigureLocationRectangleShape[row][col].first = latestElement;
				return true;
			}
		}
	}	
	return false;
}


bool FigureLocation::moveSelectFigure(size_t xPositionMove, size_t yPositionMove)
{
	auto availableMove = getAvailableMovesForFigure(positionSelectFigure.first, positionSelectFigure.second);

	bool exists = false;

	for (const auto& move : availableMove)
	{ 
		if (move.first == xPositionMove && move.second == yPositionMove)
		{
			exists = true;
		}
	}
	if (!exists)
	{
		OutputLog("ход невозможен");
		return false;
	}

	if (locationClassFigure[yPositionMove][xPositionMove]->get_SIDE() == 0)
	{
		swap(locationClassFigure[positionSelectFigure.second][positionSelectFigure.first], locationClassFigure[yPositionMove][xPositionMove]);
		swap(locationTexture[positionSelectFigure.second][positionSelectFigure.first], locationTexture[yPositionMove][xPositionMove]);


		//изменяем размер и положение
		locationRectangleShape[positionSelectFigure.second][positionSelectFigure.first].setSize(Vector2f(sizeCell, sizeCell));
		locationRectangleShape[positionSelectFigure.second][positionSelectFigure.first].setPosition(Vector2f(sizeCell * positionSelectFigure.first, sizeCell * positionSelectFigure.second));

		// установили тестуры т.к. они свапнуты
		locationRectangleShape[positionSelectFigure.second][positionSelectFigure.first].setTexture(locationTexture[positionSelectFigure.second][positionSelectFigure.first].get(), true);

		//изменяем размер и положение
		locationRectangleShape[yPositionMove][xPositionMove].setSize(Vector2f(sizeCell * precentSizeFigure, sizeCell * precentSizeFigure));
		locationRectangleShape[yPositionMove][xPositionMove].setPosition(Vector2f(sizeCell * xPositionMove + positionRectangInCell, sizeCell * yPositionMove + positionRectangInCell));

		// установили тестуры т.к. они свапнуты
		locationRectangleShape[yPositionMove][xPositionMove].setTexture(locationTexture[yPositionMove][xPositionMove].get(), true);

		return true;
	}
	// если клетка не пустая предполагается что там фигура другого игрока
	else
	{	
		// Фигура должна быть доступна для взятия т.е. Invulnerability = false		
		if (locationClassFigure[yPositionMove][xPositionMove]->get_INVULNERABLE())
		{
			OutputLog("ERROR -> class -> FigureLocation -> moveSelectFigure() -> фигура неуязвима");
			return false;
		}

		swap(locationClassFigure[positionSelectFigure.second][positionSelectFigure.first], locationClassFigure[yPositionMove][xPositionMove]);
		swap(locationTexture[positionSelectFigure.second][positionSelectFigure.first], locationTexture[yPositionMove][xPositionMove]);

		//
		locationRectangleShape[yPositionMove][xPositionMove].setSize(Vector2f(sizeCell * precentSizeFigure, sizeCell * precentSizeFigure));
		locationRectangleShape[yPositionMove][xPositionMove].setPosition(Vector2f(sizeCell * xPositionMove + positionRectangInCell, sizeCell * yPositionMove + positionRectangInCell));
		//
		locationRectangleShape[yPositionMove][xPositionMove].setTexture(locationTexture[yPositionMove][xPositionMove].get(), true);
		//
		locationTexture[positionSelectFigure.second][positionSelectFigure.first] = uniqueFigureLocationTexture[1]; // 1 - пустая текстура
		//
		locationClassFigure[positionSelectFigure.second][positionSelectFigure.first] = uniqueFigureLocationClassFigure[1]; // 1 - пустая фигура (клетка)
		//
		locationRectangleShape[positionSelectFigure.second][positionSelectFigure.first].setSize(Vector2f(sizeCell, sizeCell));
		locationRectangleShape[positionSelectFigure.second][positionSelectFigure.first].setPosition(Vector2f(sizeCell * positionSelectFigure.first, sizeCell * positionSelectFigure.second));
		//
		locationRectangleShape[positionSelectFigure.second][positionSelectFigure.first].setTexture(locationTexture[positionSelectFigure.second][positionSelectFigure.first].get(), true);

		return true;
	}

	return false;
}
/////////////////////////////////////////////////////////////////

pair<int, int> FigureLocation::getPositionFigureWhenMousePressed(Vector2f positonMouse)
{
	for (size_t yPosition = 0; yPosition < countCellOnXPosition; yPosition++)
	{
		for (size_t xPosition = 0; xPosition < countCellOnXPosition; xPosition++)
		{
			// если задели фигуру на игровом поле
			if (locationRectangleShape[yPosition][xPosition].getGlobalBounds().contains(positonMouse))
			{
				return make_pair(xPosition, yPosition);
			}
		}
	}
	return make_pair(NULL, NULL);
}
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////

bool FigureLocation::seletcFigure(size_t xPositionFigure, size_t yPositionFigure)
{
	int sideFigure = locationClassFigure[yPositionFigure][xPositionFigure]->get_SIDE();

	if (sideFigure == 0 || sideFigure == -1)
	{
		return false;
	}
	if (selectFigure)
	{
		unSeletcAllFigure();
	}

	locationRectangleShape[yPositionFigure][xPositionFigure].setOutlineThickness(-3);
	locationRectangleShape[yPositionFigure][xPositionFigure].setOutlineColor(Color::Red);

	positionSelectFigure = make_pair(xPositionFigure, yPositionFigure);
	selectFigure = true;

	return selectFigure;
}

bool FigureLocation::unSeletcAllFigure()
{
	for (size_t yPosition = 0; yPosition < countCellOnXPosition; yPosition++)
	{
		for (size_t xPosition = 0; xPosition < countCellOnXPosition; xPosition++)
		{
			locationRectangleShape[yPosition][xPosition].setOutlineThickness(0);
		}
	}
	positionSelectFigure = make_pair(0, 0);
	selectFigure = false;

	return true;
}

bool FigureLocation::figuresSelectedOrNot()
{
	return selectFigure;
}

pair<int, int> FigureLocation::getPositionSelectFigure()
{
	return positionSelectFigure;
}
//////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////

vector<pair<size_t, size_t>> FigureLocation::getAvailableMovesForFigure(size_t xPositionFigure, size_t yPositionFigure)
{
	return locationClassFigure[yPositionFigure][xPositionFigure]->getMoveForFigure(xPositionFigure, yPositionFigure, getVectorLocationFigure());
}

bool FigureLocation::promoutionFigureOnPosition(size_t xPositionFigure, size_t yPositionFigure)
{
	return locationClassFigure[yPositionFigure][xPositionFigure]->getPossibilityPromotion(xPositionFigure, yPositionFigure, getVectorLocationFigure());
}

vector<vector<tuple<int, string, bool, bool, bool>>>  FigureLocation::getVectorLocationFigure()
{
	updateVectorLocationFigure();
	return vectorLocationFigure;
}

void FigureLocation::updateVectorLocationFigure()
{
	for (size_t yPosition = 0; yPosition < countCellOnXPosition; yPosition++)
	{
		for (size_t xPosition = 0; xPosition < countCellOnXPosition; xPosition++)
		{
			get<0>(vectorLocationFigure[yPosition][xPosition]) = locationClassFigure[yPosition][xPosition]->get_SIDE();
			get<1>(vectorLocationFigure[yPosition][xPosition]) = locationClassFigure[yPosition][xPosition]->get_ID_FIGURE();
			get<2>(vectorLocationFigure[yPosition][xPosition]) = locationClassFigure[yPosition][xPosition]->get_INVULNERABLE();
			get<3>(vectorLocationFigure[yPosition][xPosition]) = locationClassFigure[yPosition][xPosition]->get_IMPORTANT();
			get<4>(vectorLocationFigure[yPosition][xPosition]) = locationClassFigure[yPosition][xPosition]->get_PROMOUTION();
		}
	}
}

//////////////////////////////////////////////////////////////////////

string FigureLocation::getIDFigure(size_t xPosition, size_t yPosition)
{
	return locationClassFigure[yPosition][xPosition]->get_ID_FIGURE();
}

int FigureLocation::getSideFigure(size_t xPosition, size_t yPosition)
{
	return locationClassFigure[yPosition][xPosition]->get_SIDE();
}

const RectangleShape& FigureLocation::getRectangleShapeFigure(size_t xPosition, size_t yPosition)
{
	return locationRectangleShape[yPosition][xPosition];
}

bool FigureLocation::getInvulnerableFigure(size_t xPosition, size_t yPosition)
{
	return locationClassFigure[yPosition][xPosition]->get_INVULNERABLE();
}

bool FigureLocation::getImportantFigure(size_t xPosition, size_t yPosition)
{
	return locationClassFigure[yPosition][xPosition]->get_IMPORTANT();
}
//////////////////////////////////////////////////////////////////////








//--//--//--//--//--//--//--//--//--//      ДЛЯ ПОЛЕ УНИКАЛЬНЫХ ФИГУР     //--//--//--//--//--//--//--//--//--//--//--//-//

bool FigureLocation::getInvulnerableUniqueFigure(size_t xPosition, size_t yPosition)
{
	int it = getIteratorUniqueFigure(xPosition, yPosition);
	return uniqueFigureLocationClassFigure[it]->get_INVULNERABLE();
}


string FigureLocation::getIDUniqueFigure(size_t xPosition, size_t yPosition)
{
	int it = getIteratorUniqueFigure(xPosition, yPosition);
	return uniqueFigureLocationClassFigure[it]->get_ID_FIGURE();
}


int FigureLocation::getSideUniqueFigure(size_t xPosition, size_t yPosition)
{
	int it = getIteratorUniqueFigure(xPosition, yPosition);
	return uniqueFigureLocationClassFigure[it]->get_SIDE();
}

bool FigureLocation::getImportantUniqueFigure(size_t xPosition, size_t yPosition)
{
	int it = getIteratorUniqueFigure(xPosition, yPosition);	
	return uniqueFigureLocationClassFigure[it]->get_IMPORTANT();
}

bool FigureLocation::getPromoutionUniqueFigure(size_t xPosition, size_t yPosition)
{
	int it = getIteratorUniqueFigure(xPosition, yPosition);
	return uniqueFigureLocationClassFigure[it]->get_PROMOUTION();
}

const RectangleShape& FigureLocation::getRectangleShapeUniqueFigure(size_t xPosition, size_t yPosition)
{
	return uniqueFigureLocationRectangleShape[yPosition][xPosition].second;
}


int FigureLocation::getIteratorUniqueFigure(size_t xPosition, size_t yPosition)
{
	return uniqueFigureLocationRectangleShape[yPosition][xPosition].first;
}
int FigureLocation::getIteratorUniqueFigure(int SIDE, string ID_FIGURE, bool INVULNERABLE, bool IMPORTANT, bool PROMOUTION)
{
	for (int it = 0; it < uniqueFigureLocationClassFigure.size(); it++)
	{
		// если находим такую фигуру то возвращаем итератор
		if (   uniqueFigureLocationClassFigure[it]->get_ID_FIGURE()       == ID_FIGURE
			&& uniqueFigureLocationClassFigure[it]->get_SIDE()             == SIDE
			&& uniqueFigureLocationClassFigure[it]->get_INVULNERABLE()     == INVULNERABLE
			&& uniqueFigureLocationClassFigure[it]->get_IMPORTANT()        == IMPORTANT
			&& uniqueFigureLocationClassFigure[it]->get_PROMOUTION()       == PROMOUTION
			)
		{
			return it;
		}
	}
	return -1;
}


bool FigureLocation::seletcUniqueFigureForPromoution(size_t xPositionFigure, size_t yPositionFigure)
{
	// выделяем фигуры в которые может превратиться фигура

	//получаем сторону текущего игрока
	int sideFigure = locationClassFigure[yPositionFigure][xPositionFigure]->get_SIDE();

	for ( auto& vectorRectangleShape : uniqueFigureLocationRectangleShape)
	{
		for ( auto& rectangleShape : vectorRectangleShape)
		{
			int it = rectangleShape.first;

			// если фигура той же стороны
			if (uniqueFigureLocationClassFigure[it]->get_SIDE() == sideFigure)
			{
				// и может превратиться в указанную фигуру???... ......
				if (locationClassFigure[yPositionFigure][xPositionFigure]->getPromoutionFigure(uniqueFigureLocationClassFigure[it]->get_SIDE(),
					                                                                           uniqueFigureLocationClassFigure[it]->get_ID_FIGURE(),
					                                                                           uniqueFigureLocationClassFigure[it]->get_INVULNERABLE(),
					                                                                           uniqueFigureLocationClassFigure[it]->get_IMPORTANT(),
																							   uniqueFigureLocationClassFigure[it]->get_PROMOUTION()
																							  )
				)
				{
					//подкрашиваем фигуру
					rectangleShape.second.setOutlineColor(Color::Red);
				}
			}
		}
	}
	return true;
}


bool FigureLocation::unSeletcUniqueFigure()
{
	for (auto& vectorRectangleShape : uniqueFigureLocationRectangleShape)
	{
		for (auto& rectangleShape : vectorRectangleShape)
		{
			rectangleShape.second.setOutlineColor(Color::Black);
		}
	}
	return true;
}


pair<int, int> FigureLocation::getPositionUniqueFigureWhenMousePressed(Vector2f positonMouse)
{
	for (size_t yPosition = 0; yPosition < countCellOnYPosition; yPosition++)
	{
		for (size_t xPosition = 0; xPosition < countCellOnXPosition; xPosition++)
		{
			// если задели фигуру на поле уникальных фигур возвращаем позицию в минусе
			if (uniqueFigureLocationRectangleShape[yPosition][xPosition].second.getGlobalBounds().contains(positonMouse))
			{
				return make_pair(xPosition, yPosition);
			}
		}
	}
	return make_pair(NULL, NULL);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




vector<pair<size_t, size_t>> FigureLocation::checkThreatFigure(size_t xPositionOnVectorLocationFigure, size_t yPositionOnVectorLocationFigure, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	vector<pair<size_t, size_t>> resultPositionEnemyFigure;

	// получаем сторону текущего игрока, у которого будет проверяться фигура
	int  sideCurrentFigure;

	sideCurrentFigure = get<0>(vectorLocationFigure[yPositionOnVectorLocationFigure][xPositionOnVectorLocationFigure]);
	
	// проверяем все фигуры на переданном игровом поле у других игроков, которые могу "угрожать взятием"
	for (size_t Ypos = 0; Ypos < countCellOnYPosition; Ypos++)
	{
		for (size_t Xpos = 0; Xpos < countCellOnXPosition; Xpos++)
		{
			// если у фигуры на позиции другая сторона, то проверяем далее....
			if (   get<0>(vectorLocationFigure[Ypos][Xpos]) != sideCurrentFigure	
				&& get<0>(vectorLocationFigure[Ypos][Xpos]) != -1                    // не учитываем край 
				&& get<0>(vectorLocationFigure[Ypos][Xpos]) != 0	                 // не учитываем пустые клетки (фигуры)
			   )
			{
				
				int it = getIteratorUniqueFigure(
					                              get<0>(vectorLocationFigure[Ypos][Xpos]),
					                              get<1>(vectorLocationFigure[Ypos][Xpos]),
					                              get<2>(vectorLocationFigure[Ypos][Xpos]),
					                              get<3>(vectorLocationFigure[Ypos][Xpos]),
					                              get<4>(vectorLocationFigure[Ypos][Xpos])
												);
				// получаем ходы на которые может сходить фигура
				auto moveForFigure = uniqueFigureLocationClassFigure[it]->getMoveForFigure(Xpos, Ypos, vectorLocationFigure);

				// если фигура может сходить на позицию проверяемой фигуры ("угрожать взятием"), то добавляем эту фигуру в вектор, она угрожает
				for (const auto& Move : moveForFigure)
				{
					if (Move.first == xPositionOnVectorLocationFigure && Move.second == yPositionOnVectorLocationFigure)
					{
						resultPositionEnemyFigure.push_back(make_pair(Xpos, Ypos));
					}
				}
			}
		}
	}	
	return resultPositionEnemyFigure;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<pair<size_t, size_t>> FigureLocation::getPositionFigure(int SIDE, string ID_Figure, bool INVULNERABLE, bool IMPORTANT, bool PROMOUTION)
{
	return positionFigure(SIDE, ID_Figure, INVULNERABLE, IMPORTANT, PROMOUTION);
}



vector<pair<size_t, size_t>> FigureLocation::getPositionFigure(int SIDE, string ID_FIGURE)
{
	return positionFigure(SIDE, ID_FIGURE, NUM_exception, NUM_exception, NUM_exception);
}



vector<pair<size_t, size_t>> FigureLocation::getPositionFigure(int SIDE)
{
	return positionFigure(SIDE, "ALL", NUM_exception, NUM_exception, NUM_exception);
}



vector<pair<size_t, size_t>> FigureLocation::getPositionsFigure(int SIDE, bool _INVULNERABLE_or_IMPORTANT_or_PROMOUTION_ , char _I_M_P_ )
{
	switch (_I_M_P_)
	{
	case 'I':
		return positionFigure(SIDE, "ALL", _INVULNERABLE_or_IMPORTANT_or_PROMOUTION_, NUM_exception, NUM_exception);

	case 'M':
		return positionFigure(SIDE, "ALL", NUM_exception, _INVULNERABLE_or_IMPORTANT_or_PROMOUTION_, NUM_exception);

	case 'P':
		return positionFigure(SIDE, "ALL", NUM_exception, NUM_exception, _INVULNERABLE_or_IMPORTANT_or_PROMOUTION_);



	default:
		return vector<pair<size_t, size_t>>();
	}	
}



vector<pair<size_t, size_t>> FigureLocation::positionFigure(int SIDE, string ID_FIGURE, int INVULNERABLE, int IMPORTANT, int PROMOUTION)
{
	vector<pair<size_t, size_t>> position;

	for (size_t yPos = 0; yPos < countCellOnYPosition; yPos++)
	{
		for (size_t xPos = 0; xPos < countCellOnXPosition; xPos++)
		{
			// если поля совпадают то добавляем

			// если передан параметр NUM_exception значение не учитывается, так же и "ALL" 
			if (   (  ID_FIGURE    == "ALL"         || ( locationClassFigure[yPos][xPos]->get_ID_FIGURE()    == ID_FIGURE    && ID_FIGURE != "ALL"     ) )
				&& (  SIDE         == NUM_exception || ( locationClassFigure[yPos][xPos]->get_SIDE()         == SIDE         && SIDE != NUM_exception  ) )
				&& (  INVULNERABLE == NUM_exception || ( locationClassFigure[yPos][xPos]->get_INVULNERABLE() == INVULNERABLE && SIDE != NUM_exception  ) )
				&& (  IMPORTANT    == NUM_exception || ( locationClassFigure[yPos][xPos]->get_IMPORTANT()    == IMPORTANT    && SIDE != NUM_exception  ) )
				&& (  PROMOUTION   == NUM_exception || ( locationClassFigure[yPos][xPos]->get_PROMOUTION()   == PROMOUTION   && SIDE != NUM_exception  ) )
			   )
			{
				position.push_back(make_pair(xPos, yPos));
			}
		}
	}
	return position;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



bool FigureLocation::checkmateForFigure(size_t xPosition, size_t yPosition, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	auto tempResult = figureCanProtectenCheckmateForFigure(xPosition, yPosition, vectorLocationFigure);

	if (tempResult.size() == 1 && tempResult[0].first == NULL && tempResult[0].second == NULL)
	{
		return true;
	}

	return false;
}

vector<pair<size_t, size_t>> FigureLocation::figureCanProtectenCheckmateForFigure(size_t xPosition, size_t yPosition, const vector<vector<tuple<int, string, bool, bool, bool>>>& vectorLocationFigure)
{
	
	int current_SIDE = locationClassFigure[yPosition][xPosition]->get_SIDE();


	/// позиции фигур которые могут защитить
	vector<pair<size_t, size_t>> resultPositionFigure;

	// край и пустую клетку не проверяем, нет смысла
	if (current_SIDE == 0 || current_SIDE == -1)
	{
		// возвращаем пустой ничего не угрожает
		return vector<pair<size_t, size_t>>();
	}

	// получаем расположение фигур на игровом поле, которые урожают этой фигуре
	auto locationThreatFigure = checkThreatFigure(xPosition, yPosition, vectorLocationFigure);


	// если фигур, которые угрожают == 0, то логично, что ничего ему не угрожает
	if (locationThreatFigure.empty())
	{
		// возвращаем пустой ничего не угрожает
		return vector<pair<size_t, size_t>>();
	}

	// позиции всех фигур текущего игрока Х / У
	auto positionAllFigureForPlayer = getPositionFigure(current_SIDE);





	// проверяем может ли какая-то фигура текущего игрока куда-то передвинуться, чтобы исключить шах 
	// проходимся по каждой фигуре 
	
	// позиция фигуры  Х / У
	for (const auto& curentPosFigure : positionAllFigureForPlayer)
	{
		// получаем доступные ходы для текущей фигуры
		auto moveForFigure = locationClassFigure[curentPosFigure.second][curentPosFigure.first]->getMoveForFigure(curentPosFigure.first, curentPosFigure.second, vectorLocationFigure);


		// проходимся по всему вектору ходов

		for (const auto& move : moveForFigure)
		{

			// создаем фиктивное расположение фигур
			auto imaginaryLocation = vectorLocationFigure;
			
			// создаем фиктивный ход 
			// свапаем "передвигая" фигуру
			swap(imaginaryLocation[curentPosFigure.second][curentPosFigure.first], imaginaryLocation[move.second][move.first]);

			// устанавливаем пустую фигуру (клетку) на бывшую позицию 
			imaginaryLocation[curentPosFigure.second][curentPosFigure.first] = make_tuple(0, "Figure", false, false, false);




			// начальная позиция проверяемой фигуры х \ у
			pair <size_t, size_t> currentPositionCheckedFigure = make_pair(xPosition, yPosition);

			// если мы дошли до проверки ходов у изначально проверяемой фигуры
			if (currentPositionCheckedFigure == curentPosFigure)
			{
				// устанавливаем новое фиктивное положение для ПРОВЕРЯЕМОЙ фигуры
				currentPositionCheckedFigure = move;
			}

		

			// проверяем угрозу с фиктивным расположением
			auto thFigure = checkThreatFigure(currentPositionCheckedFigure.first, currentPositionCheckedFigure.second, imaginaryLocation);
		
			// считаем колличество фигур которые могут угрожать на этом ходу
			// если колличество угрожающих фигур == 0, то мата нет, фигура может закрыть важную фигуру или убить своим ходом
			if (thFigure.size() == 0)
			{
				resultPositionFigure.push_back(make_pair(curentPosFigure.first, curentPosFigure.second));
			}
			
		}
		
	}
	//возвращаем 0,0 позицию, если угрозу не избежать // пустой если угроз не найдено // или заполенный фигурами, которые могут задефать
	return resultPositionFigure.empty() ? vector<pair<size_t, size_t>>(1, make_pair(NULL, NULL)) : resultPositionFigure;
}
