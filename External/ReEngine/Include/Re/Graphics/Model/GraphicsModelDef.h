#pragma once
#include <Re\Common\utility.h>

namespace Graphics
{

	/*
	*	class holding all propertites of model
	*	like color, pos, rotation, scale ect.
	*	
	*	used in animations and models	
	*/
	class ModelDef : public Res::ISerialisable
	{
	public: /// functions section
		
			/// ctors
		ModelDef(const Vector2D& position = Vector2D(), Angle rot = Angle::zero, 
			Color_f color = Color_f(), 
			const Vector2D& scale = Vector2D(), Angle rotAround = Angle::zero);
		ModelDef(std::istream& file, Res::DataScriptLoader& loader) { deserialise(file, loader); }

		/// updates takensprite to modelDef "transform".
		///		color is nondepended on parent
		///		position of parent is added to sprite
		///		rotation of parent rotates transform by some degree
		///		@pos is rotated by rotAround + parents rotation and added to sprite position 
		///		
		void setSprite(sf::Sprite& toUpdate, const sf::Transformable& parent) const;
		/// version with not parent specyfied
		void setSprite(sf::Sprite& toUpdate) const;

	public: /// Data section
		Vector2D pos;
		Vector2D scale{Vector2D(1,1)};
		/// rotation of whole model and its childrens
		Angle rot, 
		/// offset of rotation around parent, influences position and rotation by the angle
			rotAround,
		/// rotation of sprite only
			rotSprite;
		Color_f color;


		Vector2D origin;

	public: /// operators section
		ModelDef operator+(const ModelDef& other) const;
		ModelDef operator-(const ModelDef& other) const;
		ModelDef operator*(float32 other) const;
		ModelDef operator/(float32 other) const;

		void operator+=(const ModelDef& other);
		void operator-=(const ModelDef& other);
		void operator*=(float32 other);
		void operator/=(float32 other);

	protected: /// ISerialisable section
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;

	public: /// predefined values section

		/// default ModelDef, not changing sprite at update; to use in Model class
		static const ModelDef default;
		/// ModelDef with all values equal to 0; to use in animation class
		static const ModelDef zero;
	};

}