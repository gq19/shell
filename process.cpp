#include <iostream>
#include "smsh.h"

bool is_control_command(const std::string&);
int do_control_command(std::vector<std::string>& args);
bool ok_to_execute();
bool builtin_command(std::vector<std::string>& args, int& rv);

int process(std::vector<std::string>& args)
{
    int rv = 0;

    if (args.empty())
        rv = 0;
    else if (is_control_command(args[0]))
        rv = do_control_command(args);
    else if (ok_to_execute())
        if (!builtin_command(args,rv))
            rv = execute(args);
    return rv;
}
