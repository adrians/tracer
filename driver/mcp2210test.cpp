/**
 *    Copyright 2012, Kerry D. Wong
 * 
 *      http://www.kerrywong.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "mcp2210.h"

using namespace std;

void initTracer(hid_device* handle) {
    ChipSettingsDef chipDef;

    //set GPIO pins to be CS
    chipDef = GetChipSettings(handle);

    for (int i = 0; i < 9; i++) {
        if (i == 3) {
        	chipDef.GP[i].PinDesignation = GP_PIN_DESIGNATION_DEDICATED;
        	chipDef.GP[i].GPIODirection = GPIO_DIRECTION_OUTPUT;
        	chipDef.GP[i].GPIOOutput = 1;
        } else {
		chipDef.GP[i].PinDesignation = GP_PIN_DESIGNATION_CS;
        	chipDef.GP[i].GPIODirection = GPIO_DIRECTION_OUTPUT;
        	chipDef.GP[i].GPIOOutput = 1;
	}
    }

    int r = SetChipSettings(handle, chipDef);
    if (r != 0) {
        printf("Error setting SPI parameters.\n");
        return;
    }
}

void SetMCP4921(hid_device* handle, uint16_t input) {
    //configure SPI
    SPITransferSettingsDef def;
    def = GetSPITransferSettings(handle);

    //chip select is GP0
    def.ActiveChipSelectValue = 0xfffe;
    def.IdleChipSelectValue = 0xffff;
    def.BitRate = 50000l;
    def.BytesPerSPITransfer = 2;

    int r = SetSPITransferSettings(handle, def);

    if (r != 0) {
        printf("Error setting SPI parameters.\n");
        return;
    }
    
    byte spiCmdBuffer[2];
    spiCmdBuffer[0] = (0x30) | ((input >> 8) & 0x0F);
    spiCmdBuffer[1] = (input & 0xFF);
    SPIDataTransferStatusDef def1 = SPISendReceive(handle, spiCmdBuffer, 2);
}

uint16_t GetMCP3204(hid_device* handle, uint8_t channel) {
    //configure SPI
    SPITransferSettingsDef def;
    def = GetSPITransferSettings(handle);

    //chip select is GP0
    def.ActiveChipSelectValue = 0xfffd;
    def.IdleChipSelectValue = 0xffff;
    def.BitRate = 50000l;
    def.BytesPerSPITransfer = 3;

    int r = SetSPITransferSettings(handle, def);

    if (r != 0) {
        printf("Error setting SPI parameters.\n");
        return 0;
    }
    
    byte spiCmdBuffer[3];
    spiCmdBuffer[0] = (1<<6) | (1<<5) | (channel << 2);
    spiCmdBuffer[1] = 0x00;
    spiCmdBuffer[2] = 0x00;
    SPIDataTransferStatusDef def1 = SPISendReceive(handle, spiCmdBuffer, 2);

    return def1.DataReceived[1]*16 + (def1.DataReceived[0]/16);
}

int main(int argc, char** argv) {
    hid_device *handle;
    handle = InitMCP2210();
    if (handle == 0) {
        printf("ERROR opening device. Try using sudo.\n");
        exit(-1);
    }

    initTracer(handle);
    printf("{\"data\": [\n");
    for (int i = 0; i < 4000; i = i+10){
        SetMCP4921(handle, i);
	uint16_t dut = GetMCP3204(handle, 2);
	uint16_t supply = GetMCP3204(handle, 3);

	if(i != 0){
		printf(",");
	}
	printf("[%d.%03d, %d.%03d]\n",
			dut/1000,
			dut%1000,
			((supply - dut) >= 0) ? ((supply - dut)*1000/50)/1000 : 0,
			((supply - dut) >= 0) ? (((supply - dut)*1000/50)%1000) : 0
	);
    }
    SetMCP4921(handle, 0);
    printf("]}\n");
    ReleaseMCP2210(handle);

    return 0;
}
