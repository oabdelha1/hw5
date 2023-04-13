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

bool scheduleinator (int r, int c, const AvailabilityMatrix& avail, const size_t maxShifts, DailySchedule& sched, vector<int> tracker);

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

    //Shift tracker
    vector<int> tracker (avail.size(), 0);

    //Create blank schedule in sched
    vector<Worker_T> row (dailyNeed, INVALID_ID);
    vector<vector<Worker_T>> newsched (avail[0].size(), row);
    sched = newsched;

    return scheduleinator (0, 0, avail, maxShifts, sched, tracker);
}

bool scheduleinator(int r, int c, const AvailabilityMatrix& avail, const size_t maxShifts, DailySchedule& sched, vector<int> tracker){
    if (r == sched.size()) return true;
    if (c == sched[0].size()){
        return scheduleinator(r+1, 0, avail, maxShifts, sched, tracker);
    }

    if (sched[r][c] != INVALID_ID){
        scheduleinator(r, c+1, avail, maxShifts, sched, tracker);
    }

    for (size_t i = 0; i < avail.size(); i++){
        //Feeling good
        sched[r][c] = i;
        if (tracker[i] >= maxShifts){
            sched[r][c] = INVALID_ID;
            continue;
        }
        if (!avail[i][r]){
            sched[r][c] = INVALID_ID;
            continue;
        }

        tracker[i]++;

        //???
        if (!scheduleinator(r, c+1, avail, maxShifts, sched, tracker)){
            sched[r][c] = INVALID_ID;
            tracker[i]--;
            continue;
        }
        else{
            return true;
        }
    }

    return false;
}

