#include <Re\Graphics\Model\GraphicsPolygonModel.h>

namespace Graphics
{
	PolygonModel::PolygonModel(const ModelDef & def, size_t layersN, size_t pointsN)
		: ModelDef(def), shape(layersN, pointsN, Color(def.color.r, def.color.g, def.color.b, def.color.a))
	{
	}
	void PolygonModel::rewriteToVector(std::vector<PolygonModel*>& v) const
	{
		if (childDown)
			childDown->rewriteToVector(v);

		v.push_back((PolygonModel*)this);

		if (childUp)
			childUp->rewriteToVector(v);

		if (sibling)
			sibling->rewriteToVector(v);
	}
	void PolygonModel::addPart(AnimationPart * s)
	{
		parts.push_back(unique_ptr<AnimationPart>(s));
	}
	void PolygonModel::removePart(AnimationPart * s)
	{
		for (auto it = parts.begin(); it != parts.end(); ++it)
			if (it->get() == s)
			{
				parts.erase(it);
				return;
			}
	}
	void PolygonModel::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		/// update
		ModelDef def = *this;

		//for (auto &it : parts)
			//if (it->isWithinRange())
				//it->countOffset(def);

		/*if (parent)
			lastDef = def.countOffset(parent->lastDef);
		else
			lastDef = def;*/


		if (childDown)
			target.draw(*childDown, states);

		//shape.setPosition(lastDef.posNoRot);
		shape.setRotation(lastDef.rot.asDegree());
		shape.setScale(lastDef.scale);
		
		/// display
		target.draw(shape, states);

		if (sibling)
			target.draw(*sibling, states);

		if (childUp)
			target.draw(*childUp, states);
	}
	void PolygonModel::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
#ifdef RE_EDITOR
		/// TODO
#endif
	}
	void PolygonModel::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		ModelDef::deserialiseF(file, loader);
		shape.deserialise(file, loader);
		
		DATA_SCRIPT_MULTILINE(file, loader)
		{
			auto _new = new PolygonModel();

			string ud = loader.load<string>("ud", "up");
			if (ud == "up")
				addChildUp(_new);
			else
				addChildDown(_new);

			string path = loader.load<string>("path", "");
			if (path == "")
			{
				_new->deserialise(file, loader);
			}
			else
				_new->deserialise(path);
			
		}
	}
}