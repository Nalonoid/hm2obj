__Building instructions (Linux)__

git clone https://github.com/Nalonoid/hm2obj.git hm2obj

cd hm2obj

mkdir build && cd build

cmake ..

make

The binary will be located in hm2obj/bin

__Usage__

In order to have proper P3 PPM image files:

convert -compress none in.{jpg, png,...} out.ppm

./bin/hm2obj in.ppm out.obj [is_rgb={0,1}]

By default, the images are considered as grayscale.

__Example__

Input image:

![small_alaska_heightmap.png](./img/small_alaska_heightmap.png "Small Alaska heightmap")

Output OBJ in Meshlab:

![small_alaska_coarse.obj](./img/small_alaska_coarse.png "Small Alaska OBJ in Meshlab")

After a few smoothing steps:

![small_alaska_smooth.obj](./img/small_alaska_smooth.png "Small Alaska after smoothing")
