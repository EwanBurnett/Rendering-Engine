//Pseudo-Random Number Generator - Ewan Burnett 2021
//This Random Number Generator is seeded to time by default. 
//So based on the time the user runs the app, they will recieve different random events.

#pragma once
#include <random>
#include "Time.h"

struct RNG {

    void Seed(float val);

    //Returns a random integer between 0 and max, inclusive
    int RandInt(int max = 100);

private:
    std::mt19937 mt;    //Mersenne Twister RNG
    Time m_time;
};


inline void RNG::Seed(float val)
{
    
    if (val != 0) {
        //Seed the RNG to the input value. 
        mt.seed(static_cast<unsigned int>(val));
    }
    //if value is null, seed to current time.
    else {
        mt.seed(static_cast<unsigned int>(m_time.BaseTime()));
    }
    
}

inline int RNG::RandInt(int max)
{
    return (mt() % max);
}

