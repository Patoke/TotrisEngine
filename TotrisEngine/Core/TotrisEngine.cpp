#include <pch.h>
#include "Engine/Util/Renderer.hpp"
#include "Engine/Logic.hpp"

std::shared_ptr<CWindow> g_pWindow;
std::shared_ptr<CGame> g_pGame;

int WINAPI wWinMain([[maybe_unused]] HINSTANCE hInstance,
	[[maybe_unused]] HINSTANCE hPrevInstance,
	[[maybe_unused]] PWSTR pCmdLine,
	[[maybe_unused]] int nCmdShow)
{
#ifdef _DEBUG
	AllocConsole();
	freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
	freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
#endif

	// specify main m_pWindow bounds and name
	g_pWindow = std::make_shared<CWindow>("Totris", SDL_Rect(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600));
	g_pGame = std::make_shared<CGame>(SDL_Rect(100, 50, 404, 506)); // specify game bounds

	while (!g_pWindow->HasToExit()) {
		g_pWindow->RunInput([](SDL_Event event) {
			g_pGame->Input(event);
			});

		g_pWindow->SetRenderColor({ 25, 25, 25, 255 });
		g_pWindow->CreateFrame();

		g_pGame->Render();

		g_pWindow->RenderFrame();
	}
	
	g_pWindow->Destroy();

	return TRUE;
}