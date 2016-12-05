/** By Dipika - Async Publisher **/

#include "publisherWrapper.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "common-utils.h"

PublisherWrapper::PublisherWrapper(const std::string& anAddress, int nQos, long nTimeout):
  clientId("AsyncPublisher"),
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
  
PublisherWrapper::~PublisherWrapper()
{}

bool PublisherWrapper::connectToBroker(){
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

bool PublisherWrapper::publishData(const std::string& topic, const std::string payloadData, int nSeqNo){
    bool bPublished = false;
    try {
        mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(payloadData);
        pubmsg->set_qos(qos);
        //Capturing here the timestamp to be more precise
        long usec = getCurrentMicrosecond();
        calc.addMessageSentTime(usec, nSeqNo);
        client.publish(topic, pubmsg)->wait_for_completion(timeout);
        bPublished = true;
    }
    catch (const mqtt::exception& exc) {
		std::cerr << "connectToBroker => Error: " << exc.what() << std::endl;
		bPublished = false;
	}
    return bPublished;
}

bool PublisherWrapper::disconnetFromBroker(){
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
		std::cerr << "connectToBroker => Error: " << exc.what() << std::endl;
		bDisconnect = false;
	}
    return bDisconnect;
}

void PublisherWrapper::printAllStats(){
    calc.printPStats();
}
