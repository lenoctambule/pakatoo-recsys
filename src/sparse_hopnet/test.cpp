#include "SparseHN.hpp"
#include <set>
#include <fstream>
#include <sstream>

static float energy(std::stringstream &s, std::vector<t_iclamped> &seq, SparseHN &hnet, std::unordered_map<std::string, size_t> tokens)
{
    std::string word;
    float       ret;

    std::cout << s.str() << std::endl;
    seq.clear();
    while (s >> word)
    {
        auto ite = tokens.find(word);
        if (ite != tokens.end() && ite->second < 4096)
            seq.push_back(t_iclamped{.id=ite->second, .val=1});
    }
    ret = hnet.seq_energy(seq);
    std::cout << "Energy : " << ret << std::endl;
    return ret;
}

static void clean_word(std::string &word)
{
    for (size_t i = 0; i < word.size(); i++)
    {
        if (!std::isalpha(word[i]))
            word.erase(i);
        else if (std::isupper(word[i]))
            word[i] = 'a' + word[i] % 'A';
    }
}

int main(int ac, char **av)
{
    SparseHN                    hnet;
    size_t  gid = 0;
    std::unordered_map<std::string, size_t>   tokens;
    std::unordered_map<size_t, std::string>   word2id;
    std::vector<t_iclamped>         seq;
    std::ifstream harry("./harry.txt");
    std::string word;
    std::string a1("she dumbledore a sideways glance at threw here as though sharp hoping");
    std::string a2("she threw a sharp sideways glance at dumbledore here as though hoping");

    while (harry >> word)
    {
        if (seq.size() >= 32)
        {
            hnet.train(seq);
            seq.clear();
        }
        clean_word(word);
        if (word.size() == 0)
            continue ;
        auto ite = tokens.find(word);
        if (ite == tokens.end())
        {
            tokens[word] = gid;
            word2id[gid] = word;
            seq.push_back(t_iclamped{.id=gid});
            gid++;
        }
        else
            seq.push_back(t_iclamped{.id=ite->second, .val=1});
    }
    std::cout << tokens.size() << " " << word2id.size() << std::endl;

    std::stringstream s1(a1);
    std::stringstream s2(a2);

    energy(s1, seq, hnet, tokens);
    energy(s2, seq, hnet, tokens);

    hnet.save("test.pk2");

    SparseHN hnet_cpy;

    hnet_cpy.load("test.pk2");

    s2.seekg(0,std::ios::beg); s2.clear();
    s1.seekg(0,std::ios::beg); s1.clear();
    s1.str(a1);
    s2.str(a2);
    energy(s1, seq, hnet_cpy, tokens);
    energy(s2, seq, hnet_cpy, tokens);

    s1.seekg(0,std::ios::beg); s1.clear();
    std::cout << hnet.seq_energy(seq) << std::endl;
    for (size_t i = 0; i < seq.size(); i++)
        s1 << word2id[seq[i].id] << " ";
    for (size_t i = 0; i < 10; i++)
        s1 << word2id[hnet_cpy.infer(seq)] << " ";
    std::cout << hnet.seq_energy(seq) << std::endl;
    std::cout << s1.str() << std::endl;
}