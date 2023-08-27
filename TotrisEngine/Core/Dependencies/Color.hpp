#pragma once

class Color {
public:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	union {
		uint32_t col;
	};

	constexpr Color(uint32_t col) : col(col) {}

	constexpr Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}

	constexpr Color(float r, float g, float b, float a) : r(int(r / 255)), g(int(g / 255)), b(int(b / 255)), a(int(a / 255)) {}

	Color Lerp(Color&& to, float t) {
		return Color(std::lerp<uint32_t>(col, to.col, t));
	}
};