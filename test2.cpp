#include <iostream>
#include <type_traits>

// Classe de base Shape
class Shape {
public:
    virtual ~Shape() = default;
};

// Classe Rectangle avec une sous-classe Remplissage
class Rectangle : public Shape {
public:
    class Remplissage {
    public:
        void info() { std::cout << "Remplissage Rectangle" << std::endl; }
    };
};

// Classe Square avec une sous-classe Remplissage
class Square : public Shape {
public:
    class Remplissage {
    public:
        void info() { std::cout << "Remplissage Square" << std::endl; }
    };
};

// Trait pour obtenir le type de Remplissage à partir de T
template <typename T>
struct RemplissageType {
    using type = typename T::Remplissage;
};

// Fonction générique qui retourne un objet de type Remplissage
template <typename T>
typename RemplissageType<T>::type foo() {
    return typename RemplissageType<T>::type();
}

int main() {
    // Appel pour Rectangle
    auto r = foo<Rectangle>();
    r.info();  // Affiche "Remplissage Rectangle"

    // Appel pour Square
    auto s = foo<Square>();
    s.info();  // Affiche "Remplissage Square"

    return 0;
}
