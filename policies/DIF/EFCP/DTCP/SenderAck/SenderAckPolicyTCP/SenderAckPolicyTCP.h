//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef SENDERACKPOLICYTCP_H_
#define SENDERACKPOLICYTCP_H_

#include "DIF/EFCP/DTCP/SenderAck/SenderAckPolicyBase.h"

#include "DIF/EFCP/DTCP/ControlPDU_m.h"

#include "DIF/EFCP/DTP/DTPState.h"
#include "DIF/EFCP/DTCP/DTCPState.h"

class SenderAckPolicyTCP : public SenderAckPolicyBase {
public:
    uint32_t numOfAcked;

    SenderAckPolicyTCP();
    virtual ~SenderAckPolicyTCP();

    void ackPDU(DTPState* dtpState, DTCPState* dtcpState, unsigned int startSeqNum, unsigned int endSeqNum = 0);
    virtual bool run(DTPState* dtpState, DTCPState* dtcpState);
};

#endif /* SENDERACKPOLICYTCP_H_ */
