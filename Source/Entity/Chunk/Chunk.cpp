//
// Created by verrignij on 11/12/2017.
//

#include "Chunk.h"

void Chunk::Begin()
{
    Entity::Begin();
    //GenerateChunk();
    /*for (int X = 0; X < CHUNK_X + 1; X++) {
        for (int Y = 0; Y < CHUNK_Y + 1; Y++) {
            for (int Z = 0; Z < CHUNK_Z + 1; Z++) {
                auto C = new Cube();
                C->SetRelativeLocation({X * 2, -Y * 2, Z * 2});
                Cubes[X][Y][Z] = C;
            }
        }
    }*/
}

template <class Type>
inline constexpr const Type& Clamp(const Type& x, const Type& min, const Type& max)
{
    return (x < min) ? min : ((max < x) ? max : x);
}

void Chunk::GenerateChunk()
{
    double frequency = 4;
    frequency = Clamp(frequency, 0.1, 64.0);

    int octaves = 8;
    octaves = Clamp(octaves, 1, 16);

    std::uint32_t seed = 12345;

    const siv::PerlinNoise perlin(seed);
    const double fx = CHUNK_X / frequency;
    const double fz = CHUNK_Z / frequency;

    for (int Z = 0; Z < CHUNK_Z; ++Z)
    {
        for (int X = 0; X < CHUNK_X; ++X)
        {
            auto PerlinValue = perlin.octaveNoise0_1((CHUNK_X * this->X + X) / fx, (CHUNK_Z * this->Z + Z) / fz, octaves);
            const int MaxHeight = (int) (CHUNK_Y * PerlinValue);
            for (int Y = 0; Y < MaxHeight; Y++) {
                auto C = new Cube();
                C->SetRelativeLocation({(CHUNK_X * this->X) + X * 2, Y * 2, (CHUNK_X * this->Z) + Z * 2});
                C->SetChunk(this);
                C->SetHidden(true);
                Cubes[X][Z][Y] = C;
            }
        }
    }

    UpdateFacingCubes();
}

void Chunk::UpdateFacingCubes()
{
    for (int X = 0; X < CHUNK_X; X++) {
        for (int Z = 0; Z < CHUNK_Z; Z++) {
            for (int Y = 0; Y < CHUNK_Y; Y++) {
                auto C = Cubes[X][Z][Y];
                if (!C) continue;
                C->SetHidden(true);
                std::vector<Cube*> CornerCubes = {
                        X == 0 ? nullptr : Cubes[X - 1][Z][Y],
                        X == CHUNK_X - 1 ? nullptr : Cubes[X + 1][Z][Y],
                        Z == 0 ? nullptr : Cubes[X][Z - 1][Y],
                        Z == CHUNK_Z - 1 ? nullptr : Cubes[X][Z + 1][Y],
                        Y == 0 ? nullptr : Cubes[X][Z][Y - 1],
                        Y == CHUNK_Y - 1 ? nullptr : Cubes[X][Z][Y + 1],
                };

                // If any of the cubes on the corner doesn't exist, the cube is visible.
                for (auto CornerCube : CornerCubes) {
                    if (!CornerCube) C->SetHidden(false);
                }
            }
        }
    }
}

Chunk::Chunk(int X, int Z) : X(X), Z(Z)
{
    for (auto &Cube : Cubes)
        for (auto &Zz : Cube)
            for (auto &Yy : Zz)
                Yy = nullptr;
    GenerateChunk();
}

