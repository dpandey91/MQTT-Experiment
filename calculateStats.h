#ifndef CALCULATE_STATS_H
#define CALCULATE_STATS_H

#include <vector>

class CalculateStats{

public:    
    CalculateStats();
    ~CalculateStats();
    
    void addPLatencyToList(long latency);
    double getAvgPLatency();
    double getAvgJitter();
   
   void addMessageArrivalTime(long arrivalTime);
   std::vector<long> getInterarrivalTimes();
   
   void printInterarrivalTimes();

private:
    void calculateInterarrivalTime();
    
    std::vector<long> platency;
    std::vector<long> messageArrivalTime;
    std::vector<long> interarrivalTime;
    std::vector<long> jitter;
    long sumPLatency;
    long sumJitter;
};

#endif //CALCULATE_STATS_H