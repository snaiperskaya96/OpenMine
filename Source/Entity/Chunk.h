//
// Created by snaiperskaya on 10/12/17.
//

#ifndef OPENMINE_CHUNK_H
#define OPENMINE_CHUNK_H


#include <thread>
#include "Cube.h"

class Chunk : public Entity
{
    void Begin() override;
protected:
    std::vector<Cube*> Cubes;

    void SpawnStuff();
};

void Chunk::Begin()
{
    Entity::Begin();
    int MAX_X, MAX_Y, MAX_Z;
    MAX_X = MAX_Y = MAX_Z = 16;
    MAX_Y = 16;
    for (int X = 0; X < MAX_X + 1; X++) {
        for (int Y = 0; Y < MAX_Y + 1; Y++) {
            for (int Z = 0; Z < MAX_Z + 1; Z++) {
                auto C = new Cube();
                C->SetRelativeLocation({X * 2, -Y * 2, Z * 2});
                if (X != 0 && X != MAX_X && Z != 0 && Z != MAX_Z && Y != 0 && Y != MAX_Y) {
                    C->SetHidden(true);
                }
                Cubes.push_back(C);
            }
        }
    }
}

void Chunk::SpawnStuff()
{
    int MAX_X, MAX_Y, MAX_Z;
    MAX_X = MAX_Y = MAX_Z = 10;
    for (int X = 0; X < MAX_X + 1; X++) {
        for (int Y = 0; Y < MAX_Y + 1; Y++) {
            for (int Z = 0; Z < MAX_Z + 1; Z++) {
                auto C = new Cube();
                C->SetRelativeLocation({X * 2, Y * 2, Z * 2});
                if (X != 0 && X != MAX_X && Z != 0 && Z != MAX_Z && Y != 0 && Y != MAX_Y) {
                    C->SetHidden(true);
                }
                Cubes.push_back(C);
            }
        }
    }
}


#endif //OPENMINE_CHUNK_H
