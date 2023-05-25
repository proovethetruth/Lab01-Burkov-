
#ifndef POLYNOM_H
#define POLYNOM_H

#include <iostream>
#include <ostream>

class Polynom
{
public:
    int r;
    int* x;
    Polynom();
    Polynom(int r);
    Polynom(int r, int* x);
    Polynom(const Polynom& p);
    ~Polynom();
    int deg();
    bool optimize();
    Polynom& sdvig(int s);
    int int_to_poly(int num);
    const bool null_cheker();
    friend const Polynom operator+(const Polynom&, const Polynom&);
    friend const Polynom operator*(const Polynom&, const Polynom&);
    friend const Polynom operator%(const Polynom&, const Polynom&);
    friend const bool operator==(const Polynom&, const Polynom&);
    Polynom& operator=(const Polynom&);

    void print();
};

#endif
