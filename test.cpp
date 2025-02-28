#include <iostream>
#include <array>
#include <vector>

// abstract
class _Instance { };

class Object
{
public:

    struct Instance : _Instance
    {
        int x, y;
        void moveto(int dx, int dy) { x = dx; y = dy; }
    };
    
protected:

    std::vector<Instance> inst;

public:

    Instance& create()
    {
        inst.push_back({});
        return inst.back();
    }
};

class Mario : public Object
{
public:

    Mario() : Object() {}

    struct Instance : _Instance
    {
        int x, y;
        void moveby(int dx, int dy) { x += dx; y += dy; }
        void spec() const { std::cout << "Mario!\n"; }
    };

private:

    std::vector<Instance> inst;

public:

    Instance& create()
    {
        inst.push_back({});
        return inst.back();
    }
};

using Obj_type = int;
constexpr int NB_OBJ_TYPES = 2;
constexpr Obj_type OBJECT = 0;
constexpr Obj_type MARIO = 1;

template <typename Obj>
struct ObjectSpec {
    using InstanceType = typename Obj::Instance;
};

class World
{
private:

    std::array<Object*, NB_OBJ_TYPES> objects;

public:

    World()
    {
        objects[OBJECT] = new Object();
        objects[MARIO]  = new Mario();
    }

    template<typename Obj>
    typename ObjectSpec<Obj>::InstanceType create(Obj_type type)
    {
        // on peut accéder à Mario.create() uniquement car le type Obj donné en template est Mario et non Object
        // Si on n'avait pas utilisé un template, et utilisé le create sur Mario en le considérant comme un type Object,
        // alors la fonction create de la classe Object aurait été appelée, puisque celle-ci n'est pas virtual.
        // Mais on ne pouvait pas avoir de fonction virtual create dans Object qui renvoie un type (objInstance)
        // différent de la fonction create de Mario (mrInstance)
        return static_cast<Obj*>( objects[type] )->create();
        // on remarque que la fonction create doit avoir le même prototype pour toutes les classes dérivées de Object.
    }
};

signed main()
{
    World w;

    auto mario = w.create<Mario>(MARIO);
    auto obj = w.create<Object>(OBJECT);

    mario.spec();
    obj.moveto(1, 0);
    std::cout << obj.x << std::endl;
}
