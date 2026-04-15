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
    // получаем расположение важных ФИГУР текущего игрока ( "король" - могут быть и другие) 
    m_positionImportantFigure = m_ptrLocation.get()->getPositionsFigure(m_currentPlayer, true, 'M');

    // получаем копию расположения фигур 
    auto locationFigureInGame = m_ptrLocation.get()->getLocationFigure();

    // стандартно существует единственый экземпляр ВАЖНЫХ ФИГУРЫ - король, на каждой стороне, но может быть и несколько -> проводим цикл
    // так же королей может не быть и в цикл не входим т.к. вектор будет пустой
    if (!m_positionImportantFigure.empty())
    {

        for (const auto& currentPosition : m_positionImportantFigure)
        {
            // => далее необходимо получить позиции фигур противников, которые могут угрожать королю, и выделяем их клетки в GameField
            // можно сделать аналогичные проверки для любых фигур
            
            // получаем позиции фигур противников, которые "угрожают" текущей важной фигуре взятием
            m_positionEnemyFigureThatThreaten = m_ptrLocation.get()->checkThreatForFigure(currentPosition, locationFigureInGame);

            for (const auto& cPosition : m_positionEnemyFigureThatThreaten)
            {
                // выделяем клетки на которых стоят эти фигуры
                m_ptrGameField.get()->selectCell(cPosition, sf::Color::Red);
                m_ptrGameField.get()->selectCell(currentPosition, sf::Color::Red);
                setText3(L"поставлен шах");
            }

            // получаем позиции фигур которые могут защитить указанную
            auto positionFrendlyFigure = m_ptrLocation.get()->getPositionFigureCanProtectedIndicatedFigure(currentPosition, locationFigureInGame);

            for (const auto& currentPos : positionFrendlyFigure)
            {
                // выделяем их
                m_ptrGameField.get()->selectCell(currentPos, sf::Color::Green);
            }

            if (positionFrendlyFigure.size() == 1 && positionFrendlyFigure[0] == Position::Coordinates(0,0))
            {
                setText4(L"поставлен мат игроку: " + std::to_wstring(m_currentPlayer));
            }
        }
    }

    return true;;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::performMovePlayer()
{
    m_currentPositionInGameField = getFigureOnPositionMouse();

    
    // выводим информацию о фигуре ---- ВРЕМЕННОЕ
    m_ptrTextInGameRow1.get()->setString(
        m_ptrLocation.get()->getIdFigure(m_currentPositionInGameField) + L"\t"
        + L"X:" + std::to_wstring(m_currentPositionInGameField.inRow) 
        + L" \\ Y:" + std::to_wstring(m_currentPositionInGameField.inColum)
        + L"\tSIDE: " + std::to_wstring(m_ptrLocation.get()->getSideFigure(m_currentPositionInGameField))
        + L"\nInvulnerable:\t" + std::to_wstring(m_ptrLocation.get()->getInvulnerableFigure(m_currentPositionInGameField))
        + L"\nImportant:\t\t" + std::to_wstring(m_ptrLocation.get()->getImportantFigure(m_currentPositionInGameField))
    );

    // сторона у выбранной фигуры
    int side = m_ptrLocation.get()->getSideFigure(m_currentPositionInGameField);

    // выделяем ее или снимаем выделение, если выделено то ожидается передвижение фигуры
    // так же должна совпадать сторона игрока который сейчас ходит, для выделения
    if (!m_ptrLocation.get()->figuresSelectedOrNot() && side == m_currentPlayer)
    {
        // выделяем выбранную фигуру
        m_ptrLocation.get()->seletcFigure(m_currentPositionInGameField);

        // получаем вектор доступных ходов
        auto positionSelectFigure = m_ptrLocation.get()->getPositionSelectFigure();

        m_selectCellForMove = m_ptrLocation.get()->getAvailableMovesForFigure(positionSelectFigure);

        // выделяем доступные ходы на доске
        for (const auto& onePos : m_selectCellForMove)
        {
            m_ptrGameField.get()->selectCell(onePos, sf::Color::Red);
        }
    }
    else if (m_ptrLocation.get()->figuresSelectedOrNot())
    {
        // создаем копию свойств фигуры на случай если ход выполнен в угрозу своим важным фигурам
        PropertiesFigure tempOldPF = m_ptrLocation.get()->getPropertiesFigure(m_currentPositionInGameField);

        // двигаем фигуру на выбранные координаты если возможно
        if (m_ptrLocation.get()->moveSelectFigure(m_currentPositionInGameField))
        {
            m_needCheckThreat = true;
            if (isThreat()) // если угроза нашлась - откатываем и не передаем ход
            {
                setText3(L"на эти координаты нельзя\nпередвинуть фигуру");

                auto tempPositionOld = m_ptrLocation.get()->getPositionSelectFigure();

                m_ptrLocation.get()->setFigure(tempPositionOld, m_ptrLocation.get()->getPropertiesFigure(m_currentPositionInGameField), {});

                m_ptrLocation.get()->setFigure(m_currentPositionInGameField, tempOldPF, {});
                m_ptrLocation.get()->unseletcAllFigure();
            }
            else // если передвинули и угроз нет проверяем может ли фигура превратиться в другую
            {                
                if (m_ptrLocation.get()->isPromoutionFigureOnPosition(m_currentPositionInGameField))
                {
                    m_oldPosition = m_currentPositionInGameField;

                    m_ptrLocation.get()->seletcFigure(m_currentPositionInGameField);
                    m_ptrLocation.get()->selectForPromoutionUniqueFigure(m_currentPositionInGameField);

                    setPromoution(true);
                }
                // если не может превратиться снимаем выделение
                else
                {
                    m_ptrLocation.get()->unseletcAllFigure();
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
            m_ptrLocation.get()->unseletcAllFigure();
        }
        m_ptrGameField.get()->unselectAllCell();
    }
    if (promoution())
    {
        setText3(L"Превращение доступно");
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

bool GameEngine::checkThreat()
{
    bool result = false;

    // получаем расположение ВАЖНЫХ ФИГУР ( "король" - могут быть и другие) текущего игрока
    m_positionImportantFigure = m_ptrLocation.get()->getPositionsFigure(m_currentPlayer, true, 'M');

    if (!m_positionImportantFigure.empty())
    {
        for (int countPosition = 0; countPosition < m_positionImportantFigure.size(); countPosition++)
        {
            // получаем позиции фигур противников которые "угрожают" важной фигуре взятием
            m_positionEnemyFigureThatThreaten = m_ptrLocation.get()->checkThreatForFigure(m_positionImportantFigure[countPosition], m_ptrLocation.get()->getLocationFigure());

            // если вектор не пуст значит угрозы есть
            if (!m_positionEnemyFigureThatThreaten.empty())
            {
                result = true;
            }
        }
    }

    return result;

}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::performPromouten()
{

    m_currentPositionInUniqueFigureField = getUniqueFigureOnPositionMouse();
    // выводим информацию о фигуре -- ВРЕМЕННОЕ
    setText1(m_ptrLocation.get()->getIdFigure(m_currentPositionInUniqueFigureField) + L"\t"
        + L"X:" + std::to_wstring(m_currentPositionInUniqueFigureField.inRow) 
        + L" \\ Y:" + std::to_wstring(m_currentPositionInUniqueFigureField.inColum)
        + L"\tSIDE: " + std::to_wstring(m_ptrLocation.get()->getSideFigure(m_currentPositionInUniqueFigureField))
        + L"\nInvulnerable:\t" + std::to_wstring(m_ptrLocation.get()->getInvulnerableFigure(m_currentPositionInUniqueFigureField))
        + L"\nImportant:\t\t" + std::to_wstring(m_ptrLocation.get()->getImportantFigure(m_currentPositionInUniqueFigureField))
    );
    
    // сторона передвинутой фигуры должно совпадать с выбранной
    if (m_ptrLocation.get()->getSideFigure(m_oldPosition) == m_ptrLocation.get()->getSideUniqueFigure(m_currentPositionInUniqueFigureField))
    {
        if (m_ptrLocation.get()->promoutionSelectFigure( m_ptrLocation.get()->getPropertiesFigure(m_currentPositionInUniqueFigureField)))
        {
            m_ptrLocation.get()->unselectUniqueFigure();
            m_ptrLocation.get()->unseletcAllFigure();

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

int GameEngine::getCurrentPlayer() const noexcept
{
    return m_currentPlayer;
}

void GameEngine::setCurrentPlayer(int currentPlayer)
{
    this->m_currentPlayer = currentPlayer;
}

void GameEngine::nextPlayer()
{
    m_currentPlayer < propertiesGame::countPlayer ? m_currentPlayer++ : m_currentPlayer = 1;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------

void GameEngine::setText1(std::wstring message)
{
    m_ptrTextInGameRow1.get()->setString(message);
}
void GameEngine::setText2(std::wstring message)
{
    m_ptrTextInGameRow1.get()->setString(message);
}
void GameEngine::setText3(std::wstring message)
{
    m_ptrTextInGameRow1.get()->setString(message);
}
void GameEngine::setText4(std::wstring message)
{
    m_ptrTextInGameRow1.get()->setString(message);
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
            Position::Coordinates currentPosition{ coll, row };
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

void GameEngine::displayWindowGame()
{
    m_ptrRWindow.get()->display();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
