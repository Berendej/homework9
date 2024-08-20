#include <unistd.h> /* for getopt */
#include "parser.h"

bool get_params(int c, char *args[])
{
    bool param_ok = false;
    char *cval;
    int n = getopt(c, args, "n:");
    if ('n' == n )
    {
        param_ok = bulker_c::set_n(std::stoi(optarg));
    }
    if (not param_ok)
    {
        bulker_c::usage();
        return false;
    }
    return true;
}

int main(int c, char *args[])
{
    if (not get_params(c, args))
    {
        return -1;
    }
    if ( not bulker_c::get_instance().init_async_handlers() )
    {
        return -1;
    }
    yyparse();
    bulker_c::get_instance().deinit_async_handlers();
    return 0;
}