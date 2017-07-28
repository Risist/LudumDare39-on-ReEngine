#pragma once
#include <Re\Game\Efect\EfectBase.h>
#include <Re\Graphics\Graphics.h>


namespace Efect
{
	/// Efect which will simplyfy maintaining
	/// Models within game objects
	class Model : public Base
	{
	public:

		Model() {};
		Model(const char* path);
		Model(ResId scriptId);

		virtual void onInit() override;
		virtual void onUpdate(sf::Time dt) override;

		Model* deserialiseFromString(const string& script);
		Model* deserialiseRes(ResId script);
		Model* deserialise(const char* script);

		Model* setPosition(const Vector2D& position)
		{
			model.pos = position;
			return this;
		}
		Model* setRotation(Angle angle)
		{
			model.rot = angle;
			return this;
		}
		Model* setScale(const Vector2D& scale)
		{
			model.scale = scale;
			return this;
		}
		Model* setColor(Color_f cl)
		{
			model.color = cl;
			return this;
		}
		Model* setRotationAround(Angle angle)
		{
			model.rotAround = angle;
			return this;
		}
		Model* setParent(sf::Transformable* parent)
		{
			model.parent = parent;
			return this;
		}

		Model* setTexture(ResId id)
		{
			model.setTexture(id);
		}

		/// graphics data 
		Graphics::Model model;
		vector<Graphics::Model*> modelsUpdate, modelsRendering;
	};
}