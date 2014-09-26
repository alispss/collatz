// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair

// ------------
// collatz_read
// ------------

std::pair<int, int> collatz_read (std::istream& r) {
    int i;
    r >> i;
    if (!r)
        return std::make_pair(0, 0);
    int j;
    r >> j;
    return std::make_pair(i, j);}


// -------------
// cycle_length 
// -------------

int cycle_length(int i)
{
    int length = 1;
    while (i > 1)
    {
        if(i % 2 == 0)
        {
            i >>= 1;
            ++length;
        }
        else 
        {
            i = i + (i >> 1) + 1;
            length += 2;
        }
    }
    return length;
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    int max = 0;
    if (i <= j / 2)
       i = (j / 2) + 1;
    for(; i <= j; i++)
    { 
        int length = cycle_length(i);
        if (length > max)
           max = length;
    } 
    return max;
}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {
    while (true) {
        const std::pair<int, int> p = collatz_read(r);
        if (p == std::make_pair(0, 0))
            return;
        const int i = p.first;
        const int j = p.second;
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}

// ----
// main
// ----

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;}