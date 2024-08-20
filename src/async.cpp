#include <iostream>

#include "exe_dispatcher.h"
using std::cout;

int connect()
{
    return exe_dispatcher_c::get_instance().start();
}

void receive(int handle, const cmd_vector_t &commands)
{
    exe_dispatcher_c::get_instance().receive( commands );
}

void disconnect(int async_handle)
{
    exe_dispatcher_c::get_instance().finish(async_handle);
}
