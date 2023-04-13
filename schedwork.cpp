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

bool scheduleinator (int r, int c, const AvailabilityMatrix& avail, const size_t maxShifts, DailySchedule& sched, vector<int> tracker, vector<set<int>>& daytrack, int track);

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

    //Shift number tracker
    vector<int> tracker (avail[0].size(), 0);
    //Shift day tracker
    vector<set<int>> daysscheduled(avail[0].size());

    //Create blank schedule in sched
    vector<Worker_T> row (dailyNeed, INVALID_ID);
    vector<vector<Worker_T>> newsched (avail.size(), row);
    sched = newsched;

    //Debug

    return scheduleinator (0, 0, avail, maxShifts, sched, tracker, daysscheduled, 0);
}

bool scheduleinator(int r, int c, const AvailabilityMatrix& avail, const size_t maxShifts, DailySchedule& sched, vector<int> tracker, vector<set<int>>& daytrack, int track){
    int full = sched.size()*sched[0].size();
    //cout << "r: " << r << " c: " << c << " track: " << track << endl;

    if (r == sched.size()) return true;
    //Daily
    /*
    else if (c == sched[0].size()){
        return scheduleinator(r+1, 0, avail, maxShifts, sched, tracker, daytrack, track);
    }
     */
    /*
    else if (sched[r][c] != INVALID_ID){
        scheduleinator(r, c+1, avail, maxShifts, sched, tracker, daytrack, track);
    }*/

    for (size_t i = 0; i < avail[r].size(); i++) {
        //Feeling good

        //r = day
        //c = shift
        //i = person

        if (i >= daytrack.size()){
            continue;
        }
        if (tracker[i] >= maxShifts) {
            //sched[r][c] = INVALID_ID;
            continue;
        }
        if (!avail[r][i]) {
            //sched[r][c] = INVALID_ID;
            continue;
        }
        if (daytrack[i].find(r) != daytrack[i].end()) {
            //sched[r][c] = INVALID_ID;
            continue;
        }

        bool valid = 0;
        tracker[i]++;
        sched[r][c] = i;
        daytrack[i].insert(r);

        if (c+1 == sched[r].size()){
            valid = scheduleinator(r+1, 0, avail, maxShifts, sched, tracker, daytrack, track);
        }
        else valid = scheduleinator(r, c+1, avail, maxShifts, sched, tracker, daytrack, track);

        if (valid) return true;

        sched[r][c] = INVALID_ID;
        tracker[i]--;
        daytrack[i].erase(r);

        /*
        sched[r][c] = i;
        tracker[i]++;
        daytrack[i].insert(r);
        track++;
        //???
        if (scheduleinator(r, c + 1, avail, maxShifts, sched, tracker, daytrack, track)) {
            return true;
        }

        sched[r][c] = INVALID_ID;
        tracker[i]--;
        daytrack[i].erase(r);
        track--;
        //continue;
         */
    }

    return false;
}

