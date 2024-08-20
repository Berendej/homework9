#ifndef _BULKER_ASYNC_H_
#define _BULKER_ASYNC_H_

#include "cmd.h"

int connect();
void receive(int handle, const cmd_vector_t &commands);
int disconnect(int handle);

#endif