#include "bitmessage_public.h"



void MSG_BeginReading(bitMessage_t *msg, byte *data, int dataSize) {
	msg->position = 0;
	msg->totalSize = dataSize;
	msg->data = data;
}

int MSG_SkipBytes(bitMessage_t *msg, int c) {
	if(msg->position + c > msg->totalSize)
		return 0;
	msg->position += c;
	return c;
}
int MSG_ReadString(bitMessage_t *msg, char *out, int outBufferSize) {
	int ret = 0;
	const char *start;

	start = (const char*)(msg->data + msg->position);
	while(1) {
		if(msg->position >= msg->totalSize) {
			return -1;
		}
		if(msg->data[msg->position] == 0) {
			msg->position++;
			break;
		}
		msg->position++;
	} 
	
	// TODO: safe.
	strcpy(out, start);
	return strlen(out);
}
unsigned short MSG_ReadU16(bitMessage_t *msg) {
	unsigned short ret;

	if(msg->position + sizeof(unsigned short) > msg->totalSize)
		return 0;

	ret = *(unsigned short*)(msg->data + msg->position);

	msg->position += sizeof(unsigned short);

	return ret;
}
byte MSG_ReadByte(bitMessage_t *msg) {
	byte ret;

	if(msg->position + sizeof(byte) > msg->totalSize)
		return 0;

	ret = *(byte*)(msg->data + msg->position);

	msg->position += sizeof(byte);

	return ret;
}
int MSG_CheckAndSkip(bitMessage_t *msg, const char *s, int len) {
	int i;
	if(msg->position + len > msg->totalSize)
		return 0;
	for(i = 0; i < len; i++) {
		if(msg->data[msg->position+i] != s[i])
			return 0;
	}	
	msg->position += len;
	return len;
}
int MSG_EOF(bitMessage_t *msg) {
	if(msg->position >= msg->totalSize)
		return 1;
	return 0;
}

