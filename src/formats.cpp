#include "formats.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

PPM::PPM(const std::string &path, bool rgb)
{
    _img_data.is_rgb() = rgb;
    _img_data.is_grayscale() = !rgb;
    load(path);
}

PPM::PPM(const Image& img) :
    _header("P3 "   + std::to_string(img.width()) + " "
                    + std::to_string(img.height()) + " "
                    + std::to_string(img.max_pixel_value()) + "\n"),
    _img_data(img)
{}

void PPM::save(const std::string &path)
{
    std::ifstream file_exists(path);

    if (file_exists)
    {
        std::cout << "The file " << path << " already exists!\n";
        std::string ans;

        do
            std::cout << "Would you like to erase it? (y/N) " << std::flush;
        while (getline(std::cin, ans) &&
               !ans.empty() && ans != "y" && ans != "N");

        if (ans != "y")
            return;
    }

    std::ofstream output(path);
    output << _header << "\n" << _img_data;
    std::cout << "Image " << "saved to " << path << "." << std::endl;
}

void PPM::load(const std::string &path)
{
    std::ifstream input(path);

    if (!input)
    {
        std::cout << path << "does not exists." << std::endl;
        return;
    }

    std::string ppm_type;
    std::string ppm_width;
    std::string ppm_height;
    std::string ppm_bits;

    input >> ppm_type >> ppm_width >> ppm_height >> ppm_bits;

    _img_data.width() = std::stoi(ppm_width);
    _img_data.height() = std::stoi(ppm_height);
    _img_data.max_pixel_value() = std::stof(ppm_bits);

    input >> _img_data;
    _header = ppm_type + " " + ppm_width + " " + ppm_height + " " + ppm_bits;

    std::cout << "Image " << path << " loaded." << std::endl;
}

const Image& PPM::image_data() const
{
    return _img_data;
}

Image& PPM::image_data()
{
    return _img_data;
}

/* OBJ class definitions */

OBJ::OBJ(PPM hm)
{
    Image &img = hm.image_data();
    img.normalize();

    int w = img.width();
    int h = img.height();

    _width = w;
    _height = h;
    _depth = 100.f;

    _mesh_points.clear();
    _faces_indices.clear();
    for (int i = 0; i < (int)img.pixels().size(); ++i)
    {
        // normalized x, y and z
        float x = ((float) (i % w));
        float y = img.pixels()[i].l;
        float z = ((float) ((int) (i / w)));

        _mesh_points.emplace_back(x, y, z);

        /* Add the two triangles to the faces indices
         * (only if we're not at the end of the row or on the top row)
         *  (+1) to all the indices because OBJ faces start to 1
         * v2=i+w___v3=i+w+1
         *      |\ |
         *      | \|
         *      |__\
         *   v0=i   v1=i+1
         */
        //std::cout << ((i+1)%w) << " " << (((i/w)+1) % h) << std::endl;
        if ((i+1) % w != 0 && ((i/w)+1) % h != 0)
        {
            _faces_indices.push_back(i+1);      // v0
            _faces_indices.push_back(i+w+1);    // v2
            _faces_indices.push_back(i+2);      // v1

            _faces_indices.push_back(i+2);      // v1
            _faces_indices.push_back(i+w+1);    // v2
            _faces_indices.push_back(i+w+2);    // v3
        }
    }
}

void OBJ::save(const std::string &path)
{
    std::ifstream file_exists(path);

    if (file_exists)
    {
        std::cout << "The file " << path << " already exists!\n";
        std::string ans;

        do
            std::cout << "Would you like to erase it? (y/N) " << std::flush;
        while (getline(std::cin, ans) &&
               !ans.empty() && ans != "y" && ans != "N");

        if (ans != "y")
            return;
    }

    std::ofstream output(path);
    output << "# OBJ model - " << _mesh_points.size() << " vertices - "
           << _faces_indices.size() << " faces\n";

    output << (*this);
    std::cout << "Model " << "saved to " << path << "." << std::endl;
}

const std::vector<vec3f> &OBJ::mesh_points() const
{
    return _mesh_points;
}

std::vector<vec3f> &OBJ::mesh_points()
{
    return _mesh_points;
}

std::ostream& operator<<(std::ostream &os, const OBJ &obj)
{
    for (size_t i = 0; i < obj._mesh_points.size(); ++i)
    {
        //std::cout << "VERTEX " << obj._mesh_points[i].x << std::endl;

        os  << "v "
            << obj._mesh_points[i].x << " "
            << obj._mesh_points[i].y * obj._depth << " "
            << obj._mesh_points[i].z << "\n";
    }

    for (size_t i = 0; i < obj._faces_indices.size()-2; i += 3)
    {
        os  << "f "
            << obj._faces_indices[i]    << " "
            << obj._faces_indices[i+1]  << " "
            << obj._faces_indices[i+2]  << "\n";
    }

    return os;
}
