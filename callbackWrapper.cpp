#include "callbackWrapper.h"
#include <iostream>
#include "payload.h"
#include "common-utils.h"

CallbackWrapper::CallbackWrapper():
  mqtt::callback(),
  calc(NULL),
  pSeqNo(0),
  cSeqNo(0)
{ 
	std::cout << "Called mqtt callback" << std::endl;
}

CallbackWrapper::CallbackWrapper(CalculateStats* c):
  mqtt::callback(),
  calc(c),
  pSeqNo(0),
  cSeqNo(0)
{ 
	std::cout << "Called mqtt callback" << std::endl;
}

void CallbackWrapper::connection_lost(const std::string& cause) {
	std::cout << "\nConnection lost" << std::endl;
	if (!cause.empty())
		std::cout << "\tcause: " << cause << std::endl;
}

void CallbackWrapper::delivery_complete(mqtt::idelivery_token_ptr tok) {
	//std::string messageStr = tok->get_message()->get_payload();
	//long usec2 = getCurrentMicrosecond();

	//Payload py;
	//py.setDataInObject(messageStr);
	//long usec1 = py.getTimestamp();

	//long curPing = (usec2 - usec1);
    
    //calc->addPLatencyToList(curPing, pSeqNo);
    //pSeqNo++;
	//std::cout << "After delivery_complete elapsed time for token " << tok->get_message_id() << " : " << curPing <<" microseconds " << std::endl;    
}

void CallbackWrapper::message_arrived(const std::string& topic, mqtt::message_ptr msg) {
    
    //TODO: Don't know how to get sequence number here; thus defining a variable for sequence
    long usec2 = getCurrentMicrosecond();
    std::cout << "Message arrived: " << usec2 << std::endl;
    calc->addMessageArrivalTime(usec2, cSeqNo);
    cSeqNo++;
}
