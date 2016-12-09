#include "publisherWrapper.h"
#include "payload.h"
#include "common-utils.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <sstream>
#include <string>

//export LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH

 int main(int argc, char* argv[]){

  try{
    
    if (argc < 2)    /* Test for correct number of arguments */
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
    const long nIter = pt.get<long>("noOfIterations");
    const int debugLevel = pt.get<int>("debug");
    bool bSendMsgWithTs = (pt.get<int>("sendMessageWithTs") == 1) ? true : false;
        
    long dataRate = 0.0;
    if(argc > 2)
        dataRate = atol(argv[2]);
    else
        dataRate = pt.get<long>("dataRate");
    
    double interval = 1.0/dataRate;
    
    const char messageData = pt.get<char>("data");
    const int messageSize = pt.get<int>("messageSize");
    std::string payloadData = std::basic_string<char>(messageSize, messageData);
    
    bool bRet = false;

    PublisherWrapper publishWrapper(debugLevel, ADDRESS, QOS, TIMEOUT, bSendMsgWithTs);
    bRet = publishWrapper.connectToBroker();
    if(!bRet){
        std::cout << "Failed to connect to broker" << std::endl;
        return 0;
    }
    else{
      if(debugLevel == 1){
        std::cout << "Connected to broker successfully" << std::endl;    
      }
    }
    
    double timeoutAvg = interval/10;
    if(debugLevel == 1){
        std::cout << "Timeout Avg bases on data rate : " << timeoutAvg << std::endl;
    }
    
    double currentTime = getCurrentSecond();
    double lastTokenTime = currentTime;
    double bucket = 0.0;
    int i = 0;

    std::string sendMsg = "";
    Payload payload;
    
    if(bSendMsgWithTs){
        payload.setTopic(TOPIC);
        payload.setData(payloadData);
    }

    while(i < nIter){
        
        currentTime = getCurrentSecond();
        bucket += currentTime - lastTokenTime;
        lastTokenTime = currentTime;
           
        if(bucket >= interval){
            bucket -= interval;
            
            if(bSendMsgWithTs){
                payload.setSeqNo(i);
                
                long usec1 = getCurrentMicrosecond();
                payload.setTimestamp(usec1);
                
                //This returns a json string containing data, ts and segNo
                sendMsg = payload.getString();
            }
            else{
                sendMsg = payloadData;
            }
            
            //Timeout avg interval is sent in ms as wait_for_completion call in publisher requires it in ms
            bRet = publishWrapper.publishData(TOPIC, sendMsg, i++, timeoutAvg*1000);
            if(!bRet){
                std::cout << "Failed to publish data to broker" << std::endl;
                //TODO: Ask what to do incase of failure
            }
            else{
                if(debugLevel == 1){
                  std::cout << "Published to broker successfully" << std::endl;
                }
            }    
        }
    }
    
    if(debugLevel == 1){
      std::cout << "PublisherWrapper is successful" << std::endl;
    }
    
    if(!bSendMsgWithTs){
        publishWrapper.printAllStats();
    }
    
    bRet = publishWrapper.disconnetFromBroker();
    if(!bRet){
        std::cout << "Failed to disconnet from broker" << std::endl;
        return 0;
    }
    else{
      if(debugLevel == 1){
        std::cout << "Disconnected from broker successfully" << std::endl;
      }
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
