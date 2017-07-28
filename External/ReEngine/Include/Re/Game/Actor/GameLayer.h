#pragma once
#include <Re\Game\GameActor.h>

namespace Game
{

	/*
	Actor type designed to behave one to many
	holds many subActors and runs every request on all of them

	can be used to ensure order of actor displaying
	*/
	class Layer : public Actor
	{
	public:
		void onUpdate(sf::Time dt) override;

		/// adds a new efect to the container
		/// do not pass nullptr otherwise the function will assert
		/// returns pointner taken as an argument ( to easier usage )
		Actor * addActor(Actor * _new);
		/// adds initializer list of efects to the container
		/// do not pass nullptr in any of them otherwise the function will assert
		/// each efect is activated
		void addManyActors(const initializer_list<Actor*>& actorsList)
		{
			return addManyActors(actorsList);
		}

		/// returns first found efect of type T
		/// if there is no such the one returns nullptr
		/// @Warring make sure T derrives from Base otherwise something might goes wrong
		template<typename T> T* getActor()
		{
			return getEfect<T>();
		}

		/// returns every efect of type T
		/// @Warring make sure T derrives from Base otherwise something might goes wrong
		template<typename T> void getActor(list<T*>& r)
		{
			return getEfects<T>(r);
		}

	private:
		/// this actor cannot have efect, instead holds actors
		using Efect::Multi::addEfect;
		using Efect::Multi::getEfect;
		using Efect::Multi::getEfects;
	};
}
