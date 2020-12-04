#pragma once
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <cstring>

#include <RSQuant/common.hpp>

namespace RSQ
{
class GFF3
{
  public:
    RSQ::MemberType column;
  public:
    GFF3(std::string line)
    {
        if(line.size() != 0)
        { 
            std::vector<std::string> vec;
            char* c_str = new char[line.size() + 1];
            char* save_ptr = nullptr;
            std::memcpy(c_str, line.c_str(), line.size()+1);
            char* split = strtok_r(c_str, "\t ", &save_ptr);
            while(split != nullptr)
            {
                std::cout << "split:"<< split << std::endl;
                vec.emplace_back(split);
                split = strtok_r(nullptr, "\t ", &save_ptr);
            }

            for(auto& elem : vec)
                std::cout << elem << std::endl;
            parseOneLineData<0>(vec);
        }
    }

    template <std::size_t N>
    const auto& getMember() const
    {
        return std::get<N>(this->column);
    }

    template <std::size_t N>
    void parseOneLineData(std::vector<std::string>& vec)
    {
        static_assert(N < 9 && N>=0);
        if constexpr( N==RSQ::MemberFields::ATTRIBUTES )
            std::get<N>(this->column) = vec[N];
        else
        {
            if constexpr( N==RSQ::MemberFields::SEQ_ID || 
                          N==RSQ::MemberFields::SOURCE || 
                          N==RSQ::MemberFields::FEATURE_TYPE ||
                          N==RSQ::MemberFields::SCORE
            )
                std::get<N>(this->column) = vec[N];
            else if constexpr( N==RSQ::MemberFields::FEATURE_START ||
                               N==RSQ::MemberFields::FEATURE_END
            )
                std::get<N>(this->column) = static_cast<RSQ::LocType>(stol(vec[N]));
            else if constexpr( N==RSQ::MemberFields::STRAND ||
                               N==RSQ::MemberFields::PHASE
            )
                std::get<N>(this->column) = vec[N][0];
            else
                throw("parseOneLineData fault.");
            parseOneLineData<N+1>(vec);
        }
    }

    template <std::size_t N>
    void printAllColumn()
    {
        static_assert(N<9 && N>=0);
        std::cout << std::get<N>(this->column) << std::endl;
        if constexpr(N != RSQ::MemberFields::ATTRIBUTES)
            printAllColumn<N+1>();
    }

    // template <std::size_t N>
    // void setMember(const std::tuple_element_t<N, RSQ::MemberType>& rhs)
    // {
    //     std::get<N>(this->column) = rhs;
    // }

    // template<std::size_t N=0, typename... Ts>
    // typename std::enable_if_t<N == sizeof...(Ts), void> 
    // parseLine(std::tuple<Ts...> tup, std::string line)
    // {
    //     std::cout << "END" << std::endl;
    //     return;
    // }

    // template<std::size_t N=0, typename... Ts>
    // typename std::enable_if_t<N < sizeof...(Ts), void> 
    // parseLine(std::tuple<Ts...> tup, std::string line)
    // {
    //     std::cout << N << std::endl;
        
    //     if(N==0 || N==1 || N==2 || N==std::tuple_size_v<decltype(this->column)>-1)
    //     {
    //         std::string tmp(line.substr(0, line.find(" ")));
    //         setMember(tmp);
    //     }
    //     // else if(N == 3 || N == 4)
    //     // {
    //     //     RSQ::LocType tmp = std::stol(line.substr(0, line.find(" ")));
    //     //     setMember(tmp);
    //     // }
    //     // std::get<N>(this->column) = std::stol(line.substr(0, line.find(" ")));
    //     // else if(N == 5)
    //     //     std::get<N>(this->column) = std::stod(line.substr(0, line.find(" ")));
    //     // else if(N == 6 || N == 7)
    //     //     std::get<N>(this->column) = line.substr(0, line.find(" ")).c_str();
    //     // else
    //     //     throw("gff3 should not exceed 9 column");
    //     if(line.find(" ") != std::string::npos)
    //         line = line.substr(line.find(" "));
    //     if(!line.empty())
    //         parseLine<N+1>(this->column, line.substr(line.find_first_not_of(std::string(" "))));
    // }
        


    // template<std::size_t N=0, typename... Ts>
    // constexpr void printAllColumn(std::tuple<Ts...> tup)
    // {
    //     if( N == sizeof...(Ts) )
    //         return;
    //     else
    //     {
    //         std::cout << std::get<N>(tup);
    //         printAllColumn<N+1>(tup);
    //     }
    // }
};
}