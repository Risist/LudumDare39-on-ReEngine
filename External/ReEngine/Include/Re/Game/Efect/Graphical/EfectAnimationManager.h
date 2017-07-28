#pragma once
#include <Re\Game\Efect\EfectBase.h>
#include <Re\Graphics\Model\GraphicsAnimationController.h>
#include <Re\Graphics\ResourceManager.h>

namespace Efect
{
	/// class to maintain animations
	/// since animation need to be updated separately from models
	/// this component is able does the job
	///
	/// class as well allows to turn on/off choosen animation
	class AnimationManager : public Base
	{
	public:
		AnimationManager(vector<Graphics::Model*>& _modelsUpdate)
			: modelsUpdate(_modelsUpdate)
		{
		}
		virtual void onUpdate(sf::Time dt) override;

		AnimationManager* addAnimation(ResId scriptId, Graphics::Step_t scale = 1.f)
		{
			controllers.push_back(make_unique<Graphics::AnimationController>());
			controllers.back()->deserialiseFromString(scriptInst[scriptId]);
			controllers.back()->attachToModel(modelsUpdate);
			
			controllersScale.push_back(scale);
			scaleSum += scale;
			return this;
		}
		AnimationManager* addAnimation(const char* path, Graphics::Step_t scale = 1.f)
		{
			controllers.push_back(make_unique<Graphics::AnimationController>(path));
			controllers.back()->attachToModel(modelsUpdate);
			
			controllersScale.push_back(scale);
			scaleSum += scale;
			return this;
		}
		AnimationManager* removeAnimation(size_t id)
		{
			assert(controllersScale.size() > id);
			scaleSum -= controllersScale[id];
			controllers.erase(controllers.begin() + id);
			controllersScale.erase(controllersScale.begin() + id);

			return this;
		}

		/// disables all animation beside one specific
		AnimationManager* activateOneAnimation(size_t id, Graphics::Step_t scale = 1.f);
		AnimationManager* activateAnimation(size_t id, Graphics::Step_t scale)
		{
			assert(controllersScale.size() > id);
			scaleSum += scale - controllersScale[id];
			controllersScale[id] = scale;
			return this;
		}
		Graphics::AnimationController& getAnimation(size_t id)
		{
			assert(controllers.size() > id);
			return *controllers[id];
		}
		Graphics::AnimationController& getAnimation()
		{
			return *controllers.back();
		}

		Graphics::Step_t getScale(size_t id) const { return controllersScale[id]; }
		Graphics::Step_t getScaleSum() const { return scaleSum; }

		size_t animationCount() const { return controllers.size(); }

	private:
		/// animations holded and managed in the class
		vector<unique_ptr<Graphics::AnimationController>> controllers;
		vector<Graphics::Step_t> controllersScale;
		Graphics::Step_t scaleSum;

		vector<Graphics::Model*>& modelsUpdate;
	};


}