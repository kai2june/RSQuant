#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

#include <RSQuant/common.hpp>
#include <RSQuant/format/GFF3.hpp>

namespace RSQ
{
class Indexer
{
  public:
    // using LocType = uint32_t;
    // using TranscriptAminoAcid = std::unordered_map<std::string, std::vector<std::pair<LocType, LocType>>>;
  public: 
    TranscriptAminoAcid tscaa;
  public:
    Indexer(std::ifstream& genome, std::ifstream& transcriptome)
    {
        std::string line;
        while(std::getline(transcriptome, line))
            if(line.at(0) != '#')
                break;

        std::string transcript;
        std::vector<std::pair<LocType, LocType>> vec;
        for(; std::getline(transcriptome, line); )
        {  
            RSQ::GFF3 gff3_line(line);
            std::string feature_type = gff3_line.getMember<RSQ::MemberFields::FEATURE_TYPE>();
            if(feature_type == "transcript")
            {
                if(!transcript.empty())
                {
                    tscaa[transcript] = vec;
                    vec.clear();
                    vec.shrink_to_fit();
                }
                transcript = gff3_line.getMember<RSQ::MemberFields::ATTRIBUTES>();
            }
            else if(feature_type == "CDS")
                vec.emplace_back(
                    std::make_pair(
                        gff3_line.getMember<RSQ::MemberFields::FEATURE_START>() +
                        gff3_line.getMember<RSQ::MemberFields::PHASE>()
                      , gff3_line.getMember<RSQ::MemberFields::FEATURE_END>()
                    )
                );
            else;
        }
    }
};
}