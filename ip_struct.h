#ifndef IP_STRUCT_H
#define IP_STRUCT_H

#include <vector>
#include <string>

class IpStruct
{
    std::vector<int> bytes;

public:
    static constexpr int ipVersion = 4;

    explicit IpStruct(const std::vector<std::string> &v);
    int getByte(int index) const;
    void print() const;
    bool isValid() const;
};

#endif //IP_STRUCT_H