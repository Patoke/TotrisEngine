#include <pch.h>
#include "../Piece.hpp"

// NRS system
std::bitset<pieceMaxX> g_pieceBounds[PIECE_MAX][pieceMaxRotations][pieceMaxY] = {
#pragma region PIECE_O
	{ // PIECE_O
		{ // rotation 0
			{ 0b0000 },
			{ 0b0000 },
			{ 0b0110 },
			{ 0b0110 }
		}
	},
#pragma endregion
#pragma region PIECE_I
	{ // PIECE_I
		{ // rotation 0
			{ 0b0000 },
			{ 0b0000 },
			{ 0b1111 },
			{ 0b0000 }
		},
		{ // rotation 1
			{ 0b0010 },
			{ 0b0010 },
			{ 0b0010 },
			{ 0b0010 }
		}
	},
#pragma endregion
#pragma region PIECE_S
	{ // PIECE_S
		{ // rotation 0
			{ 0b0000 },
			{ 0b0000 },
			{ 0b0011 },
			{ 0b0110 }
		},
		{ // rotation 1
			{ 0b0000 },
			{ 0b0010 },
			{ 0b0011 },
			{ 0b0001 }
		}
	},
#pragma endregion
#pragma region PIECE_Z
	{ // PIECE_Z
		{ // rotation 0
			{ 0b0000 },
			{ 0b0000 },
			{ 0b0110 },
			{ 0b0011 }
		},
		{ // rotation 1
			{ 0b0000 },
			{ 0b0001 },
			{ 0b0011 },
			{ 0b0010 }
		}
	},
#pragma endregion
#pragma region PIECE_L
	{ // PIECE_L
		{ // rotation 0
			{ 0b0000 },
			{ 0b0000 },
			{ 0b0111 },
			{ 0b0100 }
		},
		{ // rotation 1
			{ 0b0000 },
			{ 0b0110 },
			{ 0b0010 },
			{ 0b0010 }
		},
		{ // rotation 2
			{ 0b0000 },
			{ 0b0001 },
			{ 0b0111 },
			{ 0b0000 }
		},
		{ // rotation 3
			{ 0b0000 },
			{ 0b0010 },
			{ 0b0010 },
			{ 0b0011 }
		}
	},
#pragma endregion
#pragma region PIECE_J
	{ // PIECE_J
		{ // rotation 0
			{ 0b0000 },
			{ 0b0000 },
			{ 0b0111 },
			{ 0b0001 }
		},
		{ // rotation 1
			{ 0b0000 },
			{ 0b0010 },
			{ 0b0010 },
			{ 0b0110 }
		},
		{ // rotation 2
			{ 0b0000 },
			{ 0b0100 },
			{ 0b0111 },
			{ 0b0000 }
		},
		{ // rotation 3
			{ 0b0000 },
			{ 0b0011 },
			{ 0b0010 },
			{ 0b0010 }
		}
	},
#pragma endregion
#pragma region PIECE_T
	{ //PIECE_T
		{ // rotation 0
			{ 0b0000 },
			{ 0b0000 },
			{ 0b0111 },
			{ 0b0010 }
		},
		{ // rotation 1
			{ 0b0000 },
			{ 0b0010 },
			{ 0b0011 },
			{ 0b0010 }
		},
		{ // rotation 2
			{ 0b0000 },
			{ 0b0010 },
			{ 0b0111 },
			{ 0b0000 }
		},
		{ // rotation 3
			{ 0b0000 },
			{ 0b0010 },
			{ 0b0110 },
			{ 0b0010 }
		}
	}
#pragma endregion
};