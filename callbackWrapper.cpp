#include "callbackWrapper.h"
#include <iostream>
#include "payload.h"
#include "common-utils.h"

CallbackWrapper::CallbackWrapper(int nDebugLevel, bool bMsgWithTs):
  mqtt::callback(),
  calc(NULL),
  debugLevel(nDebugLevel),
  msgWithTs(bMsgWithTs),
  pSeqNo(0),
  cSeqNo(0)
{ 
    if(debugLevel == 1)
        std::cout << "Called mqtt callback" << std::endl;
}

CallbackWrapper::CallbackWrapper(int nDebugLevel, bool bMsgWithTs, CalculateStats* c):
  mqtt::callback(),
  calc(c),
  debugLevel(nDebugLevel),
  msgWithTs(bMsgWithTs),
  pSeqNo(0),
  cSeqNo(0)
{ 
  if(debugLevel == 1)
	std::cout << "Called mqtt callback" << std::endl;
}

void CallbackWrapper::connection_lost(const std::string& cause) {
    if(debugLevel == 1){
      std::cout << "\nConnection lost" << std::endl;
      if (!cause.empty())
		std::cout << "\tcause: " << cause << std::endl;    
    }
}

void CallbackWrapper::delivery_complete(mqtt::idelivery_token_ptr tok) {
    if(debugLevel == 1){
        std::cout << "Acknowlegment received in publisher with QOS 1" << std::endl;
    }
}

void CallbackWrapper::message_arrived(const std::string& topic, mqtt::message_ptr msg) {
    
    long usec2 = getCurrentMicrosecond();
    int nSeqNo = -1;
    if(msgWithTs){
        Payload py;
        std::string messageStr = msg->get_payload();
        py.setDataInObject(messageStr);
        long usec1 = py.getTimestamp();
        
        nSeqNo = py.getSeqNo();
        
        calc->addMessageSentTime(usec1, nSeqNo);
    }
    else{
        //TODO: Don't know how to get sequence number when not sending json string; thus defining a variable for sequence
        nSeqNo = cSeqNo++;
    }

    calc->addMessageArrivalTime(usec2, nSeqNo);
    if(debugLevel == 1){
        std::cout << "Message arrived with seqNo " << nSeqNo << std::endl; 
    }
}
