# Makefile for the mqttpp sample applications

PAHO_C_LIB ?= /home/fmp/static/opensrc/mqtt/paho/org.eclipse.paho.mqtt.c

all: async_pub async_sub

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

OBJECTS = publisherWrapper.o subscriberWrapper.o callbackWrapper.o payload.o calculateStats.o

async_sub: async_subscribe_main.o $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) async_subscribe_main.cpp -o async_sub $(OBJECTS) $(LDLIBS)
    
async_pub: async_publish_main.o $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) async_publish_main.cpp -o async_pub $(OBJECTS) $(LDLIBS)    

async_publish_main.o: async_publish_main.cpp payload.h publisherWrapper.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c async_publish_main.cpp
    
async_subscribe_main.o: async_subscribe_main.cpp payload.h subscriberWrapper.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c async_subscribe_main.cpp

publisherWrapper.o: publisherWrapper.cpp publisherWrapper.h callbackWrapper.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c publisherWrapper.cpp
    
subscriberWrapper.o: subscriberWrapper.cpp subscriberWrapper.h callbackWrapper.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c subscriberWrapper.cpp    

callbackWrapper.o: callbackWrapper.cpp callbackWrapper.h calculateStats.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c callbackWrapper.cpp  
    
calculateStats.o: calculateStats.cpp calculateStats.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c calculateStats.cpp        
    
payload.o: payload.cpp payload.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c payload.cpp    

.PHONY: clean
clean:
	rm -f *.o
	rm -f async_pub async_sub

.PHONY: distclean
distclean: clean


