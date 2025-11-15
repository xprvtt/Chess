#include "Core.h"

sf::Font loadFont(std::filesystem::path PathToFont)
{
    sf::Font font;

    if (font.openFromFile(PathToFont))
    {
        OutputLog("Class -> GameField -> Шрифт загружен");
    }

    OutputLog("Class -> GameField -> Ошибка загрузки шрифта");

    return font;
} 