#ifndef CALLBACK_WRAPPER_H
#define CALLBACK_WRAPPER_H

#include <iostream>
#include "mqtt/async_client.h"

/**
 * A callback class for use with the main MQTT client.
 */
class CallbackWrapper : public virtual mqtt::callback
{
public:

	CallbackWrapper();
	virtual void connection_lost(const std::string& cause);

	// We're not subscribed to anything, so this should never be called.
	virtual void message_arrived(const std::string& topic, mqtt::message_ptr msg);

	virtual void delivery_complete(mqtt::idelivery_token_ptr tok);
};

#endif //CALLBACK_H
