#include "propertiesGame.h"


unsigned propertiesGame::sizeWindowHeight = 1000;
unsigned propertiesGame::sizeWindowLength = static_cast<unsigned>(round(1000 * 1.7));

size_t propertiesGame::countCellOnLengthWindow = 10;
size_t propertiesGame::countCellOnHeightWindow = 10;

sf::Font propertiesGame::currentFont = []
{
    std::filesystem::path fontFolder = L"Font/";

    // обнаруживаем все шрифты в папке 
    std::vector<std::filesystem::path> vectorAddedFont = searchFile(fontFolder, ".ttf");

    // если шрифтов не найдено выходим
    if (vectorAddedFont.empty())
    {
        OUTPUT_LOG_ERROR("Namespace -> propertiesGame -> не найден шрифт");
        exit(-1);
    }

    return loadFont(vectorAddedFont[0]);

}();

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::filesystem::path propertiesGame::pathToEmptyImage = "Assets/Standart/Empty.png";
std::filesystem::path propertiesGame::pathToEmptyPawn = "Assets/Standart/EmptyPawn.png";

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<std::pair<std::shared_ptr<Figure>, std::filesystem::path>> propertiesGame::addedVectorUniqueFigures = []
{
    std::vector<PropertiesFigure> promoutionForPawnPlayerOne =
    {
        PropertiesFigure{L"Rook",    1, false, false, false },
        PropertiesFigure{L"Queen",   1, false, false, false },
        PropertiesFigure{L"Knight",  1, false, false, false},
        PropertiesFigure{L"Bishop",  1, false, false, false}
    };

    std::vector<PropertiesFigure>  promoutionForPawnPlayerTwo =
    {
        PropertiesFigure{ L"Rook",   2,false, false, false  },
        PropertiesFigure{ L"Queen",  2,false, false, false },
        PropertiesFigure{ L"Knight", 2,false, false, false},
        PropertiesFigure{ L"Bishop", 2,false, false, false}
    };

    std::vector<std::pair<std::shared_ptr<Figure>, std::filesystem::path>> result =
    {
        { std::make_shared<Pawn>(1, false, false, promoutionForPawnPlayerOne), L"Assets/pawn-white.png"},
        { std::make_shared<Pawn>(2, false, false, promoutionForPawnPlayerTwo), L"Assets/pawn-black.png" },
        { std::make_shared<King>(1, true, true),                               L"Assets/king-white.png" },
        { std::make_shared<King>(2, true, true),                               L"Assets/king-black.png" },
        { std::make_shared<Rook>(1),                                           L"Assets/rook-white.png" },
        { std::make_shared<Rook>(2),                                           L"Assets/rook-black.png" },
        { std::make_shared<Queen>(1),                                          L"Assets/queen-white.png" },
        { std::make_shared<Queen>(2),                                          L"Assets/queen-black.png" },
        { std::make_shared<Knight>(1),                                         L"Assets/knight-white.png" },
        { std::make_shared<Knight>(2),                                         L"Assets/knight-black.png" },
        { std::make_shared<Bishop>(1),                                         L"Assets/bishop-white.png" },
        { std::make_shared<Bishop>(2),                                         L"Assets/bishop-black.png" }
    };

    return result;

}();

//------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<PositionAndPropertiesFigure> propertiesGame::currentVectorLocationFigure = []
{
    std::vector<PositionAndPropertiesFigure> currentVectorLocationFigure;


    std::vector<PropertiesFigure>  promoutionForPawnPlayerOne =
    {
        PropertiesFigure{ L"Rook",   1, false, false, false },
        PropertiesFigure{ L"Queen",  1, false, false, false },
        PropertiesFigure{ L"Knight", 1, false, false, false},
        PropertiesFigure{ L"Bishop", 1, false, false, false}
    };

    std::vector<PropertiesFigure>  promoutionForPawnPlayerTwo =
    {
        PropertiesFigure{ L"Rook",   2, false, false, false  },
        PropertiesFigure{ L"Queen",  2, false, false, false },
        PropertiesFigure{ L"Knight", 2, false, false, false},
        PropertiesFigure{ L"Bishop", 2, false, false, false}
    };

    for (int row = 0; row < 10; row++)
    {
        for (int coll = 0; coll < 10; coll++)
        {
            // стандартная "пустая клетка"
            std::wstring name = L"Space";

            bool invulnerable = false;
            bool important = false;
            // bool promoution = false;

            if      (coll == 1 || coll == 10 - 2) { name = L"Rook"; }
            else if (coll == 2 || coll == 10 - 3) { name = L"Knight"; }
            else if (coll == 3 || coll == 10 - 4) { name = L"Bishop"; }
            else if (coll == 4)                   { name = L"Queen"; }
            else if (coll == 5)                   { name = L"King"; invulnerable = true; important = true; }


            // располагаем пешки
            if (row == 2)
            {
                currentVectorLocationFigure.emplace_back(Position::Coordinates( coll, row ), PropertiesFigure{ L"Pawn", 2, false, false, true }, promoutionForPawnPlayerOne);
            }
            // располагаем пешки
            else if (row == 10 - 3)
            {
                currentVectorLocationFigure.emplace_back(Position::Coordinates( coll, row), PropertiesFigure{  L"Pawn", 1, false, false, true }, promoutionForPawnPlayerTwo);
            }
            else if (row == 1)
            {
                currentVectorLocationFigure.emplace_back(Position::Coordinates( coll, row), PropertiesFigure{  name, 2, invulnerable, important, false }, std::vector<PropertiesFigure>{} );
            }
            else if (row == 10 - 2)
            {
                currentVectorLocationFigure.emplace_back(Position::Coordinates(coll, row), PropertiesFigure{ name, 1, invulnerable, important, false }, std::vector<PropertiesFigure>{} );
            }

            // else => none 
        }
    }

    return currentVectorLocationFigure;
}();

//------------------------------------------------------------------------------------------------------------------------------------------------------

 int propertiesGame::countPlayer = 2;
 int propertiesGame::currentPlayer = 1;

 std::wstring propertiesGame::currentParty = []
 {
    return L"Party time:\t" + getCurrentTimeWstring();

 }();
