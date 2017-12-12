//
// Created by verrignij on 11/12/2017.
//

#ifndef OPENMINE_TERRAINHANDLER_H
#define OPENMINE_TERRAINHANDLER_H

#include <glm/vec3.hpp>
#include <vector>
#include <string>

class Chunk;

#define MAX_CHUNKS_X 3
#define MAX_CHUNKS_Z 3

struct ChunkContainer
{
    int X;
    int Z;
    Chunk* MyChunk;

    bool operator==(const ChunkContainer& A)
    {
        return A.X == X && A.Z == Z;
    }
    bool operator!=(const ChunkContainer& A)
    {
        return A.X != X || A.Z != Z;
    }
};

class TerrainHandler
{
public:
    static void BuildChunksAroundCoords(glm::vec3 Coords);
    static std::vector<ChunkContainer> GetNearChunks(glm::vec3 Coords);
protected:
    static std::vector<ChunkContainer> Chunks;

    static void CreateChunk(ChunkContainer &NewChunk);
};


#endif //OPENMINE_TERRAINHANDLER_H
