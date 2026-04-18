#pragma once

#include "FigureLocation.h"
#include "GameField.h"
#include "propertiesGame.h"


class GameEngine
{
public:
	GameEngine(std::unique_ptr<sf::RenderWindow> rWindow, std::unique_ptr<FigureLocation> location, std::unique_ptr<GameField> gameField);

	/// <summary>
	/// выполнить подсветку фигур, которые угрожают важным фигурам текущего игрока
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
	[[nodiscard]]
	bool isThreat();

	/// <summary>
	/// требуется ли превращение?
	/// </summary>
	/// <returns></returns>
	[[nodiscard]]
	bool promoution() const noexcept;

	/// <summary>
	/// вывести в текст на экране номер текущего игрока
	/// </summary>
	void showCurrnetPlayer() const;

	/// <summary>
	/// получить текущего игрока, которому пренадлежит ход
	/// </summary>
	/// <returns></returns>
	[[nodiscard]]
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
	[[nodiscard]]
	bool isOpen() const;

	/// <summary>
	/// получаем координаты фигуры на позиции мышки на игровой доске
	/// </summary>
	/// <returns></returns>
	Position::Coordinates getFigureOnPositionMouse()  const;

	/// <summary>
	/// получаем коордитаны фигуры на позиции мышки на поле уникальный фигур
	/// </summary>
	/// <returns></returns>
	Position::Coordinates getUniqueFigureOnPositionMouse()  const;

	void setText1(std::wstring message);
	void setText2(std::wstring message);
	void setText3(std::wstring message);
	void setTextDebug(std::wstring message);

	/// <summary>
	/// Очистить окно 
	/// </summary>
	/// <param name="color"></param>
	void clearWindowGame(sf::Color color = sf::Color::White);

	/// <summary>
	/// Отрисовать окно
	/// </summary>
	void drawWindowGame();

	/// <summary>
	/// Отобразить окно
	/// </summary>
	void displayWindowGame();

private:

	/// <summary>
	/// позиции фигур нуждающихся в подсветке
	/// </summary>
	std::vector<Position::Coordinates> m_selectCellForMove = {};

	/// <summary>
	/// позиции фигур противника, которые угрожают фажным фигурам текущего игрока
	/// </summary>
	std::vector<Position::Coordinates> m_positionEnemyFigureThatThreaten = {};

	/// <summary>
	/// позиции важных фигур текущего игрока (currentPlayer)
	/// </summary>
	std::vector<Position::Coordinates> m_allPositionImportantFigures = {};

	std::shared_ptr<sf::Text> m_ptrTextInGameRow1;
	std::shared_ptr<sf::Text> m_ptrTextInGameRow2;
	std::shared_ptr<sf::Text> m_ptrTextInGameRow3;
	std::shared_ptr<sf::Text> m_ptrTextInGameRow4;

	/// <summary>
	/// 
	/// </summary>
	Position::Coordinates m_currentPositionInGameField = { 0, 0 };

	/// <summary>
	/// 
	/// </summary>
	Position::Coordinates m_currentPositionInUniqueFigureField = { 0, 0 };

	/// <summary>
	/// координаты предыдущей позиции x / y
	// </summary>
	Position::Coordinates m_oldPosition = { 0, 0 };

	/// <summary>
	/// окно которым мы можем управлять
	/// </summary>
	std::unique_ptr<sf::RenderWindow> m_ptrRWindow;

	/// <summary>
	/// текущее реальное расположение фигур
	/// </summary>
	std::unique_ptr<FigureLocation> m_ptrLocation;

	/// <summary>
	/// конструкция игрового поля
	/// </summary>
	std::unique_ptr<GameField> m_ptrGameField;

	/// <summary>
	/// текущий игрок, выполняющий ход
	/// </summary>
	int m_currentPlayer = 1;

	/// <summary>
	/// необходимо превращение
	/// </summary>
	bool m_needPomoution = false;

	/// <summary>
	/// Требуется проверка угроз (?) при инициализации считаем - да
	/// </summary>
	bool m_needCheckThreat = true;

	/// <summary>
	/// 
	/// </summary>
	bool m_threat = false;

	/// <summary>
	/// проверка угроз важным фигурам
	/// </summary>
	/// <returns>true - угрозы есть </returns>
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
};
