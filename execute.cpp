#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>
#include "varlib.h"

int execute(std::vector<std::string>& args)
{
    if (args.empty())
        return 0;

    // Check for the 'exit' command
    if (args[0] == "exit") {
        // You can specify an exit code here, e.g., 0 for normal termination
        int exit_code = 0;
        if (args.size() > 1) {
            try {
                exit_code = std::stoi(args[1]);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid exit code: " << args[1] << std::endl;
                return -1;
            }
        }
        std::exit(exit_code);
    }




    // Join the arguments into a single command string
    std::string command;
    for (const auto& arg : args) {
        if (!command.empty()) {
            command += " ";
        }
        command += arg;
    }

    // Set environment variables using VLtable2environ
    std::vector<std::string> environ = VLtable2environ();
    for (const auto& env : environ) {
        putenv(const_cast<char*>(env.c_str()));
    }

    // Execute the command using std::system
    int result = std::system(command.c_str());
    if (result == -1) {
        perror("cannot execute command");
        return -1;
    }

    // std::system returns 0 on success
    return result;
}
