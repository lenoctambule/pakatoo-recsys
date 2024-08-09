#include "SparseHN.hpp"
#include <set>
#include <fstream>
#include <sstream>

static float energy(std::stringstream &s, std::vector<t_iclamped> seq, SparseHN &hnet, std::map<std::string, size_t> tokens)
{
    std::string word;
    float      ret;

    std::cout << s.str() << std::endl;
    seq.clear();
    while (s >> word)
    {
        auto ite = tokens.find(word);
        if (ite != tokens.end() && ite->second < 4096)
            seq.push_back(t_iclamped{.id=ite->second});
    }
    ret = hnet.seq_energy(seq);
    std::cout << "Energy : " << ret << std::endl;
    return ret;
}

int main(int ac, char **av)
{
    SparseHN                    hnet;
    size_t  gid = 0;
    std::map<std::string, size_t>   tokens; 
    std::vector<t_iclamped>         seq;
    std::ifstream harry("./harry.txt");
    std::string word;
    std::string a1("She Dumbledore a , sideways glance at threw  here, as though sharp hoping");
    std::string a2("She threw a sharp, sideways glance at Dumbledore here, as though hoping");

    while (harry >> word)
    {
        if (seq.size() >= 32)
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

    std::stringstream s1(a1);
    std::stringstream s2(a2);

    energy(s2, seq, hnet, tokens);
    energy(s1, seq, hnet, tokens);

    hnet.save("test.pk2");

    SparseHN hnet_cpy;

    hnet_cpy.load("test.pk2");

    s2.seekg(0,std::ios::beg); s2.clear();
    s1.seekg(0,std::ios::beg); s1.clear();
    s1.str(a1);
    s2.str(a2);
    energy(s2, seq, hnet_cpy, tokens);
    energy(s1, seq, hnet_cpy, tokens);
}