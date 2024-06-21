#ifndef SMSH_H
#define SMSH_H

#include <cstddef>
#include<string>
#include<vector>
#include<memory>
#include<cstdlib>

const int YES = 1;
const int NO = 0;
std::string next_cmd(std::string& prompt,std::istream& input = std::cin);
std::vector<std::string> splitline(const std::string& line);
void freelist(std::vector<std::string>& list);
void*  emalloc(std::size_t size);
void* erealloc(void *ptr, std::size_t size);
int execute(std::vector<std::string>& args);
void fatal(const std::string& s1, const std::string& s2, int n);
int process(std::vector<std::string>& args);
#endif // SMSH_H
