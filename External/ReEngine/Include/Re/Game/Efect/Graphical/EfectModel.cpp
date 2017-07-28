#include <Re\Game\Efect\Graphical\EfectModel.h>
#include <Re\Game\GameActor.h>
namespace Efect
{
	Model::Model(const char* path)
		:model(path)
	{
		model.rewriteToVectorRendering(modelsRendering);
		model.rewriteToVectorUpdate(modelsUpdate);
	}

	Model::Model(ResId scriptId)
		:model(scriptId)
	{
		model.rewriteToVectorRendering(modelsRendering);
		model.rewriteToVectorUpdate(modelsUpdate);
	}

	void Model::onInit()
	{
		setParent(getOwner());
	}

	void Efect::Model::onUpdate(sf::Time dt)
	{
		//model.drawRecursive(cam);
		for (auto&it : modelsUpdate)
			it->updateAsPArent();
		for (auto&it : modelsRendering)
			it->drawOnly(cam);
	}

	Model * Model::deserialiseFromString(const string & script)
	{
		model.deserialiseFromString(script);
		model.rewriteToVectorRendering(modelsRendering);
		model.rewriteToVectorUpdate(modelsUpdate);
		return this;
	}

	Model * Model::deserialiseRes(ResId scriptId)
	{
		model.deserialiseFromString(scriptInst[scriptId]);
		model.rewriteToVectorRendering(modelsRendering);
		model.rewriteToVectorUpdate(modelsUpdate);
		return this;
	}

	Model * Model::deserialise(const char* script)
	{
		model.deserialise(script);
		model.rewriteToVectorRendering(modelsRendering);
		model.rewriteToVectorUpdate(modelsUpdate);
		return this;
	}

}