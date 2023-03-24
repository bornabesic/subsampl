/**
 * Copyright (C) 2023 Borna Bešić
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

#include <iostream>

#include "../src/subsampl/hashmap.hpp"

int main() {
    grouping_hashmap<int, int> map(10);

    map.insert(0, 1337);
    map.insert(1, 1332);
    map.insert(9, 5);

    map.squeeze();
    auto *values = map.move_values();

    for (const auto &value : *values) {
        std::cout << value << '\n';
    }

    return 0;
}