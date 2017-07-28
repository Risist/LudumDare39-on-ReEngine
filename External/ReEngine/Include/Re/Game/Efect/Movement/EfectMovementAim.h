#pragma once
#include <Re\Game\Efect\Movement\EfectRotateToDirection.h>


namespace Efect
{
	/// Owner will move towards setted destination
	/// when within minimalDistance radius destination is marked as arrived
	/// and waits for new destination
	/// @requires rigidbody
	class MovementAim : public Base
	{
	public:
		MovementAim(float32 movementSpeed,
			float32 minimalDistance = 50);
		MovementAim(float32 movementSpeed,
			RotateToDirection *efRotDir,
			float32 minimalDistance = 50);

		void onInit() override;
		void onUpdate(sf::Time dt) override;

		/// adds
		void setDestinationDirection(const Vector2D& newDest, float32 influenceScale = 1);
		void setDestination(const Vector2D& newDest, float32 influenceScale = 1);
		void addInfluence(const Vector2D& destVersor, float32 influenceScale)
		{
			storedInfluence += destVersor.getNormalised()*influenceScale;
			arrived = false;
		}
		void reset()
		{
			storedInfluence = Vector2D();
			arrived = true;
		}

		Vector2D getDestination() const;
		Vector2D getInfluence() const { return storedInfluence; }

		/// speed in which owner will move
		float32 movementSpeed,
			/// how close needs to move towards direction
			minimalDistance;

		/// pointner to efect which will change direction of owner
		/// nullptr disables the this feature
		RotateToDirection *efRotDir{ nullptr };

		/// tells whether agent came to destination
		bool getArrived() const { return arrived; }

		MovementAim* setInfluenceFall(float32 s)
		{
			influenceFall = s;
			return this;
		}
		float32 influenceFall{0};

	protected:
		Vector2D storedInfluence;

		/// whether or not still need to move
		bool arrived;
	};


	/*/// v influence
	class EfectMovementAimInfluence : public Base
	{
	public:

		void onInit() override;
		void onUpdate(sf::Time dt) override;


		void setDestination(const Vector2D& newDest)
		{
			storedInfluence = (Vector2D)getOwner()->getRigidbody().GetPosition() * toSfPosition - newDest;
			arrived = false;
		}
		void addInfluenceDestination(const Vector2D& newDest, float32 influenceScale)
		{
			storedInfluence += ((Vector2D)getOwner()->getRigidbody().GetPosition() * toSfPosition - newDest)
				.getNormalised()*influenceScale;
			arrived = false;
		}
		void addInfluence(const Vector2D& destVersor, float32 influenceScale)
		{
			storedInfluence += destVersor.getNormalised()*influenceScale;
			arrived = false;
		}
		void reset()
		{
			storedInfluence = Vector2D();
			arrived = true;
		}

		/// speed in which owner will move
		float32 movementSpeed,
		/// how close needs to move towards direction
			minimalDistance;

		/// pointner to efect which will change direction of owner
		/// nullptr disables the this feature
		RotateToDirection *efRotDir{ nullptr };

		/// tells whether agent came to destination
		bool getArrived() const { return arrived; }

	private:
		Vector2D storedInfluence;

		/// whether or not still need to move
		bool arrived;
	};*/
}