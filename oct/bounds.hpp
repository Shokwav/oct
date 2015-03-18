#ifndef OCT_BOUNDS_HPP
#define OCT_BOUNDS_HPP

#include "dim.hpp"

namespace oct{
template<typename T> class bounds{
public:
	template<typename TNum> friend auto contains(const bounds<TNum>& lhs, const dim<TNum>& rhs) -> bool;
	template<typename TNum> friend auto contains(const bounds<TNum>& lhs, const bounds<TNum>& rhs) -> bool;

	bounds(const dim<T>& pos, const dim<T>& size): m_position(pos), m_size(size){}

	auto get_position()const noexcept -> const dim<T>& { return (m_position); }
	auto get_size()const noexcept -> const dim<T>& { return (m_size); }

private:
	const dim<T> m_position, m_size;
};

template<typename T> auto contains(const bounds<T>& lhs, const dim<T>& rhs) -> bool {
	const auto& pos = lhs.get_position(), size = lhs.get_size();
	return ((rhs.x >= pos.x and rhs.x <= pos.x + size.x) and
			(rhs.y >= pos.y and rhs.y <= pos.y + size.y) and
			(rhs.z >= pos.z and rhs.z <= pos.z + size.z));
}

}

#endif
