#include <Re\Game\Efect\Bullets\EfectThrow.h>
#include <Re\Game\Game.h>
extern RenderWindow wnd;

namespace Efect
{
	Throw::Throw()
	{
	}

	void Throw::onUpdate(sf::Time dt)
	{
		for (auto it : data)
		{
			if (it.conditionToFire())
			{
				auto bullet = it.createBullet();
				if (bullet == nullptr)
					return;
				Game::world.addActor(bullet, it.getLayer());

				if (bullet->isRigidbodyCreated())
					bullet->getRigidbody().SetTransform(

						bullet->getRigidbody().GetPosition()
						+ it.offset.getRotated(it.rotation + getOwner()->getRotation())*toB2Position
						+ (Vector2D)getOwner()->getPosition()*toB2Position
						,
						bullet->getRigidbody().GetAngle()
						+ getOwner()->getRotation().asRadian()
					);
				else
				{
					bullet->move(it.offset.getRotated(it.rotation + getOwner()->getRotation())
						+ getOwner()->getPosition());
					bullet->rotate(getOwner()->getRotation().asDegree());
				}
			}
		}
	}
	bool Throw::conditionToFire_default()
	{
		return actionMap.isActive("fire2") && wnd.hasFocus();
	}
}