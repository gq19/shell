#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <csignal>
#include "smsh.h"
#include "varlib.h"


#define DFL_PROMPT "gongqinandzhouhuiming>>"
void setup();
void fatal(const std::string& s1, const std::string& s2, int n);


int main()
{
    std::string cmdline, prompt;
    std::vector<std::string> arglist;
    int result;

    prompt = DFL_PROMPT ;
    setup();

    while ( (cmdline = next_cmd(prompt)) != "" ){
        arglist = splitline(cmdline);
        result = process(arglist);
        freelist(arglist);
    }
    return 0;
}

void setup()
{
    extern char **environ;

    VLenviron2table(environ);
    signal(SIGINT,  SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void fatal(const std::string& s1, const std::string& s2, int n)
{
    std::cerr << "Error: " << s1 << "," << s2 << std::endl;
    std::exit(n);
}
