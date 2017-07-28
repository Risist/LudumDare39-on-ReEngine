#include <Re\Graphics\Model\GraphicsAnimationPart.h>
#include <Re\Common\Math\Math.h>

namespace Graphics
{
	AnimationPart::AnimationPart()
	{
	}
	AnimationPart::AnimationPart(size_t _modelId, const ModelDef& modelDef, Step_t _stepMin, Step_t _stepMax)
		: ModelDef(modelDef), modelId(_modelId)
	{
		stepMin = _stepMin;
		stepMax = _stepMax;
	}
	AnimationPart::AnimationPart(char * path)
	{
		deserialise(path);
	}
	void AnimationPart::onUpdateModel(Step_t scale) const
	{
		assert(defToUpdate);
		countOffset(*defToUpdate, scale);
	}
	void AnimationPart::countOffset(ModelDef & out, Step_t _scale) const
	{
		assert(step != nullptr);

		out.color += color *getActualStep() *_scale;
		out.pos += pos *getActualStep()*_scale;
		out.scale += scale*getActualStep()*_scale;
		out.rotAround += rotAround * getActualStep()*_scale;
		out.rot += rot * getActualStep()*_scale;
		out.rotSprite += rotSprite * getActualStep()*_scale;
		out.origin += origin *getActualStep()*_scale;
	}
	ModelDef AnimationPart::getDefAtStep(Step_t step) const
	{
		return (ModelDef)(*this) *  ( clamp(step, stepMin, stepMax) + stepOffset);
	}

	void AnimationPart::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		/// serialization of animation available only in editor
#	ifdef RE_EDITOR
		ModelDef::serialiseF(file, saver);

		saver.save("model", modelId);
		AnimationStepHolder::serialiseF(file, saver);
#	endif // RE_EDITOR
	}
	void AnimationPart::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		//ModelDef::deserialiseF(file, loader);	
		
		pos.x = loader.load("posX", ModelDef::zero.pos.x);
		pos.y = loader.load("posY", ModelDef::zero.pos.y);

		origin.x = loader.load("originX", ModelDef::zero.origin.x);
		origin.y = loader.load("originY", ModelDef::zero.origin.y);

		scale.x = loader.load("scaleX", ModelDef::zero.scale.x);
		scale.y = loader.load("scaleY", ModelDef::zero.scale.y);

		rot = Degree(loader.load("rot", ModelDef::zero.rot.asDegree()));
		rotAround = Degree(loader.load("rotAround", ModelDef::zero.rotAround.asDegree()));
		rotSprite = Degree(loader.load("rotSprite", ModelDef::zero.rotSprite.asDegree()));

		color.r = loader.load("clR", ModelDef::zero.color.r);
		color.g = loader.load("clG", ModelDef::zero.color.g);
		color.b = loader.load("clB", ModelDef::zero.color.b);
		color.a = loader.load("clA", ModelDef::zero.color.a);

		/////
		modelId = loader.load("model", (size_t)0);

		AnimationStepHolder::deserialiseF(file, loader);
	}
}