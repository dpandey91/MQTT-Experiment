#ifndef PUBLISHER_WRAPPER_H
#define PUBLISHER_WRAPPER_H

#include <string>
#include <thread>
#include "mqtt/async_client.h"
#include "listenerWrapper.h"
#include "callbackWrapper.h"
#include "calculateStats.h"

class PublisherWrapper{

public:
  PublisherWrapper(int nDebugLevel, const std::string& anAddress, int nQos, long nTimeout, bool bMsgWithTs);
  ~PublisherWrapper();
  
  bool connectToBroker();
  bool publishData(const std::string& topic, const std::string payloadData, int nSeqNo, int timeoutPub = -1);
  bool disconnetFromBroker();
  void printAllStats();
  
private:
  int debugLevel;
  std::string clientId;
  std::string address;
  int qos;
  long timeout;
  mqtt::async_client client;
  action_listener listener;
  mqtt::itoken_ptr conntok;
  CalculateStats calc;
  bool msgWithTs;
  CallbackWrapper cb;
};

#endif //PUBLISHER_WRAPPER_H
