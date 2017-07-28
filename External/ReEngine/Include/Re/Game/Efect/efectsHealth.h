#pragma once

/// health holder
#include <Re\Game\Efect\Health\EfectHealth.h>

/// 
#include <Re\Game\Efect\Health\EfectDamageOnCollision.h>
#include <Re\Game\Efect\Health\EfectSpawnOnDeath.h>

/**
Basic components added for health management.

Efect::Health holds health propertites, regeneration, dealing dmg / heal

Efect::DamageOnCollision - deals damage(or heal as negative value)
has 3 modes : enter, stay, and exit indicading when will deal damage

Efect::SpawnOnDeath spawns new actor at death(see Efect::Throw for more info)
/**/