#pragma once
#include <Re\Common\utility.h>

class Camera : public sf::View, public sf::RenderTexture
{
public:
	Camera();
	void create(const sf::Vector2f& size, const sf::Vector2f& center = sf::Vector2f());

	void draw(const sf::Drawable& s, const RenderStates& states = sf::RenderStates::Default );

	/// display camera onto window
	/// @param pos - offset in pos of camera's view
	void display(sf::RenderWindow& wnd, const sf::Vector2f& pos = sf::Vector2f()
		, const RenderStates& states = RenderStates());
	
	// change pos of camera
	void addCenter(const sf::Vector2f& s)
	{
		setCenter(getCenter() + s);
	}
	// change pos of camera
	void addCenter(float32 x, float32 y)
	{
		addCenter(sf::Vector2f(x, y));
	}

	/// set how much the view is scaled (sfml has no such a feature)
	void setScale(float32 s)
	{
		View::zoom(1 / lastScale);
		lastScale = s;
		View::zoom(lastScale);
	}
	/// get how much the view is scaled (sfml has no such a feature)
	float getScale()
	{
		return lastScale;
	}

	/// set brightness of camera [0,1]
	void setDarkness(float32 s)
	{
		assert(s >= 0.f && s <= 1.f);
		darkness = s;
	}
	/// add brightness of camera [-1,1]
	void addDarkness(float32 s)
	{
		darkness += s;
		darkness = clamp(darkness, 0.f, 1.f);
	}
	// get brightness of camera [0,1]
	float32 getDarkness()
	{
		return darkness;
	}

	/// set how much render is depended on previous frames [0,1]
	/// adds efect of "drunk" man  
	void setAlpha(float32 s)
	{
		assert(s >= 0.f && s <= 1.f);
		alpha = s;
	}
	/// add how much render is depended on previous frames [-1,1]
	/// adds efect of "drunk" man  
	void addAlpha(float32 s)
	{
		alpha += s;
		alpha = clamp(alpha, 0.f, 1.f);
	}
	/// get how much render is depended on previous frames [0,1]
	/// adds efect of "drunk" man  
	float32 getAlpha()
	{
		return alpha;
	}


	/// set color of background
	void setBackgroundColor(const Color& cl)
	{
		background = cl;
	}
	/// get color of background
	const Color& getBackgroundColor()
	{
		return background;
	}

	/// Makes camera follow the transform
	/// should be called every graphical update (or rarer if object does not move)
	/// @param addictionalRotation addictional rotation applied to camera
	/// @param d distance from sprite (note also rotated in sprites direction)
	void follow(const sf::Transformable& sp, Angle addIctionalRotation = Angle(), float32 d = 0);
	void followPositionOnly(const sf::Transformable& sp, float32 d = 0);
	void followRotationOnly(const sf::Transformable& sp, Angle addIctionalRotation = Angle());


	/// Changes view
	/// should be called every graphical update (or rarer if object does not move)
	/// @param addictionalRotation addictional rotation applied to camera
	/// @param d distance from sprite (note also rotated in sprites direction)
	/// @param pos new pos
	/// @param rotation rotation using which the distance will be rotated
	void follow(const Vector2D& position, Angle rotation = Angle(), Angle addIctionalRotation = Angle(), float32 d = 0);
	void followPositionOnly(const Vector2D& position, Angle rotation = Angle(), float32 d = 0);
	void followRotationOnly(Angle rotation = Angle(), Angle addIctionalRotation = Angle());

	/// Makes camera follow the transform
	/// version with damping
	void followSmooth(const sf::Transformable& sp, Vector2D alpha = Vector2D(1,1), Angle addIctionalRotation = Angle(), float32 d = 0);
	void followPositionOnlySmooth(const sf::Transformable& sp, float32 alphaPos = 1, float32 d = 0);
	void followRotationOnlySmooth(const sf::Transformable& sp, float32 alphaRot = 1, Angle addIctionalRotation = Angle());

	/// Changes view
	/// should be called every graphical update (or rarer if object does not move)
	/// @param addictionalRotation addictional rotation applied to camera
	/// @param d distance from sprite (note also rotated in sprites direction)
	/// @param pos new pos
	/// @param rotation rotation using which the distance will be rotated
	void followSmooth(const Vector2D& position, Angle rotation = Angle(), Vector2D alpha = Vector2D(1,1), Angle addIctionalRotation = Angle(), float32 d = 0);
	void followPositionOnlySmooth(const Vector2D& position, Angle rotation = Angle(), float32 alphaPos = 1, float32 d = 0);
	void followRotationOnlySmooth(const Vector2D& position, Angle rotation = Angle(), float32 alphaRot = 1, Angle addIctionalRotation = Angle());


public:
	/// overrided operators
	__forceinline Angle getRotation() const { return Degree(View::getRotation()); }
	

private:

	float32 darkness, ///< brightness of camera [0,1]
		alpha,		///< how much render is depended on previous frames [0,1]
		lastScale;	///< how much the view is scaled (sfml has no such a feature)
	
	// color using which the render texture will be cleared after displaying
	Color background;
};


extern Camera cam;