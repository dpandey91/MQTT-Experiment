#!/usr/bin/env python

import paho.mqtt.client as mqtt
import sys
import time
import random

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

try:
    msg_size = int(sys.argv[1])
    msgs_sec = int(sys.argv[2])
    msg_interval = 1.0/msgs_sec
except:
    print "usage: " + sys.argv[0] + " <message size> <messages per sec>"
    exit()

topic = "bg_load"
qos = 0 # no acks, just send and forget
data = "a"*msg_size
avg_loop_timeout = msg_interval/10

client = mqtt.Client()
client.on_connect = on_connect
client.connect("iot.eclipse.org", 1883, 60)

running = True
last_time = time.time()
bucket = 0.0
random.seed()

while running:
    # randomize the timeout +/- 25%, to avoid repeating patterns of double sends
    loop_timeout = random.uniform(avg_loop_timeout*3/4, avg_loop_timeout*5/4)
    client.loop(timeout=loop_timeout)

    current_time = time.time()
    bucket += current_time - last_time
    last_time = current_time

    if bucket >= msg_interval:
        # print 'publishing at timestamp %.6f, bucket size is %.6f' % (current_time, bucket)
        bucket -= msg_interval
        client.publish(topic, data)
