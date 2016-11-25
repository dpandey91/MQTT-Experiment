#include "callbackWrapper.h"
#include <iostream>
#include "payload.h"
#include "common-utils.h"

CallbackWrapper::CallbackWrapper():
  mqtt::callback()
{ 
	std::cout << "Called mqtt callback" << std::endl;
}

void CallbackWrapper::connection_lost(const std::string& cause) {
	std::cout << "\nConnection lost" << std::endl;
	if (!cause.empty())
		std::cout << "\tcause: " << cause << std::endl;
}

void CallbackWrapper::delivery_complete(mqtt::idelivery_token_ptr tok) {
	std::cout << "Delivery complete for token: " 
		<< (tok ? tok->get_message_id() : -1) << std::endl;

	std::string messageStr = tok->get_message()->get_payload();
	std::cout << "Message is " << messageStr << std::endl;
	long usec2 = getCurrentMicrosecond();

	Payload py;
	py.setDataInObject(messageStr);
	long usec1 = py.getTimestamp();

	long curPing = (usec2 - usec1);
	std::cout << "After delivery_complete elapsed time for" << py.getSeqNo() << ": " << curPing <<" microseconds " << std::endl;
	    
}
