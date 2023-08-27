#pragma once
#include "Piece.hpp"

class CGame {
private:
	SDL_Rect m_rBounds;
public:
	CGame(SDL_Rect m_rBounds) : m_rBounds(m_rBounds) {}

	void Render();
	void Input();

private:
	void Logic();
	void RenderBoard();
};

extern std::shared_ptr<CGame> g_pGame;