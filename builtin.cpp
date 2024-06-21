#include <iostream>
#include <cstring>
#include <cctype>
#include "smsh.h"
#include "varlib.h"

int assign(std::string &);
bool okname(const std::string &);

int builtin_command(std::vector<std::string>& args, int& resultp)
{
    int rv = 0;

    if (args[0] == "set") {    // 'set' command?
        VLlist();
        resultp = 0;
        rv = 1;
    }
    else if (args[0].find('=') != std::string::npos) {   // assignment cmd
        resultp = assign(args[0]);
        if (resultp != -1)    // x-y=123 not ok
            rv = 1;
    }
    else if (args[0] == "export") {
        if (args.size() > 1 && okname(args[1]))
            resultp = VLexport(args[1].c_str());
        else
            resultp = 1;
        rv = 1;
    }
    return rv;
}

int assign(std::string &str)
{
    size_t pos = str.find('=');
    if (pos == std::string::npos)
        return -1;

    std::string name = str.substr(0, pos);
    std::string value = str.substr(pos + 1);

    int rv = (okname(name) ? VLstore(name.c_str(), value.c_str()) : -1);
    return rv;
}

bool okname(const std::string &str)
{
    if (str.empty())
        return false;

    for (size_t i = 0; i < str.length(); ++i) {
        if ((std::isdigit(str[i]) && i == 0) || !(std::isalnum(str[i]) || str[i] == '_'))
            return false;
    }
    return true;
}
