#include "GameEngine.h"

GameEngine::GameEngine(std::unique_ptr<sf::RenderWindow> rW, std::unique_ptr < FigureLocation> pL, std::unique_ptr < GameField> gF) : m_ptrRWindow(std::move(rW)), m_ptrLocation(std::move(pL)), m_ptrGameField(std::move(gF))
{
    m_ptrTextInGameRow1 = std::make_shared<sf::Text>(propertiesGame::currentFont);
	m_ptrTextInGameRow2 = std::make_shared<sf::Text>(propertiesGame::currentFont);
	m_ptrTextInGameRow3 = std::make_shared<sf::Text>(propertiesGame::currentFont);
	m_ptrTextInGameRow4 = std::make_shared<sf::Text>(propertiesGame::currentFont);

    // текст расположенный в первом ряду
    m_ptrTextInGameRow1.get()->setString(L"-");
    m_ptrTextInGameRow1.get()->setCharacterSize(static_cast<unsigned int>(propertiesGame::sizeWindowHeight / (propertiesGame::countCellOnLengthWindow * 3)));
    m_ptrTextInGameRow1.get()->setFillColor(sf::Color::Black);
    m_ptrTextInGameRow1.get()->setPosition(sf::Vector2f(static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow / 2 + propertiesGame::sizeWindowHeight), static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow)));
    
    // текст расположенный во втором ряду
    m_ptrTextInGameRow2.get()->setString(L"-");
    m_ptrTextInGameRow2.get()->setCharacterSize(static_cast<unsigned int>(propertiesGame::sizeWindowHeight / (propertiesGame::countCellOnLengthWindow * 3)));
    m_ptrTextInGameRow2.get()->setFillColor(sf::Color::Black);
    m_ptrTextInGameRow2.get()->setPosition(sf::Vector2f(static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow / 2 + propertiesGame::sizeWindowHeight), static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow * 2)));

    // текст расположенный в 3 ряду
    m_ptrTextInGameRow3.get()->setString(L"-");
    m_ptrTextInGameRow3.get()->setCharacterSize(static_cast<unsigned int>(propertiesGame::sizeWindowHeight / (propertiesGame::countCellOnLengthWindow * 3)));
    m_ptrTextInGameRow3.get()->setFillColor(sf::Color::Black);
    m_ptrTextInGameRow3.get()->setPosition(sf::Vector2f(static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow / 2 + propertiesGame::sizeWindowHeight), static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow * 3)));

    // текст расположенный в 4 ряду
    m_ptrTextInGameRow4.get()->setString(L"-");
    m_ptrTextInGameRow4.get()->setCharacterSize(static_cast<unsigned int>(propertiesGame::sizeWindowHeight / (propertiesGame::countCellOnLengthWindow * 3)));
    m_ptrTextInGameRow4.get()->setFillColor(sf::Color::Black);
    m_ptrTextInGameRow4.get()->setPosition(sf::Vector2f(static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow / 2 + propertiesGame::sizeWindowHeight), static_cast<float>(propertiesGame::sizeWindowHeight / propertiesGame::countCellOnLengthWindow * 4)));
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool GameEngine::performBacklightThreat()
{
    const auto locationData = m_ptrLocation.get();

    // получаем расположение важных ФИГУР текущего игрока ( "король" - могут быть и другие) 
    m_allPositionImportantFigures = locationData->getPositionsFigure(m_currentPlayer, true, 'M');

    // получаем копию расположения фигур 
    auto locationFigureInGame = locationData->getLocationFigure();

    // стандартно существует единственый экземпляр ВАЖНЫХ ФИГУРЫ - король, на каждой стороне, но может быть и несколько -> проводим цикл
    // так же королей может не быть и в цикл не входим т.к. вектор будет пустой
    if (!m_allPositionImportantFigures.empty())
    {
		auto gameFieldData = m_ptrGameField.get();

        std::wstring figure;
        for (const auto& currentPosition : m_allPositionImportantFigures)
        {
            // => далее необходимо получить позиции фигур противников, которые могут угрожать королю, и выделяем их клетки в GameField
            // можно сделать аналогичные проверки для любых фигур
            

            // получаем позиции фигур противников, которые "угрожают" текущей важной фигуре взятием
            m_positionEnemyFigureThatThreaten = locationData->checkThreatForFigure(currentPosition, locationFigureInGame);
            for (const auto& enemyPosition : m_positionEnemyFigureThatThreaten)
            {
                // выделяем клетки на которых стоят эти фигуры
                gameFieldData->selectCell(enemyPosition, sf::Color::Red);
                gameFieldData->selectCell(currentPosition, sf::Color::Red);
				const auto& propertiesFigure = locationData->getPropertiesFigure(enemyPosition);
				figure += propertiesFigure.m_idFigure + L"(" + std::to_wstring(currentPosition.inRow) + L"," + std::to_wstring(currentPosition.inColum) + L")";
            }

            // получаем позиции фигур которые могут защитить указанную
            auto positionFrendlyFigure = locationData->getPositionFigureCanProtectedIndicatedFigure(currentPosition, locationFigureInGame);

            for (const auto& currentPos : positionFrendlyFigure)
            {               
                gameFieldData->selectCell(currentPos, sf::Color::Green); // выделяем их
            }

            if (positionFrendlyFigure.size() == 1 && positionFrendlyFigure.back() == Position::Coordinates(0, 0) /* позиция означает что нет доступных ходов*/)
            {
                setTextDebug(L"поставлен мат игроку: " + std::to_wstring(m_currentPlayer));
            }
        }
        if (!figure.empty()) { setText3(L"поставлен шах фигурам: " + figure); }
    }

    return true;;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::performMovePlayer()
{
    m_currentPositionInGameField = getFigureOnPositionMouse();

    auto locationData = m_ptrLocation.get();
    auto gameFieldData = m_ptrGameField.get();

    DEBUG_CODE(
        // выводим информацию о фигуре на клетке ВРЕМЕННОЕ
        m_ptrTextInGameRow1.get()->setString(
            locationData->getIdFigure(m_currentPositionInGameField) + L"\t"
            + L"X:" + std::to_wstring(m_currentPositionInGameField.inRow) 
            + L" \\ Y:" + std::to_wstring(m_currentPositionInGameField.inColum)
            + L"\tSIDE: " + std::to_wstring(locationData->getSideFigure(m_currentPositionInGameField))
            + L"\nInvulnerable:\t" + std::to_wstring(locationData->getInvulnerableFigure(m_currentPositionInGameField))
            + L"\nImportant:\t\t" + std::to_wstring(locationData->getImportantFigure(m_currentPositionInGameField))
        );
    )


    // выделяем ее или снимаем выделение, если выделено то ожидается передвижение фигуры
    // так же должна совпадать сторона игрока который сейчас ходит, для выделения
    if (!locationData->hasSelectedFigure() && locationData->getSideFigure(m_currentPositionInGameField) == m_currentPlayer)
    {
        // выделяем выбранную фигуру
        locationData->seletcFigure(m_currentPositionInGameField);

        // получаем вектор доступных ходов
        auto positionSelectFigure = locationData->getPositionSelectFigure();

        m_selectCellForMove = locationData->getAvailableMovesForFigure(positionSelectFigure);

        // выделяем доступные ходы на доске
        for (const auto& onePos : m_selectCellForMove)
        {
            gameFieldData->selectCell(onePos, sf::Color::Red);
        }
    }
    else if (locationData->hasSelectedFigure())
    {
        // создаем копию свойств фигуры на случай если ход выполнен в угрозу своими важными фигурами
        PropertiesFigure tempOldPF = locationData->getPropertiesFigure(m_currentPositionInGameField);

        // двигаем фигуру на выбранные координаты если возможно
        if (locationData->moveSelectFigure(m_currentPositionInGameField))
        {
            m_needCheckThreat = true;
            if (isThreat()) // если угроза нашлась - откатываем и не передаем ход
            {
                setTextDebug(L"на эти координаты нельзя\nпередвинуть фигуру, есть наобработанные\nугрозы");

                auto tempPositionOld = locationData->getPositionSelectFigure();

                locationData->setFigure(tempPositionOld, locationData->getPropertiesFigure(m_currentPositionInGameField), {});
                locationData->setFigure(m_currentPositionInGameField, tempOldPF, {});
                locationData->unseletcAllFigure();
            }
            else // если передвинули и угроз нет проверяем может ли фигура превратиться в другую
            {                
                if (locationData->isPromoutionFigureOnPosition(m_currentPositionInGameField))
                {
                    m_oldPosition = m_currentPositionInGameField;

                    locationData->seletcFigure(m_currentPositionInGameField);
                    locationData->selectForPromoutionUniqueFigure(m_currentPositionInGameField);

                    setPromoution(true);
                }
                // если не может превратиться снимаем выделение
                else
                {
                    locationData->unseletcAllFigure();
                }
                // передаем ход следующему игроку
                nextPlayer();
                setThreat(false);
                setText3(L" ");

                m_needCheckThreat = true;
            }
        }
        else
        {
            locationData->unseletcAllFigure();
        }
        gameFieldData->unselectAllCell();
    }
    if (promoution())
    {
        setText3(L"Превращение доступно");
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool GameEngine::checkThreat()
{
    // получаем расположение ВАЖНЫХ ФИГУР ( "король" - могут быть и другие) текущего игрока
    m_allPositionImportantFigures = m_ptrLocation.get()->getPositionsFigure(m_currentPlayer, true, 'M');
    m_positionEnemyFigureThatThreaten.clear();

    if (!m_allPositionImportantFigures.empty())
    {
		const auto locationData = m_ptrLocation.get()->getLocationFigure();

        for (auto& posImpFigure : m_allPositionImportantFigures)
        {   
            // получаем позиции фигур противников которые "угрожают" важной фигуре взятием
            const auto enemyPos = m_ptrLocation.get()->checkThreatForFigure(posImpFigure, locationData);
            m_positionEnemyFigureThatThreaten.insert(m_positionEnemyFigureThatThreaten.end(), enemyPos.begin(), enemyPos.end());
        }
    }
    return m_positionEnemyFigureThatThreaten.size();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::performPromouten()
{
    m_currentPositionInUniqueFigureField = getUniqueFigureOnPositionMouse();

	auto locationData = m_ptrLocation.get();
	auto properties = locationData->getPropertiesUniqueFigure(m_currentPositionInUniqueFigureField);

    DEBUG_CODE(
        // выводим информацию о фигуре -- ВРЕМЕННОЕ
        setText1(properties.m_idFigure + L"\t"
            + L"X:" + std::to_wstring(m_currentPositionInUniqueFigureField.inRow) 
            + L" \\ Y:" + std::to_wstring(m_currentPositionInUniqueFigureField.inColum)
            + L"\tSIDE: " + std::to_wstring(properties.m_side)
            + L"\nInvulnerable:\t" + std::to_wstring(properties.m_invulnerable)
            + L"\nImportant:\t\t" + std::to_wstring(properties.m_important)
        );
    )

    // сторона передвинутой фигуры должно совпадать с выбранной
    if (locationData->getSideFigure(m_oldPosition) == properties.m_side)
    {
        if (locationData->promoutionSelectFigure(properties))
        {
            locationData->unselectUniqueFigure();
            locationData->unseletcAllFigure();

            setPromoution(false);
            setTextDebug(L"превращение выполнено");
        }
        else
        {
            setTextDebug(L"превращение невозможно\nв эту фигуру");
			OUTPUT_LOG_ERROR("невозможно превратить фигуру в эту фигуру: причина locationData->promoutionSelectFigure( locationData->getPropertiesFigure(m_currentPositionInUniqueFigureField))");
        }
    }
    else
    {
        setTextDebug(L"неверная фигура");
    }

    if (promoution())
    {
        setText3(L"Превращение доступно");
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool GameEngine::isOpen() const
{
    return m_ptrRWindow.get()->isOpen();
}

sf::Vector2i GameEngine::getPositionMouse() const
{
    return sf::Mouse::getPosition(*m_ptrRWindow.get());
}

sf::Vector2f GameEngine::getWorldPositionMouse() const
{    
    return m_ptrRWindow.get()->mapPixelToCoords(getPositionMouse());
}
//------------------------------------------------------------------------------------------------------------------------------------------------------

bool GameEngine::isThreat()
{
    if (m_needCheckThreat)
    {
        m_needCheckThreat = false;
        m_threat = checkThreat();
    }
    return m_threat;
}

void GameEngine::setThreat(bool threat)
{
    this->m_threat = threat;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::optional<sf::Event> GameEngine::getEvent()  const
{
    return m_ptrRWindow.get()->pollEvent();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::closeGame()
{
    m_ptrRWindow.get()->close();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

Position::Coordinates GameEngine::getFigureOnPositionMouse()  const
{
    return m_ptrLocation.get()->getPositionFigureWhenMousePressed(getWorldPositionMouse());
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

Position::Coordinates GameEngine::getUniqueFigureOnPositionMouse()  const
{
    return m_ptrLocation.get()->getPositionOnMousePositionUniqueFigire(getWorldPositionMouse());
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool GameEngine::promoution() const noexcept
{
    return m_needPomoution;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::setPromoution(bool needPomoution)
{
    this->m_needPomoution = needPomoution;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::showCurrnetPlayer() const
{
    std::wstring player = L"\nСейчас ход игрока #" + std::to_wstring(m_currentPlayer);
    m_ptrTextInGameRow2.get()->setString(player);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

int GameEngine::getCurrentPlayer() const noexcept
{
    return m_currentPlayer;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::setCurrentPlayer(int currentPlayer)
{
    m_currentPlayer = currentPlayer;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::nextPlayer()
{
    m_currentPlayer < propertiesGame::countPlayer ? m_currentPlayer++ : m_currentPlayer = 1;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::setText1(std::wstring message)
{
    m_ptrTextInGameRow1.get()->setString(message);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::setText2(std::wstring message)
{
    m_ptrTextInGameRow2.get()->setString(message);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::setText3(std::wstring message)
{
    m_ptrTextInGameRow3.get()->setString(message);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::setTextDebug(std::wstring message)
{
    m_ptrTextInGameRow4.get()->setString(message);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::drawWindowGame()
{
    showCurrnetPlayer();

    m_ptrRWindow.get()->draw(*m_ptrTextInGameRow1.get());
    m_ptrRWindow.get()->draw(*m_ptrTextInGameRow2.get());
    m_ptrRWindow.get()->draw(*m_ptrTextInGameRow3.get());
    m_ptrRWindow.get()->draw(*m_ptrTextInGameRow4.get());

    for (size_t row = 0; row < propertiesGame::countCellOnLengthWindow; row++)
    {
        for (size_t coll = 0; coll < propertiesGame::countCellOnLengthWindow; coll++)
        {
            Position::Coordinates currentPosition{ row, coll };
            m_ptrRWindow.get()->draw(m_ptrGameField.get()->getRectangleShapeOnField(currentPosition));
            m_ptrRWindow.get()->draw(m_ptrGameField.get()->getFieldCoordinateOnField(currentPosition));

            m_ptrRWindow.get()->draw(m_ptrLocation.get()->getRectangleShapeFigure(currentPosition));
            m_ptrRWindow.get()->draw(m_ptrLocation.get()->getRectangleShapeUniqueFigure(currentPosition));
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::clearWindowGame(sf::Color color)
{
    m_ptrRWindow.get()->clear(color);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::displayWindowGame()
{
    m_ptrRWindow.get()->display();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
