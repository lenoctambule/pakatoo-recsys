#include "SparseHN.hpp"

typedef std::map<time_t, t_iclamped>    t_mratings;
typedef std::vector<t_iclamped>         t_vratings;

int main()
{
    SparseHN                    hn;
    std::vector<t_mratings>     user_ratings(943);
    std::vector<t_vratings>     urating_seq(943);
    std::ifstream               in("./ml-100k/u1.base");
    std::string                 line;
    std::vector<std::string>    s;
    std::vector<t_iclamped>     seq;
    time_t                      t;
    size_t                      uid;
    t_iclamped                  r;
    double                      error = 0;
    size_t                      ecount = 0;


    while (std::getline(in, line))
    {
        split(line, s, " \f\n\r\t\v");
        t       = std::strtol(s[3].c_str(), NULL, 10);
        r.id    = std::strtoul(s[1].c_str(), NULL, 10) - 1;
        r.val   = std::strtof(s[2].c_str(), NULL);
        r.val   = ((r.val - 1) / 4) * 2 - 1;
        uid     = std::strtoul(s[0].c_str(), NULL, 10);
        user_ratings[uid - 1][t] = r;
    }
    in.close();

    for (size_t i = 0; i < user_ratings.size(); i++)
    {
        for (auto ite = user_ratings[i].begin(); ite != user_ratings[i].end(); ite++)
            seq.push_back(ite->second);
        urating_seq[i] = seq;
        hn.train(seq);
        seq.clear();
    }
    hn.save("./test.pk2");
    in.open("./ml-100k/u1.test");
    size_t  i = 1;
    clock_t start = clock();
    while (std::getline(in, line))
    {
        split(line, s, " \f\n\r\t\v");
        t       = std::strtol(s[3].c_str(), NULL, 10);
        r.id    = std::strtoul(s[1].c_str(), NULL, 10) - 1;
        r.val   = std::strtof(s[2].c_str(), NULL);
        uid     = std::strtoul(s[0].c_str(), NULL, 10);
        float eval = (1 - hn.eval(urating_seq[uid - 1], r.id)) * 5;
        error   += std::pow(eval - r.val, 2);
        std::cout << eval << " " << r.val << std::endl;
        i++;
    }
    std::cout << (ecount / (20000.0f)) * 100 << "% error" << std::endl;
    std::cout << "Avg inference time = " << (((clock() - start) / CLOCKS_PER_SEC) * 1000) / 20000.0f << "ms" << std::endl;
    std::cout << "RMSE = " << std::sqrt(error / 20000.0f) << std::endl;
    in.close();
}