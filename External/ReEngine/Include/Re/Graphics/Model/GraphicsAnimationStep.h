#pragma once
#include <Re\Common\Settings.h>
#include <Re\Common\Scripts\ResScripts.h>
#include <Re\Common\Math\Math.h>
#include <limits>

namespace Graphics
{
	/// type for Animation Step counting purpose
	/// some floating point type
	using Step_t = float32;

	/// Decomposition of Animation step data
	/// gives ability to playback animation in sevral different ways
	/// used by AnimationController and MetaAnimationController
	class AnimationStep ///: public Res::ISerialisable
	{
	public:
		/// default constructor
		AnimationStep() = default;
		/// constructor initialising the AnimationStep from stream & loader
		AnimationStep(std::istream& file, Res::DataScriptLoader& loader) { deserialiseF(file, loader); }

		/// update animation step to play forward/backward (depended on sign of speed )
		/// if exceeds [stepMin, stepMax] range( inclusive) 
		/// then animation is aligned to the edge step value
		/// and stop played
		/// @return - did the animation have exceed [stepMin,stepMax] range?
		/// @arg:speedMultiplier - multiplies holded speed by the value
		bool updateInRange(Step_t speedMultiplier = 1.f);
		
		/// updates animation step to play forward/backward (depended on sign of speed )
		/// if exceeds [stepMin, stepMax] range( inclusive) 
		/// speed changes its sign and animation is played in other direction
		/// @return - did the animation have exceed [stepMin,stepMax] range?
		/// @arg:speedMultiplier - multiplies holded speed by the value
		bool updateReturn(Step_t speedMultiplier = 1.f);

		/// updates animation step to play forward/backward (depended on sign of speed )
		/// if exceeds [stepMin, stepMax] range( inclusive) 
		/// animation is looped and starts from @restartStep
		/// @return did the animation have exceed [stepMin,stepMax] range?
		/// @arg:speedMultiplier - multiplies holded speed by the value
		/// @arg:restartStep - tells what step is the beggining of the animation
		bool updateRestart(Step_t restartStep = 0, Step_t speedMultiplier = 1.f);

		/// updates animation step  to play in direstion of @towards
		/// @towards is clamped in [stepMin, stepMax] range( inclusive)
		/// @return - returns true when animation step is equal to @towards
		/// @arg:towards - desired step animation should be at in future
		/// @arg:speedMultiplier - increase/decrease speed of animation playback
		bool updateTowards( Step_t towards, Step_t speedMultiplier =1.f);

		/// update animation step to be in value of @newStep
		/// new step is clamped in [stepMin, stepMax] range( inclusive) 
		/// @return - did the animation have exceed [stepMin,stepMax] range?
		/// @arg:newStep - clamped new value of step
		bool setInRange(Step_t newStep);


		/// returns lenght of the animation
		Step_t getLenght() const { return stepMax - stepMin; }

		/// tells wether step of the AnimationStep is in given range
		bool isStepInRange(Step_t min, Step_t max) const
		{
			return step >= min && step <= max;
		}
		/// tells if given step is in range of the AnimationStep min/max
		bool isStepInRange(Step_t step) const
		{
			return step >= stepMin && step <= stepMax;
		}

		/// returns 1 or -1 dependingly on sign of speed
		Step_t getSpeedSign() const
		{
			return speed > 0 ? 1 : -1;
		}

	public:

		/// animation is only playable within the range of [stepMin, stepMax] inclusive
		Step_t stepMin{ 0 };
		Step_t stepMax{ 100.f };

		/// how fast the animation is played
		Step_t speed{ 1.f };
		/// which part the animation is in
		Step_t step{ 0.f };
	protected:
		void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const;
		void deserialiseF(std::istream& file, Res::DataScriptLoader& loader);
	};


	/// decomposition for classes which holds step from AnimationStep
	/// and reacts to it in some way
	/// used in AnimationPart and MetaAnimationPart
	class AnimationStepHolder ///: Res::ISerialisable
	{
	public:
		AnimationStepHolder(Step_t *_step = nullptr) : step(_step) {}
		/// deserialise from loader
		AnimationStepHolder(std::istream& file, Res::DataScriptLoader& loader, Step_t *_step = nullptr) 
			: step(_step) { deserialiseF(file, loader); }


	public:
		/// gets step which should be used to compute animation
		Step_t getActualStep() const
		{
			assert(step);
			return stepOffset + clamp(*step, stepMin, stepMax);
		}

		/// returns lenght of the animation
		Step_t getLenght() const { return stepMax - stepMin; }

		/// tells wether step of the AnimationStep is in given range
		bool isStepInRange(Step_t min, Step_t max) const
		{
			assert(step);
			return *step >= min && *step <= max;
		}
		/// tells if given step is in range of the AnimationStep min/max
		bool isStepInRange(Step_t step) const
		{
			return step >= stepMin && step <= stepMax;
		}
		/// tells whether the animation is playable at the moment
		bool isPlayable() const
		{
			assert(step);
			return *step >= stepMin && *step <= stepMax;
		}


	public:
		/// animation is only playable within the range of [stepMin, stepMax] inclusive
		Step_t stepMin{ -numeric_limits<Step_t>::max() };
		Step_t stepMax{ numeric_limits<Step_t>::max() }; 
		
		/// offset in animation, defines at which step the animation makes no influence
		Step_t stepOffset{ 0 };
		/// which part the animation is in
		/// takes a look on Controllers parametr
		Step_t *step;

	protected:
		void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const;
		void deserialiseF(std::istream& file, Res::DataScriptLoader& loader);
	};

}