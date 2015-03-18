#ifndef OCT_DIM_HPP
#define OCT_DIM_HPP

namespace oct{
template<typename T> struct dim{
	dim(T x, T y, T z)noexcept: x(x), y(y), z(z){}

	const T x, y, z;
};

template<typename TNum> auto operator==(const dim<TNum>& lhs, const dim<TNum>& rhs) -> bool
		{ return (lhs.x == rhs.x and lhs.y == rhs.y and lhs.z == rhs.z); }

template<typename TNum> auto operator!=(const dim<TNum>& lhs, const dim<TNum>& rhs) -> bool
		{ return (lhs.x != rhs.x or lhs.y != rhs.y or lhs.z != rhs.z); }


template<typename TNum> auto operator+(const dim<TNum>& lhs, const dim<TNum>& rhs) -> dim<TNum>
		{ return (dim<TNum>{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z}); }

template<typename TNum> auto operator-(const dim<TNum>& lhs, const dim<TNum>& rhs) -> dim<TNum>
		{ return (dim<TNum>{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z}); }

template<typename TNum> auto operator*(const dim<TNum>& lhs, const dim<TNum>& rhs) -> dim<TNum>
		{ return (dim<TNum>{lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z}); }

template<typename TNum> auto operator/(const dim<TNum>& lhs, const dim<TNum>& rhs) -> dim<TNum>
		{ return (dim<TNum>{lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z}); }


template<typename TNum> auto operator+(const dim<TNum>& lhs, TNum rhs) -> dim<TNum>
		{ return (dim<TNum>{lhs.x + rhs, lhs.y + rhs, lhs.z + rhs}); }

template<typename TNum> auto operator-(const dim<TNum>& lhs, TNum rhs) -> dim<TNum>
		{ return (dim<TNum>{lhs.x - rhs, lhs.y - rhs, lhs.z - rhs}); }

template<typename TNum> auto operator*(const dim<TNum>& lhs, TNum rhs) -> dim<TNum>
		{ return (dim<TNum>{lhs.x * rhs, lhs.y * rhs, lhs.z * rhs}); }

template<typename TNum> auto operator/(const dim<TNum>& lhs, TNum rhs) -> dim<TNum>
		{ return (dim<TNum>{lhs.x / rhs, lhs.y / rhs, lhs.z / rhs}); }

}

#endif
