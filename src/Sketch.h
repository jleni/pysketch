// Distributed under the MIT software license, see the accompanying
// file LICENSE or http://www.opensource.org/licenses/mit-license.php.

#ifndef CPPSKETCH_SKETCH_H
#define CPPSKETCH_SKETCH_H

#include <stddef.h>
#include <stdint.h>
#include <vector>

class Sketch {
    unsigned int _w, _d;
    unsigned int _bits_per_w;
    uint64_t *_data;

public:
    Sketch(unsigned int w, unsigned int d);
    ~Sketch();

    unsigned int get_w()    {   return _w;  }
    unsigned int get_d()    {   return _d;  }

    inline uint64_t get_hash_incremental(uint64_t prev_hash, uint8_t *data, size_t data_size)
    {
        uint64_t h = prev_hash;
        uint8_t *p = data;

        for(size_t i = 0; i < data_size; i++, p++){
            h = (h * 0x100000001b3) & 0xffffffffffffffff;
            h ^= *p;
        }

        return h;
    }

    uint64_t get_hash(uint8_t *data, size_t data_size);

    void get_column_indexes(uint64_t hash, int *indexes);

    void increment(uint64_t hash);

    uint64_t query(uint64_t hash);

    void increment(const int* indexes);

    uint64_t query(const int* indexes);
};

#endif // CPPSKETCH_SKETCH_H
