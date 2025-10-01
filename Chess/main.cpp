#include "Main.h"


unordered_map<string, Texture> g_TextureMap;


int main()
{

    // создаем вывод в логи
    permissions("Log/log.txt", perms::all);
    remove("Log/log.txt");
    OutputLog("Запуск!");

    ///////////////////////////////////////////////////////////////////////////////////

    /// высота окна, от нее зависит длина окна
    unsigned int sizeWindowHeight = 1000;

    /// длина окна
    unsigned int sizeWindowLength = static_cast<unsigned int>(round(sizeWindowHeight * 1.7));
    
    /// количество ИГРОВЫХ клеток на одной стороне + 2 клетки для координат
    size_t countCellOnLengthWindow = 8 + 2;
    size_t countCellOnHeightWindow = 8 + 2;

    ///////////////////////////////////////////////////////////////////////////////////



    ///////////////////////////////////  FONT   /////////////////////////////////////// 
    /// обнаруживаем все шрифты в папке 
    vector<path> searchFont = searchFile("Font/", ".ttf");

    /// если шрифтов не найдено вых
    if (searchFont.empty())
    {
        OutputLog("Шрифт не найден, завершение");
        return -1;
    }
    // используем первый в списке шрифт
    Font currentFont = loadFont(searchFont[0]);

    ///////////////////////////////////////////////////////////////////////////////////

    //// стандартные текстуры для инициализации игры ////
    path pathToEmptyimage      = "Assets/Standart/Empty.png";
    path pathToEmptyPawn       = "Assets/Standart/EmptyPawn.png";

    /// vector textrue ///



    
    ///////////////////////////////////////////////////////////////////////////////////

    
    /// текст расположенный в первом ряду
    Text textInGameRow1(currentFont);
    textInGameRow1.setString(L"-");
    textInGameRow1.setCharacterSize(static_cast<unsigned int>(sizeWindowHeight / (countCellOnLengthWindow * 3)));
    textInGameRow1.setFillColor(Color::Black);
    textInGameRow1.setPosition(Vector2f(static_cast<float>(sizeWindowHeight / countCellOnLengthWindow / 2 + sizeWindowHeight) , static_cast<float>(sizeWindowHeight / countCellOnLengthWindow)));

    /// текст расположенный во втором ряду
    Text textInGameRow2(currentFont);
    textInGameRow2.setString(L"-");
    textInGameRow2.setCharacterSize(static_cast<unsigned int>(sizeWindowHeight / (countCellOnLengthWindow * 3)));
    textInGameRow2.setFillColor(Color::Black);
    textInGameRow2.setPosition(Vector2f(static_cast<float>(sizeWindowHeight / countCellOnLengthWindow / 2 + sizeWindowHeight), static_cast<float>(sizeWindowHeight / countCellOnLengthWindow * 2)));

    /// текст расположенный во 3 ряду
    Text textInGameRow3(currentFont);
    textInGameRow3.setString(L"-");
    textInGameRow3.setCharacterSize(static_cast<unsigned int>(sizeWindowHeight / (countCellOnLengthWindow * 3)));
    textInGameRow3.setFillColor(Color::Black);
    textInGameRow3.setPosition(Vector2f(static_cast<float>(sizeWindowHeight / countCellOnLengthWindow / 2 + sizeWindowHeight), static_cast<float>(sizeWindowHeight / countCellOnLengthWindow * 3)));


    /// текст расположенный во 4 ряду
    Text textInGameRow4(currentFont);
    textInGameRow4.setString(L"-");
    textInGameRow4.setCharacterSize(static_cast<unsigned int>(sizeWindowHeight / (countCellOnLengthWindow * 3)));
    textInGameRow4.setFillColor(Color::Black);
    textInGameRow4.setPosition(Vector2f(static_cast<float>(sizeWindowHeight / countCellOnLengthWindow / 2 + sizeWindowHeight), static_cast<float>(sizeWindowHeight / countCellOnLengthWindow * 4)));

    ///////////////////////////////////////////////////////////////////////////////////



    
    // создаем окно игры

    /// Окно игры
    RenderWindow window(VideoMode({ sizeWindowLength, sizeWindowHeight }), "Chess");
    window.setFramerateLimit(60);

    /// основное игровое поле 
    /// содержит только конструкцию игрового поля
    GameField chessField(countCellOnLengthWindow, sizeWindowHeight, currentFont, Color(140, 140, 140), Color::White, Color(152, 118, 84));

    OutputLog("Инициация Игрового поля закончено");

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    OutputLog("Расположение Фигур начато");


    /// класс с полным расположением фигур \ первоначально создается пустым 
    /// для размещения фигур необходимо добавить уникальные фигуры -> AddUniqueFigure();
    /// в последствии можно установить фигуры на игровое поле-> SetFigure();

    FigureLocation newLocation(countCellOnLengthWindow, countCellOnHeightWindow, sizeWindowHeight, pathToEmptyimage, pathToEmptyimage, 0.5f);


    //// другие текстуры, такие как фигуры ///
    /// добавляем уникальные фигуры


    // превращения для пешки \ по умолчанию может превратиться в 4 стандартные фигуры
    vector<tuple<int, string, bool, bool, bool>> promoutionForPawn1 =
    {
        make_tuple(1, "Rook", false, false, false),
        make_tuple(1, "Queen", false, false, false),
        make_tuple(1, "Knight", false, false, false),
        make_tuple(1, "Bishop", false, false, false),
    };
    // превращения для пешки \ по умолчанию может превратиться в 4 стандартные фигуры
    vector<tuple<int, string, bool, bool, bool>> promoutionForPawn2 =
    {
        make_tuple(2, "Rook", false, false, false),
        make_tuple(2, "Queen", false, false, false),
        make_tuple(2, "Knight", false, false, false),
        make_tuple(2, "Bishop", false, false, false),
    };


    vector<pair<shared_ptr<Figure>, path>> addFigure =
    {
        make_pair(make_shared<Pawn>(1, false, false, promoutionForPawn1), "Assets/pawn-white.png"),
        make_pair(make_shared<Pawn>(2, false, false, promoutionForPawn2), "Assets/pawn-black.png"),
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


    for (const auto& figure : addFigure)
    {
        newLocation.addUniqueFigure(figure.first, figure.second);
    }

    /// заполняем игровое поле пешками

    // колличество игроков (Сторон)
    const int COUNT_PLAYER = 2;

    for (size_t row = 0; row < countCellOnHeightWindow; row++)
    {
        for (size_t coll = 0; coll < countCellOnLengthWindow; coll++)
        {        
            string NAME = "figure";
            bool INVULNERABLE = false;
            bool IMPORTANT = false;

            if      (coll == 1 || coll == countCellOnLengthWindow - 2)   NAME = "Rook";
            else if (coll == 2 || coll == countCellOnLengthWindow - 3)   NAME = "Knight";
            else if (coll == 3 || coll == countCellOnLengthWindow - 4)   NAME = "Bishop";
            else if (coll == 4)                                          NAME = "Queen";

            else if (coll == 5) { NAME = "King"; INVULNERABLE = true; IMPORTANT = true; }

            if (row == 2)
            {   
                newLocation.setFigure(coll, row, "Pawn", 2, false, false, promoutionForPawn1);
            }
            else if (row == countCellOnHeightWindow -3)
            {
                newLocation.setFigure(coll, row, "Pawn", 1, false, false, promoutionForPawn2);
            } 
            else if (row == 1)
            {
                newLocation.setFigure(coll, row, NAME, 2, INVULNERABLE, IMPORTANT);
            }
            else if (row == countCellOnHeightWindow - 2)
            {
                newLocation.setFigure(coll, row, NAME, 1, INVULNERABLE, IMPORTANT);
            }
        }
    }

    OutputLog("Расположение Фигур закончено");

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     

    Vector2i positionMouse;
    Vector2f mouseWorldPos;


    countdownTimer timerCD1;


    vector<pair<size_t, size_t>>  selectCellForMove;



    //
    vector<pair<size_t, size_t>> positionEnemyFigure;

    vector<pair<size_t, size_t>> positionKing = { make_pair(0,0) };
    //

    // доступно ли превращение?
    bool promoution = false;

    int currentPlayer = 1;
    bool check = false;

    // x / y
    pair<int, int> oldPosition;


    while (window.isOpen())
    {
        positionMouse = Mouse::getPosition(window);
        mouseWorldPos = window.mapPixelToCoords(positionMouse);

        // x / y
        pair<int, int> currentPositionInGameField;
        // x / y
        pair<int, int> currentgvPositionInUniqueFigureField;

        
        

        //проверяем угрожает ли что-то ВАЖНЫМ ( Important ) ФИГУРАМ у текущего игрока 

        //проводим проверку единожды для текущего игрока

        if (!check)
        {
            // считаем что проверку выполнили            
            check = true;

            //получаем расположение важных ФИГУР ( "король" - могут быть и другие) текущего игрока
            positionKing = newLocation.getPositionsFigure(currentPlayer, true, 'M');


            // получаем расположение фигур 
            vector<vector<tuple<int, string, bool, bool, bool>>> locationFigureInGame = newLocation.getVectorLocationFigure();


            // => далее необходимо получить позиции фигур противников, которые могут угрожать королю, и выделяем их клетки в GameField
            // можно сделать аналогичные проверки для любых фигур

            if (!positionKing.empty())
            {
                // стандартно существует единственый экземпляр ВАЖНЫХ ФИГУРЫ - король, на каждой стороне, но может быть и несколько :) -> проводим цикл
                // так же королей может не быть и в цикл не входим т.к. вектор будет пустой

                for (const auto& currentPosition : positionKing)
                {
                    // получаем позиции фигур противников которые "угрожают" текущей важной фигуре взятием
                    positionEnemyFigure = newLocation.checkThreatFigure(currentPosition.first, currentPosition.second, locationFigureInGame);

                    for (const auto& cPosition : positionEnemyFigure)
                    {
                        // выделяем клетки на которых стоят эти фигуры
                        chessField.selectCell(cPosition.first, cPosition.second, Color::Red);
                        chessField.selectCell(currentPosition.first, currentPosition.second, Color::Red);
                        textInGameRow3.setString(L"поставлен шах");                   
                    }


                    // получаем позиции фигур которые могут защитить указанную (
                    auto positionFrendlyFigure = newLocation.figureCanProtectenCheckmateForFigure(currentPosition.first, currentPosition.second, locationFigureInGame);
                    
                    for (const auto& currentPos : positionFrendlyFigure)
                    {
                        chessField.selectCell(currentPos.first, currentPos.second, Color::Green);
                    }

                    if (positionFrendlyFigure.size() == 1 && positionFrendlyFigure[0] == pair(size_t(0),size_t(0)))
                    {
                        wstring checkmatePlayer = L"поставлен мат игроку: " + to_wstring(currentPlayer);
                        textInGameRow4.setString(checkmatePlayer);
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
            else if (const auto& mouseButtonPressed = event->getIf<Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == Mouse::Button::Left )
                {
                    /// получаем координаты фигуры(клетки на игровом поле) по которой нажали
                    currentPositionInGameField = newLocation.getPositionFigureWhenMousePressed(mouseWorldPos);

                    /// получаем координаты фигуры(клетки на поле с уникальными фигурами) по которой нажали
                    currentgvPositionInUniqueFigureField = newLocation.getPositionUniqueFigureWhenMousePressed(mouseWorldPos);

                    if (!promoution)
                    {

                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // ВРЕМЕННОЕ
                        // выводим информацию о фигуре на игровом поле
                        string name = newLocation.getIDFigure(currentPositionInGameField.first, currentPositionInGameField.second) + "\t";
                        string coordinate = "X:" + to_string(currentPositionInGameField.first) + " \\ Y:" + to_string(currentPositionInGameField.second);
                        string sideFigure = "\tSIDE: " + to_string(newLocation.getSideFigure(currentPositionInGameField.first, currentPositionInGameField.second));


                        string invulnerable = "\nInvulnerable:\t";
                        newLocation.getInvulnerableFigure(currentPositionInGameField.first, currentPositionInGameField.second) ? invulnerable += "True" : invulnerable += "False";
                        string Important = "\nImportant:\t\t";
                        newLocation.getImportantFigure(currentPositionInGameField.first, currentPositionInGameField.second) ? Important += "True" : Important += "False";

                        textInGameRow1.setString(name + coordinate + sideFigure + invulnerable + Important);
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


                        //сторона у выбранной фигуры
                        int side = newLocation.getSideFigure(currentPositionInGameField.first, currentPositionInGameField.second);

                        /// выделяем ее или снимаем выделение, если выделено то ожидается передвижение фигуры
                        /// так же должна совпадать сторона игрока который сейчас ходит, для выделения
                        if (!newLocation.figuresSelectedOrNot() && side == currentPlayer)
                        {
                            //выделяем выбранную фигуру
                            newLocation.seletcFigure(currentPositionInGameField.first, currentPositionInGameField.second);

                            // получаем вектор доступных ходов
                            auto positionSelectFigure = newLocation.getPositionSelectFigure();

                            selectCellForMove = newLocation.getAvailableMovesForFigure(positionSelectFigure.first, positionSelectFigure.second);

                            // выделяем доступные ходы на доске
                            for (const auto& onePos : selectCellForMove)
                            {
                                chessField.selectCell(onePos.first, onePos.second, Color::Red);
                            }  
                        }
                        else if (newLocation.figuresSelectedOrNot())
                        {
                            // создаем копию фигуры на случай если ход выполнен в угрозу своим важным фигурам
                            string tempIDold           = newLocation.getIDFigure(currentPositionInGameField.first, currentPositionInGameField.second);
                            int    tempSideold         = newLocation.getSideFigure(currentPositionInGameField.first, currentPositionInGameField.second);
                            bool   tempInvulnerableold = newLocation.getInvulnerableFigure(currentPositionInGameField.first, currentPositionInGameField.second);
                            bool   tempImportantold    = newLocation.getImportantFigure(currentPositionInGameField.first, currentPositionInGameField.second);

                            // двигаем фигуру на выбранные координаты если возможно
                            if (newLocation.moveSelectFigure(currentPositionInGameField.first, currentPositionInGameField.second))
                            {
                                //передвинули
                                //если что-то так же осталось угрожать важным фигурам откатываем передвижение
                                bool threat = false;


                                //получаем расположение ВАЖНЫХ ФИГУР ( "король" - могут быть и другие) текущего игрока
                                positionKing = newLocation.getPositionsFigure(currentPlayer, true, 'M');


                                if (!positionKing.empty())
                                {
                                    for (int countPosition = 0; countPosition < positionKing.size() && !threat; countPosition++)
                                    {
                                        // получаем позиции фигур противников которые "угрожают" важной фигуре взятием
                                        positionEnemyFigure = newLocation.checkThreatFigure(positionKing[countPosition].first, positionKing[countPosition].second, newLocation.getVectorLocationFigure());

                                        // если вектор не пуст значит угрозы есть
                                        if (!positionEnemyFigure.empty())
                                        {
                                            // угроза есть
                                            threat = true;                                            
                                        }                                                     
                                    }
                                }
                                //если угроза нашлась откатываем и не передаем ход
                                if (threat)
                                {
                                    textInGameRow3.setString(L"на эти координаты нельзя\nпередвинуть фигуру");

                                    auto positionOld = newLocation.getPositionSelectFigure();
                                    newLocation.setFigure(
                                                             positionOld.first, positionOld.second,
                                                             newLocation.getIDFigure(currentPositionInGameField.first, currentPositionInGameField.second),
                                                             newLocation.getSideFigure(currentPositionInGameField.first, currentPositionInGameField.second),
                                                             newLocation.getInvulnerableFigure(currentPositionInGameField.first, currentPositionInGameField.second),
                                                             newLocation.getImportantFigure(currentPositionInGameField.first, currentPositionInGameField.second)
                                                         );

                                    newLocation.setFigure(
                                                            currentPositionInGameField.first, currentPositionInGameField.second,
                                                            tempIDold,
                                                            tempSideold,
                                                            tempInvulnerableold,
                                                            tempImportantold
                                                         );

                                    newLocation.unSeletcAllFigure();
                                }
                                else
                                {
                                    // если передвинули и угроз нет проверяем может ли фигура превратиться в другую
                                    if (newLocation.promoutionFigureOnPosition(currentPositionInGameField.first, currentPositionInGameField.second))
                                    {
                                        oldPosition = currentPositionInGameField;

                                        newLocation.seletcFigure(currentPositionInGameField.first, currentPositionInGameField.second);
                                        newLocation.seletcUniqueFigureForPromoution(currentPositionInGameField.first, currentPositionInGameField.second);

                                        promoution = true;
                                    }
                                    // если не может превратиться снимаем выделение
                                    else
                                    {
                                        newLocation.unSeletcAllFigure();
                                    }
                                    //передаем ход следующему игроку
                                    currentPlayer < COUNT_PLAYER ? currentPlayer++ : currentPlayer = 1;                               
                                    textInGameRow3.setString(L"");
                                }
                            }
                            else
                            {
                                newLocation.unSeletcAllFigure();
                            }   
                            chessField.unSelectCell();

                            // проводим проверку
                            check = false;
                        }
                    }
                    else if (promoution)
                    {

                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // ВРЕМЕННОЕ
                        // выводим информацию о фигуре на игровом поле
                        string name = newLocation.getIDUniqueFigure(currentgvPositionInUniqueFigureField.first, currentgvPositionInUniqueFigureField.second) + "\t";
                        string coordinate = "X:" + to_string(currentgvPositionInUniqueFigureField.first) + " \\ Y:" + to_string(currentgvPositionInUniqueFigureField.second);
                        string sideFigure = "\tSIDE: " + to_string(newLocation.getSideUniqueFigure(currentgvPositionInUniqueFigureField.first, currentgvPositionInUniqueFigureField.second));
                        
                        string invulnerable = "\nInvulnerable:\t";
                        newLocation.getInvulnerableUniqueFigure(currentgvPositionInUniqueFigureField.first, currentgvPositionInUniqueFigureField.second) ? invulnerable += "True" : invulnerable += "False";
                        string important = "\nImportant:\t\t";
                        newLocation.getImportantUniqueFigure(currentgvPositionInUniqueFigureField.first, currentgvPositionInUniqueFigureField.second) ? important += "True" : important += "False";
                        
                        textInGameRow1.setString(name + coordinate + sideFigure + invulnerable + important);
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



                        // сторона передвинутой фигуры должно совпадать с выбранной
                        if ( newLocation.getSideFigure(oldPosition.first, oldPosition.second) == newLocation.getSideUniqueFigure(currentgvPositionInUniqueFigureField.first, currentgvPositionInUniqueFigureField.second))
                        {
                            if (newLocation.PromoutionSelectFigure(
                                                                    newLocation.getSideUniqueFigure(currentgvPositionInUniqueFigureField.first, currentgvPositionInUniqueFigureField.second),
                                                                    newLocation.getIDUniqueFigure(currentgvPositionInUniqueFigureField.first, currentgvPositionInUniqueFigureField.second),
                                                                    newLocation.getInvulnerableUniqueFigure(currentgvPositionInUniqueFigureField.first, currentgvPositionInUniqueFigureField.second),
                                                                    newLocation.getImportantUniqueFigure(currentgvPositionInUniqueFigureField.first, currentgvPositionInUniqueFigureField.second),
                                                                    newLocation.getPromoutionUniqueFigure(currentgvPositionInUniqueFigureField.first, currentgvPositionInUniqueFigureField.second)
                                                                   )
                            )
                            {                                
                                newLocation.unSeletcUniqueFigure();
                                newLocation.unSeletcAllFigure();
                                promoution = false;
                                textInGameRow3.setString(L"превращение выполнено");
                            }
                            else
                            {
                                textInGameRow3.setString(L"превращение невозможно\nв эту фигуру");
                            }
                        }
                        else
                        {
                            textInGameRow3.setString(L"неверная фигура");
                        }
                    }
                }
            }
        }

        if (promoution)
        {
            textInGameRow3.setString(L"Превращение доступно");
        }

        wstring player = L"\nСейчас ход игрока #" + to_string(currentPlayer);
        textInGameRow2.setString(player);

        window.clear(Color::White);
        
        window.draw(textInGameRow1);
        window.draw(textInGameRow2);
        window.draw(textInGameRow3);
        window.draw(textInGameRow4);

        for (size_t row = 0; row < countCellOnLengthWindow; row++)
        {
            for (size_t coll = 0; coll < countCellOnLengthWindow; coll++)
            {
                window.draw(chessField.getRectangleShapeOnField(coll, row));
                window.draw(chessField.getFieldCoordinateOnField(coll, row));
                window.draw(newLocation.getRectangleShapeFigure(coll, row));
                window.draw(newLocation.getRectangleShapeUniqueFigure(coll, row));
            }
        } 
        window.display(); 
    }

    return 0;
}