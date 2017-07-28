#include <Re\Graphics\Model\GraphicsModel.h>
#include <Re\Graphics\Model\GraphicsAnimationPart.h>

namespace Graphics
{
	Model::Model()
		: parent(nullptr), ModelDef(ModelDef::default)
	{
	}

	Model::Model(ResId tsId, const ModelDef& def)
		: ModelDef(def), parent(nullptr)
	{
		setTexture(tsId);
	}

	Model::Model(const char * path)
		: parent(nullptr)
	{
		deserialise(path);
	}
	Model::Model(ResId scriptId)
		: parent(nullptr)
	{
		deserialiseFromString(scriptInst[scriptId]);
	}

	void Model::drawSingle(sf::RenderTarget & target, sf::RenderStates states)
	{
		//ModelDef def = *this;

		//for (auto &it : parts)
		//	it->countOffset(def);
		if(parent)
			actualDef.setSprite(sp, *parent);
		else actualDef.setSprite(sp);


		sp.rotate(__rotSprite.asDegree());
		target.draw(sp, states);
		sp.rotate(-__rotSprite.asDegree());

		actualDef = *this;
	}

	void Model::drawRecursive(sf::RenderTarget & target, sf::RenderStates states)
	{
		if (childDown)
			childDown->drawRecursive(target, states);

		drawSingle(target, states);

		/// draw sibling
		if (sibling)
			sibling->drawRecursive(target, states);

		if (childUp)
			childUp->drawRecursive(target, states);
	}

	void Model::rewriteToVectorRendering(std::vector<Model* >& v) const
	{
		if (childDown)
			childDown->rewriteToVectorRendering(v);

		v.push_back((Model*)this);

		if (sibling)
			sibling->rewriteToVectorRendering(v);

		if (childUp)
			childUp->rewriteToVectorRendering(v);
	}

	void Model::updateAsPArent()
	{
		//ModelDef def = *this;


		//for (auto &it : parts)
		//	it->countOffset(def);
		
		if (parent)
			actualDef.setSprite(sp, *parent);
		else actualDef.setSprite(sp);
		__rotSprite = actualDef.rotSprite;

		actualDef = *this;
	}

	void Model::drawOnly(sf::RenderTarget & target, sf::RenderStates states)
	{
		sp.rotate(__rotSprite.asDegree());
		target.draw(sp, states);
		sp.rotate(-__rotSprite.asDegree());
	}

	void Model::rewriteToVectorUpdate(std::vector<Model* >& v) const
	{
		v.push_back((Model*)this);

		if (childDown)
			childDown->rewriteToVectorUpdate(v);

		if (childUp)
			childUp->rewriteToVectorUpdate(v);

		if (sibling)
			sibling->rewriteToVectorUpdate(v);
	}


	void Model::setTexture(ResId id)
	{
		res.textures[id].setSprite(sp);
	}
	/**
	void Model::addAnimationPart(AnimationPart * s)
	{
		parts.push_back(s);
	}

	void Model::removeAnimationPart(AnimationPart * s)
	{
		for(auto it = parts.begin(); it != parts.end(); ++it)
			if ( *it == s)
			{
				parts.erase(it);
				return;
			}
	}/**/

	void Model::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		ModelDef::serialiseF(file, saver);
#ifdef RE_EDITOR
		/// Only in editor
		/// TODO
#endif // RE_EDITOR
	}

	void Model::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		ModelDef::deserialiseF(file, loader);
		/// set texture
		ResId tsId = loader.load("ts", 0);
		if (tsId != 0)
			setTexture(tsId);
		else
			sp.setTextureRect(sf::IntRect() );

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			string b = loader.load<string>("ud", "down");
			Model *m = new Model();

			if (b == "up")
				addUp(m);
			else // if( b == "down")
				addDown(m);

			m->deserialise(file, loader);
		}
	}
}