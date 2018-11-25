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

#ifndef DTCPECNSLOWDOWNPOLICYTCP_H_
#define DTCPECNSLOWDOWNPOLICYTCP_H_

#include "DIF/EFCP/DTCP/ECNSlowDown/ECNSlowDownPolicyBase.h"
#include "DIF/EFCP/DTCP/TxControl/TxControlPolicyTCPTahoe/TxControlPolicyTCPTahoe.h"

class DTCPECNSlowDownPolicyTCP: public ECNSlowDownPolicyBase {
public:
    virtual ~DTCPECNSlowDownPolicyTCP();
    DTCPECNSlowDownPolicyTCP();

    virtual bool run(DTPState* dtpState, DTCPState* dtcpState);

protected:
    TxControlPolicyTCPTahoe *tcpPolicy;
    using ECNSlowDownPolicyBase::initialize;
    virtual void initialize(int step);
};

#endif /* DTCPECNSLOWDOWNPOLICYTCP_H_ */
