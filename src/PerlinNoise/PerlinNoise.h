//
// Created by kaygalle on 24.05.2020.
//
#ifndef PERLINNOISE_HPP
#define PERLINNOISE_HPP

#include <vector>
#include <algorithm>
#include <random>
#include "glm/glm.hpp"

using namespace glm;

class PerlinNoise
{
    private:
        double m_scale;
        static vec3 grad3 [12];
        static std::vector <int> p;
        static int fastfloor(double x);
        static double dot_product(vec3 g, double x, double y, double z);
        static double lerp (double a, double b, double t);
        static double fade(double t);
    public:
        PerlinNoise();
        double PerlinNoise3D(double x, double y, double z);
        double fracNoise3D(double x, double y, double z);
        void setSeed(int seed);
        void setScale(double scale);
};



#endif //MINECRAFT_PERLINNOISE_HPP
