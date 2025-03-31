#include "Main.h"


unordered_map<string, Texture> TextureMap;


int main()
{

    OutputLog("Инициация");

    ///////////////////////////////////////////////////////////////////////////////////

    /// высота окна, от нее зависит длина окна
    unsigned int SizeWindowHeight = 1000;

    /// длина окна
    unsigned int SizeWindowLength = SizeWindowHeight + SizeWindowHeight * 0.5;
    
    /// количество ИГРОВЫХ клеток на одной стороне + 2 клетки для координат
    unsigned int CountCellOnLengthWindow = 8 + 2;    
    unsigned int CountCellOnHeightWindow = 8 + 2;

    ///////////////////////////////////////////////////////////////////////////////////



    ///////////////////////////////////  FONT   /////////////////////////////////////// 
    /// обнаруживаем все шрифты в папке 
    vector<path> SearchFont = SearchFile("Font/", ".ttf");

    /// если шрифтов не найдено нет смысла продолжать
    if (SearchFont.empty())
    {
        OutputLog("Шрифт не найден, завершение");
        return -1;
    }
    // используем первый в списке шрифт
    Font CurrentFont = LoadFont(SearchFont[0]);

    ///////////////////////////////////////////////////////////////////////////////////

    //// стандартные текстуры для инициализации игры ////
    path PathToEmptyimage      = "Assets/Standart/Empty.png";
    path PathToEmptyPawn       = "Assets/Standart/EmptyPawn.png";

    /// vector textrue ///



    
    ///////////////////////////////////////////////////////////////////////////////////

    
    /// текст расположенный в первом ряду
    Text TextInGameRow1(CurrentFont);
    TextInGameRow1.setString(L"TextInGameRow1");
    TextInGameRow1.setCharacterSize(SizeWindowHeight / (CountCellOnLengthWindow * 3));
    TextInGameRow1.setFillColor(Color::Black);
    TextInGameRow1.setPosition(Vector2f(SizeWindowHeight / CountCellOnLengthWindow / 2 + SizeWindowHeight , SizeWindowHeight / CountCellOnLengthWindow));

    /// текст расположенный во втором ряду
    Text TextInGameRow2(CurrentFont);
    TextInGameRow2.setString(L"TextInGameRow2");
    TextInGameRow2.setCharacterSize(SizeWindowHeight / (CountCellOnLengthWindow * 3));
    TextInGameRow2.setFillColor(Color::Black);
    TextInGameRow2.setPosition(Vector2f(SizeWindowHeight / CountCellOnLengthWindow / 2+ SizeWindowHeight , SizeWindowHeight / CountCellOnLengthWindow * 2.5));

    /// текст расположенный в третьем ряду
    Text TextInGameRow3(CurrentFont);
    TextInGameRow3.setString(L"TextInGameRow3");
    TextInGameRow3.setCharacterSize(SizeWindowHeight / (CountCellOnLengthWindow * 3));
    TextInGameRow3.setFillColor(Color::Black);
    TextInGameRow3.setPosition(Vector2f(SizeWindowHeight / CountCellOnLengthWindow / 2+ SizeWindowHeight , SizeWindowHeight / CountCellOnLengthWindow * 3));

    ///////////////////////////////////////////////////////////////////////////////////


    // создаем вывод в логи
    permissions("Log/log.txt", perms::all);
    remove("Log/log.txt");
    OutputLog("Запуск!");

    
    // создаем окно игры

    /// Окно игры
    RenderWindow window(VideoMode({ SizeWindowLength, SizeWindowHeight }), "Chess");
    window.setFramerateLimit(60);

    /// основное игровое поле 
    /// содержит только конструкцию игрового поля
    GameField ChessField(CountCellOnLengthWindow, SizeWindowHeight, CurrentFont, Color(140, 140, 140), Color::White, Color(152, 118, 84));

    OutputLog("Инициация Игрового поля закончено");

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    OutputLog("Расположение Фигур начато");


    /// класс с полным расположением фигур \ первоначально создается пустым 
    /// для размещения фигур необходимо добавить уникальные фигуры -> AddUniqueFigure();
    /// в последствии можно установить фигуры на игровое поле-> SetFigure();

    FigureLocation Newlocation(CountCellOnLengthWindow, CountCellOnHeightWindow, SizeWindowHeight, PathToEmptyimage, PathToEmptyimage, 0.5f);


    //// другие текстуры, такие как фигуры ///
    /// добавляем уникальные фигуры
    ////// 1
    path PathToBlackPawnTexture = "Assets/pawn-black.png";
    path PathToWhitePawnTexture = "Assets/pawn-white.png";

    Newlocation.AddUniqueFigure(make_shared<Pawn>(1, false), PathToWhitePawnTexture);
    Newlocation.AddUniqueFigure(make_shared<Pawn>(2, false), PathToBlackPawnTexture);


    ////// 2
    path PathToWhiteRookTexture = "Assets/rook-white.png";
    path PathToBlackRookTexture = "Assets/rook-black.png";

    Newlocation.AddUniqueFigure(make_shared<Rook>(1, false), PathToWhiteRookTexture);
    Newlocation.AddUniqueFigure(make_shared<Rook>(2, false), PathToBlackRookTexture);


    ////// 3
    path PathToWhiteQueenTexture = "Assets/queen-white.png";
    path PathToBlackQueenTexture = "Assets/queen-black.png";

    Newlocation.AddUniqueFigure(make_shared<Queen>(1, false), PathToWhiteQueenTexture);
    Newlocation.AddUniqueFigure(make_shared<Queen>(2, false), PathToBlackQueenTexture);


    ////// 4
    path PathToWhiteKnightTexture = "Assets/knight-white.png";
    path PathToBlackKnightTexture = "Assets/knight-black.png";

    Newlocation.AddUniqueFigure(make_shared<Knight>(1, false), PathToWhiteKnightTexture);
    Newlocation.AddUniqueFigure(make_shared<Knight>(2, false), PathToBlackKnightTexture);


    ////// 5
    path PathToWhiteKingTexture = "Assets/king-white.png";
    path PathToBlackKingTexture = "Assets/king-black.png";

    Newlocation.AddUniqueFigure(make_shared<King>(1, true), PathToWhiteKingTexture);
    Newlocation.AddUniqueFigure(make_shared<King>(2, true), PathToBlackKingTexture);


    ////// 6
    path PathToWhiteBishopTexture = "Assets/bishop-white.png";
    path PathToBlackBishopTexture = "Assets/bishop-black.png";

    Newlocation.AddUniqueFigure(make_shared<Bishop>(1, false), PathToWhiteBishopTexture);
    Newlocation.AddUniqueFigure(make_shared<Bishop>(2, false), PathToBlackBishopTexture);



    /// заполняем игровое поле пешками
    // колличество игроков (Сторон)
    int CountPlayer = 2;

    for (int Row = 0; Row < CountCellOnHeightWindow; Row++)
    {
        for (int Coll = 0; Coll < CountCellOnLengthWindow; Coll++)
        {        
            string Name = "Figure";
            bool invulnerable = false;

            if      (Coll == 1 || Coll == CountCellOnLengthWindow - 2)   Name = "Rook";
            else if (Coll == 2 || Coll == CountCellOnLengthWindow - 3)   Name = "Knight";
            else if (Coll == 3 || Coll == CountCellOnLengthWindow - 4)   Name = "Bishop";
            else if (Coll == 4)                                          Name = "Queen";
            else if (Coll == 5)                                        { Name = "King"; invulnerable = true; }

            if (Row == 2)
            {   
                Newlocation.SetFigure(Coll, Row, "Pawn", 2, false);
            }
            else if (Row == CountCellOnHeightWindow -3)
            {
                Newlocation.SetFigure(Coll, Row, "Pawn", 1, false);
            } 
            else if (Row == 1)
            {
                Newlocation.SetFigure(Coll, Row, Name, 2, invulnerable);
            }
            else if (Row == CountCellOnHeightWindow - 2)
            {
                Newlocation.SetFigure(Coll, Row, Name, 1, invulnerable);
            }
        }
    }

    OutputLog("Расположение Фигур закончено");

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                     
    Vector2i PositionMouse;
    Vector2f MouseWorldPos;

    CountdownTimer TimerCD1;

    vector<vector<bool>> SelectCellForMove;

    bool Promoution = false;

    int NextPlayer = 1;

    // x / y
    pair<int, int> OldPosition;

    while (window.isOpen())
    {
        PositionMouse = Mouse::getPosition(window);
        MouseWorldPos = window.mapPixelToCoords(PositionMouse);

        // x / y
        pair<int, int> CurrentPositionInGameField;

        // x / y
        pair<int, int> CurrentgvPositionInUniqueFigureField;

        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                window.close();
            }

            ///выделяем фигуру при нажатии по ней
            else if (const auto& mouseButtonPressed = event->getIf<Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == Mouse::Button::Left )
                {

                    /// получаем координаты фигуры(клетки на игровом поле) по которой нажали
                    CurrentPositionInGameField = Newlocation.GetPositionFigureWhenMousePressed(MouseWorldPos);

                    /// получаем координаты фигуры(клетки на поле с уникальными фигурами) по которой нажали
                    CurrentgvPositionInUniqueFigureField = Newlocation.GetPositionUniqueFigureWhenMousePressed(MouseWorldPos);



                    // если число минусовые то значит нажали на поле уникальных фигур
                    if (!Promoution)
                    {


                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // ВРЕМЕННОЕ
                        // выводим информацию о фигуре на игровом поле

                        string Name = Newlocation.GetIDFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second) + " ";
                        string Coordinate = "X:" + to_string(CurrentPositionInGameField.first) + " Y:" + to_string(CurrentPositionInGameField.second);
                        string sideFigure = " Side: " + to_string(Newlocation.GetSideFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second));

                        string invulnerable = "\ninvulnerable: ";
                        Newlocation.GetInvulnerableFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second) ? invulnerable += "true" : invulnerable += "false";

                        wstring Player = L"\nСейчас ход игрока #" + to_string(NextPlayer);
                        TextInGameRow1.setString(Name + Coordinate + sideFigure + invulnerable + Player);
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                        //сторона у выбранной фигуры
                        int Side = Newlocation.GetSideFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second);

                        ///выделяем ее или снимаем выделение, если выделено то ожидается передвижение фигуры
                        if (!Newlocation.FiguresSelectedOrNot() && Side == NextPlayer)
                        {
                            //выделяем выбранную фигуру
                            Newlocation.SeletcFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second);

                            // получаем вектор доступных ходов
                            SelectCellForMove = Newlocation.GetAvailableMovesForSelectFigure();

                            // выделяем доступные ходы на доске
                            ChessField.SelectCell(SelectCellForMove);


                            DebugCode
                            (
                                ////////////////////////////////////////////////////////////////////////////////////////////////////
                                /// Информация о доступных ходах                       
                                OutputLog(Newlocation.GetIDFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second));
                                for (int row = 0; row < SelectCellForMove.size(); row++)
                                {
                                    string Message;
                                    for (int coll = 0; coll < SelectCellForMove[0].size(); coll++)
                                    {
                                        SelectCellForMove[row][coll] ? Message += " X " : Message += " - ";
                                    }
                                    OutputLog(Message);
                                }
                                //////////////////////////////////////////////////////////////////////////////////////////////////////
                            );

                           

                        }
                        else
                        {
                            // двигаем фигуру на выбранные координаты если возможно
                            if (Newlocation.MoveSelectFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second))
                            {
                                //если передвинули проверяем может ли фигура превратиться в другую
                                if (Newlocation.PromoutionFigureOnPosition(CurrentPositionInGameField.first, CurrentPositionInGameField.second))
                                {
                                    TextInGameRow3.setString(L"Превращение доступно");
                                    
                                    OldPosition = CurrentPositionInGameField;

                                    Newlocation.SeletcFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second);
                                    Newlocation.SeletcUniqueFigureForPromoution(CurrentPositionInGameField.first, CurrentPositionInGameField.second);

                                    Promoution = true;
                                }
                                else
                                {
                                    Newlocation.UnSeletcFigure();
                                }

                                //передаем ход следующему игроку
                                NextPlayer < CountPlayer ? NextPlayer++ : NextPlayer = 1;
                            }
                            else
                            {
                                Newlocation.UnSeletcFigure();
                            }   
                            ChessField.UnSelectCell();
                        }

                        DebugCode
                        (
                            /////////////////////////////////////////////////////////////////////////////////
                            ///выводим доступные ходы 
                            for (int Ypos = 0; Ypos < SelectCellForMove.size(); Ypos++)
                            {
                                string Message ;
                                for (int Xpos = 0; Xpos < SelectCellForMove[0].size(); Xpos++) { Message += to_string(Newlocation.GetSideFigure(Xpos, Ypos)) + "\t"; }
                                OutputLog(Message);                           
                            }
                            for (int Ypos = 0; Ypos < SelectCellForMove.size(); Ypos++)
                            {
                                string Message = " ";
                                for (int Xpos = 0; Xpos < SelectCellForMove[0].size(); Xpos++) { Message += Newlocation.GetIDFigure(Xpos, Ypos) + "\t\t"; }
                                OutputLog(Message);
                            }                            
                            /////////////////////////////////////////////////////////////////////////////////
                        )
                    }
                    else if (Promoution)
                    {

                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // выводим информацию о фигуре на игровом поле
                        string Name = Newlocation.GetIDUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second) + " ";
                        string Coordinate = "X:" + to_string(CurrentgvPositionInUniqueFigureField.first) + " Y:" + to_string(CurrentgvPositionInUniqueFigureField.second);
                        string sideFigure = " Side: " + to_string(Newlocation.GetSideUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second));
                        string invulnerable = "\ninvulnerable: ";
                        Newlocation.GetInvulnerableUniqueFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second) ? invulnerable += "true" : invulnerable += "false";
                        TextInGameRow1.setString(Name + Coordinate + sideFigure + invulnerable);
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                        // сторона передвинутой фигуры должно совпадать с выбранной
                        if ( Newlocation.GetSideFigure(OldPosition.first, OldPosition.second) == Newlocation.GetSideUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second))
                        {
                            if (Newlocation.PromoutionSelectFigure(Newlocation.GetIDUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second)))
                            {                                
                                Newlocation.UnSeletcUniqueFigure();
                                Newlocation.UnSeletcFigure();
                                Promoution = false;
                                TextInGameRow3.setString(L"превращение выполнено");
                            }
                            else
                            {
                                TextInGameRow3.setString(L"превращение невозможно\nв эту фигуру");
                            }
                        }
                        else
                        {
                            TextInGameRow3.setString(L"неверная фигура");
                        }
                    }
                }
            }
        }

        TextInGameRow2.setString(to_string(MouseWorldPos.x) + " " + to_string(MouseWorldPos.y));

        window.clear(Color::White);
        
        window.draw(TextInGameRow1);
        window.draw(TextInGameRow2);
        window.draw(TextInGameRow3);

        for (int row = 0; row < CountCellOnLengthWindow; row++)
        {
            for (int coll = 0; coll < CountCellOnLengthWindow; coll++)
            {
                window.draw(ChessField.GetRectangleShapeOnField(coll, row));
                window.draw(ChessField.GetFieldCoordinateOnField(coll, row));
                window.draw(Newlocation.GetRectangleShapeFigure(coll, row));
                window.draw(Newlocation.GetRectangleShapeUniqueFigure(coll, row));
            }
        } 
        window.display();
    }

    return 0;
}
