
#include "shared.h"


int DGR_Parse(const byte *data, int len);

int DGR_Quick_FormatPowerState(byte *buffer, int maxSize, const char *groupName, int sequence, int flags, int channels, int numChannels);
int DGR_Quick_FormatBrightness(byte *buffer, int maxSize, const char *groupName, int sequence, int flags, byte brightness);

