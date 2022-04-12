#pragma once
#include <string>
#include "Base.h"

namespace Pixie
{
	class Console
	{
	public:
		static void Log(std::string message);
		static void LogSuccess(std::string message);
		static void LogWarning(std::string message);
		static void LogError(std::string message);

	private:

		enum class Color
		{
			DEFAULT = 7,
			GREEN = 10,
			YELLOW = 14,
			RED = 12
		};

		static std::string Timestamp();
		static void SetColor(Color color);
	};
}