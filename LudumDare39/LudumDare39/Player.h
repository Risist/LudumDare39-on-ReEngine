#pragma once
#include <Re\ReEngine.h>


class Player : public Game::Actor
{
public:
	static Player *player;

	/// virtual overrides
	void onInit() override;
	void onUpdate(sf::Time dt) override;
	bool onDeath(sf::Time dt) override;

	/// animations
	Graphics::AnimationController *animWalk{nullptr};
	
	Graphics::AnimationController *animCast{ nullptr }; 
	bool onAnimCast{ false };
	bool onAnimCastBack{ false };


	Graphics::AnimationController *animRule{ nullptr };

	/// efect ptrs
	//Efect::StaticMovement *efMovement;
	Efect::MouseMovement *efMovement;
	Efect::Health *efHealth;
	Efect::Model *efModel;


	Gui::ProgressBar* healthBar;
	Gui::ProgressBar* rageBar;
};