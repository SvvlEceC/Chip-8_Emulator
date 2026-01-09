#ifndef TIMER
#define TIMER
#include <chrono>
#include <cstdint>

struct timer
{
    uint8_t set_value;
    std::chrono::time_point<std::chrono::steady_clock> start_time;

    void set(uint8_t value){
        set_value = value;
        start_time = std::chrono::steady_clock::now();
    }

    uint8_t get(){
        auto current_time(std::chrono::steady_clock::now());
        uint32_t ticks = (std::chrono::duration_cast<std::chrono::microseconds>(current_time-start_time).count()) / 16666;

        if(set_value <= ticks) return 0;

        return set_value - (uint8_t)ticks;
    }
};
#endif