#pragma once

#include <vector>
#include "ActionListPacket.h"

namespace AL
{
    struct Packet
    {
        Packet() = default;

        //Clears the allocated data when the packet is destroyed
        ~Packet()
        {
            for (void* value : values)
            {
                free(value);
            }
        }

        //Adds a value of chosen type to the packet
        template<typename T>
        void AddValue(T value)
        {
            //Allocates the amount of memory needed to store the variable
            void* ptr = malloc(sizeof(value));
            //At the correct memory location, save the variable
            *(T*)ptr = value;
            //Adds the pointer to the pointer vector
            values.push_back(ptr);
        }

        //Retrieves a specific value given an index
        //SPECIFYING THE INCORRECT TYPE COULD LEAD TO UNDEFINED BEHAVIOUR
        template<typename T>
        T GetValue(int index = 0)
        {
            //If the vector is not emtpy return the variable at the
            //specified address of memory as the type given.
            if(!values.empty())
            {
                return *(T*)values[index];
            }
            //if the vector is empty return null
            return (T)NULL;
        }

        //Returns the vector size
        int GetSizeVec() const
        {
            return static_cast<int>(values.size());
        }

        //Pointer vector
        std::vector<void*> values{};
    };
}

