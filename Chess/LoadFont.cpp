#include "Core.h"

Font LoadFont(path PathToFont)
{
    Font font;
    if (font.openFromFile(PathToFont))
    {
        OutputLog("Class -> GameField -> Шрифт загружен");
        return font;
    }
    OutputLog("Class -> GameField -> Ошибка загрузки шрифта");
} 