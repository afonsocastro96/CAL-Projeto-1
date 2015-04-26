#pragma once

#include <string>

using namespace std;

class Local {
private:
    int id;
    long double x;
    long double y;
    string nome;
public:
    Local() { }

    Local(int id, long double x, long double y, string &nome) : id(id), x(x), y(y), nome(nome) {}
    Local(long double x, long double y, string &nome) : x(x), y(y), nome(nome) {}

    int getId() const {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }

    long double getX() const {
        return x;
    }

    void setX(long double x) {
        this->x = x;
    }

    long double getY() const {
        return y;
    }

    void setY(long double y) {
        this->y = y;
    }

    string getNome() const {
        return nome;
    }

    void setNome(string &nome) {
        Local::nome = nome;
    }

    bool operator==(Local p2) {
        return (x == p2.getX() && y == p2.getY());
    }

    friend std::ostream& operator<<(std::ostream& o, const Local& p) {
        o << to_string(p.getId()) << "\n" <<  p.getNome() << "\n" << to_string(p.getX()) << "\n" << to_string(p.getY());
        return o;
    }
};