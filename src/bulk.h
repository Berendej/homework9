#ifndef _BULK_H_
#define _BULK_H_

#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <fstream>
#include <ctime>
#include <iomanip>

#include "async.h"
#include "cmd.h"

class bulker_c
{
    static int N;
    cmd_vector_t m_commands;
    int         m_depth;
    int  m_console_handle;
    int  m_file1_handle;
    int  m_file2_handle;
    bulker_c() : m_depth(0)
                 , m_console_handle(-1)
                 , m_file1_handle(-1)
                 , m_file2_handle(-1)
    {
    }

public:
    // singleton pattern
    static bulker_c& get_instance()
    {
        static bulker_c instance;
        return instance;
    }

    static bool set_n(int n)
    {
        if ( n > 0 and n < 100 )
        {
            N = n;
            return true;
        }
        return false;
    }

    static void usage()
    {
        std::cout << "usage bulk -n 3\n";
    }

    void add(sp_cmd_t &sp_cmd)
    {
        m_commands.push_back(sp_cmd);
        if ( (0 == m_depth) and 
             (N == m_commands.size()) )
        {
            drop();
        }
    }

    void down()
    {
        if ( 0 == m_depth and m_commands.size() > 0 )
        {
            // drop anything we already have at top level
            drop();
        }
        m_depth++; 
    }

    void up()
    {
        m_depth--;
        if (0 == m_depth) 
        {
            drop();
        }
    }

    void drop()
    {
        if (0 != m_depth or m_commands.size() == 0 )
        {
            return;
        }
        receive(1, m_commands);
        m_commands.clear();
    }

    bool init_async_handlers()
    {
        m_console_handle = connect();
        m_file1_handle = connect();
        m_file2_handle = connect();
        return (     m_console_handle != -1 
                 and m_file1_handle != -1 
                 and m_file2_handle != -1 );
    }

    void deinit_async_handlers()
    {
        disconnect(m_console_handle);
        disconnect(m_file1_handle);
        disconnect(m_file2_handle);
    }

};

#endif /* _BULK_H_ */
