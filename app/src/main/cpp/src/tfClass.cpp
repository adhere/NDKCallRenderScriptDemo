#include "tfClass.h"
#include <android/log.h>
#include "ScriptC_mono.h"

#define  LOG_TAG_MY    "tfClass"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG_MY,__VA_ARGS__)

void launchMono(sp<Allocation> inputAlloc, sp<Allocation> outputAlloc, sp<RS> rs)
{
	LOGI("Step1");
	ScriptC_mono* sc = new ScriptC_mono(rs);
	LOGI("Step2");
	sc->forEach_root(inputAlloc, outputAlloc);
	LOGI("Step3");
	delete sc;
	LOGI("Step4");
}

void compute(const char * path, int X, int Y, void* inputPtr, void*& outputPtr)
{
    sp<RS> rs = new RS();
    rs->init(path);
    sp<const Element> e = Element::RGBA_8888(rs);

    sp<const Type> t = Type::create(rs, e, X, Y, 0);

    sp<Allocation> inputAlloc = Allocation::createTyped(rs, t, RS_ALLOCATION_MIPMAP_NONE,
                                                        RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT,
                                                        inputPtr);
    sp<Allocation> outputAlloc = Allocation::createTyped(rs, t, RS_ALLOCATION_MIPMAP_NONE,
                                                         RS_ALLOCATION_USAGE_SHARED | RS_ALLOCATION_USAGE_SCRIPT,
                                                         outputPtr);

    inputAlloc->copy2DRangeFrom(0, 0, X, Y, inputPtr);
    
    launchMono(inputAlloc, outputAlloc, rs);

    outputAlloc->copy2DRangeTo(0, 0, X, Y, outputPtr);
}