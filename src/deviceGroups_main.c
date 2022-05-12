#include "deviceGroups_local.h"
#include "bitmessage_public.h"

int DGR_Parse(const byte *data, int len) {
	bitMessage_t msg;
	char groupName[32];
	int sequence, flags, type;
	int bGotEOL = 0;
	int relayFlags;
	byte vals;

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
		if(type == DGR_ITEM_EOL) {
			bGotEOL = 1;
		} else if(type < DGR_ITEM_MAX_8BIT) {
			MSG_SkipBytes(&msg,1);
		} else if(type < DGR_ITEM_MAX_16BIT) {
			MSG_SkipBytes(&msg,2);
		} else if(type < DGR_ITEM_MAX_32BIT) {
			if(type == DGR_ITEM_POWER) {

				relayFlags = MSG_Read3Bytes(&msg);
				vals = MSG_ReadByte(&msg);

				printf("Power event - %i - %i\n",relayFlags,vals);
			} else {
				MSG_SkipBytes(&msg,4);
			}
		} else if(type < DGR_ITEM_MAX_STRING) {
			byte sLen = MSG_ReadByte(&msg);
			MSG_SkipBytes(&msg,sLen);
		} else if(type == DGR_ITEM_LIGHT_CHANNELS) {
			byte sLen = MSG_ReadByte(&msg);
			MSG_SkipBytes(&msg,sLen);
		} else {
			byte sLen = MSG_ReadByte(&msg);
			MSG_SkipBytes(&msg,sLen);
		}
		if(bGotEOL) {
			break;
		}
	}


	return 0;
}