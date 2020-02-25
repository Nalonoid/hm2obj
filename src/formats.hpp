#pragma once

#include <vector>
#include "image.hpp"

class PPM
{
public:
    explicit PPM(const std::string &path);
    explicit PPM(const std::string &path, bool rgb);
    explicit PPM(const Image &img);

    void save(const std::string &path = "./out.ppm");
    void load(const std::string &path = "./in.ppm");

    const Image& image_data() const;
    Image& image_data();

private:
    std::string     _header;
    Image           _img_data;
};

struct vec3f
{
    vec3f(float vx, float vy, float vz) : x(vx), y(vy), z(vz) {}
    float x, y, z;
};

class OBJ
{
public:
    OBJ(PPM heightmap);

    void save(const std::string &path = "./out.obj");
    void load(const std::string &path = "./in.obj");

    // Getters
    const std::vector<vec3f>& mesh_points() const;
    std::vector<vec3f>& mesh_points();

    // Insert model data to output
    friend std::ostream& operator<<(std::ostream &os, const OBJ &obj);

    // Read model data from input
    friend std::istream& operator>>(std::istream &is, OBJ &obj);

private:
    std::vector<vec3f> _mesh_points;
    std::vector<unsigned> _faces_indices;

    float _width;
    float _height;
    float _depth;
};
