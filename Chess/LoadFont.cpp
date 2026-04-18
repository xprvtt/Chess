#include "Core.h"

sf::Font loadFont(std::filesystem::path PathToFont)
{
    sf::Font font;

    if (font.openFromFile(PathToFont))
    {
        OUTPUT_LOG("[loadFont] -> Шрифт загружен");
    }

    OUTPUT_LOG_ERROR("[loadFont] -> Ошибка загрузки шрифта");

    return font;
} 