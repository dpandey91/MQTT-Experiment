/** By Dipika - Async Publisher **/

#include "publisherWrapper.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "common-utils.h"

PublisherWrapper::PublisherWrapper(int nDebugLevel, const std::string& anAddress, int nQos, long nTimeout, bool bMsgWithTs):
  debugLevel(nDebugLevel),
  clientId("AsyncPublisher"),
  address(anAddress),
  qos(nQos),
  timeout(nTimeout),
  client(address, clientId),
  listener(),
  conntok(NULL),
  calc(),
  msgWithTs(bMsgWithTs),
  cb(debugLevel, msgWithTs, &calc)
{
  client.set_callback(cb);
}
  
PublisherWrapper::~PublisherWrapper()
{}

bool PublisherWrapper::connectToBroker(){
    bool bConnect = false;
    try {
		conntok = client.connect();
        if(debugLevel == 1){
          std::cout << "Waiting for the connection for publisher..." << std::flush;    
        }
		
        conntok->wait_for_completion();
        if(debugLevel == 1){
          std::cout << "Connection completed" << std::endl;
        }
        bConnect = true;
    }
    catch (const mqtt::exception& exc) {
		std::cerr << "connectToBroker => Error: " << exc.what() << std::endl;
		bConnect = false;
	}
    return bConnect;
}

bool PublisherWrapper::publishData(const std::string& topic, const std::string sendMsg, int nSeqNo, int timeoutPub){
    bool bPublished = false;
    try {
        mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(sendMsg);
        pubmsg->set_qos(qos);
        
        if(timeoutPub == -1) timeoutPub = timeout;
        
        if(!msgWithTs){
          //Capturing here the timestamp to be more precise when message is sent without ts
          long usec = getCurrentMicrosecond();
          calc.addMessageSentTime(usec, nSeqNo);
        }
        
        client.publish(topic, pubmsg)->wait_for_completion(timeoutPub);
        bPublished = true;
    }
    catch (const mqtt::exception& exc) {
		std::cerr << "Published Data => Error: " << exc.get_reason_code() << std::endl;
		bPublished = false;
	}
    return bPublished;
}

bool PublisherWrapper::disconnetFromBroker(){
    bool bDisconnect = false;
    try{
        // Disconnect
        if(debugLevel == 1){
          std::cout << "Disconnecting Publisher..." << std::flush;
        }
  
        conntok = client.disconnect();
        conntok->wait_for_completion();

        if(debugLevel == 1){
            std::cout << "Publisher successfully disconnected" << std::endl;
        }

        bDisconnect = true;
    }
    catch (const mqtt::exception& exc) {
		std::cerr << "DisconnectToBroker => Error: " << exc.what() << std::endl;
		bDisconnect = false;
	}
    return bDisconnect;
}

//This function is used for printing all the calulate stats
void PublisherWrapper::printAllStats(){
    calc.printPStats();
}
