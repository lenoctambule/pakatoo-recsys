# include "core/Pakatoo.hpp"
# include <iomanip>

typedef struct s_user
{
    size_t id;
    size_t age;
    size_t zipcode;
} t_user;

static void train_model(Pakatoo &recsys)
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
        recsys.train_stream(uid, r);
        std::cout << "[" <<  loading_loop() << "] Training model ... " << std::endl;
        std::cout << LINE_ERASE;
    }
}

// static void extract_movie_features(std::vector<std::vector<t_iclamped>> &movie_features,
//                                     std::map<std::string, size_t> &features)
// {
//     std::ifstream               in;
//     std::string                 line;
//     std::vector<std::string>    s;
//     size_t                      mid;
//     std::stringstream           ss;

//     in.open("./ml-100k/u.item");
//     while(std::getline(in, line))
//     {
//         split(line, s, "|");
//         mid = std::strtoul(s[0].c_str(), NULL, 10) - 1;
//         for (size_t i = 5; i < s.size(); i++)
//         {
//             if (s[i][0] == '1')
//             {
//                 line = std::to_string(i - 5);
//                 if (features.find(line) == features.end())
//                     init_features(features, line.c_str());
//                 movie_features[mid].push_back(t_iclamped{.id=features[line], .val=1});
//             }
//         }
//     }
//     in.close();
// }

// static void extract_user_features(std::vector<std::vector<t_iclamped>> &user_features,
//                                     std::map<std::string, size_t> &features)
// {
//     std::ifstream                       in;
//     std::string                         line;
//     std::vector<std::string>            s;
//     t_user                              user;
//     size_t                              fid;

//     in.open("./ml-100k/u.user");
//     while(std::getline(in, line))
//     {
//         split(line, s, "|");
//         user.id = std::strtoul(s[0].c_str(), NULL, 10) - 1;
//         user.age = std::strtoul(s[1].c_str(), NULL, 10);
//         switch (user.age)
//         {
//             case 0 ... 12:
//                 fid = features["ukid"];
//                 break;
//             case 13 ... 21:
//                 fid = features["uteen"];
//                 break;
//             case 22 ... 30:
//                 fid = features["uyoung"];
//                 break;
//             case 31 ... 55:
//                 fid = features["umid"];
//                 break;
//             default :
//                 fid = features["uold"];
//                 break;
//         }

//         user_features[user.id].push_back(t_iclamped{.id=fid, .val=1});
//         if (s[2] == "M")
//             user_features[user.id].push_back(t_iclamped{.id=features["M"], .val=1});
//         else
//             user_features[user.id].push_back(t_iclamped{.id=features["F"], .val=1});
//         if (features.find(s[3]) == features.end())
//             init_features(features, s[3].c_str());
//         user_features[user.id].push_back(t_iclamped{.id=features[s[3]], .val=1});
//     }
//     in.close();
// }

// static void build_ctx(std::vector<std::vector<t_iclamped>> &ctx,
//                         std::vector<std::vector<t_iclamped>> const &user_ratings,
//                         std::vector<std::vector<t_iclamped>> const &user_features,
//                         std::vector<std::vector<t_iclamped>> const &movie_features,
//                         size_t                        &uid)
// {
//     std::vector<t_iclamped> const &uratings = user_ratings[uid];

//     ctx.clear();
//     for (size_t i = 0; i < uratings.size(); i++)
//     {
//         std::vector<t_iclamped> features;
//         features.insert(features.end(), user_features[uid].begin(), user_features[uid].end());
//         features.insert(features.end(), movie_features[uratings[i].id].begin(), movie_features[uratings[i].id].end());
//         features.push_back(t_iclamped{.id=0, .val=uratings[i].val});
//         ctx.push_back(features);
//     }
// }

int main()
{
    Pakatoo                                 recsys;
    std::map<std::string, size_t>           features;
    std::vector<std::vector<t_iclamped>>    injected_ctx;
    std::ifstream               in("./ml-100k/u1.test");
    std::string                 line;
    std::vector<std::string>    s;
    size_t                      uid;
    t_iclamped                  r;
    double                      error;
    clock_t                     start;
    size_t                      i = 0;

    train_model(recsys);
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
        float eval = 1 + (1 - recsys.eval(uid, r.id)) * 4;
        error   += std::pow(eval - r.val, 2);
        std::cout << "[" << loading_loop() << "] Running tests ... " << (i / 200.0f) << "%\t" << "RMSE = " << std::sqrt(error / i) << " " << eval << std::endl;
        std::cout << LINE_ERASE;
        r.val = ((r.val - 1) / 4) * 2 - 1;
        recsys.train_stream(uid, r);
        i++;
    }
    std::cout << "Avg inference time = " << (((clock() - start) / CLOCKS_PER_SEC) * 1000) / i << "ms" << std::endl;
    std::cout << "RMSE = " << std::sqrt(error / i) << std::endl;
    std::cout << "Sparsity =" << recsys.graph.tensor.getSparsity() << std::endl;
    recsys.save("./out.pk2");
}
