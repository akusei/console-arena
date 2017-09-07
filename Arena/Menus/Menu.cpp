#include "Menu.h"

#include <vector>


using namespace std;


Menu::Menu(string title, Player &player, ConLib &console) : m_Player(player), m_Console(console), m_Title(title)
{
	this->m_LargestItem = this->m_Console.LengthWithoutColor(title);
}

Menu::~Menu()
{
	this->ClearItems();
}

string Menu::AddTab(const string &text)
{
	string ret;
	int size = this->m_Console.LengthWithoutColor(text);
	int spaces = size % 8;
	spaces = 8 - spaces; //(int)(((double)text.size() / (double)8) + 0.5);

	ret.append(spaces, ' ');

	return ret;
}

void Menu::ClearItems()
{
	if (!this->m_Shortcuts.empty())
		this->m_Shortcuts.clear();

	if (!this->m_MenuItems.empty())
		this->m_MenuItems.clear();

	this->m_LargestItem = 0;
}

void Menu::AddItem()
{
	this->m_MenuItems.push_back("");
}

void Menu::AddItem(const string &text)
{
	int size = this->m_Console.LengthWithoutColor(text);
	if (size > this->m_LargestItem)
		this->m_LargestItem = size;

	this->m_MenuItems.push_back(text);
}

void Menu::AddItem(const string &shortcut, const string &item, HandlerCast callback)
{
	int size = this->m_Console.LengthWithoutColor(item);
	if (size > this->m_LargestItem)
		this->m_LargestItem = size;

	this->m_Shortcuts.insert(pair<const string &, HandlerCast>(shortcut, callback));
	this->m_MenuItems.push_back(item);
}

void Menu::ClearViewPort() const
{
	//This should not be hard coded like this
	this->m_Console.Clear(1, 3, 78, 21);
	this->SetInputPos();

}

void Menu::ClearTitle() const
{
	//This should not be hard coded like this
	this->m_Console.Clear(1, 1, 78, 1);
	this->SetInputPos();

}

void Menu::ClearInput(bool clearAll) const
{
	int x = STARTINPUTBAR;
	int width = INPUTBARWIDTH;
	if (!clearAll)
	{
		x = STARTINPUT;
		width -= STARTINPUT;
	}

	this->m_Console.Clear(x, 24, width, 1);
	this->SetInputPos();
}

void Menu::ClearError() const
{
	this->ClearInput(false);
}

void Menu::SetInputPos() const
{
	COORD pos;
	pos.X = STARTINPUT;
	pos.Y = this->m_Console.Height();
	this->m_Console.SetPosition(pos);
	this->m_Console.SetTextColor(BRIGHTWHITE);
}

void Menu::DrawTitle() const
{
	this->DrawTitle(this->m_Title);
}

void Menu::DrawTitle(const string &title) const
{
	this->ClearTitle();

	short width = this->m_Console.Width();
	short height = this->m_Console.Height();

	int viewPort = width - 1;
	int start = viewPort / 2;
	start -= this->m_Console.LengthWithoutColor(title) / 2;

	COORD pos;
	pos.X = start;
	pos.Y = 1;
	this->m_Console.SetPosition(pos);

	this->m_Console << title;
}

void Menu::DrawBorder() const
{
	this->m_Console.Clear();
	this->m_Console.SetTextColor(BRIGHTWHITE);

	short width = this->m_Console.Width();
	short height = this->m_Console.Height();
	COORD pos;

	pos.X = 0;
	pos.Y = 0;
	this->m_Console.SetPosition(pos);
	for (short i = 0; i <= width; i++)
		this->m_Console << BORDER;

	for (short i = 1; i < height; i++)
	{
		pos.X = 0;
		pos.Y = i;
		this->m_Console.SetPosition(pos);
		this->m_Console << BORDER;
		pos.X = width;
		this->m_Console.SetPosition(pos);
		this->m_Console << BORDER;
	}

	pos.X = 0;
	pos.Y = height;
	this->m_Console.SetPosition(pos);
	for (short i = 0; i <= width; i++)
		this->m_Console << BORDER;

	pos.X = 0;
	pos.Y = 2;
	this->m_Console.SetPosition(pos);
	for (short i = 0; i <= width; i++)
		this->m_Console << BORDER;
}

void Menu::DrawInput(const string &prompt, bool centered) const
{
	this->ClearInput(true);

	COORD pos;

	pos.Y = this->m_Console.Height();
	if (!centered)
		pos.X = STARTPROMPT;
	else
		pos.X = (short)((INPUTBARWIDTH / 2) - (prompt.size() / 2)) + 2;

	this->m_Console.SetPosition(pos);

	this->m_Console << prompt;
	this->SetInputPos();
}

void Menu::DrawMenu() const
{
	this->ClearViewPort();

	short width = this->m_Console.Width() - 1;
	short height = this->m_Console.Height() - 3;
	COORD pos;

	short startX = 1 + (short)(((width / 2) - (this->m_LargestItem / 2)));
	short startY = 3 + (short)((height / 2) - (this->m_MenuItems.size() / 2));

	pos.X = startX;
	pos.Y = startY;

	for (UINT i = 0; i < this->m_MenuItems.size(); i++)
	{
		this->m_Console.SetPosition(pos);
		this->m_Console << this->m_MenuItems[i];
		pos.X = startX;
		pos.Y++;
	}

	this->DrawInput("Selection:", false);
}

void Menu::DrawError(const string &error) const
{
	COORD pos;
	pos.X = STARTINPUT + 1;
	pos.Y = this->m_Console.Height();
	this->m_Console.SetPosition(pos);
	this->m_Console.SetTextColor(BRIGHTRED);

	this->m_Console << error;
	Sleep(2000);
	this->ClearError();
}

void Menu::DrawMessage(const string &msg) const
{
	COORD pos;
	pos.X = STARTINPUT + 1;
	pos.Y = this->m_Console.Height();
	this->m_Console.SetPosition(pos);
	this->m_Console.SetTextColor(BRIGHTGREEN);

	this->m_Console << msg;
	Sleep(2000);
	this->ClearError();

}

void Menu::DrawText(const string &text) const
{
	this->ClearViewPort();
	
	COORD pos;
	int size = this->m_Console.LengthWithoutColor(text);
	if (size <= TEXTWIDTH)
	{
		pos.X = (short)((VIEWPORTWIDTH / 2) - (size / 2));
		pos.Y = (short)(VIEWPORTHEIGHT / 2);
		this->m_Console.SetPosition(pos);
		this->m_Console << text;
		this->SetInputPos();
		return;
	}

	int longestLine = 0;
	int count = 0;
	bool color = false;
	vector<string> lines;
	string line;

	for (UINT i = 0; i < text.size(); i++)
	{
		if (text[i] == '&' && text[i + 1] == '#')
			color = true;

		if (text[i] == ';' && color)
			color = false;

		if (text[i] != '\n')
			line.append(1, text[i]);
		
		if (!color)
		{
			count++;
			if (text[i] == '\n' || ((count >= TEXTWIDTH - 1 && text[i] == ' ') ||
				i >= text.size() - 1 || count == VIEWPORTWIDTH))
			{
				if (count > longestLine)
					longestLine = count;
				lines.push_back(line);
				line.clear();
				count = 0;
			}
		}

	}

	pos.X = 4 + (short)((VIEWPORTWIDTH / 2) - (longestLine / 2));
	pos.Y = (short)((VIEWPORTHEIGHT / 2) - (lines.size() / 2));

	for (UINT i = 0; i < lines.size(); i++)
	{
		this->m_Console.SetPosition(pos);
		this->m_Console.WriteWithColor(lines[i]);
		pos.Y++;
	}

	this->SetInputPos();
}

void Menu::ReplaceTokens(string &text, const string &attacker, const string &weapon, const string &target, const string &damage) const
{
	size_t pos = 0;
	while ((pos = text.find(TOKENATTACKER)) != string::npos)
		text.replace(pos, strlen(TOKENATTACKER), attacker);

	while ((pos = text.find(TOKENTARGET)) != string::npos)
		text.replace(pos, strlen(TOKENTARGET), target);

	while ((pos = text.find(TOKENWEAPON)) != string::npos)
		text.replace(pos, strlen(TOKENWEAPON), weapon);

	while ((pos = text.find(TOKENDAMAGE)) != string::npos)
		text.replace(pos, strlen(TOKENDAMAGE), damage);
}

const string Menu::HandleInput(int size, bool isExpected) const
{
	char ch;
	int count = 0;
	string str;
	COORD pos;

	while (true)
	{
		this->m_Console.Read(&ch, 1);
		if (ch == ' ' && isExpected)
			continue;

		if (ch == '\x08' && count > 0)
		{
			pos.X = (STARTINPUT + count) - 1;
			pos.Y = this->m_Console.Height();
			this->m_Console.SetPosition(pos);
			this->m_Console.Write(' ');
			this->m_Console.SetPosition(pos);

			str.erase(str.size() - 1, 1);
			count--;
			continue;
		}

		if ((ch != '\r' && ch != '\n' && ch != '\x08') && count < size)
		{
			if (isExpected)
				ch = tolower(ch);
			str.append(1, ch);
			this->m_Console.Write(ch);
			count++;
		}

		if (ch == '\r' || ch == '\n')
		{
			this->ClearInput(false);

			if (!isExpected && count > 0)
				return str;
			else if (!isExpected && count <= 0)
				continue;

			bool found = false;
			map<string, HandlerCast>::const_iterator it;
			for (it = this->m_Shortcuts.begin(); it != this->m_Shortcuts.end(); it++)
			{
				if (_stricmp(str.c_str(), it->first.c_str()) == 0)
				{
					found = true;
					bool ret = it->second(str);
					if (ret)
						return str;
					break;
				}
			}

			if (!found && isExpected)
				this->DrawError("Invalid Input!");

			count = 0;
			str.clear();
		}
	}
}