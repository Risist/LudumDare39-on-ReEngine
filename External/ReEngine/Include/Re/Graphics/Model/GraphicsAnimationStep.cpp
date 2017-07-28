#include <Re\Graphics\Model\GraphicsAnimationStep.h>

namespace Graphics
{


	///////////////////////////// Step

	bool AnimationStep::updateInRange(Step_t speedMultiplier)
	{
		Step_t _speed = speed*speedMultiplier;
		if (_speed + step > stepMax)
		{
			step = stepMax;
			return true;
		}
		else if (_speed + step < stepMin)
		{
			step = stepMin;
			return true;
		}
		else
		{
			step += _speed;
			return false;
		}
	}

	bool AnimationStep::updateReturn(Step_t speedMultiplier)
	{
		Step_t _speed = speed*speedMultiplier;
		if (_speed + step > stepMax)
		{
			step = stepMax;
			speed *= -1;
			return true;
		}
		else if (_speed + step < stepMin)
		{
			step = stepMin;
			speed *= -1;
			return true;
		}
		else
		{
			step += _speed;
			return false;
		}
	}

	bool AnimationStep::updateRestart(Step_t restartStep, Step_t speedMultiplier)
	{
		Step_t _speed = speed*speedMultiplier;
		if (_speed + step > stepMax || _speed + step < stepMin)
		{
			step = restartStep;
			return true;
		}
		else
		{
			step += _speed;
			return false;
		}
	}

	bool AnimationStep::updateTowards(Step_t towards, Step_t speedMultiplier)
	{
		Step_t _speed = speed*speedMultiplier;
		towards = clamp(towards, stepMin, stepMax);

		if (step > towards)
		{
			_speed = -abs(_speed);
			if (step + _speed < towards)
			{
				step = towards;
				return true;
			}
		}
		else
		{
			_speed = abs(_speed);
			if (step + _speed > towards)
			{
				step = towards;
				return true;
			}
		}

		step += _speed;
		return false;
	}

	bool AnimationStep::setInRange(Step_t newStep)
	{
		if (newStep >= stepMax)
			step = stepMax;
		else if (newStep <= stepMin)
			step = stepMin;
		else
		{
			step = newStep;
			return false;
		}
		return true;
	}

	void AnimationStep::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save("step", step);
		saver.save("stepMin", stepMin);
		saver.save("stepMax", stepMax);
		saver.save("speed", speed);
	}

	void AnimationStep::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		step = loader.load("step", 0.f);
		stepMin = loader.load("stepMin", 0.f);
		stepMax = loader.load("stepMax", 100.f);
		speed = loader.load("speed", 1.f);
	}


	///////////////////////////// Holder

	void AnimationStepHolder::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save("stepOffset", stepOffset);
		saver.save("stepMin", stepMin);
		saver.save("stepMax", stepMax);
	}

	void AnimationStepHolder::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		stepOffset = loader.load("stepOffset", 0.f);
		stepMin = loader.load("stepMin", -std::numeric_limits<Step_t>::max() );
		stepMax = loader.load("stepMax",  std::numeric_limits<Step_t>::max() );
	}

}