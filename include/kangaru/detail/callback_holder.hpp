#pragma once

#include <functional>

#include "pointer_type.hpp"

namespace kgr {
namespace detail {

struct Holder {
	virtual ~Holder() = default;
};

template<typename T, typename... Args>
struct CallbackHolder final : Holder {
	using callback_t = std::function<service_ptr<T>(Args...)>;

	explicit CallbackHolder(callback_t callback) : _callback{std::move(callback)} {}
	
	service_ptr<T> operator ()(Args&&... args) {
		return _callback(std::forward<Args>(args)...);
	}
	
private:
	callback_t _callback;
};

} // namespace detail
} // namespace kgr
