#pragma once
#include "Util/Renderer.hpp"

constexpr int yGiveRoom = 2; // reserved to avoid noclipping onto another lane
constexpr int numXGrids = 10;
constexpr int numYGrids = 22 + yGiveRoom;
constexpr int pieceMaxX = 4;
constexpr int pieceMaxY = 4;
constexpr int defaultUpdateRate = 20;
constexpr int updateRateFasten = 15;
constexpr int pieceMaxRotations = 4;

enum EPieceType : char {
	PIECE_O,
	PIECE_I,
	PIECE_S,
	PIECE_Z,
	PIECE_L,
	PIECE_J,
	PIECE_T,
	PIECE_MAX
};

extern std::bitset<pieceMaxX> g_pieceBounds[PIECE_MAX][pieceMaxRotations][pieceMaxY];
extern std::bitset<1> g_arrGrids[numYGrids][numXGrids];

class CPiece {
private:
	int m_iRotation = 0;
	bool m_bCanMovePiece = true;
	bool m_bCanRotatePiece = true;
	bool m_bIsPressingDown = false;

	void ResetPiece();
	void DoLineChecks();
	void RotatePiece(int dir);
	bool CollisionTest(bool isXMovement);
public:
	CPiece();

	void MoveEvent();
	void UpdatePiece(bool destroy = false);
	void OnInput(SDL_Event event);

	EPieceType m_ePieceType;
	SVec2 m_vecPivot;
	int m_iUpdateRate = defaultUpdateRate;
};