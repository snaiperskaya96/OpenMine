//
// Created by verrignij on 11/12/2017.
//

#include <Utils/Thread/AsyncTask.h>
#include "TerrainHandler.h"
#include "Entity/Chunk/Chunk.h"

#define CHUNK_ACTUAL_SIZE_X (MAX_CHUNKS_X * 2 * CHUNK_X)
#define CHUNK_ACTUAL_SIZE_Z (MAX_CHUNKS_Z * 2 * CHUNK_Z)

std::vector<ChunkContainer> TerrainHandler::Chunks;

void TerrainHandler::BuildChunksAroundCoords(glm::vec3 Coords)
{
    auto NearChunks = GetNearChunks(Coords);
    for (auto& C : NearChunks) {
        bool Exists = false;
        for (auto& ExistingChunk : Chunks) {
            if (ExistingChunk == C) Exists = true;
        }
        if (!Exists) {
            new std::thread(&TerrainHandler::CreateChunk, C);
            return;
        }
    }
}

void TerrainHandler::CreateChunk(ChunkContainer NewChunk)
{
    auto C = new Chunk(NewChunk.X, NewChunk.Z);
    //AsyncTask::ExecuteOnThread(TaskThread::GAME_THREAD, [&NewChunk]() {
       Chunks.push_back({NewChunk.X, NewChunk.Z, C});
    std::cout << "Generating Chunk " << NewChunk.X << "-" << NewChunk.Z << std::endl;
    //});
}

std::vector<ChunkContainer> TerrainHandler::GetNearChunks(glm::vec3 Coords)
{
    std::vector<ChunkContainer> ToBeBuilt;

    auto ApproximateChunkX = (int) (Coords.x / CHUNK_ACTUAL_SIZE_X);
    auto ApproximateChunkZ = (int) (Coords.x / CHUNK_ACTUAL_SIZE_Z);

    auto Left = ApproximateChunkX - MAX_CHUNKS_X;
    auto Right = ApproximateChunkX + MAX_CHUNKS_X;
    auto Top = ApproximateChunkZ + MAX_CHUNKS_Z;
    auto Bottom = ApproximateChunkZ - MAX_CHUNKS_Z;

    for (int X = Left; X < Right; X++) {
        for (int Z = Bottom; Z < Top; Z++) {
            ChunkContainer C {X, Z, nullptr};
            ToBeBuilt.push_back(C);
        }
    }

    return ToBeBuilt;
}

