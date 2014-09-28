// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <cstring>  // memset
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair

// ------------
// collatz_read
// ------------

inline std::pair<int, int> collatz_read (std::istream& r) {
    int i;
    r >> i;
    if (!r)
        return std::make_pair(0, 0);
    int j;
    r >> j;
    return std::make_pair(i, j);}

int cycle_cache[1000001];

// -------------
// cycle_length 
// -------------

inline int cycle_length(int i)
{
    int j = i;
    int length = 1;
    if ( i <= 1000000 && cycle_cache[i] != 0) return cycle_cache[i];
    while (i > 1)
    {
        if(i <= 1000000 && cycle_cache[i] != 0)
        {
            length += cycle_cache[i] - 1;
            break;
        }
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
    cycle_cache[j] = length;
    return length;
}

// ------------
// collatz_length_recursive -- doesn't work with cache yet
// ------------

int cycle_length_recursive(int i)
{
    //if ( i <= 1000000 && cycle_cache[i] != 0) return cycle_cache[i];
    /*else*/ if( i == 1 )
        return 1;
    else if(i % 2 == 0)
    {
        //cycle_cache[i] = cycle_length_recursive(i >> 1);
        return  1 + cycle_length_recursive(i >> 1);
    }
    else
    {
        //cycle_cache[i] = cycle_length_recursive(i + (i >> 1) + 1);
        return 2 + cycle_length_recursive(i + (i >> 1) + 1);
    }
}

// ------------
// collatz_eval
// ------------

inline int collatz_eval (int i, int j) {
    int max = 0;
    if (i <= j / 2)
        i = (j / 2) + 1;
    if( i > j )
    {
        i = i ^ j;
        j = i ^ j;
        i = i ^ j;
    }
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

inline void collatz_print (std::ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

inline void collatz_solve (std::istream& r, std::ostream& w) {
    //std::cout << sizeof(cycle_cache) << std::endl;
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