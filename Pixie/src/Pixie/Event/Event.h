#pragma once
#include <functional>

namespace Pixie
{
	enum class EventType
	{
		None = 0,
		WindowClose
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	class Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;

		template<typename T>
		static bool Handle(Event& e, std::function<bool(T&)> func)
		{
			if (e.GetEventType() == T::GetStaticType())
			{
				func(*(T*)&e);
				return true;
			}
			return false;
		}
	};
}