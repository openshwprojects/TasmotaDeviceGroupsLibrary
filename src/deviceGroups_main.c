#include "deviceGroups_local.h"
#include "bitmessage_public.h"

int DGR_Parse(const byte *data, int len) {
	bitMessage_t msg;
	char groupName[32];
	int sequence, flags, type;
	int bGotEOL = 0;

	MSG_BeginReading(&msg,data,len);

	if(MSG_CheckAndSkip(&msg,TASMOTA_DEVICEGROUPS_HEADER,strlen(TASMOTA_DEVICEGROUPS_HEADER))==0) {
		printf("DGR_Parse: data chunk with len %i had bad header\n",len);
		return 1;
	}
	if(MSG_ReadString(&msg,groupName,sizeof(groupName)) <= 0) {
		printf("DGR_Parse: data chunk with len %i failed to read group name\n",len);
		return 1;
	}
	sequence = MSG_ReadU16(&msg);
	flags = MSG_ReadU16(&msg);
	while(MSG_EOF(&msg)==0) {
		type = MSG_ReadByte(&msg);
		switch(type){
			case DGR_ITEM_EOL:
				bGotEOL = 1;
				break;
		}
		if(bGotEOL) {
			break;
		}
	}


	return 0;
}