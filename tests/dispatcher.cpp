# include "interface/Dispatcher.hpp"

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
    Dispatcher dsp(5);

    dsp.init();
    train_model(dsp);
}