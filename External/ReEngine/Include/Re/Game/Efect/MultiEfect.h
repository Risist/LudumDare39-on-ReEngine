#pragma once
#include <Re\Game\Efect\EfectBase.h>
#include <list>


namespace Efect
{

	/// Efect that behaves like many
	/// Used as a base class for events which needs to contain others to work
	/// 
	class Multi : public Base
	{
	public:
		Multi(){}

	public:
			
		/// events - similar to those from Actor
		/// here is only dcription of eventually differences or things that are unclear
		/// So for more info look into GameActor.h file

		virtual void onInit() override;
		virtual void onStart() override;
		virtual void onUpdate(sf::Time dt) override;
		/// Actor cannot be destroyed if any of Efects returns false (is not ready to end)
		virtual bool onDeath(sf::Time dt) override;

		virtual void onCollisionEnter(Game::Actor& otherActor, b2Contact& contact) override;
		virtual void onCollisionExit(Game::Actor& otherActor, b2Contact& contact) override;
		/// "Liberum veto" all efects have to agree that collision can appear
		virtual bool shouldCollide(b2Fixture* myFixture, b2Fixture* otherFixture) override;

	public:
		/// adds a new efect to the container
		/// do not pass nullptr otherwise the function will assert
		/// returns pointner taken as an argument ( to easier usage )
		template<typename T>
		T* addEfect(T* _new, bool activated = true);

		/// returns first found efect of type T
		/// if there is no such the one returns nullptr
		/// @Warring make sure T derrives from Base otherwise something might goes wrong
		template<typename T> T* getEfect();

		/// returns every efect of type T
		/// @Warring make sure T derrives from Base otherwise something might goes wrong
		template<typename T> void getEfects(list<T*>& r);
		template<typename T> void getEfects(vector<T*>& r);


	protected:
		list<unique_ptr<Base> > efects;
	};

	template<typename T>
	T* Multi::addEfect(T * _new, bool activated)
	{
		assert(_new != nullptr);
		efects.push_back(unique_ptr<Base>(_new));
		_new->activated = activated;
		/// initialize
		_new->setOwner(getOwner());
		_new->onInit();
		return _new;
	}

	template<typename T>
	T * Multi::getEfect()
	{
		for (auto it = efects.begin(); it != efects.end(); ++it)
			if (dynamic_cast<T*>(it->get()) != nullptr)
				return (T*)it->get();
		return nullptr;
	}

	template<typename T>
	void Multi::getEfects(list<T*>& r)
	{
		for (auto it = efects.begin(); it != efects.end(); ++it)
			if (dynamic_cast<T*>(it->get()) != nullptr)
				r.push_back((T*)it->get());
	}
	template<typename T>
	void Multi::getEfects(vector<T*>& r)
	{
		for (auto it = efects.begin(); it != efects.end(); ++it)
			if (dynamic_cast<T*>(it->get()) != nullptr)
				r.push_back((T*)it->get());
	}
}