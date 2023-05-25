
#include "Polynom.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>

using namespace std;

Polynom::Polynom() {
    r = NULL;
    x = NULL;
}

Polynom::Polynom(int r) {
    this->r = r;
    x = new int[r];
    for (size_t i = 0; i < r; i++)
    {
        x[i] = 0;
    }
}

Polynom::Polynom(int r, int* x)
{
    this->r = r;
    //this->x = x;
    this->x = new int[r];
    for (size_t i = 0; i < r; i++)
    {
        this->x[i] = x[i];
    }
}

Polynom::Polynom(const Polynom& p)
{
    r = p.r;
    this->x = new int[p.r];
    for (size_t i = 0; i < p.r; i++)
    {
        this->x[i] = p.x[i];
    }
}

Polynom::~Polynom() {

}

int Polynom::deg()
{
    return r - 1;
}

const Polynom operator+(const Polynom& A, const Polynom& B)
{
    if (A.r >= B.r) {
        Polynom C(A.r, A.x);
        for (size_t i = 0; i < B.r; i++)
        {
            C.x[i] = (A.x[i] + B.x[i]) % 2;
        }
        return C;
    }
    else
    {
        Polynom C(B.r, B.x);
        for (size_t i = 0; i < A.r; i++)
        {
            C.x[i] = (A.x[i] + B.x[i]) % 2;
        }
        return C;
    }
}

const Polynom operator*(const Polynom& A, const Polynom& B)
{
    Polynom C(A.r + B.r);
    for (size_t i = 0; i < A.r; i++)
    {
        for (size_t j = 0; j < B.r; j++)
        {
            C.x[i + j] += A.x[i] * B.x[j];
            C.x[i + j] = (C.x[i + j]) % 2;
        }
    }
    return C;

}

const Polynom operator%(const Polynom& A, const Polynom& B) {
    Polynom temp(A.r, A.x);
    std::cout << "temp = ";
    temp.print();
    int d = 0;
    while (true) {
        if (temp.r >= B.r)
        {
            Polynom C(B.r, B.x);
            d = temp.r - B.r;
            C.sdvig(d);

            std::cout << "C = ";
            C.print();

            std::cout << "temp = ";
            temp.print();

            temp = temp + C;
            temp.optimize();
        }
        else
        {
            break;
        }
    }
    std::cout << "\nres mod = ";
    temp.print();
    return temp;
}

Polynom& Polynom::sdvig(int s) {
    Polynom C(r + s);

    for (size_t i = 0; i < r; i++)
    {
        C.x[i + s] = x[i];
    }
    for (size_t i = 0; i < s; i++)
    {
        C.x[i] = 0;
    }
    *this = C;
    return *this;
}

bool Polynom::optimize() {

    if (x[r - 1] != 1)
    {
        int d = r;
        while ((x[d - 1] != 1) && (d != 0))
        {
            d--;
        }

        if (d == 0) {
            int* zero = new int[1];
            zero[0] = 0;
            Polynom Z(1, zero);
            *this = Z;

            return true;
        }

        int* y = new int[d];

        for (size_t i = 0; i < d; i++)
        {
            y[i] = x[i];
        }

        Polynom C(d, y);
        *this = C;

        return true;
    }
    else
    {
        return false;
    }
}

Polynom& Polynom::operator=(const Polynom& B)
{
    r = B.r;
    x = new int[B.r];
    for (size_t i = 0; i < B.r; i++)
    {
        x[i] = B.x[i];
    }
    return *this;
}

void Polynom::print() {
    for (int i = r - 1; i >= 0; i--)
    {
        std::cout << x[i];
    }
    std::cout << std::endl;
}

const bool operator==(const Polynom& A, const Polynom& B)
{
    if (A.r == B.r) {
        for (size_t i = 0; i < A.r; i++)
        {
            if (A.x[i] != B.x[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

int Polynom::int_to_poly(int num)
{
    int count = 0;
    for (size_t i = 0; i < r; i++)
    {
        x[i] = (num >> i) % 2;
        if (x[i] == 1)
        {
            count++;
        }
    }
    return count;
}

const bool Polynom::null_cheker()
{
    if (this->r == 1)
    {
        if (this->x[r - 1] == 0)
        {
            return true;
        }
    }
    return false;
}