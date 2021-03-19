#include "ip_struct.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

int main()
{
    std::cout << "### ip_filter start" << std::endl;
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

        std::vector<IpStruct> ip_pool_1;
        std::vector<IpStruct> ip_pool_46_70;
        std::vector<IpStruct> ip_pool_46;
        for (const auto &ip : ip_pool)
        {
            // filter by first byte
            if (ip.getByte(0) == 1)
            {
                ip_pool_1.push_back(ip);
            }
            // filter by first and second bytes
            if (ip.getByte(0) == 46
                && ip.getByte(1) == 70)
            {
                ip_pool_46_70.push_back(ip);
            }
            // filter by any byte
            if (ip.getByte(0) == 46
                || ip.getByte(1) == 46
                || ip.getByte(2) == 46
                || ip.getByte(3) == 46)
            {
                ip_pool_46.push_back(ip);
            }
        }

        // output
        {
            for (const auto &ip : ip_pool)
            {
                ip.print();
            }
            for (const auto &ip : ip_pool_1)
            {
                ip.print();
            }
            for (const auto &ip : ip_pool_46_70)
            {
                ip.print();
            }
            for (const auto &ip : ip_pool_46)
            {
                ip.print();
            }
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
