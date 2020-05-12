#pragma once
class VSize {
public:
	VSize(size_t x, size_t y, size_t w, size_t h) {
		if (x < 0 ||
			y < 0 ||
			w < 0 ||
			h < 0) {
			_x = 0;
			_y = 0;
			_w = 0;
			_h = 0;
		}
		else {
			_x = x;
			_y = y;
			_w = w;
			_h = h;
		}
	}
	VSize() {
		_x = 0;
		_y = 0;
		_w = 0;
		_h = 0;
	}
	size_t _x;
	size_t _y;
	size_t _w;
	size_t _h;
};