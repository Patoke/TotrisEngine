#pragma once
// code from https://github.com/Patoke/easypos/blob/main/src/position.hpp

// raw defines for position and size, these don't have any usage more than define the variables they contain and operators
template<typename T = int>
struct SPosition {
    T x, y;

    SPosition(T&& x, T&& y) : x(x), y(y) {}

    T& operator[](int i) {
        return ((T*)this)[i];
    }

    T operator[](int i) const {
        return ((T*)this)[i];
    }

    inline SPosition operator+(const SPosition& other) const {
        return SPosition(this->x + other.x, this->y + other.y);
    }

    inline SPosition operator-(const SPosition& other) const {
        return SPosition(this->x - other.x, this->y - other.y);
    }

    inline SPosition operator/(const float& val) const {
        return SPosition(this->x / val, this->y / val);
    }

    inline SPosition operator*(const float& val) const {
        return SPosition(this->x * val, this->y * val);
    }

    inline SPosition operator-=(const SPosition& other) {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }
};

// usage defines, these contain all the helpers for these specific types unlike raw defines
struct SVec2 : SPosition<int> {
    SVec2() : SPosition<int>(0, 0) {}

    template<typename arg1, typename arg2>
    SVec2(arg1&& x, arg2&& y) : SPosition(static_cast<float>(x), static_cast<float>(y)) {}

    SVec2(const SPosition& other) : SVec2(other.x, other.y) {}

    // CAUTION: UNSAFE
    // allows to pass direct references to other types (like ImVec2, ex: vec2 = &ImVec2.x)
    SVec2(const int* other) : SVec2(other[0], other[1]) {};

    inline SVec2 Rounded(bool should_round = true) const {
        return should_round ? SVec2(round(this->x), round(this->y)) : *this;
    }
};