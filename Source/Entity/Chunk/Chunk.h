//
// Created by snaiperskaya on 10/12/17.
//

#ifndef OPENMINE_CHUNK_H
#define OPENMINE_CHUNK_H


#include <thread>
#include "Entity/Cube/Cube.h"
#include "PerlinNoise.hpp"

#define CHUNK_X 16
#define CHUNK_Y 16
#define CHUNK_Z 16

class Chunk : public Entity
{
public:
    Chunk(int X, int Z);
protected:
    void Begin() override;
    void GenerateChunk();
    void UpdateFacingCubes();
protected:
    int X = 0;
    int Z = 0;
    Cube* Cubes[CHUNK_X][CHUNK_Z][CHUNK_Y] = { nullptr };
};


#endif //OPENMINE_CHUNK_H
