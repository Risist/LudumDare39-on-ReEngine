#pragma once
#include <Re\Game\Efect\EfectBase.h>
#include <Re\Game\Actor\GameLayer.h>


namespace Efect
{
	class Throw : public Base
	{
	public:
		Throw();

		void onUpdate(sf::Time dt) override;

		Throw* addData(function<Game::Actor*()> createBullet, function<bool()> conditionToFire = conditionToFire_default)
		{
			ThrowData _d;
			_d.createBullet = createBullet;
			_d.conditionToFire = conditionToFire;
			data.push_back(_d);
			return this;
		}
		/// sets spawnpoint to last created Throw data
		Throw* setDataTransform(Vector2D offset, Angle rotation)
		{
			data.back().offset = offset;
			data.back().rotation = rotation;
			return this;
		}
		Throw* setDataLayer(function<Game::Layer*()> getLayer)
		{
			data.back().getLayer = getLayer;
			return this;
		}
		Throw* setDataLayer(Game::Layer* layer)
		{
			data.back().getLayer = [=]() {return layer; };
			return this;
		}

		static bool conditionToFire_default();

	private:
		struct ThrowData
		{
			function<Game::Actor*()> createBullet;
			/// condition to spawn (eg. pressing button)
			/// default one is pressing Action ["fire1"]
			function<bool()> conditionToFire;
			Vector2D offset;
			Angle rotation;
			function<Game::Layer*()> getLayer { []() {return (Game::Layer*)nullptr; } };
		};
		vector<ThrowData> data;
	};
}