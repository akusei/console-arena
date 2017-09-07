#pragma once
#ifndef DICE_H
#define DICE_H

#include <random>


class Dice
{
public:
	static int Roll(int dice, int sides);
	static int Random(int min, int max);


private:
	static std::random_device	m_Dev;
	static std::mt19937			m_Gen;

	Dice();
	~Dice();
};

#endif