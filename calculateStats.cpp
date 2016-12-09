#include "calculateStats.h"
#include <iostream>
#include <cstdlib>

CalculateStats::CalculateStats():
  messageSentTime(),
  messageArrivalTime(),
  pInterarrivalTime(),
  cInterarrivalTime(),
  latency(),
  cJitter(),
  sumLatency(0),
  sumCJitter(0)
{}

CalculateStats::~CalculateStats()
{}
    

void CalculateStats::addMessageSentTime(long sentTime, int seqNo){
    long noOfElements = messageSentTime.size();
    if(noOfElements > 0){
        long lastElement = messageSentTime[seqNo-1];
        long interarrival = sentTime - lastElement;
        pInterarrivalTime[seqNo] = interarrival;
    }
    messageSentTime[seqNo] = sentTime;
}

void CalculateStats::addMessageArrivalTime(long arrivalTime, int seqNo){
    long noOfElements = messageArrivalTime.size();
    if(noOfElements > 0){
        long lastElement = messageArrivalTime[seqNo-1];
        long interarrival = arrivalTime - lastElement;
        cInterarrivalTime[seqNo] = interarrival;
    }
    messageArrivalTime[seqNo] = arrivalTime;
}

void CalculateStats::calculateLatencyAtConsumer(){
    std::map<int, long>::iterator iter = messageSentTime.begin();
    while(iter != messageSentTime.end()){
        unsigned seqNo = iter->first;
        long sentTime = iter->second;
        long arrivalTime = messageArrivalTime[seqNo];
        long latencyVal = arrivalTime - sentTime;
        
        latency[seqNo] = latencyVal;
        sumLatency += latencyVal;
        
        if(seqNo > 0){
            long lastLatency = latency[seqNo-1];
            long jitterVal = abs(latencyVal - lastLatency);
            cJitter[seqNo] = jitterVal;
            sumCJitter += jitterVal;
        }
        iter++;
    }
}

double CalculateStats::getAvgLatency(){
    long noOfElements = latency.size();
    double averageLatency = -1;
    if(noOfElements > 0){
      averageLatency = sumLatency/noOfElements;
    }
    return averageLatency;
}

double CalculateStats::getAvgCJitter(){
    long noOfElements = cJitter.size();
    double averageJitter = -1;
    if(noOfElements > 0){
      averageJitter = sumCJitter/noOfElements;        
    }
    return averageJitter;
}

void CalculateStats::printCInterarrivalTimes(){
    std::cout << "Interarrival times at consmer end for messages are:" << std::endl;
    std::map<int, long>::iterator iter = cInterarrivalTime.begin();
    while(iter != cInterarrivalTime.end()){
        std::cout << iter->first << " " << iter->second << std::endl;
        iter++;
    }
}

void CalculateStats::printPInterarrivalTimes(){
    std::cout << "Interarrival times at consmer end for messages are:" << std::endl;
    std::map<int, long>::iterator iter = pInterarrivalTime.begin();
    while(iter != pInterarrivalTime.end()){
        std::cout << iter->first << " " << iter->second << std::endl;
        iter++;
    }
}

void CalculateStats::printLatency(){
    calculateLatencyAtConsumer();
    std::cout << "Latency for messages calculated at consumer end are:" << std::endl;
    std::map<int, long>::iterator iter = latency.begin();
    while(iter != latency.end()){
        std::cout << iter->first << " " << iter->second << std::endl;
        iter++;
    }
    
    std::cout << "Average Latency is " << getAvgLatency() << std::endl;
}

void CalculateStats::printCJitter(){
    std::cout << "Jitter for messages at consumer end are:" << std::endl;
    std::map<int, long>::iterator iter = cJitter.begin();
    while(iter != cJitter.end()){
        std::cout << iter->first << " " << iter->second << std::endl;
        iter++;
    }
}

void CalculateStats::printMessageSentTime(){
    std::cout << "Sent time for messages are:" << std::endl;
    std::map<int, long>::iterator iter = messageSentTime.begin();
    while(iter != messageSentTime.end()){
        std::cout << iter->first << " " << iter->second << std::endl;
        iter++;
    }
}

void CalculateStats::printMessageArrivedTime(){
    std::cout << "Arrival time for messages are:" << std::endl;
    std::map<int, long>::iterator iter = messageArrivalTime.begin();
    while(iter != messageArrivalTime.end()){
        std::cout << iter->first << " " << iter->second << std::endl;
        iter++;
    }
}

void CalculateStats::printPStats(){
    printMessageSentTime();
    //printPInterarrivalTimes();
}

void CalculateStats::printCStats(){
    printMessageArrivedTime();
    //printCInterarrivalTimes();
}