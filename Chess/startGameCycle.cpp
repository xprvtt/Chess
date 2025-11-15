#include "Main.h"



bool startGameCycle(std::unique_ptr<GameEngine> game)
{

    while (game.get()->isOpen())
    {

        ///
        /// проверяем угрозы, подсвечиваем их при наличии
        /// 
        if (game.get()->isThreat())
        {
            game.get()->performBacklightThreat();
        }



        while (const std::optional event = game.get()->getEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                game.get()->closeGame();
            }

            ///
            /// выделяем фигуру при нажатии по ней или передвигаем
            /// 
            else if (const auto& mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    ///
                    /// необходимо ли превращение?       
                    /// если нет выполняем действие игрока
                    /// 
                    game.get()->promoution() ? game.get()->performPromouten() : game.get()->performMovePlayer();
                }
            }
        }



        game.get()->clearWindowGame(sf::Color::White);

        game.get()->drawWindowGame();

        game.get()->displayWindowGame();

    }


    ///
    /// управляем необходимостью начать следующую игру
    ///
    return false;

}