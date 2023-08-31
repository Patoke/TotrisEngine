#include <pch.h>
#include "Piece.hpp"

char g_arrGrids[numXGrids][numYGrids] = { 0 };

CPiece::CPiece(EPieceType piece, SVec2 vecPos) : m_ePieceType(piece), m_vecPivot(vecPos) {
	UpdatePiece(); // update piece so it's not hidden for 1 frame
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
			char currentState = g_pieceBounds[m_ePieceType][m_iRotation][gridY][gridX];

			g_arrGrids[boardGrids.x][boardGrids.y] = destroy ? !destroy : currentState;
		}
	}
}

void CPiece::OnInput(SDL_Event event) {
	// helpers
	int scanCode = event.key.keysym.scancode;
	// vars
	bool updatePiece = false;
	// inputs
	int moveDir = scanCode == SDL_SCANCODE_LEFT ? -1 : scanCode == SDL_SCANCODE_RIGHT ? 1 : 0;
	int rotateDir = scanCode == SDL_SCANCODE_Z ? -1 : scanCode == SDL_SCANCODE_X ? 1 : 0;
#ifdef _DEBUG
	static bool canDebugChange = true;
	int debugChange = scanCode == SDL_SCANCODE_V ? -1 : scanCode == SDL_SCANCODE_B ? 1 : 0;
#endif

	switch (event.type) {
	case SDL_KEYDOWN:
#ifdef _DEBUG
		if (debugChange != 0 && canDebugChange) {
			m_ePieceType = EPieceType(int(m_ePieceType) + debugChange);
			if (m_ePieceType > PIECE_T)
				m_ePieceType = PIECE_O;
			if (m_ePieceType < PIECE_O)
				m_ePieceType = PIECE_T;

			RotatePiece(0); // don't rotate the piece but clamp its rotation
			
			updatePiece = true;

			canDebugChange = false;
		}
#endif
		
		// move left or right depending on our move direction
		if (moveDir != 0 && m_bCanMovePiece) {
			m_vecPivot.x += moveDir;

			// make sure we update the piece
			updatePiece = true;

			m_bCanMovePiece = false;
		}

		if (rotateDir != 0 && m_bCanRotatePiece) {
			// handle per piece rotations
			RotatePiece(rotateDir);

			// don't forget to update the piece after changing its layout
			updatePiece = true;

			m_bCanRotatePiece = false;
		}

		// move down faster if we pressing down
		m_iUpdateRate = scanCode == SDL_SCANCODE_DOWN ? defaultUpdateRate - 10 : defaultUpdateRate;
	
		if (updatePiece)
			UpdatePiece();

		break;

	case SDL_KEYUP:
		switch (scanCode) {
		case SDL_SCANCODE_LEFT:
		case SDL_SCANCODE_RIGHT: 
			m_bCanMovePiece = true;
			break;
		case SDL_SCANCODE_Z:
		case SDL_SCANCODE_X:
			m_bCanRotatePiece = true;
			break;
#ifdef _DEBUG
		case SDL_SCANCODE_V:
		case SDL_SCANCODE_B:
			canDebugChange = true;
			break;
#endif
		case SDL_SCANCODE_DOWN:
			m_iUpdateRate = defaultUpdateRate; 
			break;
		}
		break;
	}
}

void CPiece::RotatePiece(int dir) {
	switch (m_ePieceType) {
	case PIECE_O: // pieces with no rotation
		m_iRotation = 0;
		break;
	case PIECE_I: // pieces with 2 rotations
	case PIECE_S:
	case PIECE_Z:
		m_iRotation += dir;
		if (m_iRotation > 1)
			m_iRotation = 0;
		if (m_iRotation < 0)
			m_iRotation = 1; // do a full cycle if we rotated left
		break;
	case PIECE_L: // pieces with 4 rotations
	case PIECE_J:
	case PIECE_T:
		m_iRotation += dir;
		if (m_iRotation > 3)
			m_iRotation = 0;
		if (m_iRotation < 0)
			m_iRotation = 3;
		break;
	}
}