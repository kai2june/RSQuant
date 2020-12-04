#pragma once
#include <tuple>
#include <unordered_map>
#include <string>
#include <vector>

namespace RSQ
{
    using LocType = uint32_t;
    using MemberType = std::tuple<
        std::string
      , std::string
      , std::string 
      , LocType
      , LocType
      , std::string
      , char
      , char
      , std::string
    >;
    using TranscriptAminoAcid = std::unordered_map<std::string, std::vector<std::pair<LocType, LocType>>>;

    enum MemberFields
    {
        SEQ_ID
      , SOURCE
      , FEATURE_TYPE
      , FEATURE_START
      , FEATURE_END
      , SCORE
      , STRAND
      , PHASE
      , ATTRIBUTES
    };
}