
import time

import numpy as np
import pysubsampl


n = 100_000_000
x_range = 1000
y_range = 1000
z_range = 30
voxel_size = 0.025

data = np.random.uniform((0, 0, 0), (x_range, y_range, z_range), size=(n, 3)).astype(np.float32)
print("Points:", data.shape[0])

t_start = time.time()
indices = pysubsampl.voxel_grid_subsample_3d(data, voxel_size)
print("Subsampling took", f"{time.time() - t_start:.2f}", "s")
t_start = time.time()
data = data[indices, :]
print("Indexing took", f"{time.time() - t_start:.2f}", "s")
print("Points (subsampled):", data.shape[0])
