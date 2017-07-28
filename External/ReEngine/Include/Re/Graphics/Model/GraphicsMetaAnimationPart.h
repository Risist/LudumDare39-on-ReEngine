#pragma once
#include <Re\Graphics\Model\GraphicsAnimationStep.h>

namespace Graphics
{
	/// WIP
	/// MetaAnimation is basicaly an animation which animates other animations
	class MetaAnimationPart : public Res::ISerialisable, public AnimationStepHolder
	{
	public:
		MetaAnimationPart(Step_t *step = nullptr):AnimationStepHolder(step) {}
		MetaAnimationPart(const char* path, Step_t *step = nullptr) :AnimationStepHolder(step) { deserialise(path); }
		MetaAnimationPart(std::istream& file, Res::DataScriptLoader&loader, Step_t *step = nullptr) :AnimationStepHolder(step) { deserialise(file, loader); }

		void onUpdateAnimation() const;

		/// returns how much speed were applied to ownet animation
		Step_t getSpeedInfluenceAtStep(Step_t step) const;

	public:
		Step_t speed{0.f};
		/// id of animation to edit by the step
		size_t animId{0};
		AnimationStep *controlledAnimation{nullptr};

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}