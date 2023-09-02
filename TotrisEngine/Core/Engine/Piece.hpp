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

enum ECollideType : char {
	COLLIDE_NONE = (1 << 0),
	COLLIDE_LEFT = (1 << 1),
	COLLIDE_DOWN = (1 << 2),
	COLLIDE_RIGHT = (1 << 3),
	COLLIDE_FLOOR = (1 << 4)
};

extern std::bitset<pieceMaxX> g_pieceBounds[PIECE_MAX][pieceMaxRotations][pieceMaxY];
extern std::bitset<1> g_arrGrids[numXGrids][numYGrids];

class CPiece {
private:
	int m_iRotation = 0;
	bool m_bCanMovePiece = true;
	bool m_bCanRotatePiece = true;
	bool m_bIsPressingDown = false;

	void ResetPiece();
	void DoLineClear();
	void RotatePiece(int dir);
	ECollideType CollisionTest();
public:
	CPiece();

	void MoveEvent();
	void UpdatePiece(bool destroy = false);
	void OnInput(SDL_Event event);

	EPieceType m_ePieceType;
	SVec2 m_vecPivot;
	int m_iUpdateRate = defaultUpdateRate;
};