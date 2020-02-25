#pragma once

#include <assert.h>
#include <vector>
#include <fstream>
#include <math.h>

#define EPSILON 0.0001

struct Pixel
{
    Pixel(float gray) : r(gray), g(gray), b(gray) {}
    Pixel(float red, float gre, float blu) : r(red), g(gre), b(blu) {}

    float r;
    float g;
    float b;
};

class Image
{
    Image() {}

public:

    Image(unsigned int w, unsigned int h);
    Image(unsigned int w, unsigned int h, float max, bool rgb);

    // Getters
    const std::vector<Pixel>& pixels() const;
    std::vector<Pixel>& pixels();

    int     width() const;
    int&    width();
    int     height() const;
    int&    height();
    float   max_pixel_value() const;
    float&  max_pixel_value();
    bool    is_rgb() const;
    bool&   is_rgb();
    bool    is_grayscale() const;
    bool&   is_grayscale();

    // Access operators
    const Pixel& operator[](size_t n) const;
    Pixel& operator[](size_t n);

    // Insert Image data to output
    friend std::ostream& operator<<(std::ostream &os, const Image &img);

    // Read Image data from input
    friend std::istream& operator>>(std::istream &is, Image &img);

    // Methods
    // normalize values to lie in [0, 1] space for a grayscale image
    void normalize();
private:
    std::vector<Pixel> _pixels;
    int     _width;
    int     _height;
    float   _max_pixl_val;
    bool    _is_rgb;
    bool    _is_grayscale;

    friend class PPM;
};
