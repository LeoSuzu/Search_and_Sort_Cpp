#ifndef SEARCH_AND_SORT_TIMER_H
#define SEARCH_AND_SORT_TIMER_H

#include "Utility.h"

class Timer {
public:
    Timer();
    [[nodiscard]] double elapsed_time() const;
    void reset();
private:
    std::clock_t start_time;
};

//=================================

#endif //SEARCH_AND_SORT_TIMER_H
