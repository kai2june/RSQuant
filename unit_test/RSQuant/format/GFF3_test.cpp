#include <iostream>

#include <RSQuant/format/GFF3.hpp>

int main()
{
    RSQ::GFF3 gff3("2L      FlyBase transcript      7529    9484    .       +       .       ID=FBtr0300689;geneID=FBgn0031208;gene_name=CG11023");
    
    std::cout << "getMember: "<< gff3.getMember<RSQ::MemberFields::FEATURE_TYPE>() << std::endl;
    
    gff3.printAllColumn<0>();

    return 0;
}