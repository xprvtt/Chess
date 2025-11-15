#include "GameEngine.h"




GameEngine::GameEngine(std::unique_ptr<sf::RenderWindow> rW, std::unique_ptr < FigureLocation> pL, std::unique_ptr < GameField> gF) : rWindow(std::move(rW)), location(std::move(pL)), gameField(std::move(gF))
{
    textInGameRow1 = std::make_shared<sf::Text>(propertiesGame::currentFont);
	textInGameRow2 = std::make_shared<sf::Text>(propertiesGame::currentFont);
	textInGameRow3 = std::make_shared<sf::Text>(propertiesGame::currentFont);
	textInGameRow4 = std::make_shared<sf::Text>(propertiesGame::currentFont);

    ///
    /// текст расположенный в первом ряду
    /// 
    textInGameRow1.get()->setString(L"-");
    textInGameRow1.get()->setCharacterSize(static_cast<unsigned int>(propertiesGame::sizeWindowHeight / (propertiesGame::countCellOnLengthWindow * 3)));
    textInGameRow1.get()->setFillColor(sf::Color::Black);
    textInGameRow1.get()->setPosition(sf::Vector2f(static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow / 2 + propertiesGame::sizeWindowHeight), static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow)));
    
    ///
    /// текст расположенный во втором ряду
    /// 
    textInGameRow2.get()->setString(L"-");
    textInGameRow2.get()->setCharacterSize(static_cast<unsigned int>(propertiesGame::sizeWindowHeight / (propertiesGame::countCellOnLengthWindow * 3)));
    textInGameRow2.get()->setFillColor(sf::Color::Black);
    textInGameRow2.get()->setPosition(sf::Vector2f(static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow / 2 + propertiesGame::sizeWindowHeight), static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow * 2)));

    ///
    /// текст расположенный в 3 ряду
    /// 
    textInGameRow3.get()->setString(L"-");
    textInGameRow3.get()->setCharacterSize(static_cast<unsigned int>(propertiesGame::sizeWindowHeight / (propertiesGame::countCellOnLengthWindow * 3)));
    textInGameRow3.get()->setFillColor(sf::Color::Black);
    textInGameRow3.get()->setPosition(sf::Vector2f(static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow / 2 + propertiesGame::sizeWindowHeight), static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow * 3)));

    ///
    /// текст расположенный в 4 ряду
    /// 
    textInGameRow4.get()->setString(L"-");
    textInGameRow4.get()->setCharacterSize(static_cast<unsigned int>(propertiesGame::sizeWindowHeight / (propertiesGame::countCellOnLengthWindow * 3)));
    textInGameRow4.get()->setFillColor(sf::Color::Black);
    textInGameRow4.get()->setPosition(sf::Vector2f(static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow / 2 + propertiesGame::sizeWindowHeight), static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow * 4)));

}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



bool GameEngine::performBacklightThreat()
{
    ///
    /// получаем расположение важных ФИГУР текущего игрока ( "король" - могут быть и другие) 
    /// 
    positionImportantFigure = location.get()->getPositionsFigure(currentPlayer, true, 'M');

    ///
    /// получаем копию расположения фигур 
    /// 
    GridPropertiesFigure locationFigureInGame = location.get()->getVectorLocationFigure();

    ///
    /// стандартно существует единственый экземпляр ВАЖНЫХ ФИГУРЫ - король, на каждой стороне, но может быть и несколько -> проводим цикл
    /// так же королей может не быть и в цикл не входим т.к. вектор будет пустой
    /// 
    
    if (!positionImportantFigure.empty())
    {

        for (const auto& currentPosition : positionImportantFigure)
        {
            ///
            /// => далее необходимо получить позиции фигур противников, которые могут угрожать королю, и выделяем их клетки в GameField
            /// можно сделать аналогичные проверки для любых фигур
            /// 
            
            ///
            /// получаем позиции фигур противников, которые "угрожают" текущей важной фигуре взятием
            /// 
            positionEnemyFigureThatThreaten = location.get()->checkThreatFigure(currentPosition.first, currentPosition.second, locationFigureInGame);




            for (const auto& cPosition : positionEnemyFigureThatThreaten)
            {
                // выделяем клетки на которых стоят эти фигуры
                gameField.get()->selectCell(cPosition.first, cPosition.second, sf::Color::Red);
                gameField.get()->selectCell(currentPosition.first, currentPosition.second, sf::Color::Red);
                setText3(L"поставлен шах");
            }







            ///
            /// получаем позиции фигур которые могут защитить указанную
            /// 
            auto positionFrendlyFigure = location.get()->figureCanProtectenCheckmateForFigure(currentPosition.first, currentPosition.second, locationFigureInGame);

            for (const auto& currentPos : positionFrendlyFigure)
            {
                ///
                /// выделяем их
                /// 
                gameField.get()->selectCell(currentPos.first, currentPos.second, sf::Color::Green);
            }









            if (positionFrendlyFigure.size() == 1 && positionFrendlyFigure[0] == std::pair(size_t(0), size_t(0)))
            {
                setText4(L"поставлен мат игроку: " + std::to_wstring(currentPlayer));
            }
        }
    }

    return true;;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void GameEngine::performMovePlayer()
{

    currentPositionInGameField = getFigureOnPositionMouse();





    /////////  ВРЕМЕННОЕ   //////////////////////
    ///
    /// выводим информацию о фигуре
    textInGameRow1.get()->setString(
        location.get()->getIdFigure(currentPositionInGameField.first, currentPositionInGameField.second) + L"\t"
        + L"X:" + std::to_wstring(currentPositionInGameField.first) 
        + L" \\ Y:" + std::to_wstring(currentPositionInGameField.second)
        + L"\tSIDE: " + std::to_wstring(location.get()->getSideFigure(currentPositionInGameField.first, currentPositionInGameField.second))
        + L"\nInvulnerable:\t" + std::to_wstring(location.get()->getInvulnerableFigure(currentPositionInGameField.first, currentPositionInGameField.second))
        + L"\nImportant:\t\t" + std::to_wstring(location.get()->getImportantFigure(currentPositionInGameField.first, currentPositionInGameField.second))
    );
    ///
    /////////////////////////////////////////////






    ///
    /// сторона у выбранной фигуры
    /// 
    int side = location.get()->getSideFigure(currentPositionInGameField.first, currentPositionInGameField.second);



    ///
    /// выделяем ее или снимаем выделение, если выделено то ожидается передвижение фигуры
    /// так же должна совпадать сторона игрока который сейчас ходит, для выделения
    /// 
    if (!location.get()->figuresSelectedOrNot() && side == currentPlayer)
    {
        ///
        /// выделяем выбранную фигуру
        /// 
        location.get()->seletcFigure(currentPositionInGameField.first, currentPositionInGameField.second);

        ///
        /// получаем вектор доступных ходов
        /// 
        auto positionSelectFigure = location.get()->getPositionSelectFigure();

        selectCellForMove = location.get()->getAvailableMovesForFigure(positionSelectFigure.first, positionSelectFigure.second);

        ///
        /// выделяем доступные ходы на доске
        /// 
        for (const auto& onePos : selectCellForMove)
        {
            gameField.get()->selectCell(onePos.first, onePos.second, sf::Color::Red);
        }





    }
    else if (location.get()->figuresSelectedOrNot())
    {
        ///
        /// создаем копию свойств фигуры на случай если ход выполнен в угрозу своим важным фигурам
        /// 
        PropertiesFigure tempOldPF = location.get()->getPropertiesFigure(currentPositionInGameField.first, currentPositionInGameField.second);

        ///
        /// двигаем фигуру на выбранные координаты если возможно
        /// 
        if (location.get()->moveSelectFigure(currentPositionInGameField.first, currentPositionInGameField.second))
        {
            needCheckThreat = true;


            ///
            /// передвинули
            /// если угроза нашлась - откатываем и не передаем ход
            /// 
            if (isThreat())
            {
                setText3(L"на эти координаты нельзя\nпередвинуть фигуру");

                auto tempPositionOld = location.get()->getPositionSelectFigure();

                location.get()->setFigure( tempPositionOld.first, tempPositionOld.second, location.get()->getPropertiesFigure(currentPositionInGameField.first, currentPositionInGameField.second) );

                location.get()->setFigure(currentPositionInGameField.first, currentPositionInGameField.second, tempOldPF  );

                location.get()->unseletcAllFigure();
            }
            else
            {
                ///
                /// если передвинули и угроз нет проверяем может ли фигура превратиться в другую
                /// 
                if (location.get()->promoutionFigureOnPosition(currentPositionInGameField.first, currentPositionInGameField.second))
                {
                    oldPosition = currentPositionInGameField;

                    location.get()->seletcFigure(currentPositionInGameField.first, currentPositionInGameField.second);
                    location.get()->seletcUniqueFigureForPromoution(currentPositionInGameField.first, currentPositionInGameField.second);

                    setPromoution(true);
                }
                ///
                /// если не может превратиться снимаем выделение
                /// 
                else
                {
                    location.get()->unseletcAllFigure();
                }



                ///
                /// передаем ход следующему игроку
                /// 
                nextPlayer();
                setThreat(false);
                setText3(L" ");

                needCheckThreat = true;
            }





        }
        else
        {
            location.get()->unseletcAllFigure();
        }
        gameField.get()->unselectAllCell();
    }


    if (promoution())
    {
        setText3(L"Превращение доступно");
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




bool GameEngine::checkThreat()
{
    bool result = false;

    ///
    /// получаем расположение ВАЖНЫХ ФИГУР ( "король" - могут быть и другие) текущего игрока
    /// 
    positionImportantFigure = location.get()->getPositionsFigure(currentPlayer, true, 'M');

    if (!positionImportantFigure.empty())
    {
        for (int countPosition = 0; countPosition < positionImportantFigure.size(); countPosition++)
        {
            ///
            /// получаем позиции фигур противников которые "угрожают" важной фигуре взятием
            /// 
            positionEnemyFigureThatThreaten = location.get()->checkThreatFigure(positionImportantFigure[countPosition].first, positionImportantFigure[countPosition].second, location.get()->getVectorLocationFigure());


            ///
            /// если вектор не пуст значит угрозы есть
            /// 
            if (!positionEnemyFigureThatThreaten.empty())
            {
                result = true;
            }
        }
    }

    return result;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void GameEngine::performPromouten()
{

    currentPositionInUniqueFigureField = getUniqueFigureOnPositionMouse();

    /////////////////////////////////////////////////
    ///
    /// ВРЕМЕННОЕ
    ///
    /// выводим информацию о фигуре
    ///
    setText1(location.get()->getIdFigure(currentPositionInUniqueFigureField.first, currentPositionInUniqueFigureField.second) + L"\t"
        + L"X:" + std::to_wstring(currentPositionInUniqueFigureField.first) 
        + L" \\ Y:" + std::to_wstring(currentPositionInUniqueFigureField.second)
        + L"\tSIDE: " + std::to_wstring(location.get()->getSideFigure(currentPositionInUniqueFigureField.first, currentPositionInUniqueFigureField.second))
        + L"\nInvulnerable:\t" + std::to_wstring(location.get()->getInvulnerableFigure(currentPositionInUniqueFigureField.first, currentPositionInUniqueFigureField.second))
        + L"\nImportant:\t\t" + std::to_wstring(location.get()->getImportantFigure(currentPositionInUniqueFigureField.first, currentPositionInUniqueFigureField.second))
    );
    ///
    /////////////////////////////////////////////////




    ///
    /// сторона передвинутой фигуры должно совпадать с выбранной
    ///
    if (location.get()->getSideFigure(oldPosition.first, oldPosition.second) == location.get()->getUniqueSideFigure(currentPositionInUniqueFigureField.first, currentPositionInUniqueFigureField.second))
    {
        if (location.get()->PromoutionSelectFigure( location.get()->getPropertiesFigure(currentPositionInUniqueFigureField.first, currentPositionInUniqueFigureField.second)))
        {
            location.get()->unseletcUniqueFigure();
            location.get()->unseletcAllFigure();

            setPromoution(false);
            setText3(L"превращение выполнено");
        }
        else
        {
            setText3(L"превращение невозможно\nв эту фигуру");
        }
    }
    else
    {
        setText3(L"неверная фигура");
    }


    if (promoution())
    {
        setText3(L"Превращение доступно");
    }



}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



bool GameEngine::isOpen() const
{
    return rWindow.get()->isOpen();
}

sf::Vector2i GameEngine::getPositionMouse() const
{
    return sf::Mouse::getPosition(*rWindow.get());
}

sf::Vector2f GameEngine::getWorldPositionMouse() const
{    
    return rWindow.get()->mapPixelToCoords(getPositionMouse());
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool GameEngine::isThreat()
{
    if (needCheckThreat)
    {
        needCheckThreat = false;
        threat = checkThreat();
    }
    return threat;
}

void GameEngine::setThreat(bool threat)
{
    this->threat = threat;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




std::optional<sf::Event> GameEngine::getEvent()  const
{
    return rWindow.get()->pollEvent();
}

void GameEngine::closeGame()
{
    rWindow.get()->close();
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



std::pair<size_t, size_t> GameEngine::getFigureOnPositionMouse()  const
{
    return location.get()->getPositionFigureWhenMousePressed(getWorldPositionMouse());
}

std::pair<size_t, size_t> GameEngine::getUniqueFigureOnPositionMouse()  const
{
    return location.get()->getUniquePositionFigureWhenMousePressed(getWorldPositionMouse());
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



bool GameEngine::promoution() const noexcept
{
    return needPomoution;
}

void GameEngine::setPromoution(bool needPomoution)
{
    this->needPomoution = needPomoution;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void GameEngine::showCurrnetPlayer() const
{
    std::wstring player = L"\nСейчас ход игрока #" + std::to_wstring(currentPlayer);
    textInGameRow2.get()->setString(player);
}

int GameEngine::getCurrentPlayer() const noexcept
{
    return currentPlayer;
}

void GameEngine::setCurrentPlayer(int currentPlayer)
{
    this->currentPlayer = currentPlayer;
}

void GameEngine::nextPlayer()
{
    currentPlayer < propertiesGame::countPlayer ? currentPlayer++ : currentPlayer = 1;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void GameEngine::setText1(std::wstring message)
{
    textInGameRow1.get()->setString(message);
}
void GameEngine::setText2(std::wstring message)
{
    textInGameRow1.get()->setString(message);
}
void GameEngine::setText3(std::wstring message)
{
    textInGameRow1.get()->setString(message);
}
void GameEngine::setText4(std::wstring message)
{
    textInGameRow1.get()->setString(message);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void GameEngine::drawWindowGame()
{
    showCurrnetPlayer();

    rWindow.get()->draw(*textInGameRow1.get());
    rWindow.get()->draw(*textInGameRow2.get());
    rWindow.get()->draw(*textInGameRow3.get());
    rWindow.get()->draw(*textInGameRow4.get());


    for (size_t row = 0; row < propertiesGame::countCellOnLengthWindow; row++)
    {
        for (size_t coll = 0; coll < propertiesGame::countCellOnLengthWindow; coll++)
        {
            rWindow.get()->draw(gameField.get()->getRectangleShapeOnField(coll, row));
            rWindow.get()->draw(gameField.get()->getFieldCoordinateOnField(coll, row));
            rWindow.get()->draw(location.get()->getRectangleShapeFigure(coll, row));
            rWindow.get()->draw(location.get()->getUniqueRectangleShapeFigure(coll, row));
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void GameEngine::clearWindowGame(sf::Color color)
{
    rWindow.get()->clear(color);
}



void GameEngine::displayWindowGame()
{
    rWindow.get()->display();
}

