#pragma once
#include <Re\Graphics\Model\GraphicsMetaAnimationPart.h>
#include <Re\Graphics\Model\GraphicsAnimationController.h>

namespace Graphics
{
	/// WIP
	class MetaAnimationController : public AnimationStep, public Res::ISerialisable
	{
	public:
		MetaAnimationController() = default;
		MetaAnimationController(const char* path) { deserialise(path); }
		MetaAnimationController(std::istream& file, Res::DataScriptLoader& loader) { deserialise(file, loader); }

		/// applies change to controlled animation
		void onUpdateAnimation() const;


		/// to work parts need ptr to individual controllers
		/// by the function parts are assigned to individual controllers choosen by their animId
		/// @warring make sure vector has enough elements to fullfill all the parts
		/// @arg:animations - container of animations this MetaAnimation takes care of
		void attachToAnimation(std::vector<AnimationController>& animations);
		void attachToAnimation(std::vector<AnimationController*>& animations);
		void attachToAnimation(std::vector<unique_ptr<AnimationController>>& animations);
		void attachToAnimation(std::vector<shared_ptr<AnimationController>>& animations);

		/// adds to animation steps which will redo the animation between min and max step 
		/// to the state animation will be in initial step
		/// version for forward step playing
		/// @arg:min , max - at wich range put back steps
		///		@warring use after adding all basic steps and in the range should not be placed any new
		///	@arg:initial - which point to return
		void insertBackSteps(Step_t min, Step_t max, Step_t initial = 0);

		/// add new animation part 
		void addPart(const MetaAnimationPart& newPart);
		void addPart(const char* path);
		void addPart(std::istream& file, Res::DataScriptLoader& loader);

	private:
		vector<MetaAnimationPart> parts;

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};


}