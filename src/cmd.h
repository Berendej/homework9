#ifndef _BULK_CMD_H_
#define _BULK_CMD_H_

#include <string>
#include <vector>
#include <memory>
#include <list>

class cmd_c
{
    std::string m_val;
public:
    virtual void execute() = 0;
    cmd_c(const char *txt) : m_val(txt)
    {}
    std::string to_string()
    {
        return m_val;
    }
};
using sp_cmd_t = std::shared_ptr<cmd_c>;
using cmd_vector_t = std::vector<sp_cmd_t>;
using i_cmd_vector_t = cmd_vector_t::iterator;
using cmd_list_t = std::list<sp_cmd_t>;
using i_cmd_list_t = cmd_list_t::iterator;

class fake_cmd_c : public cmd_c
{
public:
    virtual void execute()
    {
    }

    fake_cmd_c(const char *txt) : cmd_c(txt)
    {}

    static sp_cmd_t build_cmd(const char  *txt)
    {
        sp_cmd_t sp_cmd( new fake_cmd_c(txt));
        return sp_cmd;
    }

};

#endif