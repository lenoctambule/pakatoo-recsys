#include "interface/Dispatcher.hpp"
#include <iostream>
#include <iomanip>

#define NTHREADS 10

static void train_model(Dispatcher &recsys)
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
        recsys.dispatch_training(uid, r);
        std::cout << "[" <<  loading_loop() << "] Training model ... " << std::endl;
        std::cout << LINE_ERASE;
    }
    std::cout << "Training done." << std::endl;
}

int main()
{
    Dispatcher                  dsp(NTHREADS);
    std::deque<t_result>        results;
    std::deque<float>           ratings;
    std::ifstream               in("./ml-100k/u1.test");
    std::string                 line;
    std::vector<std::string>    s;
    size_t                      uid;
    t_iclamped                  r;
    double                      error;
    clock_t                     start;
    size_t                      i = 0;

    dsp.init();
    train_model(dsp);
    while (dsp.is_training())
        ;
    std::cout << std::fixed;
    std::cout << std::setprecision(3);
    start = clock();
    while (std::getline(in, line))
    {
        std::vector<t_iclamped> features;
        split(line, s, "\t");
        r.id    = std::strtoul(s[1].c_str(), NULL, 10) - 1;
        r.val   = std::strtof(s[2].c_str(), NULL);
        uid     = std::strtoul(s[0].c_str(), NULL, 10);
        results.push_back(t_result{.state=false, .res=0});
        ratings.push_back(r.val);
        dsp.dispatch_eval(uid, r.id, &results[results.size()-1]);
        std::cout << "[" << loading_loop() << "] Running tests ... " << (i / 200.0f) << "%" << std::endl;
        std::cout << LINE_ERASE;
        i++;
    }
    for (size_t i = 0; i < results.size(); i++)
    {
        while (!results[i].state)
            ;
        float eval = 1 + (1 - results[i].res) * 4;
        error   += std::pow(eval - ratings[i], 2);
        std::cout << "[" << loading_loop() << "] Running tests ... " << (i / 200.0f) << "%\t" << "RMSE = " << std::sqrt(error / (i + 1)) << " " << eval << std::endl;
        std::cout << LINE_ERASE;
    }
    std::cout << "Avg inference time = " << (((clock() - start) / CLOCKS_PER_SEC) * 1000) / i << "ms" << std::endl;
    std::cout << "RMSE = " << std::sqrt(error / i) << std::endl;
}