#pragma once
#include <algorithm>
#include <random>
#include <numeric>

class PerlinNoise
{
public:
    explicit PerlinNoise(unsigned int seed = 0)
    {
        //Initialize the permutation table with values 0 to 255
        std::iota(std::begin(p), std::end(p), 0);

        //Shuffle the permutation table based on the seed value
        //seed is taken for the noise to be reproduced with the same sound 
        std::default_random_engine engine(seed);
        std::shuffle(std::begin(p), std::end(p), engine);
    }

    //It first computes the integer coordinates of the grid cell containing the point,
    //and the fractional offsets within the cell.
    //It then computes the fade curve values for the fractional offsets,
    //and selects four gradient vectors from the permutation table based
    //on the grid cell coordinates
    float GenerateNoise(float x, float y)
    {
        //Wraps the coordinates at the edge of the grid if they fall outside 255
        int xi = (int) floor(x) & 255;
        int yi = (int) floor(y) & 255;

        //Fractional offset of the point 
        float xf = x - floor(x);
        float yf = y - floor(y);

        //Fade curve values for the offsets 
        float u = fade(xf);
        float v = fade(yf);

        //creates a variable for the gradient vector of each of the
        //four corners of a cell
        //Gradient vector is determined via the permutation table 
        int aa, ab, ba, bb;
        aa = p[p[xi] + yi];
        ab = p[p[xi] + yi + 1];
        ba = p[p[xi + 1] + yi];
        bb = p[p[xi + 1] + yi + 1];

        //Uses linear interpolation to compute the final noise value
        float x1, x2, y1;
        x1 = lerp(grad(aa, xf, yf), grad(ba, xf - 1, yf), u);
        x2 = lerp(grad(ab, xf, yf - 1), grad(bb, xf - 1, yf - 1), u);
        y1 = lerp(x1, x2, v);

        //Scales the result to be in range from 0 to 1
        return (y1 + 1.0) / 2.0;
    }

private:
    //Fade function to smooth interpolation between gradients
    float fade(float t)
    {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    //Performs linear interpolation between two values using a
    //value T that ranges from 0 to 1
    float lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }

    //Returns a random gradient vector based on a hash value
    float grad(int hash, float x, float y)
    {
        int h = hash & 15;
        float u = h < 8 ? x : y;
        float v = h < 4 ? y : h == 12 || h == 14 ? x : 0;
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

    int p[512]{}; // Permutation table
};