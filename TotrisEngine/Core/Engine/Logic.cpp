#include <pch.h>
#include "Logic.hpp"

void CGame::Render() {
	this->Logic();
	this->RenderBoard();
}

void CGame::Input(SDL_Event event) {
	m_cCurrPiece.OnInput(event);
}

static int iCurrFrame = 0;
void CGame::Logic() {
	iCurrFrame++;

	if (iCurrFrame % m_cCurrPiece.m_iUpdateRate)
		return;
	iCurrFrame = 0; // prevent integer overflow

	m_cCurrPiece.MoveEvent();
}

void CGame::RenderBoard() {
	int scoreBoardX = m_rBounds.x + m_rBounds.w - m_rBounds.w / 3;
	SDL_Rect playArea = { m_rBounds.x, m_rBounds.y, m_rBounds.w - m_rBounds.w / 3, m_rBounds.h };
	// this is to avoid big tetrominos from clipping into other lanes
	int extraYSize = (playArea.h / (numYGrids - yGiveRoom)) * yGiveRoom;

	SVec2 gridBox = { playArea.w / numXGrids, (playArea.h + extraYSize) / numYGrids };

	// Test draw grids
	for (int gridX = 0; gridX < numXGrids; gridX++) {
		for (int gridY = yGiveRoom; gridY < numYGrids; gridY++) {
			SDL_Rect currGrid = { playArea.x + gridBox.x * gridX, playArea.y - extraYSize + gridBox.y * gridY, gridBox.x, gridBox.y };

			if (g_arrGrids[gridX][gridY] == 2)
				g_pWindow->DrawRectFilled(currGrid, { 100, 100, 255, 255 });
			else if(g_arrGrids[gridX][gridY] == 1)
				g_pWindow->DrawRectFilled(currGrid, { 100, 255, 100, 255 });
		}
	}

	g_pWindow->DrawRect(m_rBounds, { 255, 100, 100, 255 });
	g_pWindow->DrawLine({ scoreBoardX, m_rBounds.y }, { scoreBoardX, m_rBounds.y + m_rBounds.h - 1 }, { 255, 100, 100, 255 });
}