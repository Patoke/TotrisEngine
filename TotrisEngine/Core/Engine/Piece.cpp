#include <pch.h>
#include "Piece.hpp"

// 0 specifies that nothing is in that grid
// 1 specifies a block in that grid
// 2 specifies a block in that grid and a pivot point for the piece
char g_pieceBounds[PIECE_MAX][pieceMaxY][pieceMaxX] = {
	{ // PIECE_O (this one cannot be rotated, has no pivot point)
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 1, 2, 0, 0 },
		{ 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0 }
	},
	{ // PIECE_I
		{ 0, 0, 1, 0, 0 },
		{ 0, 0, 1, 0, 0 },
		{ 0, 0, 2, 0, 0 },
		{ 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0 }
	},
	{ // PIECE_S
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 2, 1, 0 },
		{ 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0 }
	},
	{ // PIECE_Z
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 1, 2, 0, 0 },
		{ 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 0, 0 }
	},
	{ // PIECE_L
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0 },
		{ 0, 0, 2, 0, 0 },
		{ 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 0, 0 }
	},
	{ // PIECE_J
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0 },
		{ 0, 0, 2, 0, 0 },
		{ 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0 }
	},
	{ // PIECE_T
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 1, 2, 1, 0 },
		{ 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0 }
	}
};

char g_arrGrids[numXGrids][numYGrids] = { 0 };

CPiece::CPiece(EPieceType piece, SVec2 vecPos) : m_ePieceType(piece), m_vecPivot(vecPos) {
	// set up the individual piece bounds for rotation
	memcpy(m_arrPieceBounds, g_pieceBounds[m_ePieceType], sizeof(g_pieceBounds[m_ePieceType]));
}

void CPiece::MoveEvent() {
	UpdatePiece(true); // destroy the previous placement of the piece
	
	// update position and stop at the bottom of the board
	// 3 = y bottom, 1 = x center
	bool isNotColliding = m_arrPieceBounds[3][1] == 1 ? m_vecPivot.y != numYGrids - 2 : m_vecPivot.y != numYGrids - 1;
	if (isNotColliding)
		m_vecPivot.y++;

	UpdatePiece(); // set up its new position
}

void CPiece::UpdatePiece(bool destroy) {
	for (int gridX = 0; gridX < pieceMaxX; gridX++) {
		for (int gridY = 0; gridY < pieceMaxY; gridY++) {
			SVec2 boardGrids = { (m_vecPivot.x - 2) + gridX, (m_vecPivot.y - 2) + gridY };
			char currentState = m_arrPieceBounds[gridY][gridX];

			g_arrGrids[boardGrids.x][boardGrids.y] = destroy ? !destroy : currentState;
		}
	}
}