//
// Created by verrignij on 12/12/2017.
//

#ifndef OPENMINE_RENDERER_H
#define OPENMINE_RENDERER_H

#include <glad/glad.h>

template<typename T>
class Renderer
{
public:
    virtual void Draw() {}
    virtual void Init();
protected:
    void BindVao();
    void UnbindVao();
protected:
    GLuint VaoId;

public:
    static T* GetInstance();
    static void Destroy();

private:

    Renderer(Renderer const&){};
    Renderer& operator=(Renderer const&){};

protected:
    static T* Instance;

    Renderer(){ Instance = static_cast <T*> (this); };
    ~Renderer(){  };
};

template<typename T>
typename T* Renderer<T>::Instance = 0;

template<typename T>
T* Renderer<T>::GetInstance()
{
    if(!Instance)
    {
        Renderer<T>::Instance = new T();
        ((Renderer*)(Renderer<T>::Instance))->Init();
    }

    return Instance;
}

template<typename T>
void Renderer<T>::Destroy()
{
    delete Renderer<T>::Instance;
    Renderer<T>::Instance = 0;
}

template<typename T>
void Renderer<T>::BindVao()
{
    glBindVertexArray(Renderer<T>::VaoId);
}

template<typename T>
void Renderer<T>::UnbindVao()
{
    glBindVertexArray(0);
}

template<typename T>
void Renderer<T>::Init()
{
    glGenVertexArrays(1, &VaoId);
}


#endif //OPENMINE_RENDERER_H
