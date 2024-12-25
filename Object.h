#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include "Instance.h"
#include "Shader.h"

class Object
{
public:

    virtual void init()      { loaded = true; std::cout << "Object::init\n"; }
    virtual void destroy()   { loaded = false; }
    virtual bool is_loaded() { return  loaded; }

    virtual void draw(const Shader& shader, const Instance& obj)
    {  /* implemented in child class */  };

protected: 

    bool loaded = false;
};


#endif