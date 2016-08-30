#pragma once

#include "Common/type.h"

namespace ve
{

enum class KeyCode : uint32;
enum class MouseButtonCode : uint32;

class EngineProxy;

class Input
{
public:
	virtual ~Input() = 0;

	virtual void update() = 0;

	// "Virtualize Cursor" means to hide the cursor and gives user a sense of unlimitted
	// cursor movement, i.e., the cursor will never be able to exit the platform's display.
	// Note that under this mode the absolute position of the cursor is unreliable, only 
	// relative measurements have their meanings.
	virtual void virtualizeCursor() const = 0;
	virtual void unvirtualizeCursor() const = 0;

	// Returns true if the key/button was detected as released after last update and pressed 
	// after current update; otherwise, false is returned.
	virtual bool isKeyDown(KeyCode keyCode) const = 0;
	virtual bool isMouseButtonDown(MouseButtonCode mouseButtonCode) const = 0;

	// Returns true if the key/button was detected as pressed after last update and released 
	// after current update; otherwise, false is returned.
	virtual bool isKeyUp(KeyCode keyCode) const = 0;
	virtual bool isMouseButtonUp(MouseButtonCode mouseButtonCode) const = 0;

	// Returns true if the key/button is continuously being pressed. Notice that this method 
	// will return false while is<X>Down() or is<X>Up() is true.
	virtual bool isKeyHold(KeyCode keyCode) const = 0;
	virtual bool isMouseButtonHold(MouseButtonCode mouseButtonCode) const = 0;

	// Returns cursor absolute position in 2-D Cartesian coordinate system (right: +x, 
	// top: +y, origin is on the lower-left corner of the platform's display).
	virtual void getCursorPositionPx(float64* out_x, float64* out_y) const = 0;

	// Returns cursor movement between last two updates in 2-D Cartesian coordinate 
	// system (right: +x, top: +y).
	virtual void getCursorMovementDeltaPx(float64* out_dx, float64* out_dy) const = 0;
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
	Z = 45U,

	// the maximum KeyCode value
	LAST = 45U
};

enum class MouseButtonCode : uint32
{
	// unknow/unsupported mouse button
	UNKNOWN = 0U,

	// mouse buttons
	LEFT   = 1U,
	//MIDDLE = 2U,
	RIGHT  = 3U,

	// the maximum MouseButtonCode value
	LAST = 3U
};

}