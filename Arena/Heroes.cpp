#include "Heroes.h"
#include "Global.h"

#include <fstream>


using namespace std;


Heroes::Heroes()
{
}

Heroes::~Heroes()
{
}

vector<HeroInfo> Heroes::Load(const std::string &filename)
{
	vector<HeroInfo> heroes;
	ifstream *file = new ifstream(filename, ios::binary);

	if (!file->is_open())
	{
		SAFE_DELETE(file);
		return heroes;
	}

	HeroInfo hero;
	while (file->read((char *)&hero, sizeof(HeroInfo)))
		heroes.push_back(hero);

	file->close();
	SAFE_DELETE(file);

	return heroes;
}

void Heroes::Save(const string &filename, const HeroInfo &hero)
{
	ofstream *file = new ofstream(filename, ios::app | ios::binary);

	if (!file->is_open())
	{
		SAFE_DELETE(file);
		return;
	}

	file->write((char *)&hero, sizeof(HeroInfo));

	file->flush();
	file->close();

	SAFE_DELETE(file);

	return;
}