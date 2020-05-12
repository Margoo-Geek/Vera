#pragma once
#include "VObject.h"

class wId {
	_private HWND id;
	_public wId(HWND id) {
		this->id = id;
	}
	_public HWND windowId() {
		return id;
	}
};