#include <pch.h>
#include "Piece.hpp"
#include "Logic.hpp" // @todo: this includes Piece.hpp, maybe remove the include above?

std::bitset<1> g_arrGrids[numYGrids][numXGrids] = {0b0};

CPiece::CPiece() {
	ResetPiece();
	UpdatePiece(); // update piece so it's not hidden for 1 frame
}

void CPiece::MoveEvent() {
	UpdatePiece(true); // destroy the previous placement of the piece

	m_vecPivot.y++;

	bool placedPiece = CollisionTest(false);
	if (placedPiece) {
		UpdatePiece(); // draw piece that collided

		DoLineChecks(); // clear line
		
		ResetPiece();
	}

	UpdatePiece(); // set up its new position
}

void CPiece::UpdatePiece(bool destroy) {
	for (int gridX = 0; gridX < pieceMaxX; gridX++) {
		for (int gridY = 0; gridY < pieceMaxY; gridY++) {
			SVec2 boardGrids = { (m_vecPivot.x - 2) + gridX, (m_vecPivot.y - 2) + gridY };
			bool isPieceBlock = g_pieceBounds[m_ePieceType][m_iRotation][gridY][gridX];
			char offBoundsTo = boardGrids.x < 0 ? 1 : boardGrids.x >= numXGrids ? -1 : 0;

			if (isPieceBlock)
				g_arrGrids[boardGrids.y][boardGrids.x] = destroy ? !destroy : isPieceBlock;
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
			// destroy piece so we don't leave pieces floating
			UpdatePiece(true);
			
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
			// destroy piece so we don't leave pieces floating
			UpdatePiece(true);
			
			m_vecPivot.x += moveDir;

			// make sure we update the piece
			updatePiece = true;

			m_bCanMovePiece = false;
		}

		if (rotateDir != 0 && m_bCanRotatePiece) {
			UpdatePiece(true);
			
			// handle per piece rotations
			RotatePiece(rotateDir);

			// don't forget to update the piece after changing its layout
			updatePiece = true;

			m_bCanRotatePiece = false;
		}

		// move down faster if we pressing down
		if (scanCode == SDL_SCANCODE_DOWN)
			m_iUpdateRate = defaultUpdateRate - updateRateFasten;
	
		if (updatePiece) {
			CollisionTest(true); // we don't care if we need to place a piece here
			UpdatePiece();
		}

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

void CPiece::ResetPiece() {
	// generate random piece
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> generator(PIECE_O, PIECE_T);
	
	m_ePieceType = EPieceType(generator(mt));
	m_iRotation = 0;

	m_vecPivot = SVec2(5, yGiveRoom); // move back to top
}

void CPiece::DoLineChecks() {
	char linesCleared = 0;

	// do line order checks from each y row thru each x column
	for (int gridY = 0; gridY < numYGrids; gridY++) {
		bool isLineClear = true;

		for (int gridX = 0; gridX < numXGrids; gridX++) {
			bool isUsedBlock = g_arrGrids[gridY][gridX][0];

			if (!isUsedBlock) {
				isLineClear = false;
				continue;
			}

			if (gridY < yGiveRoom) {
				// @todo: clear all lines for game over
				break;
			}
		}

		if (!isLineClear)
			continue;

		// for scoring system
		linesCleared++;

		// clear line @todo: move this inside the other loop?
		for (int gridX = 0; gridX < numXGrids; gridX++)
			g_arrGrids[gridY][gridX][0] = 0b0;

		// bring pieces down @todo: do it better?
		std::bitset<numXGrids> lastRow;
		std::bitset<numXGrids> currentRow;
		// only move lines above the line clear
		for (int clearY = 0; clearY <= gridY; clearY++) {
			for (int clearX = 0; clearX < numXGrids; clearX++) {
				if (clearY == 0) {
					lastRow[clearX] = g_arrGrids[clearY][clearX][0];
				}
				else {
					currentRow[clearX] = g_arrGrids[clearY][clearX][0];

					g_arrGrids[clearY][clearX][0] = lastRow[clearX];
				}
			}

			if(clearY != 0)
				lastRow = currentRow;
		}

	}

	// add score up (BPS scoring system)
	// @todo: maybe do operations with strings so we don't run risk of integer overflow?
	switch (linesCleared) {
	case 1:
		g_pGame->m_iScore += 40;
		break;
	case 2:
		g_pGame->m_iScore += 100;
		break;
	case 3:
		g_pGame->m_iScore += 300;
		break;
	case 4:
		g_pGame->m_iScore += 1200;
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

// function called after doing a movement to check if in that future movement we're gonna collide
bool CPiece::CollisionTest(bool isXMovement) {
	bool shouldPlacePiece = false;

	for (int gridX = 0; gridX < pieceMaxX; gridX++) {
		for (int gridY = 0; gridY < pieceMaxY; gridY++) {
			SVec2 boardGrids = { (m_vecPivot.x - 2) + gridX, (m_vecPivot.y - 2) + gridY };
			bool isPieceBlock = g_pieceBounds[m_ePieceType][m_iRotation][gridY][gridX];
			bool isUsedBlock = g_arrGrids[boardGrids.y][boardGrids.x][0];

			if (!isPieceBlock)
				continue;

			// we are not colliding with any blocks so we must be colliding with game bounds
			if (!isUsedBlock) {
				// check if we're colliding with the floor
				if (!isXMovement && boardGrids.y >= numYGrids) {
					m_vecPivot.y--; // null movement
					shouldPlacePiece = true;
				}

				// check if we're colliding with the walls
				if (isXMovement)
					if (boardGrids.x < 0)
						m_vecPivot.x++;
					else if (boardGrids.x >= numXGrids)
						m_vecPivot.x--;

				continue;
			}

			// do block collisions
			if (!isXMovement && gridY >= 1) {
				m_vecPivot.y--;
				shouldPlacePiece = true;
			}

			if (isXMovement)
				if (gridX < 2)
					m_vecPivot.x++;
				else if (gridX > 2)
					m_vecPivot.x--;
		}
	}
	
	return shouldPlacePiece;
}