#include "constant.h"

const int  SCORE::   BASIC       = 10;

const int  MAP::     HEIGHT      = 29;
const int  MAP::     WIDTH       = 43;

const int  PACMAN::  I           = 21;
const int  PACMAN::  J           = 21;
const int  PACMAN::  SPEED       = 6;
const int  PACMAN::  DIGESTION   = 3;
const int  PACMAN::  LIVES       = 3;

const int  GHOST::   BLINKY::  I = 11;
const int  GHOST::   BLINKY::  J = 22;

const int  GHOST::   PINKY::   I = 11;
const int  GHOST::   PINKY::   J = 21;

const int  GHOST::   INKY::    I = 11;
const int  GHOST::   INKY::    J = 23;

const int  GHOST::   CLYDE::   I = 11;
const int  GHOST::   CLYDE::   J = 24;

const int  GHOST::   BLINKY:: SI = -2;
const int  GHOST::   BLINKY:: SJ = MAP::WIDTH - 1 - 2;

const int  GHOST::   PINKY::  SI = -2;
const int  GHOST::   PINKY::  SJ =  2;

const int  GHOST::   INKY::   SI = MAP::HEIGHT + 1;
const int  GHOST::   INKY::   SJ = MAP::WIDTH - 1;

const int  GHOST::   CLYDE::  SI = MAP::HEIGHT + 1;
const int  GHOST::   CLYDE::  SJ =  0;

const int  GHOST::   SPEED       = 8;
