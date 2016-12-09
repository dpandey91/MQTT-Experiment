/** By Dipika - Async Subscriber **/

#include "subscriberWrapper.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

SubscriberWrapper::SubscriberWrapper(int nDebugLevel, const std::string& anAddress, int nQos, bool bMsgWithTs):
  debugLevel(nDebugLevel),
  clientId("AsyncSubscriber"),
  address(anAddress),
  qos(nQos),
  client(address, clientId),
  listener(),
  conntok(NULL),
  calc(),
  msgWithTs(bMsgWithTs),
  cb(debugLevel, msgWithTs, &calc)
{
  client.set_callback(cb);
}
  
SubscriberWrapper::~SubscriberWrapper()
{}

bool SubscriberWrapper::connectToBroker(){
    bool bConnect = false;
    try {
		conntok = client.connect();
        if(debugLevel == 1){
            std::cout << "Waiting for the connection for subscriber..." << std::flush;
        }
            
		conntok->wait_for_completion();

        if(debugLevel == 1){
            std::cout << "Connection completed" << std::flush;
        }
		
        bConnect = true;
    }
    catch (const mqtt::exception& exc) {
		std::cerr << "ConnectToBroker => Error: " << exc.what() << std::endl;
		bConnect = false;
	}
    return bConnect;
}

bool SubscriberWrapper::subscribeData(const std::string& topic){
    bool bSubscribed = false;
    try {
        if(debugLevel == 1){
            std::cout << "Subscribing to topic " << topic << "\n"
			<< "for client " << clientId
			<< " using QoS" << qos << "\n\n"
			<< "Press Q<Enter> to quit\n" << std::endl;    
        }
        
        client.subscribe(topic, qos);
        bSubscribed = true;
    }
    catch (const mqtt::exception& exc) {
		std::cerr << "Subscribed to data => Error: " << exc.what() << std::endl;
		bSubscribed = false;
	}
    return bSubscribed;
}

bool SubscriberWrapper::disconnetFromBroker(){
    bool bDisconnect = false;
    try{
        // Disconnect
        if(debugLevel == 1){
          std::cout << "Disconnecting Subscriber..." << std::flush;
        }
  
        conntok = client.disconnect();
        conntok->wait_for_completion();
 
        if(debugLevel == 1){
            std::cout << "Subscriber successfully disconnected" << std::endl;
        } 
        bDisconnect = true;
    }
    catch (const mqtt::exception& exc) {
		std::cerr << "DisconnectToBroker => Error: " << exc.what() << std::endl;
		bDisconnect = false;
	}
    return bDisconnect;
}

void SubscriberWrapper::printAllStats(){
    calc.printCStats();
}

void SubscriberWrapper::printLatency(){
    calc.printLatency();
}