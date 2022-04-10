#pragma once
#include "Event.h"

namespace Pixie
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
	};
}

