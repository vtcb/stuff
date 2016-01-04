#ifndef CONSTANT_H
#define CONSTANT_H

namespace SCORE {
	extern const int BASIC;
}
namespace MAP {
	extern const int HEIGHT;
	extern const int WIDTH;
}

namespace PACMAN {
	extern const int I;
	extern const int J;
	extern const int SPEED;
	extern const int DIGESTION;
	extern const int LIVES;
}

namespace GHOST {
	namespace BLINKY {
		extern const int  I;
		extern const int  J;
		extern const int SI;
		extern const int SJ;
	}
	namespace PINKY {
		extern const int  I;
		extern const int  J;
		extern const int SI;
		extern const int SJ;
	}
	namespace INKY {
		extern const int  I;
		extern const int  J;
		extern const int SI;
		extern const int SJ;
	}
	namespace CLYDE {
		extern const int  I;
		extern const int  J;
		extern const int SI;
		extern const int SJ;
	}

	extern const int SPEED;
}

enum class DIRECTION {
	RIGHT   = 0,
	DOWN    = 1,
	LEFT    = 2,
	UP      = 3
};

enum class GHOST_MODE {
	SCATTER       = 0,
	ATTACK        = 1,
	FRIGHTENED    = 2
};

#endif /* CONSTANT_H */