# Makefile for the mqttpp sample applications

PAHO_C_LIB ?= /home/fmp/static/opensrc/mqtt/paho/org.eclipse.paho.mqtt.c

all: async_pub

CXXFLAGS += -Wall -std=c++0x
CPPFLAGS += -I.. -I$(PAHO_C_LIB)/src -I/home/dipika/Desktop/MQTT/mqtt-exp/mqtt-scripts/paho-eclipse/paho.mqtt.cpp/src/samples/sample_pub

ifdef DEBUG
  CPPFLAGS += -DDEBUG
  CXXFLAGS += -g -O0
else
  CPPFLAGS += -D_NDEBUG
  CXXFLAGS += -O2
endif

LDLIBS += -L../lib -L$(PAHO_C_LIB)/src/linux_ia64 -lmqttpp -lpaho-mqtt3a #-lmqttv3a

OBJECTS = publisherWrapper.o callbackWrapper.o payload.o

async_pub: async_publish_main.o $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) async_publish_main.cpp -o async_pub $(OBJECTS) $(LDLIBS)

async_publish_main.o: async_publish_main.cpp payload.h publisherWrapper.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c async_publish_main.cpp

publisherWrapper.o: publisherWrapper.cpp publisherWrapper.h callbackWrapper.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c publisherWrapper.cpp

callbackWrapper.o: callbackWrapper.cpp callbackWrapper.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c callbackWrapper.cpp  
    
payload.o: payload.cpp payload.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c payload.cpp    

.PHONY: clean
clean:
	rm -f *.o
	rm -f async_pub

.PHONY: distclean
distclean: clean


