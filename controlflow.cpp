#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include"smsh.h"

enum class States { NEUTRAL, WANT_THEN, THEN_BLOCK };
enum class Results { SUCCESS, FAIL };

static States if_state = States::NEUTRAL;
static Results if_result = Results::SUCCESS;
static int last_stat = 0;

int syn_err(const std::string& msg);

bool ok_to_execute() {
    bool rv = true;  // default is positive

    switch (if_state) {
        case States::WANT_THEN:
            syn_err("then expected");
            rv = false;
            break;
        case States::THEN_BLOCK:
            rv = (if_result == Results::SUCCESS);
            break;
        case States::NEUTRAL:
        default:
            rv = true;
            break;
    }
    return rv;
}

bool is_control_command(const std::string& s) {
    return (s == "if" || s == "then" || s == "fi");
}

int do_control_command(std::vector<std::string>& args) {
    std::string cmd = args[0];
    int rv = -1;

    if (cmd == "if") {
        if (if_state != States::NEUTRAL)
            rv = syn_err("if unexpected");
        else {
            last_stat = process(args);  // 假设 process 函数也已被修改成C++风格
            if_result = (last_stat == 0 ? Results::SUCCESS : Results::FAIL);
            if_state = States::WANT_THEN;
            rv = 0;
        }
    } else if (cmd == "then") {
        if (if_state != States::WANT_THEN)
            rv = syn_err("then unexpected");
        else {
            if_state = States::THEN_BLOCK;
            rv = 0;
        }
    } else if (cmd == "fi") {
        if (if_state != States::THEN_BLOCK)
            rv = syn_err("fi unexpected");
        else {
            if_state = States::NEUTRAL;
            rv = 0;
        }
    } else {
        throw std::runtime_error("internal error processing: " + cmd);
    }

    return rv;
}

int syn_err(const std::string& msg) {
    if_state = States::NEUTRAL;
    std::cerr << "syntax error: " << msg << std::endl;
    return -1;
}
