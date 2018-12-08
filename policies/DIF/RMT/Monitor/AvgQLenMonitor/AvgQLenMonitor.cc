//
// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

// Author: Chris Willis (willisc@me.com)

#include "DIF/RMT/Monitor/AvgQLenMonitor/AvgQLenMonitor.h"

Define_Module(AvgQLenMonitor);

void AvgQLenMonitor::postQueueCreation(RMTQueue* queue)
{
    qAvgLengths[queue] = 0.0;
    qCounters[queue] = -1;
    qWeights[queue] = par("queueWeight").doubleValue();
}

void AvgQLenMonitor::preQueueRemoval(RMTQueue* queue)
{
    qAvgLengths.erase(queue);
    qWeights.erase(queue);
    qCounters.erase(queue);
}

// Assumed behavior: runs every time a PDU is put in the queue
void AvgQLenMonitor::postPDUInsertion(RMTQueue* queue)
{
    // first PDU inserted into the queue
    if (getPrevRegenCycleTimestamp() == 0 && getCurrentRegenCycleTimestamp()== 0)
    {
        // initialize timestamp and queue length for the current regeneration cycle
        setCurrentRegenCycleTimestamp(queue->getQTime());
        EV << "!!!INITIAL REGENERATION CYCLE STARTED AT " + getCurrentRegenCycleTimestamp().str() << endl;
        setCurrentRegenCycleQLen(queue->getLength());
        EV << "!!!CURRENT LENGTH OF QUEUE IS " + std::to_string(getCurrentRegenCycleQLen()) << endl;

        return;
    }

    // subsequent PDU insertion into queue
    // rotate variables between "previous" and "current"
    simtime_t prevTimestamp = getCurrentRegenCycleTimestamp();
    simtime_t currentTimestamp = queue->getQTime();
    double prevQLen = getCurrentRegenCycleQLen();
    double currentQLen = queue->getLength();

    setCurrentRegenCycleQLen(prevQLen + ((currentTimestamp.dbl() - prevTimestamp.dbl()) * prevQLen));
    EV << "$$$ TEST: " + std::to_string(getCurrentRegenCycleQLen()) << endl;
}

