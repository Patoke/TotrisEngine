#pragma once
#include "Util/Renderer.hpp"

constexpr int numXGrids = 10;
constexpr int numYGrids = 22;
constexpr int pieceMaxX = 4;
constexpr int pieceMaxY = 4;
constexpr int defaultUpdateRate = 20;
constexpr int pieceMaxRotations = 4;

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

extern std::array<std::vector<PieceMatrix_t>, PIECE_MAX> g_pieceBounds;
extern char g_arrGrids[numXGrids][numYGrids];

class CPiece {
private:
	int m_iRotation = 0;
	bool m_bCanMovePiece = true;
	bool m_bIsPressingDown = false;
public:
	CPiece(EPieceType piece, SVec2 vecPos);

	void MoveEvent();
	void UpdatePiece(bool destroy = false);
	void OnInput(SDL_Event event);

	EPieceType m_ePieceType;
	SVec2 m_vecPivot;
	int m_iUpdateRate = defaultUpdateRate;
};