#pragma once

#include <memory>

#define BIT(x) (1 << x)

#define PX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Pixie
{

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}