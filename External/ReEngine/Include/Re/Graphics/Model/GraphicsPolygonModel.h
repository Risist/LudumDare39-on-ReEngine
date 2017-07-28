#pragma once
#include <Re\Graphics\Model\GraphicsPolygonShape.h>
#include <Re\Graphics\Model\GraphicsModelDef.h>
#include <Re\Graphics\Model\GraphicsAnimationPart.h>

namespace Graphics
{

	/// tree like structure to maintain recursive displaying of PolygonShapes
	class PolygonModel
		: public sf::Drawable,
		public ModelDef
	{
	public:
		///ctor
		PolygonModel(const ModelDef& def = ModelDef::default, size_t layersN = 1, size_t pointsN = 1);


		/// puts elements to vector to allow iterative run through Model	
		void rewriteToVector(std::vector<PolygonModel* >& v) const;



		/// Childs & siblings
		void addChildUp(PolygonModel* _new)
		{
			if (childUp)
				childUp->addSibling(_new);
			else
			{
				childUp = unique_ptr<PolygonModel>(_new);
				childUp->parent = this;
			}
		}
		void addChildDown(PolygonModel* _new)
		{
			if (childDown)
				childDown->addSibling(_new);
			else
			{
				childDown = unique_ptr<PolygonModel>(_new);
				childDown->parent = this;
			}
		}
		
		PolygonModel* getChildUp() { return childUp.get(); }
		const PolygonModel* getChildUp() const { return childUp.get(); }

		PolygonModel* getChildDown() { return childDown.get(); }
		const PolygonModel* getChildDown() const { return childDown.get(); }

		PolygonModel* getSibling() { return sibling.get(); }
		const PolygonModel* getSibling() const { return sibling.get(); }

		PolygonModel* getParent() { return parent; }
		const PolygonModel* getParent() const { return parent; }

		void setParent(PolygonModel* s) { parent = s; }

		/// animation interface
		void addPart(AnimationPart* s);
		void removePart(AnimationPart* s);

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void addSibling(PolygonModel* _new)
		{
			if (sibling)
				sibling->addSibling(_new);
			else
			{
				sibling = unique_ptr<PolygonModel>(_new);
				sibling->parent = parent;
			}
		}
	private: /// Members

		mutable PolygonShape shape;

		/// tree structure
		PolygonModel* parent{nullptr};
		std::unique_ptr<PolygonModel> childUp, childDown, sibling;

		/// animation
		vector<unique_ptr<AnimationPart>> parts; //< list of applied animations to this shape

		mutable ModelDef lastDef{ModelDef::default};

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};


}