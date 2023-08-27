#ifndef PCH_H
#define PCH_H

// windows headers
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Psapi.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <intrin.h>

// std headers
#include <array>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <unordered_map>
#include <functional>
#include <format>
#include <numbers>
#include <print>
#include <assert.h>

// SDL (m_pRenderer) headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

// Engine headers
#include "Color.hpp"
#include "Vec2.hpp"

#endif //PCH_H