#pragma once
#include "Util/Renderer.hpp"

constexpr int numXGrids = 10;
constexpr int numYGrids = 22;
constexpr int pieceMaxX = 5;
constexpr int pieceMaxY = 5;

enum EPieceType {
	PIECE_O,
	PIECE_I,
	PIECE_S,
	PIECE_Z,
	PIECE_L,
	PIECE_J,
	PIECE_T,
	PIECE_MAX
};

extern char g_pieceBounds[PIECE_MAX][pieceMaxY][pieceMaxX];
extern char g_arrGrids[numXGrids][numYGrids];

class CPiece {
public:
	CPiece(EPieceType piece, SVec2 vecPos);

	void MoveEvent();
	void UpdatePiece(bool destroy = false);

	EPieceType m_ePieceType;
	SVec2 m_vecPivot;
	char m_arrPieceBounds[pieceMaxY][pieceMaxX];
};