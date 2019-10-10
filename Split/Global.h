#pragma once
#ifndef GLOBAL

#define GLOBAL

#define SPRITESHEET_OFFSET 1
#define SPRITESHEET_CELL_COUNT_PER_ROW 32
#define SPRITESHEET_CELL_SIZE 16
#define FRAME_RATE 144

#define PLAYER_SPEED 0.1
#define PLAYER_JUMP 60
#define PLAYER_MASS 0.5

#endif // !GLOBAL

class Global {
public:
	static int Scale;
	static int ChunkSize;
	static int ChunkCount;
};

const unsigned FLIPPED_H = 0x80000000;
const unsigned FLIPPED_V = 0x40000000;
const unsigned FLIPPED_D = 0x20000000;