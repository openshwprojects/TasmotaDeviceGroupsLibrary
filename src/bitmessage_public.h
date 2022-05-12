#include "shared.h"

typedef struct bitMessage_s {
	byte *data;
	int position;
	int totalSize;
} bitMessage_t;

// bitmessage_read.c
void MSG_BeginReading(bitMessage_t *msg, byte *data, int dataSize);
int MSG_ReadString(bitMessage_t *msg, char *out, int outBufferSize);
int MSG_SkipBytes(bitMessage_t *msg, int c);
int MSG_CheckAndSkip(bitMessage_t *msg, const char *s, int len);
unsigned short MSG_ReadU16(bitMessage_t *msg);
byte MSG_ReadByte(bitMessage_t *msg);
int MSG_EOF(bitMessage_t *msg);

// bitmessage_write.c