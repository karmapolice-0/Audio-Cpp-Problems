#include <cassert>

#include "modinv.h"

uint16_t mod_inv(uint16_t a, uint16_t m)
{
    /*int x, y;
    const uint16_t gcd = egcd(a, m, &x, &y);
    assert(gcd == 1);
    return x % m;*/
    uint16_t remainder = m,
             oldremainder = a,
             y = 0,
             x = 1,
             tmp;
    while (remainder != 0)
    {
        auto quotient = oldremainder / remainder;
        tmp = remainder;
        remainder = oldremainder - quotient * tmp;
        oldremainder = tmp;

        tmp = y;
        y = x - quotient * tmp;
        x = tmp;
    }
    return x;
}

uint16_t egcd(uint16_t a, uint16_t b, int* x, int* y)
{
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
     
    // To store results of recursive call
    int x1, y1;
    uint16_t gcd = egcd(b % a, a, &x1, &y1);
 
    // Update x and y using results of recursive
    // call
    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
    /*auto c = 0;
    auto d = 1;
    auto u = 1;
    auto v = 0;
    while (a != 0)
    {
        auto q = b / a;
        auto r = b % a;
        auto m = c - u * q;
        auto n = d - v * q;
        b = a;
        a = r;
        c = u;
        d = v;
        u = m;
        v = n;
    }
    x = c;
    y = d;
    return b;*/
}