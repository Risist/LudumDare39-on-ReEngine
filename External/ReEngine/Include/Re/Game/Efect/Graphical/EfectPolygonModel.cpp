#include <Re\Game\Efect\Graphical\EfectPolygonModel.h>
#include <Re\Game\GameActor.h>
#include <Re\Graphics\Camera.h>

namespace Efect
{
	PolygonModel::PolygonModel(const char* path, UpdateMode mode)
		: updateMode(mode), updateOwner(nullptr)
	{
		model.deserialise(path);
	}
	PolygonModel::PolygonModel(const Graphics::ModelDef& def, size_t layersN, size_t pointsN, UpdateMode mode)
		: updateMode(mode), model(def, layersN, pointsN)
	{

	}

	void PolygonModel::onInit()
	{
		updateOwner = getOwner();
	}
	void PolygonModel::onUpdate(sf::Time dt)
	{
		if (updateOwner)
		{
			if (updateMode == toTransform)
			{
				//model.posNoRot = updateOwner->getPosition();
				//model.rot = updateOwner->getRotation();
			}
			else if (updateMode == toPhysics)
			{
				//model.posNoRot = Vector2D(updateOwner->getRigidbody().GetPosition()) * toSfPosition;
				//model.rot = Radian(updateOwner->getRigidbody().GetAngle());
			}
		}


		cam.draw(model);
	}
}