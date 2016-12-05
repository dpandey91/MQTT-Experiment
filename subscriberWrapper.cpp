/** By Dipika - Async Publisher **/

#include "subscriberWrapper.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

//#define DEBUG_SUB

SubscriberWrapper::SubscriberWrapper(const std::string& anAddress, int nQos, long nTimeout):
  clientId("AsyncSubscriber"),
  address(anAddress),
  qos(nQos),
  timeout(nTimeout),
  client(address, clientId),
  listener(),
  conntok(NULL),
  calc(),
  cb(&calc)
{
  client.set_callback(cb);
}
  
SubscriberWrapper::~SubscriberWrapper()
{}

bool SubscriberWrapper::connectToBroker(){
    bool bConnect = false;
    try {
		conntok = client.connect();
#ifdef DEBUG_SUB
		std::cout << "Waiting for the connection..." << std::flush;
#endif        
		conntok->wait_for_completion();
#ifdef DEBUG_SUB
		std::cout << "OK" << std::endl;
#endif        
        bConnect = true;
    }
    catch (const mqtt::exception& exc) {
		std::cerr << "connectToBroker => Error: " << exc.what() << std::endl;
		bConnect = false;
	}
    return bConnect;
}

bool SubscriberWrapper::subscribeData(const std::string& topic){
    bool bSubscribed = false;
    try {
#ifdef DEBUG_SUB        
        std::cout << "Subscribing to topic " << topic << "\n"
			<< "for client " << clientId
			<< " using QoS" << qos << "\n\n"
			<< "Press Q<Enter> to quit\n" << std::endl;
#endif            

        client.subscribe(topic, qos);
        bSubscribed = true;
    }
    catch (const mqtt::exception& exc) {
		std::cerr << "subscribed to data => Error: " << exc.what() << std::endl;
		bSubscribed = false;
	}
    return bSubscribed;
}

bool SubscriberWrapper::disconnetFromBroker(){
    bool bDisconnect = false;
    try{
        // Disconnect
#ifdef DEBUG_SUB        
        std::cout << "Disconnecting..." << std::flush;
#endif        
        conntok = client.disconnect();
        conntok->wait_for_completion();
#ifdef DEBUG_SUB        
        std::cout << "OK" << std::endl;
#endif        
        bDisconnect = true;
    }
    catch (const mqtt::exception& exc) {
		std::cerr << "disconnectToBroker => Error: " << exc.what() << std::endl;
		bDisconnect = false;
	}
    return bDisconnect;
}

void SubscriberWrapper::printAllStats(){
    calc.printCStats();
}