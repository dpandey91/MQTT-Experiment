/** By Dipika - Async Publisher **/

#include "publisherWrapper.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

PublisherWrapper::PublisherWrapper(const std::string& anAddress, int nQos, long nTimeout):
  clientId("AsyncPublisher"),
  address(anAddress),
  qos(nQos),
  timeout(nTimeout),
  client(address, clientId),
  listener(),
  conntok(NULL),
  //pubtok(),
  cb()
{
 // callback cb;
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

/*bool PublisherWrapper::publishData(const std::string& topic, const void* payload, size_t payloadLen){
    bool bPublished = false;
    try {
        std::cout << "Sending next message..." << std::flush;
        mqtt::idelivery_token_ptr pubtok;
        mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(payload, payloadLen);
        pubtok = client.publish(topic, pubmsg, nullptr, listener);
        pubtok->wait_for_completion();
        std::cout << "OK" << std::endl;
        bPublished = true;
    }
    catch (const mqtt::exception& exc) {
		std::cerr << "connectToBroker => Error: " << exc.what() << std::endl;
		bPublished = false;
	}
    return bPublished;
}*/

bool PublisherWrapper::publishData(const std::string& topic, const std::string payloadData){
    bool bPublished = false;
    try {
        std::cout << "Sending next message..." << std::flush;

        mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(payloadData);
	pubmsg->set_qos(qos);
	client.publish(topic, pubmsg)->wait_for_completion(timeout);
	std::cout << "OK" << std::endl;
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
