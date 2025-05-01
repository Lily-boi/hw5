#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool backtrack(const AvailabilityMatrix& avail, 
                const size_t dailyNeed,
                const size_t maxShifts, 
                DailySchedule& sched, 
                std::vector<int>& shiftsAssigned,
                size_t day, size_t slot);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    const size_t n = avail.size();
    const size_t k = avail[0].size();

    sched.resize(n);

    std::vector<int> shiftsAssigned(k, 0);

    return backtrack(avail, dailyNeed, maxShifts, sched, shiftsAssigned, 0, 0);
}

bool backtrack(const AvailabilityMatrix& avail, 
                const size_t dailyNeed,
                const size_t maxShifts, 
                DailySchedule& sched, 
                std::vector<int>& shiftsAssigned,
                size_t day, size_t slot) {
    
    size_t n = avail.size();
    size_t k  = avail[0].size();

    if (day == n) {
        return true;
    }

    if (slot == dailyNeed) {
        return backtrack(avail, dailyNeed, maxShifts, sched, shiftsAssigned, day+1, 0);
    }

    for (size_t worker = 0; worker < k; ++worker) {
        if (avail[day][worker] && shiftsAssigned[worker] < static_cast<int>(maxShifts) && std::find(sched[day].begin(), sched[day].end(), worker) == sched[day].end()) {
            sched[day].push_back(worker);
            shiftsAssigned[worker]++;

            if (backtrack(avail, dailyNeed, maxShifts, sched, shiftsAssigned, day, slot+1)) {
                return true;
            }

            sched[day].pop_back();
            shiftsAssigned[worker]--;
        }

    }
    return false;

}