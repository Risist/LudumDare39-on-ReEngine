#pragma once
#include <Re\Graphics\ResourceManager.h>
#include <Re\Graphics\Model\GraphicsModelDef.h>

// #define RE_EDITOR

namespace Graphics
{
	class AnimationPart;

	class Model : 
		public ModelDef
	{
	public:
		Model();
		/// manualy set model
		Model(ResId tsId, const ModelDef& def);
		/// load model from path
		Model(const char* path);
		Model(ResId scriptId);

		/// display model onto target
		/// does not draw childrens
		void drawSingle(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
		/// display model onto target. Draws childrens using recursive calls
		void drawRecursive(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
		
		
		/// Functions to use in vector wise version
		/// updateAsParent should be called on every model put in vector created by rewriteToVectorUpdate
		/// then call drawOnly on every object put into vector created by rewriteToVectorRendering
		void updateAsPArent();
		void drawOnly(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

		/// put pointners to model parts to vector in animation/update order
		/// i.e.  object -> sibling -> childDown -> childUp
		void rewriteToVectorUpdate(std::vector<Model* >& v) const;
		/// put pointners to model parts to vector in rendering order
		/// i.e. childDown -> object -> sibling -> childUp
		void rewriteToVectorRendering(std::vector<Model* >& v) const;

		/// set texture to the one with id of res.textures
		void setTexture(ResId id);


		/// add child above
		/// pass a pointner to model created by "new Model"
		void addUp(Model *s)
		{
			if (childUp == nullptr)
			{
				s->parent = &sp;
				childUp = unique_ptr<Model>(s);
			}
			else
				childUp->addSibling(s);
		}
		/// add child under
		/// pass a pointner to model created by "new Model"
		void addDown(Model *s)
		{
			if (childDown == nullptr) 
			{
				s->parent = &sp;
				childDown = unique_ptr<Model>(s);
			}
			else
				childDown->addSibling(s);
		}

		/// Animations
		//void addAnimationPart(AnimationPart* s);
		//void removeAnimationPart(AnimationPart* s);

		/// getters ///

		Model* getChildUp()
		{
			return childUp.get();
		}
		Model* getChildDown()
		{
			return childDown.get();
		}
		Model* getSibling()
		{
			return sibling.get();
		}

		Model* getChildUp() const
		{
			return childUp.get();
		}
		Model* getChildDown() const
		{
			return childDown.get();
		}
		Model* getSibling() const
		{
			return sibling.get();
		}

		/// returns actually drawn position
		Vector2D getPosition() const
		{
			return sp.getPosition();
		}
		/// returns actually drawn rotation
		Angle getRotation() const
		{
			return Degree(sp.getRotation()) + rotSprite;
		}
		/// returns actually drawn scale
		Vector2D getScale() const
		{
			return sp.getScale();
		}
		const Texture* getTexture() const
		{
			return sp.getTexture();
		}

		/// transformable model is updated to
		Transformable* parent;
		ModelDef actualDef;
	protected:
		/// actual graphical representation of the model
		sf::Sprite sp;
		/// holded rotation of sprite computed by update function
		/// for internal usage
		Angle __rotSprite;

		//list<AnimationPart*> parts;
	protected: /// Double Tree data
		/// DoubleTree is like standard tree but have two separated childrens
		/// Those childrens describes the rendering order which is:
		///		childs down(and their childrens)
		///		calling model
		///		childs up(and their childrens)

		/// adds a sibling to the model
		/// for internal purposes
		/// use addUp or addDown instead
		void addSibling(Model *s)
		{
			if (sibling == nullptr)
			{
				sibling = unique_ptr<Model>(s);
				s->parent = parent;
			}
			else
				sibling->addSibling(s);
		}

		/// child can be placed either above or under
		/// which child ptr is used determine rendering order
		std::unique_ptr<Model> childUp, childDown,
			/// sibling to this model
			/// shows all models on the same layer
			/// Rendering order: first this one then siblings
			sibling;

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}