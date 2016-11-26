#include "publisherWrapper.h"
#include "payload.h"
#include "common-utils.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

//export LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH

int main(int argc, char* argv[]){

  try{
    
    if (argc != 2)    /* Test for correct number of arguments */
    {
	std::cerr << "Usage: " << argv[0] <<" <Json configuration file>" << std::endl;
        exit(1);
    }

    boost::property_tree::ptree pt;
    boost::property_tree::read_json(argv[1], pt);
    
    const std::string ADDRESS = pt.get<std::string>("address");
    const std::string TOPIC = pt.get<std::string>("topic");
    //TODO: Handle reading data from input file if file name is specified
    const std::string payloadData = pt.get<std::string>("data");
    const int  QOS = pt.get<int>("qos");
    const long TIMEOUT = pt.get<long>("timeout");
    const long nIter = pt.get<long>("noOfIterations");
    const double iterDelay = pt.get<double>("iterationDelay");

    bool bRet = false;

    PublisherWrapper publishWrapper(ADDRESS, QOS, TIMEOUT);
    bRet = publishWrapper.connectToBroker();
    if(!bRet){
        std::cout << "Failed to connect to broker" << std::endl;
        return 0;
    }
    else{
      std::cout << "Connected to broker successfully" << std::endl;
    }

    //As now same data is published for nIter, setting data and its topic before iterations, else handle multiple parts of data to be published
    Payload payload;
    payload.setTopic(TOPIC);
    payload.setData(payloadData);
    
    struct timespec reqDelay, remDelay;
    for(int i = 0; i < nIter; i++){
	payload.setSeqNo(i);
	long usec1 = getCurrentMicrosecond();
	payload.setTimestamp(usec1);
	std::string payloadData = payload.getString();

	bRet = publishWrapper.publishData(TOPIC, payloadData);
	if(!bRet){
		std::cout << "Failed to publish data to broker" << std::endl;
		//TODO: Ask what to do incase of failure
	}
	else{
		std::cout << "Published to broker successfully" << std::endl;
	}
	if(iterDelay > 0){
		reqDelay.tv_sec = iterDelay;
    		remDelay.tv_nsec = 0;
		nanosleep((const struct timespec*)&reqDelay, &remDelay);
	}
    }
    
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
  catch (const mqtt::exception& exc) {
    std::cerr << "Error: " << exc.what() << std::endl;
    return 0;
  }
  catch (std::exception const& e)
  {
    std::cerr << e.what() << std::endl;
  }
  catch (...) {
    std::cout << "Oops, someone threw an exception!" << std::endl;
    return 0;
  }
}
