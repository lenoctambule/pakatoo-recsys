# include "interface/Instance.hpp"
# include <iomanip>

typedef struct s_user
{
    size_t id;
    size_t age;
    size_t zipcode;
} t_user;

static void train_model(Instance &recsys)
{
    std::ifstream                       in;
    std::string                         line;
    t_iclamped                          r;
    std::vector<std::string>            s;
    size_t                              uid;

    in.open("./ml-100k/u1.base");
    while (std::getline(in, line))
    {
        split(line, s, "\t");
        r.id    = std::strtoul(s[1].c_str(), NULL, 10) - 1;
        r.val   = std::strtof(s[2].c_str(), NULL);
        r.val   = ((r.val - 1) / 4) * 2 - 1;
        uid     = std::strtoul(s[0].c_str(), NULL, 10);
        recsys.stream_train(uid, r);
        std::cout << "[" <<  loading_loop() << "] Training model ... " << std::endl;
        std::cout << LINE_ERASE;
    }
}

int main()
{
    Instance                    recsys;
    std::ifstream               in("./ml-100k/u1.test");
    std::string                 line;
    std::vector<std::string>    s;
    size_t                      uid;
    t_iclamped                  r;
    double                      error = 0;
    clock_t                     start;
    size_t                      i = 0;

    train_model(recsys);
    std::cout << std::fixed;
    std::cout << std::setprecision(3);
    start = clock();
    while (std::getline(in, line))
    {
        split(line, s, "\t");
        r.id    = std::strtoul(s[1].c_str(), NULL, 10) - 1;
        r.val   = std::strtof(s[2].c_str(), NULL);
        uid     = std::strtoul(s[0].c_str(), NULL, 10);
        float eval = 1 + recsys.stream_eval(uid, r.id) * 4;
        error   += std::pow(eval - r.val, 2);
        std::cout << "[" << loading_loop() << "] Running tests ... " << (i / 200.0f) << "%\t" << "RMSE = " << std::sqrt(error / i) << " " << eval << std::endl;
        std::cout << LINE_ERASE;
        r.val = ((r.val - 1) / 4) * 2 - 1;
        recsys.stream_train(uid, r);
        i++;
    }
    std::cout << "Avg infer time\t= " << (((clock() - start) / (double)CLOCKS_PER_SEC) * 1000.0f) / i << "ms" << std::endl;
    std::cout << "RMSE\t\t= " << std::sqrt(error / i) << std::endl;
    std::cout << "Sparsity\t= " << recsys.cf_graph.tensor.getSparsity() << std::endl;
    recsys.save("./out.pk2");
}
