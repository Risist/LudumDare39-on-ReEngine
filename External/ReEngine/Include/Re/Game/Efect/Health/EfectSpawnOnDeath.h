#pragma once
#include <Re\Game\Efect\EfectBase.h>
#include <Re\Game\Actor\GameLayer.h>

namespace Efect
{
	/// spawns something when actor dies
	class SpawnOnDeath : public Base
	{
	public:
		SpawnOnDeath(function<Game::Actor*()> _createActor);

		bool onDeath(sf::Time dt) override;


		function<Game::Actor*()> createActor;
		
		SpawnOnDeath* setOffset(Vector2D _offset, Angle _angle)
		{
			offset = _offset;
			angle = _angle;
			return this;
		}
		SpawnOnDeath* setLayer(function<Game::Layer*()> layerF)
		{
			getLayer = layerF;
			return this;
		}
		SpawnOnDeath* setLayer(Game::Layer* layer)
		{
			getLayer = [=]() {return layer;  };
			return this;
		}


		/// data which defines spawning pos
		/// relative to owner
		Vector2D offset;
		Angle angle;
		function<Game::Layer*()> getLayer{ []() {return (Game::Layer*)nullptr; } };
	};


}