// Distributed under the MIT software license, see the accompanying
// file LICENSE or http://www.opensource.org/licenses/mit-license.php.

#include <iostream>
#include <cstring>
#include <cmath>
#include "Sketch.h"

Sketch::Sketch(unsigned int w, unsigned int d) {
    _w = w;
    _d = d;
    _data = new uint64_t[_w*_d];
    _bits_per_w = (unsigned int)(ceil(std::log2(_w)));

    memset(_data, 0, sizeof(uint64_t) * _w * _d);
}

Sketch::~Sketch() {
    delete[] _data;
}

uint64_t Sketch::get_hash(uint8_t *data, size_t data_size)
{
    // Based on Fowler–Noll–Vo hash function
    uint64_t h = 0xcbf29ce484222325;
    return get_hash_incremental(h, data, data_size);
}

void Sketch::get_column_indexes(uint64_t hash, int *indexes)
{
    // get columns
    // get as many columns as necessary
    int64_t curr_hash = hash;
    int16_t tmp;

    for (int i=0; i<_d; i++)
    {
        tmp = (int16_t) (curr_hash % _w);
        curr_hash >>= _bits_per_w;

        if (curr_hash<_w)
            curr_hash = get_hash_incremental(hash, (uint8_t *) &i, sizeof(i) ); // Generate another hash

        indexes[i]=tmp;
    }
}

void Sketch::increment(uint64_t hash)
{
    int indexes[_d];
    get_column_indexes(hash, indexes);
    return increment(indexes);
}

uint64_t Sketch::query(uint64_t hash)
{
    int indexes[_d];
    get_column_indexes(hash, indexes);
    return query(indexes);
}

void Sketch::increment(const int *indexes)
{
    uint64_t *p = _data;
    for(unsigned int i=0; i<_d; i++)
    {
        p[indexes[i]]++;
        p+=_d;
    }
}

uint64_t Sketch::query(const int *indexes)
{
    uint64_t *p = _data;
    uint64_t min = INT64_MAX;

    for(unsigned int i=0; i<_d; i++)
    {
        uint64_t v = p[indexes[i]];
        if (v<min)
            min = v;

        p+=_d;
    }

    return min;
}
