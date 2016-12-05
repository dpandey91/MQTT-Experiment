#include "calculateStats.h"
#include <iostream>
#include <cstdlib>

#define DEBUG

CalculateStats::CalculateStats():
  messageSentTime(),
  messageArrivalTime(),
  pInterarrivalTime(),
  cInterarrivalTime(),
  pJitter(),
  cJitter(),
  pLatency(),
  cLatency(),
  sumPLatency(0),
  sumPJitter(0),
  sumCLatency(0),
  sumCJitter(0)
{}

CalculateStats::~CalculateStats()
{}
    
void CalculateStats::addPLatencyToList(long latency, long seqNo){
    long noOfElements = pLatency.size();
    if(noOfElements > 0){
        long lastElement = pLatency[seqNo-1];
        long jitterVal = abs(latency - lastElement);
        pJitter[seqNo] = jitterVal;
        sumPJitter += jitterVal;
    }
    
    pLatency[seqNo] = latency;
    sumPLatency += latency;
}

double CalculateStats::getAvgPLatency(){
    long noOfElements = pLatency.size();
    double averageLatency = -1;
    if(noOfElements > 0){
      averageLatency = sumPLatency/noOfElements;
    }
    return averageLatency;
}

double CalculateStats::getAvgPJitter(){
    long noOfElements = pJitter.size();
    double averageJitter = -1;
    if(noOfElements > 0){
      averageJitter = sumPJitter/noOfElements;        
    }
    return averageJitter;
}

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
        long latency = arrivalTime - sentTime;
        
        cLatency[seqNo] = latency;
        sumCLatency += latency;
        
        if(seqNo > 0){
            long lastLatency = cLatency[seqNo-1];
            long jitterVal = abs(latency - lastLatency);
            cJitter[seqNo] = jitterVal;
            sumCJitter += jitterVal;
        }
    }
}

double CalculateStats::getAvgCLatency(){
    long noOfElements = cLatency.size();
    double averageCLatency = -1;
    if(noOfElements > 0){
      averageCLatency = sumCLatency/noOfElements;
    }
    return averageCLatency;
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

void CalculateStats::printCLatency(){
    std::cout << "Latency for messages at consumer end are:" << std::endl;
    std::map<int, long>::iterator iter = cLatency.begin();
    while(iter != cLatency.end()){
        std::cout << "Message: " << iter->first << " is " << iter->second << std::endl;
        iter++;
    }
}

void CalculateStats::printCJitter(){
    std::cout << "Jitter for messages at consumer end are:" << std::endl;
    std::map<int, long>::iterator iter = cJitter.begin();
    while(iter != cJitter.end()){
        std::cout << "Message: " << iter->first << " is " << iter->second << std::endl;
        iter++;
    }
}

void CalculateStats::printMessageSentTime(){
#ifdef DEBUG    
    std::cout << "Sent time for messages are:" << std::endl;
#endif    
    std::map<int, long>::iterator iter = messageSentTime.begin();
    while(iter != messageSentTime.end()){
        std::cout << iter->second << std::endl;
        iter++;
    }
}

void CalculateStats::printMessageArrivedTime(){
#ifdef DEBUG        
    std::cout << "Arrival time for messages are:" << std::endl;
#endif    
    std::map<int, long>::iterator iter = messageArrivalTime.begin();
    while(iter != messageArrivalTime.end()){
        std::cout << iter->second << std::endl;
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