#pragma once
#include <cmath>

class PerlinNoise
{
public:
    PerlinNoise(const PerlinNoise&) = delete;
    PerlinNoise& operator=(const PerlinNoise&) = default;

    //Allows access to perlin noise in the whole code base
    static float GenerateNoise(float x, float y)
    {
        return Get().Noise(x,y);
    }

private:
    PerlinNoise() = default;
    ~PerlinNoise() = default;

    //Private get function, no need to be public as we just need generate noise to be
    static PerlinNoise& Get()
    {
        static PerlinNoise instance;
        return instance;
    }

    //It first computes the integer coordinates of the grid cell containing the point,
    //and the fractional offsets within the cell.
    //It then computes the fade curve values for the fractional offsets,
    //and selects four gradient vectors from the permutation table based
    //on the grid cell coordinates
    float Noise(float x, float y)
    {
        //Wraps the coordinates at the edge of the grid if they fall outside 255
        int xi = (int)std::floor(x) & 255;
        int yi = (int)std::floor(y) & 255;

        //Fractional offset of the point 
        float xf = x - std::floor(x);
        float yf = y - std::floor(y);

        //Fade curve values for the offsets 
        float u = Fade(xf);
        float v = Fade(yf);
#
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
        x1 = Lerp(Grad(aa, xf, yf), Grad(ba, xf - 1, yf), u);
        x2 = Lerp(Grad(ab, xf, yf - 1), Grad(bb, xf - 1, yf - 1), u);
        y1 = Lerp(x1, x2, v);

        //Scales the result to be in range from 0 to 1
        return (y1 + 1.0) / 2.0;
    }

    //Fade function to smooth interpolation between gradients 
    float Fade(float t)
    {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    //Performs linear interpolation between two values using a
    //value T that ranges from 0 to 1
    float Lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }

    //Returns a random gradient vector based on a hash value 
    float Grad(int hash, float x, float y)
    {
        //H is a value between 0 and 15
        int h = hash & 15;
        float u = h < 8 ? x : y;
        float v = h < 4 ? y : h == 12 || h == 14 ? x : 0;
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

    //Original perlin noise permutation table
    int p[256] = {151, 160, 137, 91, 90, 15,
                  131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23,
                  190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
                  88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
                  77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244,
                  102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196,
                  135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123,
                  5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 179,
                  162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84,
                  204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243,
                  141, 128, 195, 78, 66, 215, 61, 156, 180};
};