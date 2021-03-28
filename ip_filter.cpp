#include "ip_struct.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

template<typename Iterator>
void ip_print_if(Iterator begin, Iterator end, std::function<bool(const IpStruct&)> func)
{
    for (auto iter = begin; iter != end; ++iter)
    {
        auto ip = static_cast<IpStruct>(*iter);
        if (func(ip))
        {
            ip.print();
        }
    }
}


int main()
{
    try
    {
        std::vector<IpStruct> ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            if (line.empty())
            {
                break;
            }
            std::vector<std::string> v = split(line, '\t');
            auto _v = split(v.at(0), '.');
            auto ip = IpStruct(_v);
            if (ip.isValid())
            {
                ip_pool.push_back(ip);
            }
        }

        // reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), [](IpStruct &first, IpStruct &second) -> bool
        {
            for (int index = 0; index < IpStruct::ipVersion; ++index)
            {
                int f_byte = first.getByte(index);
                int s_byte = second.getByte(index);
                if (f_byte == -1 
                    || s_byte == -1)
                {
                    return false;
                }
                if (f_byte == s_byte)
                {
                    continue;
                }
                else
                {
                    return f_byte > s_byte;
                }
            }
            return false;
        });

        // print sorted
        for (const auto &ip : ip_pool)
        {
            ip.print();
        }

        // filter by first byte
        ip_print_if(ip_pool.begin(), ip_pool.end(), [](const IpStruct &ip) -> bool
        {
            return ip.getByte(0) == 1;
        });


        // filter by first and second bytes
        ip_print_if(ip_pool.begin(), ip_pool.end(), [](const IpStruct &ip) -> bool
        {
            return ip.getByte(0) == 46 && ip.getByte(1) == 70;
        });

        // filter by any byte
        ip_print_if(ip_pool.begin(), ip_pool.end(), [](const IpStruct &ip) -> bool
        {
            return ip.getByte(0) == 46
                || ip.getByte(1) == 46
                || ip.getByte(2) == 46
                || ip.getByte(3) == 46;
        });
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
