#include "ConLib.h"

#include <iomanip>
#include <iostream>
#include <sstream>


using namespace std;


ConLib::ConLib()
{
	this->InitConLib();
}

ConLib::ConLib(int width, int height)
{
	this->InitConLib();

	COORD size;
	size.X = width;
	size.Y = height;

	SMALL_RECT rect;
	rect.Top = rect.Left = 0;
	rect.Right = width - 1;
	rect.Bottom = height - 1;

	SetConsoleWindowInfo(this->m_Screen, TRUE, &rect);
	SetConsoleScreenBufferSize(this->m_Screen, size);
}

ConLib::~ConLib()
{
}

void ConLib::InitConLib()
{
	this->m_Screen = GetStdHandle(STD_OUTPUT_HANDLE);
	this->m_Keyboard = GetStdHandle(STD_INPUT_HANDLE);

	DWORD oldMode;
	GetConsoleMode(this->m_Keyboard, &oldMode);
	oldMode = oldMode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_MOUSE_INPUT);
	SetConsoleMode(this->m_Keyboard, oldMode);
	SetConsoleMode(this->m_Screen, ENABLE_PROCESSED_OUTPUT);

	this->SetTextColor(ConRed | ConGreen | ConBlue);
	this->SetBackgroundColor(0);

	CONSOLE_CURSOR_INFO info;
	info.dwSize = 10;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(this->m_Screen, &info);
}

void ConLib::SetBackgroundColor(WORD color)
{
	this->m_BackgroundColor = 0;

	if (color & ConRed)
		this->m_BackgroundColor |= BACKGROUND_RED;
	if (color & ConGreen)
		this->m_BackgroundColor |= BACKGROUND_GREEN;
	if (color & ConBlue)
		this->m_BackgroundColor |= BACKGROUND_BLUE;
	if (color & ConIntensity)
		this->m_BackgroundColor |= BACKGROUND_INTENSITY;

	SetConsoleTextAttribute(this->m_Screen, this->m_TextColor | this->m_BackgroundColor);
}

void ConLib::SetTextColor(WORD color)
{
	this->m_TextColor = 0;

	if (color & ConRed)
		this->m_TextColor |= FOREGROUND_RED;
	if (color & ConGreen)
		this->m_TextColor |= FOREGROUND_GREEN;
	if (color & ConBlue)
		this->m_TextColor |= FOREGROUND_BLUE;
	if (color & ConIntensity)
		this->m_TextColor |= FOREGROUND_INTENSITY;

	SetConsoleTextAttribute(this->m_Screen, this->m_TextColor | this->m_BackgroundColor);

}

void ConLib::SetTitle(const string &title) const
{
	SetConsoleTitle(title.c_str());
}

void ConLib::SetPosition(const COORD &position) const
{
	SetConsoleCursorPosition(this->m_Screen, position);
}

void ConLib::SetOutputCodePage(UINT cp) const
{
	SetConsoleOutputCP(cp);
}

void ConLib::Clear() const
{
	COORD start;
	DWORD written;

	start.X = 0;
	start.Y = 0;

	DWORD size = this->Width() * this->Height();

	FillConsoleOutputAttribute(this->m_Screen, this->m_TextColor | this->m_BackgroundColor, size, start, &written);
	FillConsoleOutputCharacter(this->m_Screen, ' ', size, start, &written);
	SetConsoleCursorPosition(this->m_Screen, start);
}

void ConLib::Clear(int x, int y, int width, int height) const
{
	COORD start;
	DWORD written;

	for (int i = 0; i < height; i++)
	{
		start.X = x;
		start.Y = y + i;

		FillConsoleOutputAttribute(this->m_Screen, this->m_TextColor | this->m_BackgroundColor, width, start, &written);
		FillConsoleOutputCharacter(this->m_Screen, ' ', width, start, &written);
	}

	start.X = 0;
	start.Y = 0;
	SetConsoleCursorPosition(this->m_Screen, start);
}

int ConLib::LengthWithoutColor(const string &text) const
{
	int ret = 0;
	bool start = true;

	for (UINT i = 0; i < text.size(); i++)
	{
		if (text[i] == '%' && text[i + 1] == '#')
			start = false;

		if (text[i] == ';' && !start)
			start = true;

		if (text[i] != ';' && start)
			ret++;
	}

	return ret;
}

void ConLib::WriteLine(const string &text)
{
	string t = text;
	t.append("\r\n");
	this->Write((char *)t.c_str());
}

void ConLib::WriteLine()
{
	this->WriteLine("");
}

void ConLib::WriteLine(char ch)
{
	char buffer[2] = { ch, '\0' };
	this->WriteLine(buffer);
}

void ConLib::WriteLine(float num)
{
	ostringstream str;
	str << num;
	string s(str.str());
	this->WriteLine(s);
}

void ConLib::WriteLine(int num)
{
	char buffer[100];
	_itoa_s(num, buffer, 10);
	this->WriteLine(buffer);
}

void ConLib::WriteWithColor(const string &text)
{
	for (UINT i = 0; i < text.size(); i++)
	{
		if (text[i] == '%' && text[i + 1] == '#')
		{
			i += 2;
			bool back = false;
			if (text[i] == 'b')
			{
				back = true;
				i++;
			}
			
			string num;
			char ch = text[i++];
			while (ch != ';')
			{
				num.append(1, ch);
				ch = text[i++];	
			}

			WORD color = atoi(num.c_str());
			
			if (back)
				this->SetBackgroundColor(color);
			else
				this->SetTextColor(color);
		}
		this->Write(text[i]);
	}
}

void ConLib::Write(const string &text)
{
	DWORD written;
	for (UINT i = 0; i < text.size(); i++)
	{
		if (text[i] == '%' && text[i + 1] == '#')
		{
			i += 2;
			string num;
			char ch = text[i++];
			while (ch != ';')
			{
				num.append(1, ch);
				ch = text[i++];	
			}

			WORD color = atoi(num.c_str());
			this->SetTextColor(color);
		}
		//WriteConsole(this->m_Screen, text.c_str(), strlen(text.c_str()), &written, NULL);
		WriteConsole(this->m_Screen, &text[i], 1, &written, NULL);
	}
}

void ConLib::Write(float num)
{
	this->Write(to_string(num));
}

void ConLib::Write(int num)
{
	this->Write(to_string(num));
}

void ConLib::Write(char ch)
{
	string str;
	str.append(1, ch);
	this->Write(str);
}

void ConLib::Read(char *buffer, DWORD size) const
{
	DWORD read;
	ReadConsole(this->m_Keyboard, buffer, size, &read, NULL);
}

int ConLib::GetKey(bool pause) const
{
	DWORD read;
	INPUT_RECORD event;
	int ret = 0;

	if (pause)
	{
		while (ret == 0)
		{
			ReadConsoleInput(this->m_Keyboard, &event, 1, &read);

			if (event.EventType == KEY_EVENT && event.Event.KeyEvent.bKeyDown)
				ret = event.Event.KeyEvent.wVirtualKeyCode;
		}
	}
	else
	{
		ReadConsoleInput(this->m_Keyboard, &event, 1, &read);

		if (event.EventType == KEY_EVENT && event.Event.KeyEvent.bKeyDown)
			ret = event.Event.KeyEvent.wVirtualKeyCode;
	}

	return ret;
}

const short ConLib::Width() const
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(this->m_Screen, &info);

	return info.dwSize.X - 1;
}

const short ConLib::Height() const
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(this->m_Screen, &info);

	return info.dwSize.Y - 1;
}

ConLib &operator <<(ConLib &target, const string &value)
{
	if (value.find_first_of("%#") != string::npos)
		target.WriteWithColor(value);
	else
		target.Write(value);

	return target;
}

ConLib &operator <<(ConLib &target, const float &value)
{
	target.Write(value);
	return target;
}

ConLib &operator <<(ConLib &target, const int &value)
{
	target.Write(value);
	return target;
}

ConLib &operator <<(ConLib &target, const char &value)
{
	target.Write(value);
	return target;
}

ConLib &operator <<(ConLib &target, ConLib::StandardEndLine value)
{
	return value(target);
}

ConLib &ConLib::endl(ConLib &target)
{
	target.Write("\r\n");
	return target;
}