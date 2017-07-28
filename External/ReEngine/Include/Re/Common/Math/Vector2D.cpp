#include <Re\Common\Math\Vector2D.h>
#include <Re\Common\Math\Math.h>

Angle Vector2D::angle() const
{
	// to avoid deviding by 0
	/*if (x == 0)
	{
		if (y >= 0)
			return Angle::Degree(0);
		else
			return Angle::Degree(180);
	}

	float32 alfa = atan(y / x) * 180.f / M_PI;
	if (x > 0)
	alfa += 90.f;
	else if (x < 0)
		alfa += 270.f;

	return Angle::Degree(alfa);*/

	return Radian(atan2(y,x)) + Degree(90);
}

Vector2D randRange(const Vector2D & min, const Vector2D & max)
{
	return Vector2D(randRange(min.x, max.x), randRange(min.y, max.y));
}

Vector2D clamp(const Vector2D & value, const Vector2D & min, const Vector2D & max)
{
	return Vector2D(clamp(value.x, min.x, max.x), clamp(value.y, min.y, max.y));
}
