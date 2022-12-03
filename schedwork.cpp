
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduler(std::map<Worker_T, int>& shifts, const AvailabilityMatrix& avail, const size_t dailyNeed, DailySchedule& schedule, size_t day, size_t ID);
bool availabe(std::map<Worker_T, int>& shifts,  int workerID); //checks if worker has availability
bool shiftcheck(DailySchedule& sched, int day, size_t ID ); //checks if day is filled our not
bool needworkers(DailySchedule& schedule, int day, AvailabilityMatrix& avail, int i); //checks if a day needs workers
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

    
    map<Worker_T, int> shifts; 
    for(auto i = 0; i < (int)avail[0].size(); i++){
      shifts.insert(make_pair(i, maxShifts));
    }
vector<Worker_T> x(dailyNeed, INVALID_ID); 
    for(auto i = 0; i< (int)avail.size();i++){
      sched.push_back(x);
    }
    bool schedule = scheduler(shifts, avail, dailyNeed, sched, 0, 0);
    if(schedule)
    {
        return true;
    }
    else return false;
}
bool availabe(std::map<Worker_T, int>& shifts,  int workerID)
{
    if(shifts[workerID] >= 1)
    {
        return true;
    }
    else if(shifts[workerID] < 0)
    {
         return false;
    }
    return false;
}
bool shiftcheck(DailySchedule& sched, int day, size_t ID )
{
    if(ID == sched[day].size() -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool needworkers(DailySchedule& schedule, int day, const AvailabilityMatrix& avail, int i)
{   
    if(find(schedule[day].begin(), schedule[day].end(), i) == schedule[day].end() && avail[day][i] == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool scheduler(std::map<Worker_T, int>& shifts, const AvailabilityMatrix& avail, const size_t dailyNeed, DailySchedule& schedule, size_t day, size_t ID)
{
    bool filled = false;
    if(day == schedule.size())
    {
        return true; 
    }
    
    else if(day != schedule.size())
    { 
        for(auto i = 0; i < (int)avail[day].size(); ++i)
        {
            if(needworkers(schedule, day, avail, i) && availabe(shifts, i))
            {
                schedule[day][ID] = i;
                shifts[i] = shifts[i] - 1;
                
                if(!shiftcheck(schedule, day, ID))
                {
                    filled = scheduler(shifts, avail, dailyNeed, schedule, day+1, 0);
                }
                
                else if(shiftcheck(schedule, day, ID))
                {
                    filled = scheduler(shifts, avail, dailyNeed, schedule, day, ID+1);
                }
                if(filled != false)
                {
                    return filled;
                }
                schedule[day][ID] = -1;
                shifts[i] = shifts[i] + 1; 
            }
        }
    }
    if (filled == false) 
    {
        return false;
    }
    return 0;
}