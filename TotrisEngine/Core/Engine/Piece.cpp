#include <pch.h>
#include "Piece.hpp"

std::bitset<1> g_arrGrids[numXGrids][numYGrids] = {0b0};

CPiece::CPiece() {
	ResetPiece();
	UpdatePiece(); // update piece so it's not hidden for 1 frame
}

void CPiece::MoveEvent() {
	UpdatePiece(true); // destroy the previous placement of the piece

	m_vecPivot.y++;
	
	ECollideType collider = CollisionTest();
	if (collider & COLLIDE_FLOOR || collider & COLLIDE_DOWN) {
		m_vecPivot.y--; // stop down movement

		UpdatePiece(); // draw piece that collided
	
		ResetPiece();
	}

	UpdatePiece(); // set up its new position
}

void CPiece::UpdatePiece(bool destroy) {
	for (int gridX = 0; gridX < pieceMaxX; gridX++) {
		for (int gridY = 0; gridY < pieceMaxY; gridY++) {
			SVec2 boardGrids = { (m_vecPivot.x - 2) + gridX, (m_vecPivot.y - 2) + gridY };
			bool isPieceBlock = g_pieceBounds[m_ePieceType][m_iRotation][gridY][gridX];

			if (isPieceBlock)
				g_arrGrids[boardGrids.x][boardGrids.y] = destroy ? !destroy : isPieceBlock;
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

			ECollideType collider = CollisionTest();
			if (collider & COLLIDE_LEFT || collider & COLLIDE_RIGHT)
				m_vecPivot.x -= moveDir; // stop movement to our direction

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
		m_iUpdateRate = scanCode == SDL_SCANCODE_DOWN ? defaultUpdateRate - updateRateFasten : defaultUpdateRate;
	
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

void CPiece::ResetPiece() {
	// generate random piece
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> generator(PIECE_O, PIECE_T);
	
	m_ePieceType = EPieceType(generator(mt));
	m_iRotation = 0;

	m_vecPivot = SVec2(5, yGiveRoom); // move back to top
}

void CPiece::DoLineClear() {
	// @todo: implement this
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
ECollideType CPiece::CollisionTest() {
	int outType = COLLIDE_NONE;
	bool shouldItMap = false;
	std::bitset<pieceMaxX> collideMap[pieceMaxY] = { 0b0 };

	for (int gridX = 0; gridX < pieceMaxX; gridX++) {
		for (int gridY = 0; gridY < pieceMaxY; gridY++) {
			SVec2 boardGrids = { (m_vecPivot.x - 2) + gridX, (m_vecPivot.y - 2) + gridY };
			bool isPieceBlock = g_pieceBounds[m_ePieceType][m_iRotation][gridY][gridX];
			bool isUsedBlock = g_arrGrids[boardGrids.x][boardGrids.y][0];

			if (!isPieceBlock)
				continue;

			// check if we're colliding with the floor first
			if (boardGrids.y >= numYGrids) {
				outType |= COLLIDE_FLOOR;
			}

			// check if we're colliding with the walls
			if (boardGrids.x < 0)
				outType |= COLLIDE_LEFT;
			else if (boardGrids.x >= numXGrids)
				outType |= COLLIDE_RIGHT;

			// we are not colliding, stop execution
			if (!isUsedBlock)
				continue;

			// populate collision map
			shouldItMap = true;
			collideMap[gridX][gridY] = 0b1;
		}
	}
	
	// iterate collision map
	if (!shouldItMap)
		return ECollideType(outType);

	// @todo: maybe embed the collideMap functionality directly in the other loop?
	for (int collX = 0; collX < pieceMaxX; collX++) {
		for (int collY = 0; collY < pieceMaxY; collY++) {
			bool collided = collideMap[collX][collY];

			if (!collided)
				continue;

			// @todo: this is a horrible way to check for down colliders, please change
			if (collY == pieceMaxY - 1)
				outType |= COLLIDE_DOWN;
		
			if (collX < 2)
				outType |= COLLIDE_LEFT;
			else if (collX > 2)
				outType |= COLLIDE_RIGHT;
		}
	}

	return ECollideType(outType);
}