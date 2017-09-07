#pragma once
#ifndef CONLIB_H
#define CONLIB_H

#define WIN32_LEAN_AND_MEAN


#include <windows.h>
#include <string>


using namespace std;


enum ConColor
{
	ConRed = 1,
	ConGreen = 2,
	ConBlue = 4,
	ConIntensity = 8
};


class ConLib
{
public:
	ConLib();
	ConLib(int width, int height);
	virtual ~ConLib();

	void SetBackgroundColor(WORD color);
	void SetTextColor(WORD color);
	void SetTitle(const string &title) const;
	void SetPosition(const COORD &position) const;
	void SetOutputCodePage(UINT cp) const;

	void	Clear() const;
	void	Clear(int x, int y, int width, int height) const;
	void	WriteLine(const string &text);
	void	WriteLine(float num);
	void	WriteLine(char ch);
	void	WriteLine(int num);
	void	WriteLine();
	void	Write(const string &text);
	void	Write(float num);
	void	Write(int num);
	void	Write(char ch);
	void	WriteWithColor(const string &text);
	int		LengthWithoutColor(const string &text) const;

	void	Read(char *buffer, DWORD size) const;
	int		GetKey(bool pause) const;

	const short Width() const;
	const short Height() const;

	typedef ConLib& (*StandardEndLine)(ConLib&);

	friend ConLib &operator <<(ConLib &target, const string &value);
	friend ConLib &operator <<(ConLib &target, const float &value);
	friend ConLib &operator <<(ConLib &target, const int &value);
	friend ConLib &operator <<(ConLib &target, const char &value);
	friend ConLib &operator <<(ConLib &target, StandardEndLine value);
	static ConLib &endl(ConLib &target);

private:
	HANDLE	m_Screen;
	HANDLE	m_Keyboard;
	WORD	m_TextColor;
	WORD	m_BackgroundColor;

	void InitConLib();
};

#endif