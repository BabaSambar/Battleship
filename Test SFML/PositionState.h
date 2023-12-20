#pragma once

enum class PositionStateVisible: int
{
	Blank = 0,
	Revealed = 1,
	Intact = 2,
	Destroying = 3,
	Destroyed = 4
};
enum class PositionStateHidden: int
{
	False = 0,
	Ship1 = 1,
	Ship2 = 2,
	Ship3 = 3,
	Ship4 = 4,
	Ship5 = 5
};
