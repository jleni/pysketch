// Distributed under the MIT software license, see the accompanying
// file LICENSE or http://www.opensource.org/licenses/mit-license.php.

#ifndef PYSKETCH_PYSKETCH_H
#define PYSKETCH_PYSKETCH_H

#include "../src/Sketch.h"

extern "C" {
    Sketch *Sketch_new(unsigned int p1, unsigned int p2) {return new Sketch(p1, p2);}

    uint64_t Sketch_get_hash(Sketch *s, uint8_t * data, size_t data_size)
    {
        return s->get_hash(data, data_size);
    }

    uint64_t Sketch_get_hash_incremental(Sketch *s, uint64_t prev_hash, uint8_t * data, size_t data_size)
    {
        return s->get_hash_incremental(prev_hash, data, data_size);
    }

    void Sketch_get_column_indexes(Sketch *s, uint64_t hash, int *indexes)
    {
        s->get_column_indexes(hash, indexes);
    }

    void Sketch_increment(Sketch *s, uint64_t hash)
    {
        s->increment(hash);
    }

    void Sketch_query(Sketch *s, uint64_t hash)
    {
        s->query(hash);
    }

    void Sketch_increment_idxs(Sketch *s, int *indexes)
    {
        s->increment(indexes);
    }

    void Sketch_query_idxs(Sketch *s, int *indexes)
    {
        s->increment(indexes);
    }

    void Sketch_delete(Sketch* s) { delete s; }
};

#endif //CPPSKETCH_PYSKETCH_H
