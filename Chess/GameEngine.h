#pragma once

#include "FigureLocation.h"
#include "GameField.h"
#include "propertiesGame.h"



/// <summary>
/// основной движок игры
/// </summary>
class GameEngine
{
public:


	GameEngine(std::unique_ptr<sf::RenderWindow> rWindow, std::unique_ptr<FigureLocation> location, std::unique_ptr<GameField> gameField);

	/// <summary>
	/// выполнить подсветку фигур (чаще при угрозе)
	/// </summary>
	/// <returns></returns>
	bool performBacklightThreat();

	/// <summary>
	/// выполнить ход игрока
	/// </summary>
	void performMovePlayer();


	/// <summary>
	/// выполнить превращение (если доступно)
	/// </summary>
	void performPromouten();






	/// <summary>
	/// получить положение мышки
	/// </summary>
	/// <returns></returns>
	sf::Vector2i getPositionMouse() const;

	/// <summary>
	/// получить положение мышки
	/// </summary>
	/// <returns></returns>
	sf::Vector2f getWorldPositionMouse() const;







	/// <summary>
	/// есть ли какая-то угроза важным фигурам текущего игрока?
	/// </summary>
	/// <returns></returns>
	bool isThreat();








	/// <summary>
	/// требуется ли превращение?
	/// </summary>
	/// <returns></returns>
	bool promoution() const noexcept;









	/// <summary>
	/// вывести в текст на экране номер текущего игрока
	/// </summary>
	void showCurrnetPlayer() const;

	/// <summary>
	/// получить текущего игрока, которому пренадлежит ход
	/// </summary>
	/// <returns></returns>
	int getCurrentPlayer() const noexcept;

	/// <summary>
	/// установить текущего игрока, которому будет принадлежать ход
	/// </summary>
	/// <param name="player"></param>
	void setCurrentPlayer(int player);

	/// <summary>
	/// передать ход следующему игроку
	/// </summary>
	void nextPlayer();







	/// <summary>
	/// получить текущий ивент с RenderWindow
	/// </summary>
	/// <returns></returns>
	std::optional<sf::Event> getEvent()  const;

	/// <summary>
	/// закрыть окно игры
	/// </summary>
	void closeGame();

	/// <summary>
	/// открыто ли окно игры?
	/// </summary>
	/// <returns></returns>
	bool isOpen() const;








	/// <summary>
	/// получаем координаты фигуры на позиции мышки на игровой доске
	/// </summary>
	/// <returns></returns>
	std::pair<size_t, size_t> getFigureOnPositionMouse()  const;

	/// <summary>
	/// получаем коордитаны фигуры на позиции мышки на поле уникальный фигур
	/// </summary>
	/// <returns></returns>
	std::pair<size_t, size_t> getUniqueFigureOnPositionMouse()  const;




	void setText1(std::wstring message);

	void setText2(std::wstring message);

	void setText3(std::wstring message);

	void setText4(std::wstring message);








	void clearWindowGame(sf::Color color);

	void drawWindowGame();

	void displayWindowGame();

	

private:

	/// <summary>
	/// проверка угроз важным фигурам
	/// </summary>
	bool checkThreat();

	/// <summary>
	/// изменить значение нужды превращения
	/// </summary>
	/// <param name="promoution"></param>
	void setPromoution(bool promoution);

	/// <summary>
	/// изменить значение угрозы
	/// </summary>
	/// <param name="threat"></param>
	void setThreat(bool threat);




	/// <summary>
	/// окно которым мы можем управлять
	/// </summary>
	std::unique_ptr<sf::RenderWindow> rWindow;

	/// <summary>
	/// текущее реальное расположение фигур
	/// </summary>
	std::unique_ptr<FigureLocation> location;

	/// <summary>
	/// конструкция игрового поля
	/// </summary>
	std::unique_ptr<GameField> gameField;



	std::shared_ptr<sf::Text> textInGameRow1;
	std::shared_ptr<sf::Text> textInGameRow2;
	std::shared_ptr<sf::Text> textInGameRow3;
	std::shared_ptr<sf::Text> textInGameRow4;

		
	/// <summary>
	/// позиции фигур нуждающихся в подсветке
	/// </summary>
	std::vector<std::pair<size_t, size_t>> selectCellForMove;

	/// <summary>
	/// позиции фигур противника, которые угрожают фажным фигурам текущего игрока
	/// </summary>
	std::vector<std::pair<size_t, size_t>> positionEnemyFigureThatThreaten;

	/// <summary>
	/// позиции важных фигур текущего игрока (currentPlayer)
	/// </summary>
	std::vector<std::pair<size_t, size_t>> positionImportantFigure;


	/// <summary>
	/// 
	/// </summary>
	std::pair<size_t, size_t> currentPositionInGameField;

	/// <summary>
	/// 
	/// </summary>
	std::pair<size_t, size_t> currentPositionInUniqueFigureField;


	
	/// <summary>
	/// координаты предыдущей позиции x / y
	/// </summary>
	std::pair<size_t, size_t> oldPosition;

	
	/// <summary>
	/// необходимо превращение
	/// </summary>
	bool needPomoution = false;


	/// <summary>
	/// текущий игрок, выполняющий ход
	/// </summary>
	int currentPlayer = 1;




	/// <summary>
	/// Требуется проверка угроз (?) при инициализации считаем - да
	/// </summary>
	bool needCheckThreat = true;



	/// <summary>
	/// 
	/// </summary>
	bool threat = false;

};
