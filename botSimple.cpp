#include "bots.h"
void cBotSimple::ChooseNextGridPosition()
{
	if (PositionX() > gTarget.PositionX())
	{
		if (gLevel.isValid(PositionX(), PositionY()) == false) 
		{

		}
		else 
		{
			SetNext((PositionX() + -1), (PositionY()), gLevel);
		}
	}
	else if (PositionX() < gTarget.PositionX())
	{
		if (gLevel.isValid(PositionX(), PositionY()) == false)
		{

		}
		else 
		{
			SetNext((PositionX() + 1), (PositionY()), gLevel);
		}
	}

	else if (PositionY() > gTarget.PositionY())
	{
		if (gLevel.isValid(PositionX(), PositionY()) == false) 
		{

		}
		else
		{
			SetNext((PositionX()), (PositionY() - 1), gLevel);
		}
	}
	else if (PositionY() < gTarget.PositionY())
	{
		if (gLevel.isValid(PositionX(), PositionY()) == false)
		{
		}
		else
		{
			SetNext((PositionX()), (PositionY() + 1), gLevel);
		}
	}
}