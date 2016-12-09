#ifndef CALLBACK_WRAPPER_H
#define CALLBACK_WRAPPER_H

#include <iostream>
#include "mqtt/async_client.h"
#include "calculateStats.h"

/**
 * A callback class for use with the main MQTT client.
 */
class CallbackWrapper : public virtual mqtt::callback
{
public:

	CallbackWrapper(int nDebugLevel, bool bMsgWithTs);
    CallbackWrapper(int nDebugLevel, bool bMsgWithTs, CalculateStats* c);
	virtual void connection_lost(const std::string& cause);

	// We're not subscribed to anything, so this should never be called.
	virtual void message_arrived(const std::string& topic, mqtt::message_ptr msg);

	virtual void delivery_complete(mqtt::idelivery_token_ptr tok);
    
private:
    CalculateStats* calc;
    int debugLevel;
    bool msgWithTs;
    unsigned pSeqNo;
    unsigned cSeqNo;
};

#endif //CALLBACK_H
