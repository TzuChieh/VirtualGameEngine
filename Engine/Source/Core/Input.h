#pragma once

#include "Common/type.h"

namespace xe
{

enum class KeyCode : uint32;

class Input
{
public:
	virtual bool init() = 0;
	virtual void update() = 0;
	virtual void decompose() = 0;

	// Returns true if the key was detected as released after last update and pressed 
	// after current update; otherwise, false is returned.
	virtual bool isKeyDown(KeyCode keyCode) const = 0;

	// Returns true if the key was detected as pressed after last update and released 
	// after current update; otherwise, false is returned.
	virtual bool isKeyUp(KeyCode keyCode) const = 0;

	// Returns true if the key is continuously being pressed. Notice that this method 
	// will return false while isKeyDown() or isKeyUp() is true.
	virtual bool isKeyHold(KeyCode keyCode) const = 0;
};

enum class KeyCode : uint32
{
	// unknow/unsupported key
	UNKNOWN = 0U,

	// F<X> keys
	F1 = 1U,
	F2 = 2U,
	F3 = 3U,
	F4 = 4U,
	F5 = 6U,
	F6 = 6U,
	F7 = 7U,
	F8 = 8U,
	F9 = 9U,
	F10 = 10U,
	F11 = 11U,
	F12 = 12U,

	// characters
	A = 20U,
	B = 21U,
	C = 22U,
	D = 23U,
	E = 24U,
	F = 25U,
	G = 26U,
	H = 27U,
	I = 28U,
	J = 29U,
	K = 30U,
	L = 31U,
	M = 32U,
	N = 33U,
	O = 34U,
	P = 35U,
	Q = 36U,
	R = 37U,
	S = 38U,
	T = 39U,
	U = 40U,
	V = 41U,
	W = 42U,
	X = 43U,
	Y = 44U,
	Z = 45U
};

}