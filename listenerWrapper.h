#ifndef ACTION_LISTENER_H
#define ACTION_LISTENER_H

#include <iostream>
#include "mqtt/async_client.h"

/**
 * A base action listener.
 */
class action_listener : public virtual mqtt::iaction_listener
{
protected:
	virtual void on_failure(const mqtt::itoken& tok) {
		std::cout << "\n\tListener: Failure on token: " 
			<< tok.get_message_id() << std::endl;
	}

	virtual void on_success(const mqtt::itoken& tok) {
		std::cout << "\n\tListener: Success on token: " 
			<< tok.get_message_id() << std::endl;
	}
};


/**
 * A derived action listener for publish events.
 */
class delivery_action_listener : public action_listener
{
	bool done_;

	virtual void on_failure(const mqtt::itoken& tok) {
		action_listener::on_failure(tok);
		done_ = true;
	}

	virtual void on_success(const mqtt::itoken& tok) {
		action_listener::on_success(tok);
		done_ = true;
	}

public:
	delivery_action_listener() : done_(false) {}
	bool is_done() const { return done_; }
};

#endif //ACTION_LISTENER_H