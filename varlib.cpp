#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#define MAXVARS 200

struct var {
    std::string str;    // name=val string
    bool global;        // a boolean
};

static var tab[MAXVARS];  // the table

static std::string new_string(const std::string& name, const std::string& val);
static var* find_item(const std::string& name, int first_blank);

int VLstore(const std::string& name, const std::string& val) {
    var* itemp;
    std::string s;
    int rv = 1;

    // find spot to put it and make new string
    if ((itemp = find_item(name, 1)) != nullptr && !(s = new_string(name, val)).empty()) {
        if (!itemp->str.empty())   // has a val?
            itemp->str.clear();    // y: remove it
        itemp->str = s;
        rv = 0;  // ok!
    }
    return rv;
}

std::string new_string(const std::string& name, const std::string& val) {
    return name + "=" + val;
}

std::string VLlookup(const std::string& name) {
    var* itemp;

    if ((itemp = find_item(name, 0)) != nullptr)
        return itemp->str.substr(name.length() + 1); // return value part
    return "";
}

int VLexport(const std::string& name) {
    var* itemp;
    int rv = 1;

    if ((itemp = find_item(name, 0)) != nullptr) {
        itemp->global = true;
        rv = 0;
    } else if (VLstore(name, "") == 1) {
        rv = VLexport(name);
    }
    return rv;
}

static var* find_item(const std::string& name, int first_blank) {
    for (int i = 0; i < MAXVARS && !tab[i].str.empty(); ++i) {
        std::string& s = tab[i].str;
        if (s.substr(0, name.length()) == name && s[name.length()] == '=')
            return &tab[i];
    }
    if (first_blank < MAXVARS && first_blank)
        return &tab[first_blank];
    return nullptr;
}

void VLlist() {
    for (int i = 0; i < MAXVARS && !tab[i].str.empty(); ++i) {
        if (tab[i].global)
            std::cout << "  * " << tab[i].str << std::endl;
        else
            std::cout << "    " << tab[i].str << std::endl;
    }
}

int VLenviron2table(char* env[]) {
    int i;
    std::string newstring;

    for (i = 0; env[i] != nullptr; ++i) {
        if (i == MAXVARS)
            return 0;
        newstring = env[i];
        tab[i].str = newstring;
        tab[i].global = true;
    }
    while (i < MAXVARS) {   // I know we don't need this
        tab[i].str.clear(); // static globals are cleared
        tab[i++].global = false;
    }
    return 1;
}

std::vector<std::string> VLtable2environ() {
    std::vector<std::string> envtab;

    for (int i = 0; i < MAXVARS && !tab[i].str.empty(); ++i) {
        if (tab[i].global)
            envtab.push_back(tab[i].str);
    }
    return envtab;
}
