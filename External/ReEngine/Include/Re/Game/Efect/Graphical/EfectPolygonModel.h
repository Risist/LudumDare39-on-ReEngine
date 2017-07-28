#pragma once
#include <Re\Game\Efect\EfectBase.h>
#include <Re\Graphics\Model\GraphicsPolygonModel.h>

namespace Efect
{
	/// model made from many polygonal shapes which vibrates at displaying
	class PolygonModel : public Base
	{
	public:
		enum UpdateMode
		{
			toPhysics,
			toTransform
		}updateMode;
		/// creates model from .res script in path file
		PolygonModel(const char* path, UpdateMode mode = toTransform);
		/// manual creation
		PolygonModel(const Graphics::ModelDef& def = Graphics::ModelDef::default, 
			size_t layersN = 1, size_t pointsN = 1, 
			UpdateMode mode = toPhysics);


		void onInit() override;
		void onUpdate(sf::Time dt) override;

		/// setters
		PolygonModel* setUpdateOwner(Game::Actor* owner)
		{
			updateOwner = owner;
			return this;
		}
		PolygonModel* setUpdateMode(UpdateMode mode)
		{
			updateMode = mode;
			return this;
		}

		

		Graphics::PolygonModel model;
		/// actor to which the model will be updated;
		Game::Actor *updateOwner{nullptr};
	};
}