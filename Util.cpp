#include "Util.h"

std::string trim(const std::string& s)
{
    std::string result(s);
    size_t pos = result.find_first_not_of(" ");
    if (pos != std::string::npos)
        result.erase(0, pos);

    pos = result.find_last_not_of(" ");
    if (pos != std::string::npos)
        result.erase(pos + 1);

    return result;
}

vector<string> split(const string& str, char delimiter)
{
    vector<string> result;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter))
        result.push_back(trim(token));

    return result;
}
