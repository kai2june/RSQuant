#include <iostream>

#include <RSQuant/indexer.hpp>

int main(int argc, char* argv[])
{
    std::ifstream genome("/mammoth/flux_simulator_data/tiny_Droso.fa");
    std::ifstream transcriptome("/mammoth/flux_simulator_data/tiny_Droso.gff3");
    RSQ::Indexer indexer(genome, transcriptome);

    return 0;
}