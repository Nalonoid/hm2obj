#include <algorithm>
#include <iostream>
#include "image.hpp"

Image::Image(unsigned int w, unsigned int h) : _max_pixl_val(255.f),
    _is_rgb(true), _is_grayscale(false)
{
    _pixels.resize(w*h, Pixel(0.9f, 0.9f, 0.1f));
}

Image::Image(unsigned int w, unsigned int h, float max, bool rgb) :
    _max_pixl_val(max), _is_rgb(rgb), _is_grayscale(!rgb)
{
    _pixels.resize(w*h, Pixel(0.0f));
}

const std::vector<Pixel>& Image::pixels() const
{
    return _pixels;
}

std::vector<Pixel>& Image::pixels()
{
    return _pixels;
}

int Image::width() const
{
    return _width;
}

int &Image::width()
{
    return _width;
}

int Image::height() const
{
    return _height;
}

int &Image::height()
{
    return _height;
}

float Image::max_pixel_value() const
{
    return _max_pixl_val;
}

float& Image::max_pixel_value()
{
    return _max_pixl_val;
}

bool Image::is_rgb() const
{
    assert(_is_rgb == !_is_grayscale);
    return _is_rgb;
}

bool &Image::is_rgb()
{
    return _is_rgb;
}

bool Image::is_grayscale() const
{
    assert(_is_rgb == !_is_grayscale);
    return _is_grayscale;
}

bool &Image::is_grayscale()
{
    return _is_grayscale;
}

const Pixel& Image::operator[](size_t n) const
{
    return _pixels[n];
}

Pixel& Image::operator[](size_t n)
{
    return _pixels[n];
}

void Image::normalize()
{
    if (_is_rgb)
        return;

    const auto minmax = std::minmax_element(std::begin(_pixels),
            std::end(_pixels), [](const Pixel &p1, const Pixel &p2)
    {
        return p1.r > p2.r;
    });

    std::vector<Pixel> pixels;
    for (Pixel p : _pixels)
        pixels.emplace_back(
                    (p.r-minmax.second->r)/(minmax.first->r-minmax.second->r));

    _pixels = pixels;
}

std::ostream& operator<<(std::ostream &os, const Image &img)
{
    for (size_t i = 0; i < img._pixels.size(); ++i)
    {
        os  << static_cast<int>(img._pixels[i].r*img._max_pixl_val) << " "
            << static_cast<int>(img._pixels[i].g*img._max_pixl_val) << " "
            << static_cast<int>(img._pixels[i].b*img._max_pixl_val) << "\n";
    }

    return os;
}

std::istream& operator>>(std::istream &is, Image &img)
{
    img._pixels.clear();

    float r, g, b;
    while (is >> r >> g >> b)
    {
        img._pixels.emplace_back(r/img._max_pixl_val,
                                 g/img._max_pixl_val,
                                 b/img._max_pixl_val);
    }

    return is;
}
