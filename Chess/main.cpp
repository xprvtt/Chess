#include "Main.h"


unordered_map<string, Texture> TextureMap;


int main()
{

    // создаем вывод в логи
    permissions("Log/log.txt", perms::all);
    remove("Log/log.txt");
    OutputLog("Запуск!");

    ///////////////////////////////////////////////////////////////////////////////////

    /// высота окна, от нее зависит длина окна
    unsigned int SizeWindowHeight = 1000;

    /// длина окна
    unsigned int SizeWindowLength = static_cast<unsigned int>(round(SizeWindowHeight * 1.7));
    
    /// количество ИГРОВЫХ клеток на одной стороне + 2 клетки для координат
    size_t CountCellOnLengthWindow = 8 + 2;
    size_t CountCellOnHeightWindow = 8 + 2;

    ///////////////////////////////////////////////////////////////////////////////////



    ///////////////////////////////////  FONT   /////////////////////////////////////// 
    /// обнаруживаем все шрифты в папке 
    vector<path> SearchFont = SearchFile("Font/", ".ttf");

    /// если шрифтов не найдено вых
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
    TextInGameRow1.setString(L"-");
    TextInGameRow1.setCharacterSize(static_cast<unsigned int>(SizeWindowHeight / (CountCellOnLengthWindow * 3)));
    TextInGameRow1.setFillColor(Color::Black);
    TextInGameRow1.setPosition(Vector2f(static_cast<float>(SizeWindowHeight / CountCellOnLengthWindow / 2 + SizeWindowHeight) , static_cast<float>(SizeWindowHeight / CountCellOnLengthWindow)));

    /// текст расположенный во втором ряду
    Text TextInGameRow2(CurrentFont);
    TextInGameRow2.setString(L"-");
    TextInGameRow2.setCharacterSize(static_cast<unsigned int>(SizeWindowHeight / (CountCellOnLengthWindow * 3)));
    TextInGameRow2.setFillColor(Color::Black);
    TextInGameRow2.setPosition(Vector2f(static_cast<float>(SizeWindowHeight / CountCellOnLengthWindow / 2 + SizeWindowHeight), static_cast<float>(SizeWindowHeight / CountCellOnLengthWindow * 2)));

    /// текст расположенный во 3 ряду
    Text TextInGameRow3(CurrentFont);
    TextInGameRow3.setString(L"-");
    TextInGameRow3.setCharacterSize(static_cast<unsigned int>(SizeWindowHeight / (CountCellOnLengthWindow * 3)));
    TextInGameRow3.setFillColor(Color::Black);
    TextInGameRow3.setPosition(Vector2f(static_cast<float>(SizeWindowHeight / CountCellOnLengthWindow / 2 + SizeWindowHeight), static_cast<float>(SizeWindowHeight / CountCellOnLengthWindow * 3)));


    /// текст расположенный во 4 ряду
    Text TextInGameRow4(CurrentFont);
    TextInGameRow4.setString(L"-");
    TextInGameRow4.setCharacterSize(static_cast<unsigned int>(SizeWindowHeight / (CountCellOnLengthWindow * 3)));
    TextInGameRow4.setFillColor(Color::Black);
    TextInGameRow4.setPosition(Vector2f(static_cast<float>(SizeWindowHeight / CountCellOnLengthWindow / 2 + SizeWindowHeight), static_cast<float>(SizeWindowHeight / CountCellOnLengthWindow * 4)));

    ///////////////////////////////////////////////////////////////////////////////////



    
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

    FigureLocation NewLocation(CountCellOnLengthWindow, CountCellOnHeightWindow, SizeWindowHeight, PathToEmptyimage, PathToEmptyimage, 0.5f);


    //// другие текстуры, такие как фигуры ///
    /// добавляем уникальные фигуры


    // превращения для пешки \ по умолчанию может превратиться в 4 стандартные фигуры
    vector<tuple<int, string, bool, bool, bool>> PromoutionForPawn1 =
    {
        make_tuple(1, "Rook", false, false, false),
        make_tuple(1, "Queen", false, false, false),
        make_tuple(1, "Knight", false, false, false),
        make_tuple(1, "Bishop", false, false, false),
    };
    // превращения для пешки \ по умолчанию может превратиться в 4 стандартные фигуры
    vector<tuple<int, string, bool, bool, bool>> PromoutionForPawn2 =
    {
        make_tuple(2, "Rook", false, false, false),
        make_tuple(2, "Queen", false, false, false),
        make_tuple(2, "Knight", false, false, false),
        make_tuple(2, "Bishop", false, false, false),
    };


    vector<pair<shared_ptr<Figure>, path>> AddFigure =
    {
        make_pair(make_shared<Pawn>(1, false, false, PromoutionForPawn1), "Assets/pawn-white.png"),
        make_pair(make_shared<Pawn>(2, false, false, PromoutionForPawn2), "Assets/pawn-black.png"),
        make_pair(make_shared<Rook>(1),                                   "Assets/rook-white.png"),
        make_pair(make_shared<Rook>(2),                                   "Assets/rook-black.png"),
        make_pair(make_shared<Queen>(1),                                  "Assets/queen-white.png"),
        make_pair(make_shared<Queen>(2),                                  "Assets/queen-black.png"),
        make_pair(make_shared<Knight>(1),                                 "Assets/knight-white.png"),
        make_pair(make_shared<Knight>(2),                                 "Assets/knight-black.png"),
        make_pair(make_shared<King>(1, true, true),                       "Assets/king-white.png"),
        make_pair(make_shared<King>(2, true, true),                       "Assets/king-black.png"),
        make_pair(make_shared<Bishop>(1),                                 "Assets/bishop-white.png"),
        make_pair(make_shared<Bishop>(2),                                 "Assets/bishop-black.png"),
    };


    for (const auto& Figure : AddFigure)
    {
        NewLocation.AddUniqueFigure(Figure.first, Figure.second);
    }

    /// заполняем игровое поле пешками

    // колличество игроков (Сторон)
    int CountPlayer = 2;

    for (size_t Row = 0; Row < CountCellOnHeightWindow; Row++)
    {
        for (size_t Coll = 0; Coll < CountCellOnLengthWindow; Coll++)
        {        
            string Name = "Figure";
            bool invulnerable = false;
            bool Important = false;

            if      (Coll == 1 || Coll == CountCellOnLengthWindow - 2)   Name = "Rook";
            else if (Coll == 2 || Coll == CountCellOnLengthWindow - 3)   Name = "Knight";
            else if (Coll == 3 || Coll == CountCellOnLengthWindow - 4)   Name = "Bishop";
            else if (Coll == 4)                                          Name = "Queen";

            else if (Coll == 5) { Name = "King"; invulnerable = true; Important = true; }

            if (Row == 2)
            {   
                NewLocation.SetFigure(Coll, Row, "Pawn", 2, false, false, PromoutionForPawn1);
            }
            else if (Row == CountCellOnHeightWindow -3)
            {
                NewLocation.SetFigure(Coll, Row, "Pawn", 1, false, false, PromoutionForPawn2);
            } 
            else if (Row == 1)
            {
                NewLocation.SetFigure(Coll, Row, Name, 2, invulnerable, Important);
            }
            else if (Row == CountCellOnHeightWindow - 2)
            {
                NewLocation.SetFigure(Coll, Row, Name, 1, invulnerable, Important);
            }
        }
    }

    OutputLog("Расположение Фигур закончено");

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     

    Vector2i PositionMouse;
    Vector2f MouseWorldPos;


    CountdownTimer TimerCD1;


    vector<pair<size_t, size_t>>  SelectCellForMove;



    //
    vector<pair<size_t, size_t>> PositionEnemyFigure;

    vector<pair<size_t, size_t>> PositionKing = { make_pair(0,0) };
    //

    // доступно ли превращение?
    bool Promoution = false;

    int CurrentPlayer = 1;
    bool Check = false;

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

        
        

        //проверяем угрожает ли что-то ВАЖНЫМ ( Important ) ФИГУРАМ у текущего игрока 

        //проводим проверку единожды для текущего игрока

        if (!Check)
        {
            // считаем что проверку выполнили            
            Check = true;

            //получаем расположение важных ФИГУР ( "король" - могут быть и другие) текущего игрока
            PositionKing = NewLocation.GetPositionsFigure(CurrentPlayer, true, 'M');


            // получаем расположение фигур 
            vector<vector<tuple<int, string, bool, bool, bool>>> LocationFigureInGame = NewLocation.GetVectorLocationFigure();


            // => далее необходимо получить позиции фигур противников, которые могут угрожать королю, и выделяем их клетки в GameField
            // можно сделать аналогичные проверки для любых фигур

            if (!PositionKing.empty())
            {
                // стандартно существует единственый экземпляр ВАЖНЫХ ФИГУРЫ - король, на каждой стороне, но может быть и несколько :) -> проводим цикл
                // так же королей может не быть и в цикл не входим т.к. вектор будет пустой

                for (const auto& CurrentPosition : PositionKing)
                {
                    // получаем позиции фигур противников которые "угрожают" текущей важной фигуре взятием
                    PositionEnemyFigure = NewLocation.CheckThreatFigure(CurrentPosition.first, CurrentPosition.second, LocationFigureInGame);

                    for (const auto& CPosition : PositionEnemyFigure)
                    {
                        // выделяем клетки на которых стоят эти фигуры
                        ChessField.SelectCell(CPosition.first, CPosition.second, Color::Red);
                        ChessField.SelectCell(CurrentPosition.first, CurrentPosition.second, Color::Red);
                        TextInGameRow3.setString(L"поставлен шах");                   
                    }


                    // получаем позиции фигур которые могут защитить указанную (
                    auto PositionFrendlyFigure = NewLocation.FigureCanProtectenCheckmateForFigure(CurrentPosition.first, CurrentPosition.second, LocationFigureInGame);
                    
                    for (const auto& CurrentPos : PositionFrendlyFigure)
                    {
                        ChessField.SelectCell(CurrentPos.first, CurrentPos.second, Color::Green);
                    }

                    if (PositionFrendlyFigure.size() == 1 && PositionFrendlyFigure[0].second == 0 && PositionFrendlyFigure[0].first == 0)
                    {
                        wstring CheckmatePlayer = L"поставлен мат игроку: " + to_wstring(CurrentPlayer);
                        TextInGameRow4.setString(CheckmatePlayer);
                    }

                }
            }
        }

        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                window.close();
            }
            ///выделяем фигуру при нажатии по ней
            if (const auto& mouseButtonPressed = event->getIf<Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == Mouse::Button::Left )
                {
                    /// получаем координаты фигуры(клетки на игровом поле) по которой нажали
                    CurrentPositionInGameField = NewLocation.GetPositionFigureWhenMousePressed(MouseWorldPos);

                    /// получаем координаты фигуры(клетки на поле с уникальными фигурами) по которой нажали
                    CurrentgvPositionInUniqueFigureField = NewLocation.GetPositionUniqueFigureWhenMousePressed(MouseWorldPos);

                    if (!Promoution)
                    {

                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // ВРЕМЕННОЕ
                        // выводим информацию о фигуре на игровом поле
                        string Name = NewLocation.GetIDFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second) + "\t";
                        string Coordinate = "X:" + to_string(CurrentPositionInGameField.first) + " \\ Y:" + to_string(CurrentPositionInGameField.second);
                        string sideFigure = "\tSIDE: " + to_string(NewLocation.GetSideFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second));

                        string invulnerable = "\nInvulnerable:\t";
                        NewLocation.GetInvulnerableFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second) ? invulnerable += "True" : invulnerable += "False";
                        string Important = "\nImportant:\t\t";
                        NewLocation.GetImportantFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second) ? Important += "True" : Important += "False";

                        TextInGameRow1.setString(Name + Coordinate + sideFigure + invulnerable + Important);
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


                        //сторона у выбранной фигуры
                        int Side = NewLocation.GetSideFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second);

                        /// выделяем ее или снимаем выделение, если выделено то ожидается передвижение фигуры
                        /// так же должна совпадать сторона игрока который сейчас ходит, для выделения
                        if (!NewLocation.FiguresSelectedOrNot() && Side == CurrentPlayer)
                        {
                            //выделяем выбранную фигуру
                            NewLocation.SeletcFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second);

                            // получаем вектор доступных ходов
                            auto PositionSelectFigure = NewLocation.GetPositionSelectFigure();

                            SelectCellForMove = NewLocation.GetAvailableMovesForFigure(PositionSelectFigure.first, PositionSelectFigure.second);

                            // выделяем доступные ходы на доске
                            for (const auto& OnePos : SelectCellForMove)
                            {
                                ChessField.SelectCell(OnePos.first, OnePos.second, Color::Red);
                            }  
                        }
                        else if (NewLocation.FiguresSelectedOrNot())
                        {
                            // создаем копию фигуры на случай если ход выполнен в угрозу своим важным фигурам
                            string TempIDold           = NewLocation.GetIDFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second);
                            int    TempSideold         = NewLocation.GetSideFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second);
                            bool   TempInvulnerableold = NewLocation.GetInvulnerableFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second);
                            bool   TempImportantold    = NewLocation.GetImportantFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second);

                            // двигаем фигуру на выбранные координаты если возможно
                            if (NewLocation.MoveSelectFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second))
                            {
                                //передвинули
                                //если что-то так же осталось угрожать важным фигурам откатываем передвижение
                                bool Threat = false;


                                //получаем расположение ВАЖНЫХ ФИГУР ( "король" - могут быть и другие) текущего игрока
                                PositionKing = NewLocation.GetPositionsFigure(CurrentPlayer, true, 'M');


                                if (!PositionKing.empty())
                                {
                                    for (int CountPosition = 0; CountPosition < PositionKing.size() && !Threat; CountPosition++)
                                    {
                                        // получаем позиции фигур противников которые "угрожают" важной фигуре взятием
                                        PositionEnemyFigure = NewLocation.CheckThreatFigure(PositionKing[CountPosition].first, PositionKing[CountPosition].second, NewLocation.GetVectorLocationFigure());

                                        // если вектор не пуст значит угрозы есть
                                        if (!PositionEnemyFigure.empty())
                                        {
                                            // угроза есть
                                            Threat = true;                                            
                                        }                                                     
                                    }
                                }
                                //если угроза нашлась откатываем и не передаем ход
                                if (Threat)
                                {
                                    TextInGameRow3.setString(L"на эти координаты нельзя\nпередвинуть фигуру");

                                    auto PositionOld = NewLocation.GetPositionSelectFigure();
                                    NewLocation.SetFigure(
                                                             PositionOld.first, PositionOld.second,
                                                             NewLocation.GetIDFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second),
                                                             NewLocation.GetSideFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second),
                                                             NewLocation.GetInvulnerableFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second),
                                                             NewLocation.GetImportantFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second)
                                                         );

                                    NewLocation.SetFigure(
                                                            CurrentPositionInGameField.first, CurrentPositionInGameField.second,
                                                            TempIDold,
                                                            TempSideold,
                                                            TempInvulnerableold,
                                                            TempImportantold
                                                         );

                                    NewLocation.UnSeletcAllFigure();
                                }
                                else
                                {
                                    // если передвинули и угроз нет проверяем может ли фигура превратиться в другую
                                    if (NewLocation.PromoutionFigureOnPosition(CurrentPositionInGameField.first, CurrentPositionInGameField.second))
                                    {
                                        OldPosition = CurrentPositionInGameField;

                                        NewLocation.SeletcFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second);
                                        NewLocation.SeletcUniqueFigureForPromoution(CurrentPositionInGameField.first, CurrentPositionInGameField.second);

                                        Promoution = true;
                                    }
                                    // если не может превратиться снимаем выделение
                                    else
                                    {
                                        NewLocation.UnSeletcAllFigure();
                                    }
                                    //передаем ход следующему игроку
                                    CurrentPlayer < CountPlayer ? CurrentPlayer++ : CurrentPlayer = 1;                               
                                    TextInGameRow3.setString(L"");
                                }
                            }
                            else
                            {
                                NewLocation.UnSeletcAllFigure();
                            }   
                            ChessField.UnSelectCell();

                            // проводим проверку
                            Check = false;
                        }
                    }
                    else if (Promoution)
                    {

                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // ВРЕМЕННОЕ
                        // выводим информацию о фигуре на игровом поле
                        string Name = NewLocation.GetIDUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second) + "\t";
                        string Coordinate = "X:" + to_string(CurrentgvPositionInUniqueFigureField.first) + " \\ Y:" + to_string(CurrentgvPositionInUniqueFigureField.second);
                        string sideFigure = "\tSIDE: " + to_string(NewLocation.GetSideUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second));
                        
                        string invulnerable = "\nInvulnerable:\t";
                        NewLocation.GetInvulnerableUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second) ? invulnerable += "True" : invulnerable += "False";
                        string Important = "\nImportant:\t\t";
                        NewLocation.GetImportantUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second) ? Important += "True" : Important += "False";
                        
                        TextInGameRow1.setString(Name + Coordinate + sideFigure + invulnerable + Important);
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



                        // сторона передвинутой фигуры должно совпадать с выбранной
                        if ( NewLocation.GetSideFigure(OldPosition.first, OldPosition.second) == NewLocation.GetSideUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second))
                        {
                            if (NewLocation.PromoutionSelectFigure(
                                                                    NewLocation.GetSideUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second),
                                                                    NewLocation.GetIDUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second),
                                                                    NewLocation.GetInvulnerableUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second),
                                                                    NewLocation.GetImportantUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second),
                                                                    NewLocation.GetPromoutionUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second)
                                                                   )
                            )
                            {                                
                                NewLocation.UnSeletcUniqueFigure();
                                NewLocation.UnSeletcAllFigure();
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

        if (Promoution)
        {
            TextInGameRow3.setString(L"Превращение доступно");
        }

        wstring Player = L"\nСейчас ход игрока #" + to_string(CurrentPlayer);
        TextInGameRow2.setString(Player);

        window.clear(Color::White);
        
        window.draw(TextInGameRow1);
        window.draw(TextInGameRow2);
        window.draw(TextInGameRow3);
        window.draw(TextInGameRow4);

        for (size_t row = 0; row < CountCellOnLengthWindow; row++)
        {
            for (size_t coll = 0; coll < CountCellOnLengthWindow; coll++)
            {
                window.draw(ChessField.GetRectangleShapeOnField(coll, row));
                window.draw(ChessField.GetFieldCoordinateOnField(coll, row));
                window.draw(NewLocation.GetRectangleShapeFigure(coll, row));
                window.draw(NewLocation.GetRectangleShapeUniqueFigure(coll, row));
            }
        } 
        window.display(); 
    }

    return 0;
}