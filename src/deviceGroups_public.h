
#include "shared.h"


typedef struct dgrCallbacks_s {
	void (*processPower)(int relayStates, byte relaysCount);
	// they are both sent together by Tasmota devices
	void (*processBrightnessPowerOn)(byte brightness);
	void (*processLightBrightness)(byte brightness);

} dgrCallbacks_t;


typedef struct dgrDevice_s {
	char groupName[32];
	u32 devGroupShare_In;
	u32 devGroupShare_Out;
	dgrCallbacks_t cbs;
} dgrDevice_t;

int DGR_Parse(const byte *data, int len, dgrDevice_t *dev);

int DGR_Quick_FormatPowerState(byte *buffer, int maxSize, const char *groupName, int sequence, int flags, int channels, int numChannels);
int DGR_Quick_FormatBrightness(byte *buffer, int maxSize, const char *groupName, int sequence, int flags, byte brightness);



