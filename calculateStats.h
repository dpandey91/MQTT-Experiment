#ifndef CALCULATE_STATS_H
#define CALCULATE_STATS_H

#include <map>

class CalculateStats{

public:    
    CalculateStats();
    ~CalculateStats();
    
    void addMessageSentTime(long sentTime, int seqNo);
    void addMessageArrivalTime(long arrivalTime, int seqNo);
    void calculateLatencyAtConsumer();
   
    double getAvgLatency();
    double getAvgCJitter();
   
    void printLatency();
    void printCJitter();
        
    void printPInterarrivalTimes();
    void printCInterarrivalTimes();
    
    void printMessageSentTime();
    void printMessageArrivedTime();
    
    void printPStats();
    void printCStats();
    
private:
    
    std::map<int, long> messageSentTime;
    std::map<int, long> messageArrivalTime;
    std::map<int, long> pInterarrivalTime;
    std::map<int, long> cInterarrivalTime;
    
    std::map<int, long> latency;
    std::map<int, long> cJitter;
    
    long sumLatency;
    long sumCJitter;
};

#endif //CALCULATE_STATS_H