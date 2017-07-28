#include <Re\Graphics\Model\GraphicsMetaAnimationController.h>

namespace Graphics
{
	///
	void MetaAnimationController::onUpdateAnimation() const
	{
		for (auto it : parts)
			it.onUpdateAnimation();
	}
	
	///
	void MetaAnimationController::attachToAnimation(std::vector<AnimationController>& animations)
	{
		for (auto it = parts.begin(); it != parts.end(); ++it)
			it->controlledAnimation = &animations[it->animId];
	}
	void MetaAnimationController::attachToAnimation(std::vector<AnimationController*>& animations)
	{
		for (auto it = parts.begin(); it != parts.end(); ++it)
			it->controlledAnimation = animations[it->animId];
	}
	void MetaAnimationController::attachToAnimation(std::vector<unique_ptr<AnimationController>>& animations)
	{
		for (auto it = parts.begin(); it != parts.end(); ++it)
			it->controlledAnimation = animations[it->animId].get();
	}
	void MetaAnimationController::attachToAnimation(std::vector<shared_ptr<AnimationController>>& animations)
	{
		for (auto it = parts.begin(); it != parts.end(); ++it)
			it->controlledAnimation = animations[it->animId].get();
	}

	///
	void MetaAnimationController::insertBackSteps(Step_t min, Step_t max, Step_t initial)
	{
	}
	
	///
	void MetaAnimationController::addPart(const MetaAnimationPart & newPart)
	{
		parts.push_back(newPart);
	}
	void MetaAnimationController::addPart(const char * path)
	{
		parts.push_back(MetaAnimationPart(path));
	}	
	void MetaAnimationController::addPart(std::istream & file, Res::DataScriptLoader & loader)
	{
		parts.push_back(MetaAnimationPart(file, loader));
	}
	
	///
	void MetaAnimationController::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		AnimationStep::serialiseF(file, saver);
		/// TODO
	}
	void MetaAnimationController::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		AnimationStep::deserialiseF(file, loader);

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			string type = loader.load<string>("type", "part");

			if (type == "part")
			{
				addPart(file, loader);
			}
			else if (type == "back")
			{
				Step_t initial = loader.load("initial", 0);
				Step_t min = loader.load("stepMin", 0);
				Step_t max = loader.load("stepMax", 0);
				insertBackSteps(min, max, initial);
			}
			else
			{
				cerr << "MetaAnimationController: load type = " << type << " is undefined\n";
			}
		}
	}
}