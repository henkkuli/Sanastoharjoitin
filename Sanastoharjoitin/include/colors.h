#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <ostream>

enum consoleFrontColor {
	f_black = 0,
	f_dark_blue = 1,
	f_dark_green = 2,
	f_dark_aqua = 3, f_dark_cyan = 3,
	f_dark_red = 4,
	f_dark_purple = 5, f_dark_pink = 5, f_dark_magenta = 5,
	f_dark_yellow = 6,
	f_dark_white = 7,
	f_gray = 8,
	f_blue = 9,
	f_green = 10,
	f_aqua = 11, f_cyan = 11,
	f_red = 12,
	f_purple = 13, f_pink = 13, f_magenta = 13,
	f_yellow = 14,
	f_white = 15
};
enum consoleBackColor {
	b_black = 0 << 4,
	b_dark_blue = 1 << 4,
	b_dark_green = 2 << 4,
	b_dark_aqua = 3 << 4, b_dark_cyan = 3 << 4,
	b_dark_red = 4 << 4,
	b_dark_purple = 5 << 4, b_dark_pink = 5 << 4, b_dark_magenta = 5 << 4,
	b_dark_yellow = 6 << 4,
	b_dark_white = 7 << 4,
	b_gray = 8 << 4,
	b_blue = 9 << 4,
	b_green = 10 << 4,
	b_aqua = 11 << 4, b_cyan = 11 << 4,
	b_red = 12 << 4,
	b_purple = 13 << 4, b_pink = 13 << 4, b_magenta = 13 << 4,
	b_yellow = 14 << 4,
	b_white = 15 << 4
};
extern HANDLE _stdConsoleHandle;
extern consoleFrontColor _stdFrontColor;
extern consoleBackColor _stdBackColor;

inline std::ostream& operator<< (std::ostream& stream, const consoleFrontColor c) {
	if (!_stdConsoleHandle) {
		_stdConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	_stdFrontColor = c;
	unsigned short wAttribs = _stdBackColor | _stdFrontColor;
	SetConsoleTextAttribute(_stdConsoleHandle, wAttribs);
	return stream;
}

inline std::ostream& operator<< (std::ostream& stream, const consoleBackColor c) {
	if (!_stdConsoleHandle) {
		_stdConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	_stdBackColor = c;
	unsigned short wAttribs = _stdBackColor | _stdFrontColor;
	SetConsoleTextAttribute(_stdConsoleHandle, wAttribs);
	return stream;
}


#else
#error "Other operating systems than Windows are not supported, yet"
#endif
