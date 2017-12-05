//
// Created by verrignij on 05/12/2017.
//

#ifndef OPENMINE_BASECACHE_H
#define OPENMINE_BASECACHE_H

#include <map>

template <class IndexType, class CacheType>
class BaseCache
{
public:
    inline static CacheType* Get(IndexType Key)
    {
        auto Found = Cache.find(Key);

        if (Found != Cache.end()) {
            return Found->second;
        }

        return nullptr;
    }

    inline static void Add(IndexType Key, CacheType* Value)
    {
        if (!Get(Key)) {
            Cache[Key] = Value;
        }
    }
protected:
    static std::map<IndexType, CacheType*> Cache;
};

#endif //OPENMINE_BASECACHE_H
