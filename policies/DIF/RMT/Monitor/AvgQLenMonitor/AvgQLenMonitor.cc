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

void AvgQLenMonitor::postPDUInsertion(RMTQueue* queue)
{
    // if queue length is 1, then there's no congestion so no need to start monitoring
    if (queue->getLength() == 1)
    {
        return;
    }

    // runs each time a PDU is inserted into the queue
    // first, rotate variables from "current" to "previous"
    double prevQLen = getCurrentRegenCycleAvgQLen();
    simtime_t prevTimestamp = getCurrentRegenCycleTimestamp();
    double currentQLen = queue->getLength();
    simtime_t currentTimestamp = queue->getQTime();

    // second, calculate current regeneration cycle queue length and record timestamp and current cycle's queue length
    setCurrentRegenCycleAvgQLen(currentQLen + ((currentTimestamp.dbl() - prevTimestamp.dbl()) * prevQLen));
    EV << "!!!PDU INSERTED INTO QUEUE. CURRENT LENGTH OF QUEUE IS " + std::to_string(getCurrentRegenCycleAvgQLen()) << endl;
    setCurrentRegenCycleTimestamp(currentTimestamp);
    EV << "!!!PDU INSERTED INTO QUEUE AT " + getCurrentRegenCycleTimestamp().str() << endl;
}

void AvgQLenMonitor::postPDURelease(RMTQueue* queue)
{
    EV << "!!!PDU RELEASED FROM QUEUE. CURRENT LENGTH OF QUEUE IS " + std::to_string(getCurrentRegenCycleAvgQLen()) << endl;
    // if queue length is 0 and current regeneration cycle's queue length is not 0, then there was
    // congestion and now it's gone so start a new regeneration cycle
    if (queue->getLength() == 0 && getCurrentRegenCycleAvgQLen() != 0)
    {
        setPrevRegenCycleAvgQLen(getCurrentRegenCycleAvgQLen());
        setCurrentRegenCycleAvgQLen(0);
        EV << "!!!STARTING NEW REGENERATION CYCLE STARTED AT " + queue->getQTime().str() << endl;
    }
}