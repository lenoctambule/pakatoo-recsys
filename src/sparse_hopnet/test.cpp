#include "SparseHN.hpp"
#include <set>
#include <fstream>
#include <sstream>

int main(int ac, char **av)
{
    SparseHN                    hnet(1024);
    size_t  gid = 0;
    std::map<std::string, size_t>   tokens; 
    std::vector<t_iclamped>         seq;
    std::ifstream harry("./harry.txt");
    std::string word;

    while (harry >> word)
    {
        if (seq.size() >= 512)
        {
            hnet.train(seq);
            seq.clear();
        }
        auto ite = tokens.find(word);
        if (ite == tokens.end())
        {
            tokens[word] = gid;
            seq.push_back(t_iclamped{.id=gid});
            gid++;
        }
        else
            seq.push_back(t_iclamped{.id=ite->second});
    }

    // std::stringstream ss("She threw a sharp, sideways glance at Dumbledore here, as though hoping");
    std::stringstream ss("She Dumbledore a , sideways glance at threw  here, as though sharp hoping");

    seq.clear();
    while (ss >> word)
    {
        auto ite = tokens.find(word);
        if (ite != tokens.end() && ite->second < 4096)
            seq.push_back(t_iclamped{.id=ite->second});
    }
    
    std::cout << "Energy : " << hnet.seq_energy(seq) << std::endl;
}