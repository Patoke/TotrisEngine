#include <pch.h>
#include "Logic.hpp"

static CPiece testPiece{ PIECE_I, {5, 0} };
void CGame::Render() {
	this->Logic();
	this->RenderBoard();
}

void CGame::Input(SDL_Event event) {
	testPiece.OnInput(event);
}

static int iCurrFrame = 0;
void CGame::Logic() {
	iCurrFrame++;

	if (iCurrFrame % testPiece.m_iUpdateRate)
		return;
	iCurrFrame = 0; // prevent integer overflow

	testPiece.MoveEvent();
}

void CGame::RenderBoard() {
	int scoreBoardX = m_rBounds.x + m_rBounds.w - m_rBounds.w / 3;
	SDL_Rect playArea = { m_rBounds.x, m_rBounds.y, m_rBounds.w - m_rBounds.w / 3, m_rBounds.h };
	SVec2 gridBox = { playArea.w / numXGrids, playArea.h / numYGrids };

	g_pWindow->DrawRect(m_rBounds, { 255, 100, 100, 255 });
	g_pWindow->DrawLine({ scoreBoardX, m_rBounds.y}, { scoreBoardX, m_rBounds.y + m_rBounds.h - 1 }, { 255, 100, 100, 255 });

	// Test draw grids
	for (int gridX = 0; gridX < numXGrids; gridX++) {
		for (int gridY = 0; gridY < numYGrids; gridY++) {
			SDL_Rect currGrid = { playArea.x + gridBox.x * gridX, playArea.y + gridBox.y * gridY, gridBox.x, gridBox.y };

			if (g_arrGrids[gridX][gridY] == 2)
				g_pWindow->DrawRectFilled(currGrid, { 100, 100, 255, 255 });
			else if(g_arrGrids[gridX][gridY] == 1)
				g_pWindow->DrawRectFilled(currGrid, { 100, 255, 100, 255 });
			else if(g_arrGrids[gridX][gridY] == 0)
				g_pWindow->DrawRect(currGrid, { 100, 255, 100, 255 });
		}
	}
}