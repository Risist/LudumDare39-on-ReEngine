#include "Camera.h"

Camera cam;

Camera::Camera() : lastScale(1), darkness(1), alpha(1)
{
}
void Camera::create(const sf::Vector2f& size, const sf::Vector2f& center)
{
	reset(sf::FloatRect(size, size));

	RenderTexture::create((unsigned int)size.x, (unsigned int)size.y);

	setCenter(center);
}

void Camera::draw(const sf::Drawable & s, const RenderStates & states)
{
	RenderTexture::draw(s);
}


void Camera::follow(const sf::Transformable& sp, Angle addIctionalRotation, float32 d)
{
	follow(sp.getPosition(), Degree(sp.getRotation()), addIctionalRotation, d);
}
void Camera::followPositionOnly(const sf::Transformable& sp, float32 d )
{
	followPositionOnly(sp.getPosition(), Degree(sp.getRotation()), d);
}
void Camera::followRotationOnly(const sf::Transformable& sp, Angle addIctionalRotation)
{
	followRotationOnly(Degree(sp.getRotation()), addIctionalRotation);
}

void Camera::follow(const Vector2D& position, Angle rotation, Angle addIctionalRotation, float32 d)
{
	Vector2D vd(0, d);
	vd.rotate(rotation);

	setRotation((rotation + addIctionalRotation).asDegree());
	setCenter(position + vd);
}
void Camera::followPositionOnly(const Vector2D& position, Angle rotation, float32 d)
{
	Vector2D vd(0, d);
	vd.rotate(rotation);

	setCenter(position + vd);
}
void Camera::followRotationOnly( Angle rotation, Angle addIctionalRotation)
{
	setRotation((rotation + addIctionalRotation).asDegree());
}

void Camera::followSmooth(const sf::Transformable & sp, Vector2D alpha, Angle addIctionalRotation, float32 d)
{
	followSmooth(sp.getPosition(), Degree(sp.getRotation()), alpha, addIctionalRotation, d);
}

void Camera::followPositionOnlySmooth(const sf::Transformable & sp, float32 alpha, float32 d)
{
	followPositionOnlySmooth(sp.getPosition(), Degree(sp.getRotation()), alpha, d);
}

void Camera::followRotationOnlySmooth(const sf::Transformable & sp, float32 alphaRot, Angle addIctionalRotation)
{
}

void Camera::followSmooth(const Vector2D & position, Angle rotation, Vector2D alpha, Angle addIctionalRotation, float32 d)
{
	Vector2D vd(0, d);
	vd.rotate(rotation);

	//setRotation((rotation + addIctionalRotation).asDegree());
	setCenter(lerp((Vector2D)getCenter(), position, alpha.x) + vd);

	Angle aD = getRotation();
	Angle aR = rotation + addIctionalRotation;

	Angle diff = aD - aR;


	setRotation(
		aD.asDegree() + (aR.minimalDiffirence(aD)*alpha.y).asDegree());
}

void Camera::followPositionOnlySmooth(const Vector2D & position, Angle rotation, float32 alphaPos, float32 d)
{
	Vector2D vd(0, d);
	vd.rotate(rotation);
	
	setCenter(lerp((Vector2D)getCenter(), position, alphaPos) + vd);
}

void Camera::followRotationOnlySmooth(const Vector2D & position, Angle rotation, float32 alphaRot, Angle addIctionalRotation)
{
	Angle aD = getRotation();
	Angle aR = rotation + addIctionalRotation;

	float32 sign = (aD.normalized() > aR.normalized() )*2.f - 1.f;

	setRotation(
		aD.asDegree() + sign*(aR.minimalDiffirence(aD)*alphaRot).asDegree());
}



void Camera::display(sf::RenderWindow& wnd, const sf::Vector2f& pos, const RenderStates& states)
{
	RenderTexture::display();
	RenderTexture::setView(*this);

	sf::Sprite sprite(RenderTexture::getTexture());
	sprite.setPosition(pos);
	sprite.setColor(sf::Color(
		(sf::Uint8)(255 * darkness), 
		(sf::Uint8)(255 * darkness), 
		(sf::Uint8)(255 * darkness), 
		(sf::Uint8)(255 * alpha)));

	wnd.draw(sprite,states);
	RenderTexture::clear(background);
}