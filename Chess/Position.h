#pragma once

#include "Core.h"

namespace Position {

	/// <summary>
	/// структура для хранения позиции, располагает переменные { y, x }
	/// позиция 0, 0 обозначает левый вверх
	/// </summary>
	struct Coordinates
	{
		/// <summary>
		/// позиция ряд
		/// </summary>
		size_t inRow = 0;

		/// <summary>
		/// позиция столбец
		/// </summary>
		size_t inColum = 0;
		
		Coordinates() = default;

		Coordinates(size_t y, size_t x) : inRow(y), inColum(x) {};

		void moveRight() { inColum++; }
		void moveLeft() { inColum == 0 ? inColum = 0 : inColum--; }
		void moveDown() { inRow++; }
		void moveUp() { inRow == 0 ? inRow = 0 : inRow--; }

		void moveDiagUpLeft() { inRow--; inColum--; }
		void moveDiagUpRight() { inRow--; inColum++; }
		void moveDiagDownLeft() { inRow++; inColum--; }
		void moveDiagDownRight() { inRow++; inColum++; }

		bool operator==(const Coordinates& other) const
		{
			return inRow == other.inRow && inColum == other.inColum;
		}
		Coordinates operator+(const Coordinates& other) const
		{
			return 	{ inRow + other.inRow, inColum + other.inColum };
		}
		Coordinates operator+(const std::pair<int, int> offset) const
		{
			int y = static_cast<int>(inRow) + offset.first;
			int x = static_cast<int>(inColum) + offset.second;

			if (y < 0) { y = 0; }
			if (x < 0) { x = 0; }
			return { static_cast<size_t>(y), static_cast<size_t>(x) };
		}
		Coordinates operator-(const Coordinates& other) const
		{
			return
			{
				(inRow >= other.inRow) ? inRow - other.inRow : 0,
				(inColum >= other.inColum) ? inColum - other.inColum : 0
			};
		}
	};

	/// <summary>
	/// переменная "сдвиг" для Coordinates { inRow, inColum }
	/// </summary>
	inline std::pair<int, int>offsetLeftBy(unsigned short step = 1) { return { 0, -step }; }

	/// <summary>
	/// переменная "сдвиг" для Coordinates { inRow, inColum }
	/// </summary>
	inline std::pair<int, int>OffsetRightBy(unsigned short  step = 1) { return{ 0, step }; }

	/// <summary>
	/// переменная "сдвиг" для Coordinates { inRow, inColum }
	/// </summary>
	inline std::pair<int, int>OffsetUpBy(unsigned short  step = 1) { return { -step, 0 }; }

	/// <summary>
	/// переменная "сдвиг" для Coordinates { inRow, inColum }
	/// </summary>
	inline std::pair<int, int>OffsetDownBy(unsigned short  step = 1) { return  { step, 0 }; }

	/// <summary>
	/// переменная "сдвиг" для Coordinates { inRow, inColum }
	/// </summary>
	inline std::pair<int, int>OffsetDiagUpLeftBy(unsigned short  step = 1) { return { -step, -step }; }

	/// <summary>
	/// переменная "сдвиг" для Coordinates { inRow, inColum }
	/// </summary>
	inline std::pair<int, int>OffsetDiagUpRightBy(unsigned short  step = 1) { return { -step, step }; }

	/// <summary>
	/// переменная "сдвиг" для Coordinates { inRow, inColum }
	/// </summary>
	inline std::pair<int, int>OffsetDiagDownLeftBy(unsigned short  step = 1) { return { step, -step }; }

	/// <summary>
	/// переменная "сдвиг" для Coordinates { inRow, inColum }
	/// </summary>
	inline std::pair<int, int>OffsetDiagDownRightBy(unsigned short  step = 1) { return { step, step }; }
}