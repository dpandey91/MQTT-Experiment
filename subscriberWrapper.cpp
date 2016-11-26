/** By Dipika - Async Publisher **/

#include "subscriberWrapper.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

SubscriberWrapper::SubscriberWrapper(const std::string& anAddress, int nQos, long nTimeout):
  clientId("AsyncSubscriber"),
  address(anAddress),
  qos(nQos),
  timeout(nTimeout),
  client(address, clientId),
  listener(),
  conntok(NULL),
  cb()
{
  client.set_callback(cb);
}
  
SubscriberWrapper::~SubscriberWrapper()
{}

bool SubscriberWrapper::connectToBroker(){
    bool bConnect = false;
    try {
		conntok = client.connect();
		std::cout << "Waiting for the connection..." << std::flush;
		conntok->wait_for_completion();
		std::cout << "OK" << std::endl;
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
        std::cout << "Subscribing to topic " << topic << "\n"
			<< "for client " << clientId
			<< " using QoS" << qos << "\n\n"
			<< "Press Q<Enter> to quit\n" << std::endl;

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
        std::cout << "Disconnecting..." << std::flush;
        conntok = client.disconnect();
        conntok->wait_for_completion();
        std::cout << "OK" << std::endl;
        bDisconnect = true;
    }
    catch (const mqtt::exception& exc) {
		std::cerr << "disconnectToBroker => Error: " << exc.what() << std::endl;
		bDisconnect = false;
	}
    return bDisconnect;
}
