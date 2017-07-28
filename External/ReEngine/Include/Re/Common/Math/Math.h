#pragma once

#include <Re\Common\Math\Angle.h>
#include <Re\Common\Math\Vector2D.h>
#include <Re\Common\Math\NewtonianResource.h>



template <typename Ty>
inline Ty min(Ty x, Ty y)
{
	return x > y ? y : x;
}

template <typename Ty>
inline Ty max(Ty x, Ty y)
{
	return x > y ? x :y;
}

template< class Type> 
inline Type clamp(Type value, Type min, Type max)
{
	if (value > max)
		return max;
	else if (value < min)
		return min;
	return value;
}

inline Vector2D max(const Vector2D& v1, const Vector2D& v2);
inline Vector2D min(const Vector2D& v1, const Vector2D& v2);

inline float32 randRange(float32 min, float32 max)
{
	return (float)rand() / RAND_MAX * (max - min) + min;
}
inline sf::Time randRange(sf::Time min, sf::Time max)
{
	return (float)rand() / RAND_MAX * (max - min) + min;
}

template<typename Ty, typename AlphaTy >
inline Ty lerp(Ty x1, Ty x2, AlphaTy t)
{
	return x1 + (x2 - x1)*t;
}