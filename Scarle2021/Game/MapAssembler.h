#pragma once
#include <vector>
#include <random>

#include "PerlinNoise.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

class MapAssembler
{
public:
    
    static std::vector<std::vector<float>> GenerateNoiseMap(const int& map_width, const int& map_height, std::mt19937_64& prng,
        const int& octaves, float scale, const float& persistance, const float& lacunarity, const Vector2& offset)
    {
        //Map is a 2D array
        std::vector<std::vector<float>> noise_map;

        //Noise map vector is initialized to all 0s
        noise_map.reserve(map_height);
        for(int y = 0; y < map_height; y++)
        {
            noise_map.emplace_back(std::vector<float>());
            noise_map.back().reserve(map_width);

            for(int x = 0; x < map_width; x++)
            {
                //default cost set to 0
                noise_map.back().emplace_back(0);
            }
        }

        //inits a offset vec for the octaves
        std::vector<Vector2> octaves_offset;

        //Sets a fixed range for the octaves offset
        std::uniform_real_distribution<float> range(-100000, 100000);

        //Octaves offsets are initialized
        for (int i = 0; i < octaves; ++i)
        {
            const float offset_x = range(prng) + offset.x;
            const float offset_y = range(prng) + offset.y;
            octaves_offset.emplace_back(Vector2{offset_x, offset_y});
        }

        //Caps the scale to prevent undefined behaviour
        if(scale <= 0)
        {
            scale = 0.001f;
        }
        
        float half_width = map_width * 0.5f;
        float half_height = map_height * 0.5f;

        PerlinNoise perlin_noise(1234);

        //using perlin noise generates the noise map
        for (int y = 0; y < map_height; ++y)
        {
            for (int x = 0; x < map_width; ++x)
            {
                float amplitude = 1;
                float frequency = 1;
                float noise_height = 0;

                //Ocaves loop
                for (int i = 0; i < octaves; ++i)
                {
                    //Scales the X and Y value
                    float scaled_x = ((x-half_width) / 10) / scale * frequency + octaves_offset[i].x;
                    float scaled_y = ((y-half_height) / 10) / scale * frequency - octaves_offset[i].y;

                    //a -1 is applied to allow the value to be both negative and positive
                    float perlin_value = perlin_noise.GenerateNoise(scaled_x, scaled_y) * 2 - 1;
                    noise_height += perlin_value * amplitude;

                    amplitude *= persistance;
                    frequency *= lacunarity;
                }
                
                noise_map[x][y] = (noise_height + 1) / 2;
            }
        }

        return noise_map;
    }
};