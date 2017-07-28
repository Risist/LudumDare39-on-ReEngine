#pragma once

// sfml
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <SFML\Audio.hpp>
using namespace sf;

// box 2d
#include <Box2D\Box2D.h>

// thor
#include <Thor\Math.hpp>
#include <Thor\Resources.hpp>
#include <Thor\Particles.hpp>
#include <Thor\Input.hpp>
#include <Thor\Animations.hpp>


// std
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>

using namespace std;

#ifndef M_PI
#define M_PI		3.14159265359f
#endif


/// Constant sized types
typedef signed char	int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long int int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long int uint64;
typedef float float32;
typedef double float64;




extern int32 velocityIterations;
extern int32 positionIterations;


/// since box2d operates in meters whereas sfml uses pixels
/// we need an way to conwerts those systems
/// multiplay an vector/pos scalar by appropriate conversion value
extern const float toB2Position;
extern const float toSfPosition;