#pragma once

#include <Re\Common\Settings.h>
#include <iostream>

class Angle;
Angle Radian(float32 angle);
Angle Degree(float32 angle);

class Angle
{
	Angle(float32 initialDegree);
public:
	Angle();

	static const Angle full;
	static const Angle zero;

	friend Angle Radian(float32 angle);
	friend Angle Degree(float32 angle);
	

	inline float32 asRadian() const
	{
		return (float32)(degree / 180.f * M_PI);
	}
	inline float32 asDegree() const
	{
		return degree;
	}

	inline float sin() const
	{
		return ::sin(asRadian());
	}
	inline float cos() const
	{
		return ::sin(asRadian());
	}
	inline Vector2f getVersor() const
	{
		return Vector2f(-sin(), cos());
	}

	Angle minimalDiffirence(const Angle& other) const;
	///
	Angle normalized() const
	{
		return Degree((float32)((int)degree % 360));
	}
	void normalize()
	{
		degree = (float32)((int)degree % 360);
	}

	inline bool operator>(const Angle& other) const
	{
		return degree > other.degree;
	}
	inline bool operator>=(const Angle& other) const
	{
		return degree >= other.degree;
	}
	inline bool operator<(const Angle& other) const
	{
		return degree < other.degree;
	}
	inline bool operator<=(const Angle& other) const
	{
		return degree <= other.degree;
	}

	inline Angle operator+(const Angle& other) const
	{
		return Degree(asDegree() + other.asDegree());
	}
	inline Angle operator-(const Angle& other) const
	{
		return Degree(asDegree() - other.asDegree());
	}
	inline Angle operator*(const Angle& other) const
	{
		return Degree(asDegree() * other.asDegree());
	}
	inline Angle operator/(const Angle& other) const
	{
		assert(other.degree != 0);
		return Degree(asDegree() / other.asDegree());
	}


	inline Angle operator*(float32 other) const
	{
		return Degree(asDegree() * other);
	}
	inline Angle operator/(float32 other) const
	{
		assert(other != 0);
		return Degree(asDegree() / other);
	}

	inline void operator+=(const Angle& other)
	{
		degree += other.asDegree();
	}
	inline void operator-=(const Angle& other)
	{
		degree -= other.asDegree();
	}
	inline void operator*=(const Angle& other)
	{
		degree *= other.asDegree();
	}
	inline void operator/=(const Angle& other)
	{
		assert(other.degree != 0);
		degree /= other.asDegree();
	}

	inline void operator*=(float32 other)
	{
		degree *= other;
	}
	inline void operator/=(float32 other)
	{
		assert(other != 0);
		degree /= other;
	}

	inline Angle operator-() const
	{
		return Degree(-degree);
	}

	inline bool operator==(Angle other) const
	{
		return degree == other.degree;
	}
	inline bool operator!=(Angle other) const
	{
		return degree != other.degree;
	}

private:
	// angle in degrees
	float32 degree;
};

Angle randRange(Angle min, Angle max);
Angle clamp(Angle value, Angle min, Angle max);