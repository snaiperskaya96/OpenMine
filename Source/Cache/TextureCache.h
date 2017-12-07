//
// Created by verrignij on 05/12/2017.
//

#ifndef OPENMINE_TEXTURECACHE_H
#define OPENMINE_TEXTURECACHE_H

#include <Texture/Texture.h>
#include "Cache/BaseCache.h"

class TextureCache : public BaseCache<std::string, Texture>
{
public:
    static inline void Add(std::string Key, Texture* Value)
    {
        BaseCache::Add(Key, Value);
    }
};

#endif //OPENMINE_TEXTURECACHE_H
