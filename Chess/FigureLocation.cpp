
#include "FigureLocation.h"




FigureLocation::FigureLocation(size_t countCellOnXPosition, size_t countCellOnYPosition, int windowHeight, std::filesystem::path pathToEmptyTextureGameField, std::filesystem::path pathToEmptyTextureEdge, float precentSizeFigure)
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

	vectorLocationFigure.resize(countCellOnXPosition, std::vector<PropertiesFigure>(countCellOnXPosition));




	///
	/// РАЗМЕРЫ 
	///
	
	//--//--//--//--//--//--//--//--//--//    ДЛЯ ФИГУР НА ДОСКЕ   //--//--//--//--//--//--//--//--//--//--//--//--//--//--//
																													
	locationClassFigure.resize(   countCellOnYPosition, std::vector<std::shared_ptr<Figure>>     (countCellOnXPosition));
	locationTexture.resize(       countCellOnYPosition, std::vector<std::shared_ptr<sf::Texture>>(countCellOnXPosition));
	locationRectangleShape.resize(countCellOnYPosition, std::vector<sf::RectangleShape>          (countCellOnXPosition));





	 
	//--//--//--//--//--//--//--//--//--//  ДЛЯ УНИКАЛЬНЫХ ФИГУР   //--//--//--//--//--//--//--//--//--//--//--//--//--//--//
																															
	uniqueFigureLocationRectangleShape.resize(countCellOnYPosition,std::vector<std::pair<size_t, sf::RectangleShape>>(countCellOnXPosition));	
	
	///
	/// край
	/// 
	uniqueFigureLocationClassFigure.push_back(std::make_shared<Space>(-1, true, false));
	uniqueFigureLocationTexture.push_back(std::make_shared<sf::Texture>(pathToEmptyTextureEdge));

	///
	/// пустая клетка
	/// 
	uniqueFigureLocationClassFigure.push_back(std::make_shared<Space>(0));
	uniqueFigureLocationTexture.push_back(std::make_shared<sf::Texture>(pathToEmptyTextureGameField));













	for (size_t yPosition = 0; yPosition < countCellOnYPosition; yPosition++)
	{
		for (size_t xPosition = 0; xPosition < countCellOnXPosition; xPosition++)
		{
			int U; // итератор расположение уникального класса и уникальную текстуру в векторах

			///
			/// если край то используем фигуру-край == Side -1
			/// 
			if (xPosition == 0 || yPosition == 0 || xPosition == countCellOnXPosition - 1 || yPosition == countCellOnYPosition - 1)
			{
				U = 0; // итератор на край 

				locationClassFigure[yPosition][xPosition] = uniqueFigureLocationClassFigure[U];
				locationTexture[yPosition][xPosition] = uniqueFigureLocationTexture[U];

				locationRectangleShape[yPosition][xPosition].setTexture(uniqueFigureLocationTexture[U].get(), true);

				uniqueFigureLocationRectangleShape[yPosition][xPosition].second.setTexture(uniqueFigureLocationTexture[U].get(), true);
				uniqueFigureLocationRectangleShape[yPosition][xPosition].first = U;
			}

			///
			/// в противном случае считаем как пустая клетка == Side 0
			/// 
			else

			{
				U = 1; // итератор на пустую клетку (фигуру)

				locationClassFigure[yPosition][xPosition] = uniqueFigureLocationClassFigure[U];
				locationTexture[yPosition][xPosition] = uniqueFigureLocationTexture[U];

				locationRectangleShape[yPosition][xPosition].setTexture(uniqueFigureLocationTexture[U].get(), true);

				uniqueFigureLocationRectangleShape[yPosition][xPosition].second.setTexture(uniqueFigureLocationTexture[U].get(), true);
			}







			//--//--//--//--//--//--//--//--//--//   ДЛЯ ФИГУР НА ДОСКЕ  //--//--//--//--//--//--//--//--//--//--//--//--//--//-//
																																
			locationRectangleShape[yPosition][xPosition].setSize(sf::Vector2f(sizeCell, sizeCell));										
			locationRectangleShape[yPosition][xPosition].setPosition(sf::Vector2f(xPosition * sizeCell, yPosition * sizeCell));



			//--//--//--//--//--//--//--//--//--//     ДЛЯ УНИКАЛЬНЫХ ФИГУР   //--//--//--//--//--//--//--//--//--//--//--//--//--//

			uniqueFigureLocationRectangleShape[yPosition][xPosition].second.setSize(sf::Vector2f(sizeCell * precentSizeFigure, sizeCell * precentSizeFigure));
			uniqueFigureLocationRectangleShape[yPosition][xPosition].second.setPosition(sf::Vector2f(xPosition * sizeCell * precentSizeFigure + windowHeight, yPosition * sizeCell * precentSizeFigure + windowHeight / 2 ));
			uniqueFigureLocationRectangleShape[yPosition][xPosition].second.setOutlineColor(sf::Color::Black);






			vectorLocationFigure[yPosition][xPosition].side         = locationClassFigure[yPosition][xPosition]->getSide();
			vectorLocationFigure[yPosition][xPosition].idFigure     = locationClassFigure[yPosition][xPosition]->getIdFigure();
			vectorLocationFigure[yPosition][xPosition].invulnerable = locationClassFigure[yPosition][xPosition]->getInvulnerable();
			vectorLocationFigure[yPosition][xPosition].important    = locationClassFigure[yPosition][xPosition]->getImportant();
			vectorLocationFigure[yPosition][xPosition].promoution   = locationClassFigure[yPosition][xPosition]->getPromoution();

		}
	}
}











//--//--//--//--//--//--//--//--//--//    ДЛЯ ФИГУР НА ДОСКЕ   //--//--//--//--//--//--//--//--//--//--//--//--//



/// 
/// установка по сухим параметрам устаревает => апнуть полноценную замену =>
/// bool FigureLocation::setFigure(size_t xPosition, size_t yPosition, PropertiesFigure pF)
/// 

bool FigureLocation::setFigure(size_t xPosition, size_t yPosition, std::wstring idFigure, int side, bool invulnerable, bool important, std::vector<PropertiesFigure> vectorPromoution /* нет проверки (!) */)
{

	if (locationClassFigure.size() <= yPosition || locationClassFigure[yPosition].size() <= xPosition)
	{
		OutputLog("ERROR -> Class -> FigureLocation -> SetFigure -> попытка установить ЗА границу");
		return false;		
	}

	if (locationClassFigure[yPosition][xPosition]->getSide() == -1)
	{
		OutputLog("ERROR -> Class -> FigureLocation -> SetFigure -> попытка установить НА границу");
		return false;
	}




	for (int it = 0; it < uniqueFigureLocationClassFigure.size(); it++)
	{
		///
		/// находим итератор указанной финугы
		/// 
		if (   uniqueFigureLocationClassFigure[it]->getSide()          == side
			&& uniqueFigureLocationClassFigure[it]->getIdFigure()      == idFigure
			&& uniqueFigureLocationClassFigure[it]->getInvulnerable()  == invulnerable
			&& uniqueFigureLocationClassFigure[it]->getImportant()     == important
		   )
		{
			///
			/// станавливаем текстуру фигуры на поле
			/// 
			locationTexture[yPosition][xPosition] = uniqueFigureLocationTexture[it];

			///
			/// устанавливаем позицию и размер фигуры -> меньше чем пустая клетка или край
			///
			locationRectangleShape[yPosition][xPosition].setSize(sf::Vector2f(sizeCell * precentSizeFigure, sizeCell * precentSizeFigure));
			locationRectangleShape[yPosition][xPosition].setPosition(sf::Vector2f(xPosition * sizeCell + positionRectangInCell, yPosition * sizeCell + positionRectangInCell));

			///
			/// передаем установленную текстуру
			/// 
			locationRectangleShape[yPosition][xPosition].setTexture(locationTexture[yPosition][xPosition].get(), true);

			///
			/// ставим класс фигуры на поле
			/// 
			locationClassFigure[yPosition][xPosition] = uniqueFigureLocationClassFigure[it];

			return true;
		}
	}
	OutputLog("ERROR -> Class -> FigureLocation -> SetFigure -> фигура не найдена, сначала ее необходимо добавить -> AddUniqueFigure()");
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool FigureLocation::setFigure(size_t xPosition, size_t yPosition, PropertiesFigure pF)
{
	return setFigure(xPosition, yPosition, pF.idFigure, pF.side, pF.invulnerable, pF.important, {} /* ДОБАВИТЬ vectorPromoution В PropertiesFigure*/);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool FigureLocation::setFigureVector(const std::vector<PositionAndPropertiesFigure>& locationFigure)
{
	bool result = true;

	for (const auto& currentFigure : locationFigure)
	{		
		if (!setFigure( currentFigure.xPosition,
			            currentFigure.yPosition,
			            currentFigure.propertions.idFigure,
			            currentFigure.propertions.side,
			            currentFigure.propertions.invulnerable,
			            currentFigure.propertions.important,
			            currentFigure.vectorPromoution
		              )
		   )
		{
			std::wstring ws = currentFigure.propertions.idFigure;			
			OutputLog("ERROR -> Class -> FigureLocation -> setFigureVector -> фигура не размещена или размещена с ошибкой координат: \t" + std::string(ws.begin(), ws.end()) + "\t" + std::to_string(currentFigure.xPosition) + " " + std::to_string(currentFigure.yPosition));

			result = false;
		}
		
	}

	return result;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool FigureLocation::PromoutionSelectFigure(int side, std::wstring idFigure, bool invulnerable, bool important, bool promoution)
{

	///
	/// фигура может превратиться в указанную фигуру???.........
	/// 
	if (locationClassFigure[positionSelectFigure.second][positionSelectFigure.first]->getPromoutionFigure(side, idFigure, invulnerable, important, promoution))
	{
		for (int it = 0; it < uniqueFigureLocationClassFigure.size(); it++)
		{
			if ( uniqueFigureLocationClassFigure[it]->getIdFigure() == idFigure && 
				 uniqueFigureLocationClassFigure[it]->getSide() == locationClassFigure[positionSelectFigure.second][positionSelectFigure.first]->getSide()
			   )
			{
				///
				/// заменяем текстуру
				/// 
				locationTexture[positionSelectFigure.second][positionSelectFigure.first] = uniqueFigureLocationTexture[it];

				///
				/// передаем установленную текстуру
				/// 
				locationRectangleShape[positionSelectFigure.second][positionSelectFigure.first].setTexture(locationTexture[positionSelectFigure.second][positionSelectFigure.first].get(), true);

				///
				/// ставим класс фигуры на поле
				/// 
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool FigureLocation::PromoutionSelectFigure(PropertiesFigure pF)
{
	return PromoutionSelectFigure(pF.side, pF.idFigure, pF.invulnerable, pF.important, pF.promoution);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////











bool FigureLocation::addUniqueFigure(std::shared_ptr<Figure> newFigureOrHeirs, std::filesystem::path currentTextureFigure)
{

	///
	/// изначально считаем что фигура уникальная 
	/// проверяем есть ли такие фигуры у нас еще?
	/// начинаем с 2 т.к. 0 и 1 слоты заняты заранее "краем" и пустой фигурой (видимой как пустая клетка) соответственно
	/// 
	size_t Size = uniqueFigureLocationClassFigure.size();





	for (int it = 2; it < Size; it++)
	{
		///
		/// если поля совпадают значит не уникальна и не добавляем
		/// 
		if (   uniqueFigureLocationClassFigure[it].get()->getIdFigure()          == newFigureOrHeirs.get()->getIdFigure()
			&& uniqueFigureLocationClassFigure[it].get()->getSide()              == newFigureOrHeirs.get()->getSide()
			&& uniqueFigureLocationClassFigure[it].get()->getInvulnerable()      == newFigureOrHeirs.get()->getInvulnerable()
			&& uniqueFigureLocationClassFigure[it].get()->getImportant()         == newFigureOrHeirs.get()->getImportant()
			&& uniqueFigureLocationClassFigure[it].get()->getVectorPromoution()  == newFigureOrHeirs.get()->getVectorPromoution()
		   )
		{			
			return false;
		}	
	}





	///
	/// иначе, если поля отличаются добавляем
	/// 
	uniqueFigureLocationClassFigure.push_back(newFigureOrHeirs);
	uniqueFigureLocationTexture.push_back(std::make_shared<sf::Texture>(currentTextureFigure));

	for (size_t row = 1; row < countCellOnYPosition - 1; row++)
	{
		for (size_t col = 1; col < countCellOnXPosition - 1; col++)
		{
			///
			/// если клетка пустая то сразу же размещаем никальную фигуру на поле уникальных фигур
			/// 
			if (uniqueFigureLocationRectangleShape[row][col].first == 0)
			{
				size_t latestElement = uniqueFigureLocationTexture.size() - 1;

				///
				/// ставим текстуру
				/// 
				uniqueFigureLocationRectangleShape[row][col].second.setTexture(uniqueFigureLocationTexture[latestElement].get(), true);
				uniqueFigureLocationRectangleShape[row][col].second.setOutlineThickness(-2);
				uniqueFigureLocationRectangleShape[row][col].second.setOutlineColor(sf::Color::Black);

				///
				/// ставим итератор откуда привязали
				/// 
				uniqueFigureLocationRectangleShape[row][col].first = latestElement;
				return true;
			}
		}
	}	


	return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool FigureLocation::addUniqueVectorFigure(std::vector<std::pair<std::shared_ptr<Figure>, std::filesystem::path>> vectorUniqueFigure)
{
	bool result = true;

	for (const auto& [figure, path] : vectorUniqueFigure)
	{
		if (!addUniqueFigure(figure, path))
		{
			std::wstring ws = figure.get()->getIdFigure();
			OutputLog("Error -> Class -> FigureLocation -> addUniqueVectorFigure -> фигура не добавлена:\t" + std::string(ws.begin(), ws.end()));
			result = false;
		}
	}

	return result;
}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




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

	if (locationClassFigure[yPositionMove][xPositionMove]->getSide() == 0)
	{
		swap(locationClassFigure[positionSelectFigure.second][positionSelectFigure.first], locationClassFigure[yPositionMove][xPositionMove]);
		swap(locationTexture[positionSelectFigure.second][positionSelectFigure.first], locationTexture[yPositionMove][xPositionMove]);

		///
		/// изменяем размер и положение
		/// 
		locationRectangleShape[positionSelectFigure.second][positionSelectFigure.first].setSize(sf::Vector2f(sizeCell, sizeCell));
		locationRectangleShape[positionSelectFigure.second][positionSelectFigure.first].setPosition(sf::Vector2f(sizeCell * positionSelectFigure.first, sizeCell * positionSelectFigure.second));

		///
		/// установили тестуры т.к. они свапнуты
		/// 
		locationRectangleShape[positionSelectFigure.second][positionSelectFigure.first].setTexture(locationTexture[positionSelectFigure.second][positionSelectFigure.first].get(), true);

		///
		/// изменяем размер и положение
		/// 
		locationRectangleShape[yPositionMove][xPositionMove].setSize(sf::Vector2f(sizeCell * precentSizeFigure, sizeCell * precentSizeFigure));
		locationRectangleShape[yPositionMove][xPositionMove].setPosition(sf::Vector2f(sizeCell * xPositionMove + positionRectangInCell, sizeCell * yPositionMove + positionRectangInCell));

		///
		/// установили тестуры т.к. они свапнуты
		/// 
		locationRectangleShape[yPositionMove][xPositionMove].setTexture(locationTexture[yPositionMove][xPositionMove].get(), true);

		return true;
	}
	else
	{	
		///
		/// если клетка не пустая предполагается что там фигура другого игрока
		/// 

		///
		/// Фигура должна быть доступна для взятия т.е. Invulnerability = false
		/// 		
		if (locationClassFigure[yPositionMove][xPositionMove]->getInvulnerable())
		{
			OutputLog("ERROR -> class -> FigureLocation -> moveSelectFigure() -> фигура неуязвима");
			return false;
		}

		swap(locationClassFigure[positionSelectFigure.second][positionSelectFigure.first], locationClassFigure[yPositionMove][xPositionMove]);
		swap(locationTexture[positionSelectFigure.second][positionSelectFigure.first], locationTexture[yPositionMove][xPositionMove]);

		
		locationRectangleShape[yPositionMove][xPositionMove].setSize(sf::Vector2f(sizeCell * precentSizeFigure, sizeCell * precentSizeFigure));
		locationRectangleShape[yPositionMove][xPositionMove].setPosition(sf::Vector2f(sizeCell * xPositionMove + positionRectangInCell, sizeCell * yPositionMove + positionRectangInCell));
		

		locationRectangleShape[yPositionMove][xPositionMove].setTexture(locationTexture[yPositionMove][xPositionMove].get(), true);
		

		///
		/// 1 - пустая текстура		
		/// 
		locationTexture[positionSelectFigure.second][positionSelectFigure.first] = uniqueFigureLocationTexture[1];

		///
		/// 1 - пустая фигура (клетка)
		/// 
		locationClassFigure[positionSelectFigure.second][positionSelectFigure.first] = uniqueFigureLocationClassFigure[1]; 
		
		locationRectangleShape[positionSelectFigure.second][positionSelectFigure.first].setSize(sf::Vector2f(sizeCell, sizeCell));
		locationRectangleShape[positionSelectFigure.second][positionSelectFigure.first].setPosition(sf::Vector2f(sizeCell * positionSelectFigure.first, sizeCell * positionSelectFigure.second));
		
		locationRectangleShape[positionSelectFigure.second][positionSelectFigure.first].setTexture(locationTexture[positionSelectFigure.second][positionSelectFigure.first].get(), true);

		return true;
	}

	return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////












//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


std::pair<size_t, size_t> FigureLocation::getPositionFigureWhenMousePressed(sf::Vector2f positonMouse)  const
{
	for (size_t yPosition = 0; yPosition < countCellOnXPosition; yPosition++)
	{
		for (size_t xPosition = 0; xPosition < countCellOnXPosition; xPosition++)
		{
			// если задели фигуру на игровом поле
			if (locationRectangleShape[yPosition][xPosition].getGlobalBounds().contains(positonMouse))
			{
				return { xPosition, yPosition };
			}
		}
	}
	return { 0, 0 };
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////













//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool FigureLocation::seletcFigure(size_t xPositionFigure, size_t yPositionFigure)
{
	int sideFigure = locationClassFigure[yPositionFigure][xPositionFigure]->getSide();

	if (sideFigure == 0 || sideFigure == -1)
	{
		return false;
	}
	if (selectFigure)
	{
		unseletcAllFigure();
	}

	locationRectangleShape[yPositionFigure][xPositionFigure].setOutlineThickness(-3);
	locationRectangleShape[yPositionFigure][xPositionFigure].setOutlineColor(sf::Color::Red);

	positionSelectFigure = { static_cast<int>(xPositionFigure), static_cast<int>(yPositionFigure) };
	selectFigure = true;

	return selectFigure;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



bool FigureLocation::unseletcAllFigure()
{
	for (size_t yPosition = 0; yPosition < countCellOnXPosition; yPosition++)
	{
		for (size_t xPosition = 0; xPosition < countCellOnXPosition; xPosition++)
		{
			locationRectangleShape[yPosition][xPosition].setOutlineThickness(0);
		}
	}
	positionSelectFigure = std::make_pair(0, 0);
	selectFigure = false;

	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool FigureLocation::figuresSelectedOrNot() const noexcept
{
	return selectFigure;
}






std::pair<size_t, size_t> FigureLocation::getPositionSelectFigure() const
{
	return positionSelectFigure;
}





std::vector<std::pair<size_t, size_t>> FigureLocation::getAvailableMovesForFigure(size_t xPositionFigure, size_t yPositionFigure)
{
	return locationClassFigure[yPositionFigure][xPositionFigure]->getMoveForFigure(xPositionFigure, yPositionFigure, getVectorLocationFigure());
}





bool FigureLocation::promoutionFigureOnPosition(size_t xPositionFigure, size_t yPositionFigure)
{
	return locationClassFigure[yPositionFigure][xPositionFigure]->getPossibilityPromotion(xPositionFigure, yPositionFigure, getVectorLocationFigure());
}




GridPropertiesFigure  FigureLocation::getVectorLocationFigure()
{
	updateVectorLocationFigure();
	return vectorLocationFigure;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void FigureLocation::updateVectorLocationFigure()
{
	for (size_t yPosition = 0; yPosition < countCellOnXPosition; yPosition++)
	{
		for (size_t xPosition = 0; xPosition < countCellOnXPosition; xPosition++)
		{
			vectorLocationFigure[yPosition][xPosition].side         = locationClassFigure[yPosition][xPosition]->getSide();
			vectorLocationFigure[yPosition][xPosition].idFigure     = locationClassFigure[yPosition][xPosition]->getIdFigure();
			vectorLocationFigure[yPosition][xPosition].invulnerable = locationClassFigure[yPosition][xPosition]->getInvulnerable();
			vectorLocationFigure[yPosition][xPosition].important    = locationClassFigure[yPosition][xPosition]->getImportant();
			vectorLocationFigure[yPosition][xPosition].promoution   = locationClassFigure[yPosition][xPosition]->getPromoution();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



std::wstring FigureLocation::getIdFigure(size_t xPosition, size_t yPosition) const
{
	return locationClassFigure[yPosition][xPosition]->getIdFigure();
}



int FigureLocation::getSideFigure(size_t xPosition, size_t yPosition) const
{
	return locationClassFigure[yPosition][xPosition]->getSide();
}



const sf::RectangleShape& FigureLocation::getRectangleShapeFigure(size_t xPosition, size_t yPosition) const
{
	return locationRectangleShape[yPosition][xPosition];
}



bool FigureLocation::getInvulnerableFigure(size_t xPosition, size_t yPosition) const
{
	return locationClassFigure[yPosition][xPosition]->getInvulnerable();
}



bool FigureLocation::getImportantFigure(size_t xPosition, size_t yPosition) const
{
	return locationClassFigure[yPosition][xPosition]->getImportant();
}


PropertiesFigure FigureLocation::getPropertiesFigure(size_t xPosition, size_t yPosition)
{	
	
	return { getSideFigure(xPosition, yPosition),
			 getIdFigure(xPosition, yPosition),
			 getInvulnerableFigure(xPosition, yPosition),
			 getImportantFigure(xPosition, yPosition),
			 getUniquePromoutionFigure(xPosition, yPosition)
		   };
}

































//--//--//--//--//--//--//--//--//--//      ДЛЯ ПОЛЕ УНИКАЛЬНЫХ ФИГУР     //--//--//--//--//--//--//--//--//--//--//--//-//

bool FigureLocation::getUniqueInvulnerableFigure(size_t xPosition, size_t yPosition)
{
	size_t it = getIteratorUniqueFigure(xPosition, yPosition);
	return uniqueFigureLocationClassFigure[it]->getInvulnerable();
}



std::wstring FigureLocation::getUniqueIdFigure(size_t xPosition, size_t yPosition)
{
	size_t it = getIteratorUniqueFigure(xPosition, yPosition);
	return uniqueFigureLocationClassFigure[it]->getIdFigure();
}



int FigureLocation::getUniqueSideFigure(size_t xPosition, size_t yPosition)
{
	size_t it = getIteratorUniqueFigure(xPosition, yPosition);
	return uniqueFigureLocationClassFigure[it]->getSide();
}



bool FigureLocation::getUniqueImportantFigure(size_t xPosition, size_t yPosition)
{
	size_t it = getIteratorUniqueFigure(xPosition, yPosition);
	return uniqueFigureLocationClassFigure[it]->getImportant();
}



bool FigureLocation::getUniquePromoutionFigure(size_t xPosition, size_t yPosition)
{
	size_t it = getIteratorUniqueFigure(xPosition, yPosition);
	return uniqueFigureLocationClassFigure[it]->getPromoution();
}



const sf::RectangleShape& FigureLocation::getUniqueRectangleShapeFigure(size_t xPosition, size_t yPosition)
{
	return uniqueFigureLocationRectangleShape[yPosition][xPosition].second;
}




size_t FigureLocation::getIteratorUniqueFigure(size_t xPosition, size_t yPosition)
{
	return uniqueFigureLocationRectangleShape[yPosition][xPosition].first;
}




size_t FigureLocation::getIteratorUniqueFigure(PropertiesFigure otherFigure)
{
	for (size_t it = 0; it < uniqueFigureLocationClassFigure.size(); it++)
	{
		///
		/// если находим такую фигуру то возвращаем итератор
		/// 
		if (   uniqueFigureLocationClassFigure[it]->getIdFigure()      == otherFigure.idFigure
			&& uniqueFigureLocationClassFigure[it]->getSide()          == otherFigure.side
			&& uniqueFigureLocationClassFigure[it]->getInvulnerable()  == otherFigure.invulnerable
			&& uniqueFigureLocationClassFigure[it]->getImportant()     == otherFigure.important
			&& uniqueFigureLocationClassFigure[it]->getPromoution()    == otherFigure.promoution
			)
		{
			return it;
		}
	}
	return -1;
}



//bool FigureLocation::checkMoveForFigure(size_t xPositionCurrent, size_t yPositionCurrent, size_t xPositionMove, size_t yPositionMove, const GridPropertiesFigure& vectorLocationFigure)
//{
//	return false;
//}



bool FigureLocation::seletcUniqueFigureForPromoution(size_t xPositionFigure, size_t yPositionFigure)
{
	///
	/// выделяем фигуры в которые может превратиться фигура
	/// 

	///
	/// получаем сторону текущего игрока
	/// 
	int sideFigure = locationClassFigure[yPositionFigure][xPositionFigure]->getSide();

	for ( auto& vectorRectangleShape : uniqueFigureLocationRectangleShape)
	{
		for ( auto& rectangleShape : vectorRectangleShape)
		{
			size_t it = rectangleShape.first;

			///
			/// если фигура той же стороны
			/// 
			if (uniqueFigureLocationClassFigure[it]->getSide() == sideFigure)
			{
				///
				/// и может превратиться в указанную фигуру???... 
				/// 
				if (locationClassFigure[yPositionFigure][xPositionFigure]->getPromoutionFigure( uniqueFigureLocationClassFigure[it]->getSide(),
					                                                                            uniqueFigureLocationClassFigure[it]->getIdFigure(),
					                                                                            uniqueFigureLocationClassFigure[it]->getInvulnerable(),
					                                                                            uniqueFigureLocationClassFigure[it]->getImportant(),
																							    uniqueFigureLocationClassFigure[it]->getPromoution()
																							  )
				   )
				{
					///
					/// подсвечиваем фигуру
					/// 
					rectangleShape.second.setOutlineColor(sf::Color::Red);
				}
			}
		}
	}
	return true;
}


bool FigureLocation::unseletcUniqueFigure()
{
	for (auto& vectorRectangleShape : uniqueFigureLocationRectangleShape)
	{
		for (auto& rectangleShape : vectorRectangleShape)
		{
			rectangleShape.second.setOutlineColor(sf::Color::Black);
		}
	}
	return true;
}


std::pair<int, int> FigureLocation::getUniquePositionFigureWhenMousePressed(sf::Vector2f positonMouse)
{
	for (size_t yPosition = 0; yPosition < countCellOnYPosition; yPosition++)
	{
		for (size_t xPosition = 0; xPosition < countCellOnXPosition; xPosition++)
		{
			///
			/// если задели фигуру на поле уникальных фигур возвращаем позицию в минусе
			/// 
			if (uniqueFigureLocationRectangleShape[yPosition][xPosition].second.getGlobalBounds().contains(positonMouse))
			{
				return { static_cast<int>(xPosition), static_cast<int>(yPosition) };
			}
		}
	}
	return { 0, 0 };
}











std::vector<std::pair<size_t, size_t>> FigureLocation::checkThreatFigure( size_t xPositionOnVectorLocationFigure, 
																		  size_t yPositionOnVectorLocationFigure, 
																		  const  GridPropertiesFigure& vectorLocationFigure
																		)
{
	std::vector<std::pair<size_t, size_t>> resultPositionEnemyFigure;


	///
	/// получаем сторону текущего игрока, у которого будет проверяться фигура
	/// 
	int  sideCurrentFigure;

	sideCurrentFigure = vectorLocationFigure[yPositionOnVectorLocationFigure][xPositionOnVectorLocationFigure].side;
	
	///
	/// проверяем все фигуры на переданном игровом поле у других игроков, которые могу "угрожать взятием"
	/// 
	for (size_t Ypos = 0; Ypos < countCellOnYPosition; Ypos++)
	{
		for (size_t Xpos = 0; Xpos < countCellOnXPosition; Xpos++)
		{

			///
			/// если у фигуры на позиции другая сторона, то проверяем далее....
			/// 
			if (    vectorLocationFigure[Ypos][Xpos].side != sideCurrentFigure	
				 && vectorLocationFigure[Ypos][Xpos].side != -1                    // не учитываем край 
				 && vectorLocationFigure[Ypos][Xpos].side != 0	                  // не учитываем пустые клетки (фигуры)
			   )
			{
				
				size_t it = getIteratorUniqueFigure({vectorLocationFigure[Ypos][Xpos].side,
												     vectorLocationFigure[Ypos][Xpos].idFigure,
												     vectorLocationFigure[Ypos][Xpos].invulnerable,
												     vectorLocationFigure[Ypos][Xpos].important,
												     vectorLocationFigure[Ypos][Xpos].promoution
												   });

				///
				/// получаем ходы на которые может сходить фигура
				/// 
				auto moveForFigure = uniqueFigureLocationClassFigure[it]->getMoveForFigure(Xpos, Ypos, vectorLocationFigure);


				///
				/// если фигура может сходить на позицию проверяемой фигуры ("угрожать взятием"), то добавляем эту фигуру в вектор, она угрожает
				/// 
				for (const auto& Move : moveForFigure)
				{
					if (Move.first == xPositionOnVectorLocationFigure && Move.second == yPositionOnVectorLocationFigure)
					{
						resultPositionEnemyFigure.emplace_back(Xpos, Ypos);
					}
				}
			}
		}
	}	
	return resultPositionEnemyFigure;
}











std::vector<std::pair<size_t, size_t>> FigureLocation::getPositionFigure(int side, std::wstring idFigure, bool invulnerable, bool important, bool promoution) 
{
	return positionFigure(side, idFigure, invulnerable, important, promoution);
}



std::vector<std::pair<size_t, size_t>> FigureLocation::getPositionFigure(int side, std::wstring idFigure)  
{
	return positionFigure(side, idFigure, numException, numException, numException);
}



std::vector<std::pair<size_t, size_t>> FigureLocation::getPositionFigure(int side) 
{
	return positionFigure(side, wsExceprion, numException, numException, numException);
}



std::vector<std::pair<size_t, size_t>> FigureLocation::getPositionsFigure(int side, bool invulnerableOrImportantOrPromoution , char IMP ) 
{
	switch (IMP)
	{
	case 'I':
		return positionFigure(side, wsExceprion, invulnerableOrImportantOrPromoution, numException, numException);

	case 'M':
		return positionFigure(side, wsExceprion, numException, invulnerableOrImportantOrPromoution, numException);

	case 'P':
		return positionFigure(side, wsExceprion, numException, numException, invulnerableOrImportantOrPromoution);

	default:
		return std::vector<std::pair<size_t, size_t>>();
	}	
}






std::vector<std::pair<size_t, size_t>> FigureLocation::positionFigure(int side, std::wstring idFigure, int invulnerable, int important, int promoution)
{
	std::vector<std::pair<size_t, size_t>> position;

	for (size_t yPos = 0; yPos < countCellOnYPosition; yPos++)
	{
		for (size_t xPos = 0; xPos < countCellOnXPosition; xPos++)
		{
			///
			/// если поля совпадают то добавляем
			/// 

			///
			/// если передан параметр numException значение не учитывается, так же и wsExceprion 
			/// 
			if (    (  idFigure     == wsExceprion  || ( locationClassFigure[yPos][xPos]->getIdFigure()                       == idFigure     && idFigure != wsExceprion) )
				 && (  side         == numException || ( static_cast<int>(locationClassFigure[yPos][xPos]->getSide())         == side         && side != numException   ) )
				 && (  invulnerable == numException || ( static_cast<int>(locationClassFigure[yPos][xPos]->getInvulnerable()) == invulnerable && side != numException   ) )
				 && (  important    == numException || ( static_cast<int>(locationClassFigure[yPos][xPos]->getImportant())    == important    && side != numException   ) )
				 && (  promoution   == numException || ( static_cast<int>(locationClassFigure[yPos][xPos]->getPromoution())   == promoution   && side != numException   ) )
			   )
			{
				position.emplace_back(xPos, yPos);
			}
		}
	}
	return position;
}



bool FigureLocation::checkmateForFigure(size_t xPosition, size_t yPosition, const GridPropertiesFigure& vectorLocationFigure)
{
	auto tempResult = figureCanProtectenCheckmateForFigure(xPosition, yPosition, vectorLocationFigure);

	if (tempResult.size() == 1 && tempResult[0].first == NULL && tempResult[0].second == NULL)
	{
		return true;
	}

	return false;
}




std::vector<std::pair<size_t, size_t>> FigureLocation::figureCanProtectenCheckmateForFigure(size_t xPosition, size_t yPosition, const GridPropertiesFigure& vectorLocationFigure)
{
	
	int current_SIDE = locationClassFigure[yPosition][xPosition]->getSide();

	///
	/// позиции фигур которые могут защитить
	/// 
	std::vector<std::pair<size_t, size_t>> resultPositionFigure;


	///
	/// край и пустую клетку не проверяем, нет смысла
	/// 
	if (current_SIDE == 0 || current_SIDE == -1)
	{
		// возвращаем пустой ничего не угрожает
		return std::vector<std::pair<size_t, size_t>>();
	}

	///
	/// получаем расположение фигур на игровом поле, которые урожают этой фигуре
	/// 
	auto locationThreatFigure = checkThreatFigure(xPosition, yPosition, vectorLocationFigure);

	///
	/// если фигур, которые угрожают == 0, то логично, что ничего ему не угрожает
	/// 
	if (locationThreatFigure.empty())
	{
		///
		/// возвращаем пустой ничего не угрожает
		/// 
		return std::vector<std::pair<size_t, size_t>>();
	}

	///
	/// позиции всех фигур текущего игрока Х / У
	/// 
	auto positionAllFigureForPlayer = getPositionFigure(current_SIDE);




	///
	/// проверяем может ли какая-то фигура текущего игрока куда-то передвинуться, чтобы исключить шах 
	/// проходимся по каждой фигуре 
	///
	
	///
	/// позиция фигуры  Х / У
	/// 
	for (const auto& curentPosFigure : positionAllFigureForPlayer)
	{
		///
		/// получаем доступные ходы для текущей фигуры
		/// 
		auto moveForFigure = locationClassFigure[curentPosFigure.second][curentPosFigure.first]->getMoveForFigure(curentPosFigure.first, curentPosFigure.second, vectorLocationFigure);

		///
		/// проходимся по всему вектору ходов
		///
		for (const auto& move : moveForFigure)
		{
			///
			/// создаем фиктивное расположение фигур
			/// 
			GridPropertiesFigure imaginaryLocation = vectorLocationFigure;
			
			///
			/// создаем фиктивный ход 
			/// свапаем "передвигая" фигуру
			/// 
			PropertiesFigure tempPropertiesFigure = imaginaryLocation[curentPosFigure.second][curentPosFigure.first];
			imaginaryLocation[curentPosFigure.second][curentPosFigure.first] = imaginaryLocation[move.second][move.first];
			imaginaryLocation[move.second][move.first] = tempPropertiesFigure;

			//swap(imaginaryLocation[curentPosFigure.second][curentPosFigure.first], imaginaryLocation[move.second][move.first]);



			///
			/// устанавливаем пустую фигуру (клетку) на бывшую позицию 
			/// 
			imaginaryLocation[curentPosFigure.second][curentPosFigure.first] = { 0, L"Figure", false, false, false };




			///
			/// начальная позиция проверяемой фигуры х \ у
			///
			std::pair <size_t, size_t> currentPositionCheckedFigure = std::make_pair(xPosition, yPosition);


			///
			/// если мы дошли до проверки ходов у изначально проверяемой фигуры
			/// 
			if (currentPositionCheckedFigure == curentPosFigure)
			{
				///
				/// устанавливаем новое фиктивное положение для ПРОВЕРЯЕМОЙ фигуры
				/// 
				currentPositionCheckedFigure = move;
			}

		
			///
			/// проверяем угрозу с фиктивным расположением
			/// 
			auto thFigure = checkThreatFigure(currentPositionCheckedFigure.first, currentPositionCheckedFigure.second, imaginaryLocation);
		

			///
			/// считаем колличество фигур которые могут угрожать на этом ходу
			/// если колличество угрожающих фигур == 0, то мата нет, фигура может закрыть важную фигуру или убить своим ходом
			/// 
			if (thFigure.size() == 0)
			{
				resultPositionFigure.emplace_back(curentPosFigure.first, curentPosFigure.second);
			}
			
		}
		
	}

	///
	/// возвращаем 0,0 позицию, если угрозу не избежать // пустой если угроз не найдено // или заполенный фигурами, которые могут задефать
	/// 
	return resultPositionFigure.empty() ? std::vector<std::pair<size_t, size_t>>(1, { 0, 0 } ) : resultPositionFigure;
}
