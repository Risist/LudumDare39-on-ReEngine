#include <Re\Game\Efect\EfectBase.h>

namespace Efect
{

	/// health component
	
	class Health : public Base
	{
	public:
		Health(float32 maxHealth = 100.f, float32 percentInitialHealth = 1.f);

		void onUpdate(sf::Time dt) override;


		/// heal/damage events
		/// both can have negative arguments 
		/// which is basically using another function with positive arg
		void damage(float32 amount, Game::Actor* causer);
		void heal(float32 amount, Game::Actor* causer);

		/// event called when owner takes damage
		/// 1st argument tells how much health is changed in terms of heal
		/// used in both heal and damage
		function<void(float32, Game::Actor*)> damageReaction;

		/// actual amount of hitpoints
		/// when actual value will go bellow 0 owner dies
		float32 actual;
		/// dmage/heal is multiplayed by inverseDefence
		float32 inverseDefence{1};
		/// maximal amount of hitpoints
		/// see MaxMode for info what will happened when exceeding max helth
		float32 max;

		bool isInMaxRange() { return actual < max; }

		/// enum for representation what will happened when exceeding max health
		enum MaxMode
		{
			truncate,		//< lose all health he
			dealDamage,		//< exceeding max health will cause damage eg. max = 100; actual = 175 then after mode actual = 35
			nothing,		//< do not use max health
		}maxMode{truncate};


		/// 
		float32 regeneration{0};
		float32 regenerationDamping{0};

		/// functions for initialization
		Health*	setDamageReaction(function<void(float32, Game::Actor*)> s)
		{
			damageReaction = s;
			return this;
		}
		Health* setMax(float32 maxHp, MaxMode mode = truncate)
		{
			max = maxHp;
			maxMode = mode;
			return this;
		}
		Health* setRegeneration(float32 _regeneration, float32 _regenerationDamping)
		{
			regeneration = _regeneration;
			regenerationDamping = _regenerationDamping;
			return this;
		}
		Health* setDefence(float32 s)
		{
			assert(s != 0);
			inverseDefence = 1 / s;
			return this;
		}
		Health* setInverseDefence(float32 s)
		{
			inverseDefence = s;
			return this;
		}
		Health* setActual(float32 s)
		{
			actual = s;
			return this;
		}
	};

}