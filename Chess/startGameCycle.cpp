#include "Main.h"

bool startGameCycle(std::unique_ptr<GameEngine> game)
{
	auto gameData = game.get();

    while (gameData->isOpen())
    {
        // проверяем угрозы текущего игрока, подсвечиваем их при наличии
        if (gameData->isThreat())
        {
			gameData->performBacklightThreat(); // подсветка фигур, которые угрожают важным фигурам текущего игрока
        }

        while (const std::optional event = gameData->getEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                gameData->closeGame();
            }    

            else if (const auto& mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) // выделяем фигуру при нажатии по ней или передвигаем
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    // необходимо ли превращение?       
                    // если нет обрабатываем действие игрока
                    gameData->promoution() ? gameData->performPromouten() : gameData->performMovePlayer();
                }
            }
        }

        gameData->clearWindowGame(sf::Color::White);
        gameData->drawWindowGame();
        gameData->displayWindowGame();
    }
    // управляем необходимостью начать следующую игру
    return false;
}