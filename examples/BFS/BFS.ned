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

package rina.examples.BFS;

import ned.DatarateChannel;
import rina.src.CS.Host1AP;
import rina.src.CS.InteriorRouter2Int;

// I think these are the things I need to modify for BFS integration
// import rina.src.DIF.EFCP.???
// import rina.src.DIF.RA.???
// import rina.src.DIF.RMT.???

//
// TODO Auto-generated network
//
network BFS
{
    @display("bgb=377,232");
    submodules:
        hostA: Host1AP {
            @display("p=48,102");
        }
        hostB: Host1AP {
            @display("p=318,102");
        }
        switch: InteriorRouter2Int {
            @display("p=186,102");
        }
    connections:
        hostA.medium <--> DatarateChannel { datarate = 100Mbps; delay = 100us; ber = 0; } <--> switch.medium[0];
        switch.medium[0] <--> DatarateChannel { datarate = 100Mbps; delay = 100us; ber = 0; } <--> hostB.medium;
}
