//
// Created by verrignij on 05/12/2017.
//

#ifndef OPENMINE_POOL_H
#define OPENMINE_POOL_H

#include <glad/glad.h>
#include <vector>

class Pool
{
public:
    virtual void Init() = 0;
protected:
    static std::vector<GLuint> Vaos;
};
#endif //OPENMINE_POOL_H
