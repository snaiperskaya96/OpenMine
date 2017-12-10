//
// Created by verrignij on 05/12/2017.
//

#ifndef OPENMINE_BASECACHE_H
#define OPENMINE_BASECACHE_H

#include <map>
#include <vector>

template <class T>
struct CacheItem
{
    std::string Name;
    T* Element;
};

template <class T>
class BaseCache
{
public:
    static T* Get(std::string& Key);

    static void Add(std::string& Name, T* Value);
protected:
    static std::vector<CacheItem<T>> Cache;
};

template<class T> std::vector<CacheItem<T>> BaseCache<T>::Cache; // only change here

template<class T>
T *BaseCache<T>::Get(std::string &Key)
{
    for (auto& C : Cache) {
        if (C.Name == Key) {
            return C.Element;
        }
    }

    return nullptr;
}

template<class T>
void BaseCache<T>::Add(std::string &Name, T *Value)
{
    if (Get(Name) == nullptr) {
        Cache.push_back({Name, Value});
    }
}

#endif //OPENMINE_BASECACHE_H
