#include <pch.h>
#include "Piece.hpp"

char g_arrGrids[numXGrids][numYGrids] = { 0 };

CPiece::CPiece(EPieceType piece, SVec2 vecPos) : m_ePieceType(piece), m_vecPivot(vecPos) {
	UpdatePiece(); // update piece so it's not hidden for 1 frame

	// @todo: finish new poitioning system XD
	auto lol = g_pieceBounds[0][0][0][0];
}

void CPiece::MoveEvent() {
	UpdatePiece(true); // destroy the previous placement of the piece
	
	// update position and stop at the bottom of the board
	//bool shouldCollideOne = g_pieceBounds[m_ePieceType][3][1] || g_pieceBounds[m_ePieceType][3][2] || g_pieceBounds[m_ePieceType][3][3];
	//bool shouldCollideTwo = g_pieceBounds[m_ePieceType][4][1] || g_pieceBounds[m_ePieceType][4][2] || g_pieceBounds[m_ePieceType][4][3];

	//bool isCollidingWithFloor = false;
	//if (shouldCollideTwo && m_vecPivot.y == numYGrids - 3)
	//	isCollidingWithFloor = true;
	//else if(shouldCollideOne && m_vecPivot.y == numYGrids - 2)
	//	isCollidingWithFloor = true;
	//else if (m_vecPivot.y == numYGrids - 1)
	//	isCollidingWithFloor = true;

	//bool isColliding = isCollidingWithFloor;
	//if (!isColliding)
	//	m_vecPivot.y++;

	UpdatePiece(); // set up its new position
}

void CPiece::UpdatePiece(bool destroy) {
	for (int gridX = 0; gridX < pieceMaxX; gridX++) {
		for (int gridY = 0; gridY < pieceMaxY; gridY++) {
			SVec2 boardGrids = { (m_vecPivot.x - 2) + gridX, (m_vecPivot.y - 2) + gridY };
			//char currentState = g_pieceBounds[m_ePieceType][gridY][gridX];

			//g_arrGrids[boardGrids.x][boardGrids.y] = destroy ? !destroy : currentState;
		}
	}
}

void CPiece::OnInput(SDL_Event event) {
	int scanCode = event.key.keysym.scancode;
	switch (event.type) {
	case SDL_KEYDOWN:
		// move left or right depending on our move direction
		if (m_bCanMovePiece) {
			int moveDir = scanCode == SDL_SCANCODE_LEFT ? -1 : scanCode == SDL_SCANCODE_RIGHT ? 1 : 0;
			m_vecPivot.x += moveDir;

			// make sure we update the piece
			UpdatePiece();

			m_bCanMovePiece = false;
		}

		// move down faster if we pressing down
		m_iUpdateRate = scanCode == SDL_SCANCODE_DOWN ? defaultUpdateRate - 10 : defaultUpdateRate;
		break;

	case SDL_KEYUP:
		switch (scanCode) {
		case SDL_SCANCODE_LEFT:
		case SDL_SCANCODE_RIGHT: 
			m_bCanMovePiece = true;
			break;
		case SDL_SCANCODE_Z:
		case SDL_SCANCODE_X:
			break;
		case SDL_SCANCODE_DOWN:
			m_iUpdateRate = defaultUpdateRate; 
			break;
		}
		break;
	}
}