#include "deviceGroups_local.h"
#include "bitmessage_public.h"

int DGR_Parse(const byte *data, int len) {
	bitMessage_t msg;
	char groupName[32];
	int sequence, flags, type;
	int bGotEOL = 0;
	int relayFlags,i;
	byte vals;
	byte relaysCnt;

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
	printf("DGR_Parse: seq %i, flags %i\n",sequence, flags);
	while(MSG_EOF(&msg)==0) {
		type = MSG_ReadByte(&msg);
		printf("Next section - %i\n",type);
		if(type == DGR_ITEM_EOL) {
			bGotEOL = 1;
		} else if(type < DGR_ITEM_MAX_8BIT) {
			vals = MSG_ReadByte(&msg);
			if(type == DGR_ITEM_BRI_POWER_ON) {
				printf("DGR_ITEM_BRI_POWER_ON: %i\n",vals);
			} else if(type == DGR_ITEM_LIGHT_BRI) {
				printf("DGR_ITEM_LIGHT_BRI: %i\n",vals);
			} else {

			}
		} else if(type < DGR_ITEM_MAX_16BIT) {
			MSG_SkipBytes(&msg,2);
		} else if(type < DGR_ITEM_MAX_32BIT) {
			if(type == DGR_ITEM_POWER) {
				int total = 0;

				relayFlags = MSG_Read3Bytes(&msg);
				relaysCnt = MSG_ReadByte(&msg);

				printf("Power event - values %i, numChannels %i, chans=",relayFlags,relaysCnt);
				for(i = 0; i < relaysCnt; i++) {
					if(BIT_CHECK(relayFlags,i)) {
						printf("[ON]");
					} else {
						printf("[OFF]");
					}
				}
				printf("\n");
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