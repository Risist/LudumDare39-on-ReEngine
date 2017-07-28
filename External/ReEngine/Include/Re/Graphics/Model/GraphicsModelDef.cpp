#include <Re\Graphics\Model\GraphicsModelDef.h>

namespace Graphics
{
	const ModelDef ModelDef::default(Vector2D(), Angle::zero, Color_f(255.f, 255.f, 255.f, 255.f),  Vector2D(1,1), Angle::zero );
	const ModelDef ModelDef::zero(Vector2D(), Angle::zero, Color_f(), Vector2D(), Angle::zero);

	ModelDef::ModelDef(const Vector2D & _position, Angle _rot, Color_f _color, const Vector2D & _scale, Angle _rotAround)
		: pos(_position), rot(_rot), color(_color), scale(_scale), rotAround(_rotAround)
	{
	}

	void ModelDef::setSprite(sf::Sprite & toUpdate, const sf::Transformable& parent) const
	{
		toUpdate.setPosition( 
			(pos* parent.getScale() ).
				getRotated(rotAround + Degree(parent.getRotation()) ) 
			+ parent.getPosition()
		);
		toUpdate.setRotation( parent.getRotation() + rotAround.asDegree() + rot.asDegree() );
		toUpdate.setScale(scale * parent.getScale() );
		
		toUpdate.setColor(sf::Color(
			clamp(color.r, 0.f, 255.f),
			clamp(color.g, 0.f, 255.f),
			clamp(color.b, 0.f, 255.f),
			clamp(color.a, 0.f, 255.f)
		));
		toUpdate.setOrigin(toUpdate.getTextureRect().width*0.5f + origin.x,
			toUpdate.getTextureRect().height*0.5f + origin.y);
	}

	void ModelDef::setSprite(sf::Sprite & toUpdate) const
	{
		toUpdate.setPosition( pos.getRotated(rot));
		toUpdate.setRotation(rotSprite.asDegree() + rotAround.asDegree() + rot.asDegree() );
		toUpdate.setScale(scale );

		toUpdate.setColor(sf::Color(
			clamp(color.r, 0.f, 255.f),
			clamp(color.g, 0.f, 255.f),
			clamp(color.b, 0.f, 255.f),
			clamp(color.a, 0.f, 255.f)
		));
		toUpdate.setOrigin(toUpdate.getTextureRect().width*0.5f + origin.x,
			toUpdate.getTextureRect().height*0.5f + origin.y);
	}

	ModelDef ModelDef::operator+(const ModelDef & other)  const
	{
		ModelDef def;
		def.pos = pos + other.pos;
		def.rot = rot+ other.rot;
		def.rotAround = rotAround+ other.rotAround;
		def.rotSprite = rotSprite + other.rotSprite;
		def.scale = scale + other.scale;
		def.color = color + other.color;
		def.origin = origin + other.origin;
		return def;
	}
	ModelDef ModelDef::operator-(const ModelDef & other) const
	{
		ModelDef def;
		def.pos = pos - other.pos;
		def.rot = rot - other.rot;
		def.rotAround = rotAround - other.rotAround;
		def.rotSprite = rotSprite - other.rotSprite;
		def.scale = scale - other.scale;
		def.color = color - other.color;
		def.origin = origin - other.origin;
		return def;
	}
	ModelDef ModelDef::operator*(float32 other) const
	{
		ModelDef def;
		def.pos = pos * other;
		def.rot = rot * other;
		def.rotAround = rotAround * other;
		def.rotSprite = rotSprite * other;
		def.scale = scale * other;
		def.color = color * other;
		def.origin = origin * other;
		return def;
	}
	ModelDef ModelDef::operator/(float32 other) const
	{
		assert(other != 0);
		ModelDef def;
		def.pos = pos / other;
		def.rot = rot / other;
		def.rotAround = rotAround / other;
		def.rotSprite = rotSprite / other;
		def.scale = scale / other;
		def.color = color / other;
		def.origin = origin / other;
		return def;
	}
	void ModelDef::operator+=(const ModelDef & other)
	{
		pos += other.pos;
		rot += other.rot;
		rotAround += other.rotAround;
		rotSprite += other.rotSprite;
		scale += other.scale;
		color += other.color;
		origin += other.origin;
	}
	void ModelDef::operator-=(const ModelDef & other)
	{
		pos -= other.pos;
		rot -= other.rot;
		rotAround -= other.rotAround;
		rotSprite -= other.rotSprite;
		scale -= other.scale;
		color -= other.color;
		origin -= other.origin;
	}
	void ModelDef::operator*=(float32 other)
	{
		pos *= other;
		rot *= other;
		rotAround *= other;
		rotSprite *= other;
		scale *= other;
		color *= other;
		origin *= other;
	}
	void ModelDef::operator/=(float32 other)
	{
		assert(other != 0);
		pos /= other;
		rot /= other;
		rotAround /= other;
		rotSprite /= other;
		scale /= other;
		color /= other;
		origin /= other;
	}
	void ModelDef::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save("posX", pos.x);
		saver.save("posY", pos.y);

		saver.save("originX", origin.x);
		saver.save("originY", origin.y);

		saver.save("scaleX", scale.x);
		saver.save("scaleY", scale.y);

		saver.save("rot", rot.asDegree());
		saver.save("rotAround", rotAround.asDegree());
		saver.save("rotSprite", rotSprite.asDegree());

		saver.save("clR", color.r);
		saver.save("clG", color.g);
		saver.save("clB", color.b);
		saver.save("clA", color.a);
	}
	void ModelDef::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		pos.x = loader.load("posX", ModelDef::default.pos.x);
		pos.y = loader.load("posY", ModelDef::default.pos.y);

		origin.x = loader.load("originX", ModelDef::default.origin.x);
		origin.y = loader.load("originY", ModelDef::default.origin.y);

		scale.x = loader.load("scaleX", ModelDef::default.scale.x);
		scale.y = loader.load("scaleY", ModelDef::default.scale.y);

		rot = Degree(loader.load("rot", ModelDef::default.rot.asDegree()) );
		rotAround = Degree(loader.load("rotAround", ModelDef::default.rotAround.asDegree()) );
		rotSprite = Degree(loader.load("rotSprite", ModelDef::default.rotSprite.asDegree()));

		color.r = loader.load("clR", ModelDef::default.color.r);
		color.g = loader.load("clG", ModelDef::default.color.g);
		color.b = loader.load("clB", ModelDef::default.color.b);
		color.a = loader.load("clA", ModelDef::default.color.a);
	}
}