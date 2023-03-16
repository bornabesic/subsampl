/**
 * Copyright (C) 2021 Borna Bešić
 *
 * This file is part of subsampl.
 *
 * subsampl is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * subsampl is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with subsampl.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <vector>

template <typename K, typename V> class grouping_hashmap {

    struct key_meta {
        K key;
        bool occupied = false;
    };

  private:
    uint64_t size;
    std::vector<key_meta> *metas;
    std::vector<V> *values;
    std::hash<K> hash;
    bool owns_values = true;

  public:
    grouping_hashmap() = delete;

    grouping_hashmap(const uint64_t size) {
        this->size = size;
        this->metas = new std::vector<key_meta>(size);
        this->values = new std::vector<V>(size);
    }

    std::vector<V> *move_values() {
        this->owns_values = false;
        return this->values;
    }

    inline void squeeze() {
        if (this->size < 2)
            return;

        auto &metas_ref = *this->metas;
        auto &values_ref = *this->values;

        uint64_t index_unoccupied = 0;
        uint64_t index_end = this->size - 1;
        while (true) {
            auto &meta_unoccupied = metas_ref[index_unoccupied];
            while (index_unoccupied != this->size - 1 &&
                   meta_unoccupied.occupied)
                meta_unoccupied = metas_ref[++index_unoccupied];

            auto &meta_end = metas_ref[index_end];
            while (index_end != 0 && !meta_end.occupied)
                meta_end = metas_ref[--index_end];

            if (index_unoccupied >= index_end)
                break;
            else {
                meta_unoccupied.key = meta_end.key;
                meta_unoccupied.occupied = true;

                values_ref[index_unoccupied] = values_ref[index_end];
                meta_end.occupied = false;
            }
        }

        if (index_unoccupied > index_end)
            this->size = index_unoccupied;
        else if (index_unoccupied == 0)
            this->size = 0; // Empty
        else if (index_unoccupied == this->size - 1) {
        } // Full
        else
            assert(false); // Cannot happen

        metas_ref.resize(this->size);
        values_ref.resize(this->size);
    }

    inline void insert(const K &key, const V &value) {
        const auto hash = this->hash(key);
        auto index = hash % this->size;

        auto &metas_ref = *this->metas;
        auto &values_ref = *this->values;

        auto &meta = metas_ref[index];
        while (meta.occupied) {
            if (meta.key == key)
                break;
            else {
                index = (index + 1) % this->size;
                meta = metas_ref[index];
            }
        }

        meta.key = key;
        meta.occupied = true;
        values_ref[index] = value;
    }

    ~grouping_hashmap() {
        delete this->metas;
        if (this->owns_values)
            delete this->values;
    }
};