/*
 * header for varlib.c package
 */

#ifndef VARLIB_H
#define VARLIB_H

#include <vector>
#include <string>

int VLenviron2table(char **);
int VLexport(const std::string&);
std::string VLlookup(const std::string&);
void VLlist();
int VLstore(const std::string&, const std::string&);
std::vector<std::string> VLtable2environ();

#endif // VARLIB_H
