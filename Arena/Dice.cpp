#include "Dice.h"

#include <random>
#include <time.h>


std::random_device		Dice::m_Dev;
std::mt19937			Dice::m_Gen(Dice::m_Dev());


Dice::Dice()
{
}

Dice::~Dice()
{
}

int Dice::Roll(int dice, int sides)
{
	int total = 0;
	for (int i = 0; i < dice; i++)
		total += Dice::Random(1, sides);

	return total;
}

int Dice::Random(int min, int max)
{
	std::uniform_int_distribution<> dis(min, max);
	return dis(Dice::m_Gen);
}