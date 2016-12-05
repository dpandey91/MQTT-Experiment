#include "subscriberWrapper.h"
#include "payload.h"
#include "common-utils.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#define DEBUG_2

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
    const int  QOS = pt.get<int>("qos");
    const long TIMEOUT = pt.get<long>("timeout");
    
    bool bRet = false;

    SubscriberWrapper subscriberWrapper(ADDRESS, QOS, TIMEOUT);
    bRet = subscriberWrapper.connectToBroker();
    if(!bRet){
        std::cout << "Failed to connect to broker" << std::endl;
        return 0;
    }
    else{
      std::cout << "Connected to broker successfully" << std::endl;
    }

    bRet = subscriberWrapper.subscribeData(TOPIC);
    if(!bRet){
        std::cout << "Failed to publish data to broker" << std::endl;
        //TODO: Ask what to do incase of failure
    }
    else{
#ifdef DEBUG_2        
        std::cout << "Subscribed to broker successfully" << std::endl;
#endif        
    }

    while (std::tolower(std::cin.get()) != 'q');
    
#ifdef DEBUG_2        
    std::cout << "SubscriberWrapper is successful" << std::endl;
#endif

    subscriberWrapper.printAllStats();
    bRet = subscriberWrapper.disconnetFromBroker();
    if(!bRet){
        std::cout << "Failed to disconnet from broker" << std::endl;
        return 0;
    }
    else{
#ifdef DEBUG_2                
      std::cout << "Disconnected from broker successfully" << std::endl;
#endif      
    }
    
    
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
