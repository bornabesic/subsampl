
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <subsampl/subsampl.hpp>

TEST_CASE("Points are subsampled within voxels", "[voxel]") {
    const uint32_t nrows = 5;
    const float voxel_size = 0.3f;
    const float32 data[nrows * 3] = {
        0.f,  0.f,   0.f,
        0.25f, 0.1f, 0.1f,
        0.5f, 0.2f, 0.2f,
        0.75f, 0.2f, 0.2f,
        1.f,  0.2f, 0.2f,
    };

    auto *indices_ptr = voxel_grid_subsample_3d(data, nrows, voxel_size);
    auto &indices = *indices_ptr;
    std::sort(indices.begin(), indices.end());

    REQUIRE(indices.size() == 4);
    CHECK(indices[0] == 1);
    CHECK(indices[1] == 2);
    CHECK(indices[2] == 3);
    CHECK(indices[3] == 5);
}
