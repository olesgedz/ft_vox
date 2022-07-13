#include "PerlinNoise.h"
#include <numeric>

vec3 PerlinNoise::grad3 [] = {{1,1,0},{-1,1,0},{1,-1,0},{-1,-1,0},
                              {1,0,1},{-1,0,1},{1,0,-1},{-1,0,-1},
                              {0,1,1},{0,-1,1},{0,1,-1},{0,-1,-1}};

std::vector <int> PerlinNoise::p = {
    151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
    8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
    35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,
    134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
    55,46,245,40,244,102,143,54, 65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
    18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,
    250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
    189,28,42,223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167,
    43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,
    97,228,251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,
    107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 };

PerlinNoise::PerlinNoise()
{
    p.insert(p.end(), p.begin(), p.end());
}

void PerlinNoise::setSeed(int seed)
{
    p.resize(256);
    std::iota(p.begin(), p.end(), 0);
    std::default_random_engine engine(seed);
    std::shuffle(p.begin(), p.end(), engine);
    p.insert(p.end(), p.begin(), p.end());
}

void PerlinNoise::setScale(double scale)
{
    m_scale = scale;
}

int PerlinNoise::fastfloor(double x)
{
    return x > 0 ? (int)x : (int) x - 1;
}

double PerlinNoise::dot_product(vec3 g, double x, double y, double z)
{
    return g.x * x + g.y * y + g.z * z;
}

double PerlinNoise::lerp(double a, double b, double t)
{
    return (1 - t) * a + t * b;
}

double PerlinNoise::fade(double t)
{
    return t*t*t*(t*(t*6-15)+10);
}

double PerlinNoise::PerlinNoise3D(double x, double y, double z)
{
    x /= m_scale;
    y /= m_scale;
    z /= m_scale;

    int X = fastfloor(x);
    int Y = fastfloor(y);
    int Z = fastfloor(z);

    x = x - X;
    y = y - Y;
    z = z - Z;

    X = X & 255;
    Y = Y & 255;
    Z = Z & 255;

    int gi000 = p[X+p[Y+p[Z]]] % 12;
    int gi001 = p[X+p[Y+p[Z+1]]] % 12;
    int gi010 = p[X+p[Y+1+p[Z]]] % 12;
    int gi011 = p[X+p[Y+1+p[Z+1]]] % 12;
    int gi100 = p[X+1+p[Y+p[Z]]] % 12;
    int gi101 = p[X+1+p[Y+p[Z+1]]] % 12;
    int gi110 = p[X+1+p[Y+1+p[Z]]] % 12;
    int gi111 = p[X+1+p[Y+1+p[Z+1]]] % 12;

    double n000= dot_product(grad3[gi000], x, y, z);
    double n100= dot_product(grad3[gi100], x-1, y, z);
    double n010= dot_product(grad3[gi010], x, y-1, z);
    double n110= dot_product(grad3[gi110], x-1, y-1, z);
    double n001= dot_product(grad3[gi001], x, y, z-1);
    double n101= dot_product(grad3[gi101], x-1, y, z-1);
    double n011= dot_product(grad3[gi011], x, y-1, z-1);
    double n111= dot_product(grad3[gi111], x-1, y-1, z-1);

    double u = fade(x);
    double v = fade(y);
    double w = fade(z);

    double nx00 = lerp(n000, n100, u);
    double nx01 = lerp(n001, n101, u);
    double nx10 = lerp(n010, n110, u);
    double nx11 = lerp(n011, n111, u);

    double nxy0 = lerp(nx00, nx10, v);
    double nxy1 = lerp(nx01, nx11, v);

    double nxyz = lerp(nxy0, nxy1, w);
    return nxyz;
}

double PerlinNoise::fracNoise3D(double x, double y, double z)
{
    double value = 0.0;
    double factor = 1.0;
    for (int i = 0; i < 8; i++)
    {
        value += PerlinNoise3D(x / factor, y / factor, z / factor);
        factor *= 2.0;
    }
    return value;
}


