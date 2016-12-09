#ifndef SUBSCRIBER_WRAPPER_H
#define SUBSCRIBER_WRAPPER_H

#include <string>
#include <thread>
#include "mqtt/async_client.h"
#include "listenerWrapper.h"
#include "callbackWrapper.h"
#include "calculateStats.h"

class SubscriberWrapper{

public:
  SubscriberWrapper(int nDebugLevel, const std::string& anAddress, int nQos, bool bMsgWithTs);
  ~SubscriberWrapper();
  
  bool connectToBroker();
  bool subscribeData(const std::string& topic);
  bool disconnetFromBroker();
  void printAllStats();
  void printLatency();
  
private:
  int debugLevel;
  std::string clientId;
  std::string address;
  int qos;
  mqtt::async_client client;
  action_listener listener;
  mqtt::itoken_ptr conntok;
  CalculateStats calc;
  bool msgWithTs;
  CallbackWrapper cb;
};

#endif //SUBSCRIBER_WRAPPER_H
