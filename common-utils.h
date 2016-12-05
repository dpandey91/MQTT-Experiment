#ifndef WRAPPER_COMMON_H
#define WRAPPER_COMMON_H

//Time
#include <sys/time.h>
#include <time.h>

#include <limits>
#include <cmath>

inline long getMicroseconds(struct timeval *t) {
  return (t->tv_sec) * 1000000 + (t->tv_usec);
}

inline long getCurrentMicrosecond(){
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    long usec = getMicroseconds(&currentTime);
    return usec;
}

inline double getCurrentSecond(){
    return getCurrentMicrosecond()/1000000;
}

inline double getRandDouble(double min, double max) {
  return min + (rand() / (RAND_MAX + 1.0f)) * (max - min);
}

#endif //WRAPPER_COMMON_H
