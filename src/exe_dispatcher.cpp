#include "exe_dispatcher.h"

int exe_dispatcher_c::start()
{
    if (not m_console_executor.is_working())
    {
        if (m_console_executor.start())
        {
            return m_console_executor.get_handle();
        }
        return -1;
    }
    if (not m_file_executor1.is_working())
    {
        if (m_file_executor1.start())
        {
            return m_file_executor1.get_handle();
        }
        return -1;
    }
    if (not m_file_executor2.is_working())
    {
        if (m_file_executor2.start())
        {
            return m_file_executor2.get_handle();
        }
        return -1;
    }
    // failed
    return -1; 
}

void exe_dispatcher_c::receive(const cmd_vector_t &commands)
{
    if ( m_console_executor.is_working() )
    {
        m_console_executor.receive_command(commands);
    }
    if (m_file_executor1.is_working() or
        m_file_executor2.is_working() )
    {
        file_executor_c::receive_command(commands);
    }
}

void exe_dispatcher_c::finish(int cmd_handle)
{
    if ( cmd_handle == m_console_executor.get_handle() )
    {
        m_console_executor.finish();
        return;
    }
    if ( cmd_handle == m_file_executor1.get_handle() )
    {
        m_file_executor1.finish();
        return;
    }
    if ( cmd_handle == m_file_executor2.get_handle() )
    {
        m_file_executor2.finish();
        return;
    }
}
