#include "Main.h"


unordered_map<string, Texture> TextureMap;


int main()
{

    OutputLog("���������");

    ///////////////////////////////////////////////////////////////////////////////////

    /// ������ ����, �� ��� ������� ����� ����
    unsigned int SizeWindowHeight = 1000;

    /// ����� ����
    unsigned int SizeWindowLength = SizeWindowHeight + SizeWindowHeight * 0.5;
    
    /// ���������� ������� ������ �� ����� ������� + 2 ������ ��� ���������
    unsigned int CountCellOnLengthWindow = 8 + 2;   
    unsigned int CountCellOnHeightWindow = 8 + 2;

    ///////////////////////////////////////////////////////////////////////////////////



    ///////////////////////////////////  FONT   /////////////////////////////////////// 
    /// ������������ ��� ������ � ����� 
    vector<path> SearchFont = SearchFile("Font/", ".ttf");

    /// ���� ������� �� ������� ��� ������ ����������
    if (SearchFont.empty())
    {
        OutputLog("����� �� ������, ����������");
        return -1;
    }
    // ���������� ������ � ������ �����
    Font CurrentFont = LoadFont(SearchFont[0]);

    ///////////////////////////////////////////////////////////////////////////////////

    //// ����������� �������� ��� ������������� ���� ////
    path PathToEmptyimage      = "Assets/Standart/Empty.png";
    path PathToEmptyPawn       = "Assets/Standart/EmptyPawn.png";

    /// vector textrue ///



    
    ///////////////////////////////////////////////////////////////////////////////////

    
    /// ����� ������������� � ������ ����
    Text TextInGameRow1(CurrentFont);
    TextInGameRow1.setString(L"TextInGameRow1");
    TextInGameRow1.setCharacterSize(SizeWindowHeight / (CountCellOnLengthWindow * 3));
    TextInGameRow1.setFillColor(Color::Black);
    TextInGameRow1.setPosition(Vector2f(SizeWindowHeight / CountCellOnLengthWindow / 2 + SizeWindowHeight , SizeWindowHeight / CountCellOnLengthWindow));

    /// ����� ������������� �� ������ ����
    Text TextInGameRow2(CurrentFont);
    TextInGameRow2.setString(L"TextInGameRow2");
    TextInGameRow2.setCharacterSize(SizeWindowHeight / (CountCellOnLengthWindow * 3));
    TextInGameRow2.setFillColor(Color::Black);
    TextInGameRow2.setPosition(Vector2f(SizeWindowHeight / CountCellOnLengthWindow / 2+ SizeWindowHeight , SizeWindowHeight / CountCellOnLengthWindow * 2.5));

    /// ����� ������������� �� ������ ����
    Text TextInGameRow3(CurrentFont);
    TextInGameRow3.setString(L"TextInGameRow3");
    TextInGameRow3.setCharacterSize(SizeWindowHeight / (CountCellOnLengthWindow * 3));
    TextInGameRow3.setFillColor(Color::Black);
    TextInGameRow3.setPosition(Vector2f(SizeWindowHeight / CountCellOnLengthWindow / 2+ SizeWindowHeight , SizeWindowHeight / CountCellOnLengthWindow * 3));

    ///////////////////////////////////////////////////////////////////////////////////


    // ������� ����� � ����
    permissions("Log/log.txt", perms::all);
    remove("Log/log.txt");
    OutputLog("������!");

    
    // ������� ���� ����

    /// ���� ����
    RenderWindow window(VideoMode({ SizeWindowLength, SizeWindowHeight }), "Chess");
    window.setFramerateLimit(60);

    /// �������� ������� ���� 
    /// �������� ������ ����������� �������� ����
    GameField ChessField(CountCellOnLengthWindow, SizeWindowHeight, CurrentFont, Color(140, 140, 140), Color::White, Color(152, 118, 84));

    OutputLog("��������� �������� ���� ���������");

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    OutputLog("������������ ����� ������");


    /// ����� � ������ ������������� ����� \ ������������� ��������� ������ 
    /// ��� ���������� ����� ���������� �������� ���������� ������ -> AddUniqueFigure();
    /// � ����������� ����� ���������� ������ �� ������� ����-> SetFigure();

    FigureLocation Newlocation(CountCellOnLengthWindow, CountCellOnHeightWindow, SizeWindowHeight, PathToEmptyimage, PathToEmptyimage, 0.5f);


    //// ������ ��������, ����� ��� ������ ///
    /// ��������� ���������� ������
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



    /// ��������� ������� ���� �������
    // ����������� ������� (������)
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

    OutputLog("������������ ����� ���������");

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

            ///�������� ������ ��� ������� �� ���
            else if (const auto& mouseButtonPressed = event->getIf<Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == Mouse::Button::Left )
                {

                    /// �������� ���������� ������(������ �� ������� ����) �� ������� ������
                    CurrentPositionInGameField = Newlocation.GetPositionFigureWhenMousePressed(MouseWorldPos);

                    /// �������� ���������� ������(������ �� ���� � ����������� ��������) �� ������� ������
                    CurrentgvPositionInUniqueFigureField = Newlocation.GetPositionUniqueFigureWhenMousePressed(MouseWorldPos);



                    // ���� ����� ��������� �� ������ ������ �� ���� ���������� �����
                    if (!Promoution)
                    {


                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // ���������
                        // ������� ���������� � ������ �� ������� ����

                        string Name = Newlocation.GetIDFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second) + " ";
                        string Coordinate = "X:" + to_string(CurrentPositionInGameField.first) + " Y:" + to_string(CurrentPositionInGameField.second);
                        string sideFigure = " Side: " + to_string(Newlocation.GetSideFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second));

                        string invulnerable = "\ninvulnerable: ";
                        Newlocation.GetInvulnerableFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second) ? invulnerable += "true" : invulnerable += "false";

                        wstring Player = L"\n������ ��� ������ #" + to_string(NextPlayer);
                        TextInGameRow1.setString(Name + Coordinate + sideFigure + invulnerable + Player);
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                        //������� � ��������� ������
                        int Side = Newlocation.GetSideFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second);

                        ///�������� �� ��� ������� ���������, ���� �������� �� ��������� ������������ ������
                        if (!Newlocation.FiguresSelectedOrNot() && Side == NextPlayer)
                        {
                            //�������� ��������� ������
                            Newlocation.SeletcFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second);

                            // �������� ������ ��������� �����
                            SelectCellForMove = Newlocation.GetAvailableMovesForSelectFigure();

                            // �������� ��������� ���� �� �����
                            ChessField.SelectCell(SelectCellForMove);


                            DebugCode
                            (
                                ////////////////////////////////////////////////////////////////////////////////////////////////////
                                /// ���������� � ��������� �����                       
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
                            // ������� ������ �� ��������� ���������� ���� ��������
                            if (Newlocation.MoveSelectFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second))
                            {
                                //���� ����������� ��������� ����� �� ������ ������������ � ������
                                if (Newlocation.PromoutionFigureOnPosition(CurrentPositionInGameField.first, CurrentPositionInGameField.second))
                                {
                                    TextInGameRow3.setString(L"����������� ��������");
                                    
                                    OldPosition = CurrentPositionInGameField;

                                    Newlocation.SeletcFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second);
                                    Newlocation.SeletcUniqueFigureForPromoution(CurrentPositionInGameField.first, CurrentPositionInGameField.second);

                                    Promoution = true;
                                }
                                else
                                {
                                    Newlocation.UnSeletcFigure();
                                }

                                //�������� ��� ���������� ������
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
                            ///������� ��������� ���� 
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
                        // ������� ���������� � ������ �� ������� ����
                        string Name = Newlocation.GetIDUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second) + " ";
                        string Coordinate = "X:" + to_string(CurrentgvPositionInUniqueFigureField.first) + " Y:" + to_string(CurrentgvPositionInUniqueFigureField.second);
                        string sideFigure = " Side: " + to_string(Newlocation.GetSideUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second));
                        string invulnerable = "\ninvulnerable: ";
                        Newlocation.GetInvulnerableUniqueFigure(CurrentPositionInGameField.first, CurrentPositionInGameField.second) ? invulnerable += "true" : invulnerable += "false";
                        TextInGameRow1.setString(Name + Coordinate + sideFigure + invulnerable);
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                        // ������� ������������ ������ ������ ��������� � ���������
                        if ( Newlocation.GetSideFigure(OldPosition.first, OldPosition.second) == Newlocation.GetSideUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second))
                        {
                            if (Newlocation.PromoutionSelectFigure(Newlocation.GetIDUniqueFigure(CurrentgvPositionInUniqueFigureField.first, CurrentgvPositionInUniqueFigureField.second)))
                            {                                
                                Newlocation.UnSeletcUniqueFigure();
                                Newlocation.UnSeletcFigure();
                                Promoution = false;
                                TextInGameRow3.setString(L"����������� ���������");
                            }
                            else
                            {
                                TextInGameRow3.setString(L"����������� ����������\n� ��� ������");
                            }
                        }
                        else
                        {
                            TextInGameRow3.setString(L"�������� ������");
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