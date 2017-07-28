#pragma once
#include <Re\Graphics\Model\GraphicsAnimationPart.h>

namespace Graphics
{

	class Model;

	class AnimationController : public Res::ISerialisable, public AnimationStep
	{
	public:
		AnimationController();
		AnimationController(const char* path);
		AnimationController(std::istream& file, Res::DataScriptLoader& loader) { deserialise(file, loader); };

		/// call this on every frame before model update/ after drawing
		/// updates model's actulDef to fullfil model state after appling animation
		/// @arg:scale - allows you to scale influence of the animation
		///			usefull for example in merging animations
		void onUpdateModel(Step_t scale= 1.f);

		/// add new animation part 
		void addPart(const AnimationPart& newPart);

		/// attach the animation to model
		/// animation parts holds ptr's to actualDef from models part 
		/// modelId determine which modelPart is choosen
		/// call after initialisation of modelId and before first onUpdate
		/// @Warring! slow operation. Don't use that on every frame 
		/// @Warring! make sure model after rewrite to vector will have enough elements
		///				that there is no part with modelId not pointing to model
		void attachToModel(Model& model);
		void attachToModel(vector<Model*>& model);

		/// adds to animation steps which will redo the animation between min and max step 
		/// to the state animation will be in initial step
		/// version for forward step playing
		void insertBackSteps(Step_t min, Step_t max, Step_t initial = 0);
		
	private:
		/// animation parts holded
		vector<AnimationPart> parts;

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}