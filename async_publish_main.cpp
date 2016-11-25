#include "publisherWrapper.h"
#include "payload.h"
#include "common-utils.h"

/*long getMicroseconds(struct timeval *t) {
  return (t->tv_sec) * 1000000 + (t->tv_usec);
}

long getCurrentMicrosecond(){
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    long usec = getMicroseconds(&currentTime);
    return usec;
}*/

//export LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH

int main(int argc, char* argv[]){
    
    const std::string ADDRESS("tcp://localhost:1883");
    const std::string TOPIC("hello");
    const char* PAYLOAD1 = "Hello World!";
    const int  QOS = 1;
    const long TIMEOUT = 10000L;
    
    int nSeqNo = 1;
    bool bRet = false;
    
    Payload payload(PAYLOAD1, TOPIC, nSeqNo);
    PublisherWrapper publishWrapper(ADDRESS, QOS, TIMEOUT);
    
    bRet = publishWrapper.connectToBroker();
    if(!bRet){
        std::cout << "Failed to connect to broker" << std::endl;
        return 0;
    }
    else{
      std::cout << "Connected to broker successfully" << std::endl;
    }

    long usec1 = getCurrentMicrosecond();
    payload.setTimestamp(usec1);
    std::string payloadData = payload.getString();
    
    bRet = publishWrapper.publishData(TOPIC, payloadData);
    if(!bRet){
        std::cout << "Failed to publish data to broker" << std::endl;
        return 0;
    }
    else{
      std::cout << "Published to broker successfully" << std::endl;
    }

    long usec2 = getCurrentMicrosecond();
    long curPing = (usec2 - usec1);
    //printf("After publish in main elapsed time for (%d): %ld microseconds\n", nSeqNo, curPing);
    
    bRet = publishWrapper.disconnetFromBroker();
    if(!bRet){
        std::cout << "Failed to disconnet from broker" << std::endl;
        return 0;
    }
    else{
      std::cout << "Disconnected from broker successfully" << std::endl;
    }
    
    std::cout << "PublisherWrapper is successful" << std::endl;
    return 1;
}
