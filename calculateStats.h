#ifndef CALCULATE_STATS_H
#define CALCULATE_STATS_H

#include <map>

class CalculateStats{

public:    
    CalculateStats();
    ~CalculateStats();
    
    void addPLatencyToList(long latency, long seqNo);
    double getAvgPLatency();
    double getAvgPJitter();
   
    void addMessageSentTime(long sentTime, int seqNo);
    void addMessageArrivalTime(long arrivalTime, int seqNo);
    void calculateLatencyAtConsumer();
   
    double getAvgCLatency();
    double getAvgCJitter();
   
    std::map<int, long> getInterarrivalTimes();
   
    
    void printCLatency();
    void printCJitter();
    void printAllStats();
    
    void printPInterarrivalTimes();
    void printCInterarrivalTimes();
    
    void printMessageSentTime();
    void printMessageArrivedTime();
    void printPStats();
    void printCStats();
    
private:
    
    //Any metric at C end is w.r.t its calculation at consumer end for QOS 0
    
    std::map<int, long> messageSentTime;
    std::map<int, long> messageArrivalTime;
    std::map<int, long> pInterarrivalTime;
    std::map<int, long> cInterarrivalTime;
    std::map<int, long> pJitter;
    std::map<int, long> cJitter;
    
    std::map<int, long> pLatency;
    
    //This latency is for QOS 0 where it is calculated based on latency value calculated as consumer end
    std::map<int, long> cLatency;
    
    long sumPLatency;
    long sumPJitter;
    
    long sumCLatency;
    long sumCJitter;
};

#endif //CALCULATE_STATS_H