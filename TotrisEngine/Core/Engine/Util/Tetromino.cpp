#include <pch.h>
#include "../Piece.hpp"

// NRS system
char g_pieceBounds[PIECE_MAX][pieceMaxRotations][4][4] = {
#pragma region PIECE_O
	{ // PIECE_O
		{ // rotation 0
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 1, 1, 0 }
		}
	},
#pragma endregion
#pragma region PIECE_I
	{ // PIECE_I
		{ // rotation 0
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 1, 1, 1, 1 },
			{ 0, 0, 0, 0 }
		}, 
		{ // rotation 1
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 }
		}
	},
#pragma endregion
#pragma region PIECE_S
	{ // PIECE_S
		{ // rotation 0
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 1, 1 },
			{ 0, 1, 1, 0 }
		},
		{ // rotation 1
			{ 0, 0, 0, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 1 },
			{ 0, 0, 0, 1 }
		}
	},
#pragma endregion
#pragma region PIECE_Z
	{ // PIECE_Z
		{ // rotation 0
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 1, 1 }
		},
		{ // rotation 1
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 1 },
			{ 0, 0, 1, 1 },
			{ 0, 0, 1, 0 }
		}
	},
#pragma endregion
#pragma region PIECE_L
	{ // PIECE_L
		{ // rotation 0
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 1 },
			{ 0, 1, 0, 0 }
		},
		{ // rotation 1
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 }
		},
		{ // rotation 2
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 1 },
			{ 0, 1, 1, 1 },
			{ 0, 0, 0, 0 }
		},
		{ // rotation 3
			{ 0, 0, 0, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 1 }
		}
	},
#pragma endregion
#pragma region PIECE_J
	{ // PIECE_J
		{ // rotation 0
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 1 },
			{ 0, 0, 0, 1 }
		},
		{ // rotation 1
			{ 0, 0, 0, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 1, 1, 0 }
		},
		{ // rotation 2
			{ 0, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 1, 1 },
			{ 0, 0, 0, 0 }
		},
		{ // rotation 3
			{ 0, 0, 0, 0 },
			{ 0, 0, 1, 1 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 }
		}
	},
#pragma endregion
#pragma region PIECE_T
	{ //PIECE_T
		{ // rotation 0
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 1 },
			{ 0, 0, 1, 0 }
		},
		{ // rotation 1
			{ 0, 0, 0, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 1 },
			{ 0, 0, 1, 0 }
		},
		{ // rotation 2
			{ 0, 0, 0, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 1, 1, 1 },
			{ 0, 0, 0, 0 }
		},
		{ // rotation 3
			{ 0, 0, 0, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 1, 0 }
		}
	}
#pragma endregion
};