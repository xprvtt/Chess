#include "Core.h"

Font LoadFont(path PathToFont)
{
    Font font;
    if (font.openFromFile(PathToFont))
    {
        OutputLog("Class -> GameField -> ����� ��������");
        return font;
    }
    OutputLog("Class -> GameField -> ������ �������� ������");
}