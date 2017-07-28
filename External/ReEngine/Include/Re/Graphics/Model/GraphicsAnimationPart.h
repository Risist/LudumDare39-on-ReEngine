#pragma once
#include <Re\Graphics\Model\GraphicsModelDef.h>
#include <Re\Graphics\Model\GraphicsAnimationStep.h>

namespace Graphics
{
	/// Class describes animation part
	/// inherits from Transformable and its values shows how model part will change
	class AnimationPart : public ModelDef, public AnimationStepHolder
	{
	public:
		/// default constructor
		AnimationPart();
		/// manually creates animation part
		AnimationPart(size_t modelId, const ModelDef& def, Step_t stepMin, Step_t stepMax );
		/// loades animation part from file
		AnimationPart(char* path);
		/// deserialise from loader
		AnimationPart(std::istream& file, Res::DataScriptLoader& loader) { deserialise(file, loader); }

		/// updates actual definition of model the animationPart is attached to
		/// should be called every frame before model update
		/// do not call this when the model is removed
		/// @arg:scale - allows you to scale influence of the animation
		///			usefull for example in merging animations
		void onUpdateModel(Step_t scale = 1.f) const;

		/// count offset described by this animationPart after applying step 
		/// @Warring firstly step should be assigned 
		/// @param [out] Transformable& out 
		///		where to save counted transformable 
		void countOffset( ModelDef& out, Step_t scale = 1.f) const;
		ModelDef getDefAtStep(Step_t step) const;


		// index of model in revrited vector that the animation affects 
		size_t modelId{0};
		/// a modelDef which will be updated 
		ModelDef* defToUpdate{nullptr};
	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}