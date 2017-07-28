#include <Re\Graphics\Model\GraphicsAnimationController.h>
#include <Re\Graphics\Model\GraphicsModel.h>

namespace Graphics
{

	AnimationController::AnimationController()
	{
	}

	AnimationController::AnimationController(const char * path)
	{
		deserialise(path);
	}

	void AnimationController::onUpdateModel(Step_t scale)
	{
		for (auto it : parts)
			it.onUpdateModel( scale );
	}

	
	void AnimationController::addPart(const AnimationPart& newPart)
	{
		parts.push_back(newPart);
		parts.back().step = &step;
	}

	
	void AnimationController::attachToModel(Model & model)
	{
		vector<Model*> rewritedVector;
		model.rewriteToVectorUpdate(rewritedVector);

		for (auto&it : parts)
		{
			assert(it.modelId < rewritedVector.size());
			it.defToUpdate = &rewritedVector[it.modelId]->actualDef;
		}
	}

	void AnimationController::attachToModel(vector<Model*>& model)
	{
		for (auto&it : parts)
		{
			assert(it.modelId < model.size());
			it.defToUpdate = &model[it.modelId]->actualDef;
		}
	}
	/**/
	/// helper struct to force zero sonstructor at ModelDef
	struct Df : public ModelDef
	{
		Df() :ModelDef(ModelDef::zero) {}
	};
	void AnimationController::insertBackSteps(Step_t min, Step_t max, Step_t initial)
	{
		Step_t stepLenght = 1/(max - min);
		/// sum of steps at min
		
		std::map<  int, Df> partsDef;

		for (auto &it : parts)
			partsDef[it.modelId] += it.getDefAtStep(min) - it.getDefAtStep(initial);

		for (auto &it : partsDef)
		{
			addPart(AnimationPart(it.first, it.second *-stepLenght, min, max) );
			parts.back().stepOffset = -min;
		}
	}

	void AnimationController::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
#ifdef RE_ENGINE
		/// animation serialization available only in editor
		/// TODO
#endif // RE_ENGINE
	}

	void AnimationController::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		AnimationStep::deserialiseF(file, loader);

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			string type = loader.load<string>("type", "part");

			if (type == "part")
			{
				addPart(AnimationPart(file, loader));
			}
			else if( type == "back")
			{
				Step_t initial = loader.load("initial", 0);
				Step_t min = loader.load("stepMin", 0);
				Step_t max = loader.load("stepMax", 0);
				insertBackSteps(min, max, initial);
			}
			else
			{
				cerr << "AnimationController: load type = " << type << " is undefined\n";
			}
		}
	}

}