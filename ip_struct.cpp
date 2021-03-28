#include "ip_struct.h"

#include <iostream>

IpStruct::IpStruct(const std::vector<std::string> &v)
{
    if (v.size() != ipVersion)
    {
        return;
    }

    bytes.reserve(ipVersion);
    for (const auto &byte_str : v)
    {
        int byte = std::stoi(byte_str);
        if (byte < 0 || byte > 255)
        {
            bytes.clear();
            break;
        }
        bytes.push_back(byte);
    }
}

int IpStruct::getByte(int index) const
{
    if (index < 0 || index >= ipVersion)
    {
        return -1;
    }
    return bytes[index];
}

void IpStruct::print() const
{
    for (auto byte = bytes.cbegin(); byte != bytes.cend(); ++byte)
    {
        if (byte != bytes.cbegin())
        {
            std::cout << '.';
        }
        std::cout << *byte;
    }
    std::cout << std::endl;
}

bool IpStruct::isValid() const
{
    return (!bytes.empty());
}