#include "deviceGroups_local.h"
#include "bitmessage_public.h"

int DGR_BeginWriting(bitMessage_t *msg, const char *groupName, unsigned short sequence, unsigned short flags) {
	if(MSG_WriteBytes(&msg,TASMOTA_DEVICEGROUPS_HEADER,strlen(TASMOTA_DEVICEGROUPS_HEADER))==0) {
		printf("DGR_BeginWriting: no space for header\n");
		return 1;
	}
	if(MSG_WriteString(&msg,groupName) <= 0) {
		printf("DGR_BeginWriting: no space for group name\n");
		return 1;
	}
	if(MSG_WriteU16(&msg,sequence) <= 0) {
		printf("DGR_BeginWriting: no space for sequence\n");
		return 1;
	}
	if(MSG_WriteU16(&msg,flags) <= 0) {
		printf("DGR_BeginWriting: no space for flags\n");
		return 1;
	}
	return 0;
}
void DGR_AppendPowerState(bitMessage_t *msg, int numChannels, int channelBits) {
	MSG_WriteByte(msg,DGR_ITEM_POWER);
	MSG_Write3Bytes(msg,channelBits);
	MSG_WriteByte(msg,numChannels);
}
void DGR_AppendColorRGBCW(bitMessage_t *msg, byte r, byte g, byte b, byte c, byte w) {
	MSG_WriteByte(msg,DGR_ITEM_LIGHT_CHANNELS);
	MSG_WriteByte(msg,5);
	MSG_WriteByte(msg,r);
	MSG_WriteByte(msg,g);
	MSG_WriteByte(msg,b);
	MSG_WriteByte(msg,c);
	MSG_WriteByte(msg,w);
}
void DGR_AppendDimmer(bitMessage_t *msg, byte dimmValue) {
	MSG_WriteByte(msg,DGR_ITEM_LIGHT_BRI);
	MSG_WriteByte(msg,dimmValue);
}
void DGR_Finish(bitMessage_t *msg) {
	MSG_WriteByte(msg,DGR_ITEM_EOL);

}
