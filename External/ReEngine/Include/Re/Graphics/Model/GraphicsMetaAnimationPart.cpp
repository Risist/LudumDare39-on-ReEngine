#include <Re\Graphics\Model\GraphicsMetaAnimationPart.h>

namespace Graphics
{




	void MetaAnimationPart::onUpdateAnimation() const
	{
		assert(controlledAnimation);
		/// step is increased
		/// before model update clamp the value
		/// and after make it 0
		controlledAnimation->step += speed*getActualStep();
	}

	Step_t MetaAnimationPart::getSpeedInfluenceAtStep(Step_t step) const
	{
		return step*speed;
	}

	void MetaAnimationPart::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		AnimationStepHolder::serialiseF(file, saver);

		saver.save<Step_t>("speed", speed);
		saver.save<size_t>("animId", animId);
	}

	void MetaAnimationPart::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		AnimationStepHolder::deserialiseF(file, loader);

		speed = loader.load<Step_t>("speed", 0.f);
		animId = loader.load<size_t>("animId", 0);
	}

}