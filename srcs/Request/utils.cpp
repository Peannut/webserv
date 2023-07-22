#include "includes.hpp"

bool isUnreserved(const char & c)
{
    return ( \
        std::isalnum(c) || \
        c == '-' || \
        c == '.' || \
        c == '_' || \
        c == '~' \
    );
}
bool isReserved(const char & c)
{
    return ( \
        c == '?' || \
        c == '=' || \
        c == '&' || \
        c == ':' \
    );
}
bool isOWS(const char & c)
{
    return ( c == ' ' || c == 9 );
}
bool isHEXDIG(const char & c)
{
    return (\
        std::isdigit(c) || \
        c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || \
        c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F'
    );
}
// visible character
bool isVchar(const char & c)
{
    return ( c >= 32 && c <= 126 );
}
// any visible character except delimiter
bool isTchar(const char & c)
{
    return ( \
        isUnreserved(c) || \
        c == '!' || \
        c == '#' || \
        c == '$' || \
        c == '%' || \
        c == '&' || \
        c == '\'' || \
        c == '*' || \
        c == '+' || \
        c == '^' || \
        c == '`' || \
        c == '|' \
    );
}

bool isMethodChar(const char & c)
{
    return (
        c == 'G' || c == 'E' || c == 'T' || \
        c == 'P' || c == 'O' || c == 'S' || \
        c == 'D' || c == 'L' \
    );
}
bool isPathChar(const char & c)
{
    return (c == '/' || isUnreserved(c));
}
bool isQueryChar(const char & c)
{
    return (isUnreserved(c));
}

void toupperFieldKey(std::string & field_key)
{
    for (size_t len = field_key.size(), i = 0; i < len; ++i)
        field_key[i] = std::toupper(field_key[i]);
}
void trimFieldVal(std::string & field_val)
{
    std::string::iterator it = field_val.begin();
    while (!field_val.empty() && isOWS(*(field_val.end() - 1)))
        field_val.erase(field_val.end() - 1);
    while (!field_val.empty() && it != field_val.end() && isOWS(*it))
        ++it;
    if (!field_val.empty())
        field_val.erase(field_val.begin(), it);
}

bool isContentLengthValValid(const std::string & val)
{
    for (size_t sz = val.size(), i = 0; i < sz; ++i)
        if (!std::isdigit(val[i]))
            return false;
    return true;
}
bool isTransferEncodingValValid(const std::string & val)
{
    for (size_t sz = val.size(), i = 0; i < sz; ++i)
        if (!std::islower(val[i]))
            return false;
    return true;
}
size_t matching_location(const std::string & path, const std::string & location_path)
{
    size_t lenMatched = (size_t)0;
    size_t lenPath = path.length();
    size_t lenLocationPath = location_path.length();

    if (lenLocationPath < lenPath)
        return (size_t)0;

    while (lenMatched < lenPath && lenMatched < lenLocationPath)
    {
        if (path[lenMatched] != location_path[lenMatched])
            break;
        ++lenMatched;
    }
    
    return lenMatched;
}
