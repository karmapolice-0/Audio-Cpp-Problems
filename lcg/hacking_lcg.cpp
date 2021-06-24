#include <iostream>
#include <vector>
#include <algorithm>
#include "modinv.h"
using namespace std;

constexpr uint16_t mod_max = (1 << 16) - 1;

uint16_t absmod(uint16_t value, uint16_t mod)
{
    return value < 0 ? value + mod : value;
}

vector<uint16_t> gensequence(vector<uint16_t> sequence, uint16_t a, uint16_t c, uint16_t m)
{
    auto seed = sequence[0];
    auto size = sequence.size() + 1;
    vector<uint16_t> res { seed };
    res.resize(size);

    for(auto i = 1; i < size; ++i)
    {
        res.at(i) = (a * res.at(i - 1) + c) % m;
    }
    return res;
}

bool verification(const vector<uint16_t>& expected, uint16_t a, uint16_t c, uint16_t m)
{   
    auto actual = gensequence(expected, a, c, m);
    actual.pop_back();
    return actual == expected;
}



int main()
{
    vector<uint16_t> seq = { 157, 5054, 25789, 13214 };
    auto seqmax = *max_element(seq.begin(), seq.end());
    
    for (auto m = seqmax + 1; m <= mod_max; ++m)
    {
        auto diff1 = absmod(seq[0] - seq[1], m);
        auto diff2 = absmod(seq[1] - seq[2], m);

        auto a = ( diff2 * absmod(mod_inv(diff1, m), m) ) % m;

        auto diff3 = absmod(seq[1] - a * seq[0], m);
        auto c = diff3 % m;

        if (verification(seq, a, c, m)){
            cout << "a: " << a << ", c: " << c << ", m: "
            << m << '\n';
            for (auto const &elem : gensequence(seq, a, c, m) )
                cout << elem << ' ';
            cout << endl;
        }
        
    }

    return 0;
}