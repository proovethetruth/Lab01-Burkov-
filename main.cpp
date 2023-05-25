
#include <sstream>
#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>
#include "Polynom.h"

int test(int, int, int*, int*, int*, int);
int test_1(Polynom, Polynom, Polynom);
int test_2(int, int, int*, int*, int*, int);


int main() {
    int r = 3;
    int l = 0;
    int k = 4;
    int* g_m = new int[r + 1]{ 1, 0, 1, 1 };
    int* m_m = new int[k + l]{ 0, 1, 1, 1 };
    int* e_m = new int[k + r + l]{ 0, 1, 0, 1, 1, 0, 0 };

    test(r, k, g_m, m_m, e_m, l);

    return 0;
}

int test(int r, int k, int* g_m, int* m_m, int* e_m, int l) {
    Polynom g(r + 1, g_m);
    std::cout << "g = ";
    g.print();

    Polynom e(r + k + l, e_m);
    std::cout << "e = ";
    e.print();

    Polynom m(k + l, m_m);
    std::cout << "m = ";
    m.print();

    Polynom tmp(k + l);
    tmp = m;
    tmp.optimize();
    tmp.sdvig(g.deg());

    Polynom c(tmp);

    c = c % g;
    c.optimize();
    std::cout << "c = ";
    c.print();

    Polynom a(m.deg() + g.deg());
    a = tmp + c;
    a.optimize();
    std::cout << "a = ";
    a.print();

    Polynom b(a.deg() + 1);
    b = a + e;
    std::cout << "b = ";
    b.print();

    Polynom S(b.deg() + 1);
    S = b % g;
    S.optimize();
    std::cout << "S = ";
    S.print();

    int w_e = 0;
    for (size_t i = 0; i < e.deg() + 1; i++)
    {
        if (e.x[i] != 0) {
            w_e++;
        }
    }

    if (S.null_cheker())
    {
        if (w_e != 0)
        {
            std::cout << "E = 0, but |e| not = 0 \nERROR NOT FINDED" << std::endl;
            return 2;
        }
        else
        {
            std::cout << "E = 0, |e| = 0 \nSUCCESS" << std::endl;
            return 0;
        }
    }
    else
    {
        if (w_e != 0)
        {
            std::cout << "E = 1, |e| not = 0 \nERROR FINDED" << std::endl;
            return 1;
        }
        else
        {
            std::cout << "E = 1, |e| = 0 \n???ERROR???" << std::endl;
            return -2;
        }
    }
    return -1;
}

int test_1(Polynom g, Polynom m, Polynom e) {//(int r, int k, int* g_m, int* m_m, int* e_m, int l){ //(Polynom g, Polynom e, Polynom m)
    Polynom tmp(m.deg() + 1);
    tmp = m;
    tmp.sdvig(g.deg());

    Polynom c(tmp);

    c = c % g;
    c.optimize();


    Polynom a(m.deg() + g.deg());
    a = tmp + c;
    a.optimize();


    Polynom b(a.deg() + 1);
    b = a + e;


    Polynom S(b.deg() + 1);
    S = b % g;
    S.optimize();


    int w_e = 0;
    for (size_t i = 0; i < e.deg() + 1; i++)
    {
        if (e.x[i] != 0) {
            w_e++;
        }
    }

    if (S.null_cheker())
    {
        if (w_e != 0)
        {
            //std::cout << "E = 0, but |e| not = 0 \nERROR NOT FINDED" << std::endl;
            return 2;
        }
        else
        {
            //std::cout << "E = 0, |e| = 0 \nSUCCESS" << std::endl;
            return 0;
        }
    }
    else
    {
        if (w_e != 0)
        {
            //std::cout << "E = 1, |e| not = 0 \nERROR FINDED" << std::endl;
            return 1;
        }
        else
        {
            //std::cout << "E = 1, |e| = 0 \n???ERROR???" << std::endl;
            return -2;
        }
    }
    return -1;
}

int test_2(int r, int k, int* g_m, int* m_m, int* e_m, int l)
{
    std::vector<Polynom> me;
    Polynom g(r + 1, g_m);
    Polynom m(k + l, m_m);
    Polynom e(r + k + l, e_m);

    for (int i = 0; i < pow(2, r + k + l); i++)
    {
        //std::cout << i << std::endl;
        if (e.int_to_poly(i) < r) {
            e.print();

            if (test_1(g, m, e) == 2) { // (r, k, g_m, m_m, e.x, l)
                me.push_back(e);
            }
        }
    }

    std::cout << "Error vector's in which error's were not detected:" << std::endl;

    for (auto& i : me) {
        i.print();
    }
    return 0;
}