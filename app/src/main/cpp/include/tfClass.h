#ifndef __RSMONOWRAPPER_H__
#define __RSMONOWRAPPER_H__

#include "RenderScript.h"

using namespace android::RSC;

void compute(const char * path, int X, int Y, void* inputPtr, void*& outputPtr);

#endif