#include "Main.h"


bool nextGame = false;

std::unique_ptr<GameEngine> getGameEngine();


int main()
{
    // создаем вывод в логи
    std::filesystem::permissions("Log/log.txt", std::filesystem::perms::all);
    remove("Log/log.txt");
    OUTPUT_LOG("Запуск!");    

    do 
    {        
        /*
        * 
        * // возможность загрузить игру (тут)
        * importSave();
        *
        * 
        * // возможность выгрузить игру / перенести -> startGameCycle()
        * exportSave();
        *
        */

        // основной цикл
        nextGame = startGameCycle(getGameEngine());;

    } while ( nextGame );

    return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------

std::unique_ptr<GameEngine> getGameEngine()
{
    // создаем окно игры из настроек propertiesGame 
    std::unique_ptr rWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode({ propertiesGame::sizeWindowLength, propertiesGame::sizeWindowHeight }), "Chess");
    rWindow.get()->setFramerateLimit(100);

    // основное игровое поле из настроек propertiesGame
    // содержит только конструкцию игрового поля
    std::unique_ptr<GameField> chessField = std::make_unique<GameField>(propertiesGame::countCellOnLengthWindow, propertiesGame::sizeWindowHeight, propertiesGame::currentFont, sf::Color(140, 140, 140), sf::Color::White, sf::Color(152, 118, 84));


    // класс с полным расположением фигур \ первоначально создается пустым исходя изнастроек propertiesGame 
    // для размещения фигур необходимо добавить уникальные фигуры -> AddUniqueFigure();
    // в последствии можно установить фигуры на игровое поле-> SetFigure();   
    std::unique_ptr<FigureLocation> newLocation = std::make_unique< FigureLocation>(propertiesGame::countCellOnLengthWindow, propertiesGame::countCellOnHeightWindow, propertiesGame::sizeWindowHeight, propertiesGame::pathToEmptyImage, propertiesGame::pathToEmptyImage, 0.5f);
    
    // добавляем все уникальные фигуры
    newLocation.get()->addUniqueVectorFigure(propertiesGame::addedVectorUniqueFigures);
    
    // заполняем игровое поле
    newLocation.get()->setFigureVector(propertiesGame::currentVectorLocationFigure);

    return std::make_unique<GameEngine>(std::move(rWindow), std::move(newLocation), std::move(chessField));
}
