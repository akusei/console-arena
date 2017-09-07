#pragma once
#ifndef WINDOW_H
#define WINDOW_H


#include "ConLib.h"

#include <string>


class Window
{
public:
	Window(ConLib &console);
	virtual ~Window();

	void SetTitle(const std::string &title);
	void SetPrompt(const std::string &prompt);
	
	void DrawWindow() const;
	void DrawError() const;
	void ClearError() const;

private:
	ConLib		&m_Console;
	std::string	m_Prompt;
	std::string m_Title;
};


#endif