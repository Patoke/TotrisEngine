#pragma once
#include "Piece.hpp"

class CGame {
private:
	SDL_Rect m_rBounds;
public:
	CGame(SDL_Rect m_rBounds) : m_rBounds(m_rBounds) {}

	void Render();
	void Input(SDL_Event event);

	int m_iScore = 0;

private:
	void Logic();
	void RenderBoard();

	int m_iCurrFrame = 0;
	CPiece m_cCurrPiece{};
};

extern std::shared_ptr<CGame> g_pGame;