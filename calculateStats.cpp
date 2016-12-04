#include "calculateStats.h"
#include <iostream>
#include <cstdlib>

CalculateStats::CalculateStats():
  platency(),
  messageArrivalTime(),
  interarrivalTime(),
  jitter(),
  sumPLatency(0),
  sumJitter(0)
{}

CalculateStats::~CalculateStats()
{}
    
void CalculateStats::addPLatencyToList(long latency){
    long noOfElements = platency.size();
    if(noOfElements > 0){
        long lastElement = platency[noOfElements-1];
        long jitterVal = abs(latency - lastElement);
        jitter.push_back(jitterVal);
        sumJitter += jitterVal;
    }
    
    platency.push_back(latency);
    sumPLatency += latency;
}

double CalculateStats::getAvgPLatency(){
    long noOfElements = platency.size();
    double averageLatency = -1;
    if(noOfElements > 0){
      averageLatency = sumPLatency/noOfElements;
    }
    return averageLatency;
}

double CalculateStats::getAvgJitter(){
    long noOfElements = jitter.size();
    double averageJitter = -1;
    if(noOfElements > 0){
      averageJitter = sumJitter/noOfElements;        
    }
    return averageJitter;
}
   
void CalculateStats::addMessageArrivalTime(long arrivalTime){
    long noOfElements = messageArrivalTime.size();
    if(noOfElements > 0){
        long lastElement = messageArrivalTime[noOfElements-1];
        long interarrival = arrivalTime - lastElement;
        interarrivalTime.push_back(interarrival);
    }
    messageArrivalTime.push_back(arrivalTime);
}

std::vector<long> CalculateStats::getInterarrivalTimes(){
    return interarrivalTime;
}
   
void CalculateStats::printInterarrivalTimes(){
    std::cout << "Interarrival times for messages are:" << std::endl;
    for(int i = 0; i < interarrivalTime.size(); i++){
        std::cout << "Message: " << i << " is " << interarrivalTime[i] << std::endl;
    }
}

