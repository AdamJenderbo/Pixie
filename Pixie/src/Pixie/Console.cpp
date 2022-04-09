#include "Console.h"
#include "Time.h"
#include <iostream>
#include <Windows.h>

void Pixie::Console::Log(std::string message)
{
	std::cout << Timestamp() << " " << message << std::endl;
	SetColor(Color::DEFAULT);
}

void Pixie::Console::LogSuccess(std::string message)
{
	SetColor(Color::GREEN);
	Log(message);
}

void Pixie::Console::LogWarning(std::string message)
{
	SetColor(Color::YELLOW);
	Log(message);
}

void Pixie::Console::LogError(std::string message)
{
	SetColor(Color::RED);
	Log(message);
}

std::string Pixie::Console::Timestamp()
{
	return "[" + Time::Now().ToString() + "]";
}

void Pixie::Console::SetColor(Color color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (int)color);
}
