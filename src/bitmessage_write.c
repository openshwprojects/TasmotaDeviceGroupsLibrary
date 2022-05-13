#include "bitmessage_public.h"

int MSG_WriteBytes(bitMessage_t *msg, void *p, int numBytes) {
	if(msg->position + numBytes >= msg->totalSize)
		return 0;
	memcpy(msg->data + msg->position,p,numBytes);
	msg->position += numBytes;
	return numBytes;
}
int MSG_WriteString(bitMessage_t *msg, const char *s) {
	return MSG_WriteBytes(msg,s,strlen(s)+1);
}
int MSG_WriteU16(bitMessage_t *msg, unsigned short s) {
	return MSG_WriteBytes(msg,&s, sizeof(s));
}
int MSG_WriteByte(bitMessage_t *msg, byte s) {
	return MSG_WriteBytes(msg,&s, sizeof(s));
}

int MSG_Write3Bytes(bitMessage_t *msg, int s) {
	return MSG_WriteBytes(msg,&s, 3);
}
