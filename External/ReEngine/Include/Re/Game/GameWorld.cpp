#include <Re\Game\GameWorld.h>
#include <Re\Graphics\Camera.h>
extern RenderWindow wnd;

extern thor::ActionMap<string> actionMap;

namespace Game
{
	World world;

	World::World()
		: physicalWorld(Vector2D())
	{
		// contact listeners
		physicalWorld.SetContactListener(&contactListener);
		physicalWorld.SetContactFilter(&contactFilter);
	}
	World::~World()
	{
		clear();
	}

	void World::clear()
	{
		for (auto it : actorList)
			if(it)
				delete it;
		actorList.clear();

		for (auto it : actorToAdd)
			if(it)
				delete it;
		actorToAdd.clear();
	}

	void World::onUpdate(sf::Time dt)
	{
		/// fixed update (?)
		physicalWorld.Step(1.f/60.f, velocityIterations, positionIterations);

		for (auto it : actorToAdd)
		{
			actorList.push_back(it);
			it->onStart();
		}
		actorToAdd.clear();

		for (auto it = actorList.begin(); it != actorList.end();)
		{
			auto actorIt = *it;
			if (!actorIt->isActive())
				continue;

			{
				if (actorIt->isAlive())
				{
					actorIt->onUpdate(dt);
					++it;
				}
				else if (actorIt->onDeath(dt))
				{
					actorToRemove.push_back(actorIt);
					actorList.erase(it++);
				}
			}
		}

		for (auto it : actorToRemove)
			delete it;
		actorToRemove.clear();


		/// to show physics colliders
		if (actionMap.isActive("debugPhysics"))
			debugDisplayPhysics(Color(50, 50, 50, 200), Color(20, 20, 20, 200));
	}

	

	void World::debugDisplayPhysics(Color clNotColliding, Color clColliding)
	{

		auto bodyIt = physicalWorld.GetBodyList();
		while (bodyIt)
		{
			if (!bodyIt->IsActive())
				continue;

			auto fixtureIt = bodyIt->GetFixtureList();
			while (fixtureIt)
			{
				auto _shape = fixtureIt->GetShape();
				
				switch (_shape->GetType())
				{
				case b2Shape::e_circle:
				{
					auto shape = (b2CircleShape*)_shape;
					sf::CircleShape sh;
					sh.setPosition((Vector2D)bodyIt->GetPosition() *toSfPosition);
					
					sh.setRadius(shape->m_radius *toSfPosition);

					sh.setRotation( Radian(bodyIt->GetAngle() ).asDegree() );
					//sh.setOrigin(
						//sh.getRadius() + shape->m_p.x*toSfPosition, 
						//sh.getRadius() + shape->m_p.y*toSfPosition);
					sh.setOrigin(
						sh.getRadius(),
						sh.getRadius());
					sh.setFillColor(clNotColliding);

					cam.draw(sh);
				}
					break;
				case b2Shape::e_polygon:
				{
					auto shape = (b2PolygonShape*)_shape;
					sf::ConvexShape sh;
					sh.setPosition((Vector2D)bodyIt->GetPosition() *toSfPosition);
					sh.setRotation(Radian(bodyIt->GetAngle()).asDegree());


					sh.setPointCount(((b2PolygonShape*)_shape)->m_count);
					for (int i = 0; i < sh.getPointCount(); ++i)
						sh.setPoint(i, (Vector2D)((b2PolygonShape*)_shape)->m_vertices[i]*toSfPosition);

					sh.setFillColor(clNotColliding);
					cam.draw(sh);
				}
					break;
				default:
					break;
				}

				fixtureIt = fixtureIt->GetNext();
			}


			bodyIt = bodyIt->GetNext();
		}

	}


	void ContactListener::BeginContact(b2Contact * contact)
	{
		if (contact->IsTouching())
		{
			Game::Actor * actorA = (Game::Actor*)contact->GetFixtureA()->GetBody()->GetUserData();
			Game::Actor * actorB = (Game::Actor*)contact->GetFixtureB()->GetBody()->GetUserData();

			/// make sure can cast to reference
			assert(actorA != nullptr);
			assert(actorB != nullptr);

			actorA->onCollisionEnter(*actorB, *contact);
			actorB->onCollisionEnter(*actorA, *contact);
		}
	}
	void ContactListener::EndContact(b2Contact * contact)
	{
		if (contact->IsTouching())
		{
			Game::Actor * actorA = (Game::Actor*)contact->GetFixtureA()->GetBody()->GetUserData();
			Game::Actor * actorB = (Game::Actor*)contact->GetFixtureB()->GetBody()->GetUserData();

			assert(actorA != nullptr);
			assert(actorB != nullptr);
			
			actorA->onCollisionExit(*actorB, *contact);
			actorB->onCollisionExit(*actorA, *contact);
		}
	}

	bool ContactFilter::ShouldCollide(b2Fixture * fixtureA, b2Fixture * fixtureB)
	{
		assert(fixtureA->GetBody()->GetUserData() != nullptr);
		assert(fixtureB->GetBody()->GetUserData() != nullptr);

		return ((Actor*)fixtureA->GetBody()->GetUserData())->shouldCollide(fixtureA, fixtureB) 
			&& ((Actor*)fixtureB->GetBody()->GetUserData())->shouldCollide(fixtureB, fixtureA);
	}
}