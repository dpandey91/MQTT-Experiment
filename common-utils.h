#ifndef WRAPPER_COMMON_H
#define WRAPPER_COMMON_H

//Time
#include <sys/time.h>
#include <time.h>

inline long getMicroseconds(struct timeval *t) {
  return (t->tv_sec) * 1000000 + (t->tv_usec);
}

inline long getCurrentMicrosecond(){
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    long usec = getMicroseconds(&currentTime);
    return usec;
}

#endif //WRAPPER_COMMON_H
