# include "Pakatoo.hpp"

typedef struct s_user
{
    size_t id;
    size_t age;
    size_t zipcode;
} t_user;

static void init_features(std::map<std::string, size_t> &features, char const *fname)
{
    static size_t gid = 0;

    features[fname] = gid;
    //std::cout << "Added feature " << fname << " with id " << gid << std::endl;
    gid++;
}

static void extract_user_ratings(std::vector<std::vector<t_iclamped>> &user_ratings)
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
        user_ratings[uid - 1].push_back(r);
    }
}

static void extract_movie_features(std::vector<std::vector<t_iclamped>> &movie_features,
                                    std::map<std::string, size_t> &features)
{
    std::ifstream               in;
    std::string                 line;
    std::vector<std::string>    s;
    size_t                      fid;
    size_t                      mid;
    std::stringstream           ss;

    in.open("./ml-100k/u.item");
    while(std::getline(in, line))
    {
        split(line, s, "|");
        mid = std::strtoul(s[0].c_str(), NULL, 10) - 1;
        for (size_t i = 5; i < s.size(); i++)
        {
            if (s[i][0] == '1')
            {
                line = std::to_string(i - 5);
                if (features.find(line) == features.end())
                    init_features(features, line.c_str());
                movie_features[mid].push_back(t_iclamped{.id=features[line], .val=1});
            }
        }
    }
    in.close();
}

static void extract_user_features(std::vector<std::vector<t_iclamped>> &user_features,
                                    std::map<std::string, size_t> &features)
{
    std::ifstream                       in;
    std::string                         line;
    std::vector<std::string>            s;
    t_user                              user;
    size_t                              fid;

    in.open("./ml-100k/u.user");
    while(std::getline(in, line))
    {
        split(line, s, "|");
        user.id = std::strtoul(s[0].c_str(), NULL, 10) - 1;
        user.age = std::strtoul(s[1].c_str(), NULL, 10);
        switch (user.age)
        {
            case 0 ... 12:
                fid = features["ukid"];
                break;
            case 13 ... 21:
                fid = features["uteen"];
                break;
            case 22 ... 30:
                fid = features["uyoung"];
                break;
            case 31 ... 55:
                fid = features["umid"];
                break;
            default :
                fid = features["uold"];
                break;
        }

        user_features[user.id].push_back(t_iclamped{.id=fid, .val=1});
        if (s[2] == "M")
            user_features[user.id].push_back(t_iclamped{.id=features["M"], .val=1});
        else
            user_features[user.id].push_back(t_iclamped{.id=features["F"], .val=1});
        if (features.find(s[3]) == features.end())
            init_features(features, s[3].c_str());
        user_features[user.id].push_back(t_iclamped{.id=features[s[3]], .val=1});
    }
    in.close();
}

static void build_ctx(std::vector<std::vector<t_iclamped>> &ctx,
                        std::vector<std::vector<t_iclamped>> const &user_ratings,
                        std::vector<std::vector<t_iclamped>> const &user_features,
                        std::vector<std::vector<t_iclamped>> const &movie_features,
                        size_t                        &uid)
{
    std::vector<t_iclamped> const &uratings = user_ratings[uid];

    ctx.clear();
    for (size_t i = 0; i < uratings.size(); i++)
    {
        std::vector<t_iclamped> features;
        features.insert(features.end(), user_features[uid].begin(), user_features[uid].end());
        features.insert(features.end(), movie_features[uratings[i].id].begin(), movie_features[uratings[i].id].end());
        features.push_back(t_iclamped{.id=0, .val=uratings[i].val});
        ctx.push_back(features);
    }
}

int main()
{
    Pakatoo                             recsys;
    std::map<std::string, size_t>       features;
    std::vector<std::vector<t_iclamped>>    user_ratings(943);
    std::vector<std::vector<t_iclamped>>    user_features(943);
    std::vector<std::vector<t_iclamped>>    movie_features(1682);
    std::vector<std::vector<t_iclamped>>    injected_ctx;
    
    char const *ft[] = { "rating",
                        "ukid",
                        "uteen",
                        "uyoung",
                        "umid",
                        "uold",
                        "M",
                        "F",
                        NULL};

    for (size_t i = 0; ft[i] != NULL; i++)
        init_features(features, ft[i]);
    extract_user_features(user_features, features);
    extract_movie_features(movie_features, features);
    extract_user_ratings(user_ratings);
    for (size_t i = 0; i < user_ratings.size(); i++)
    {
        build_ctx(injected_ctx, user_ratings, user_features, movie_features, i);
        recsys.train(user_ratings[i], injected_ctx);
    }


    std::ifstream               in("./ml-100k/u1.test");
    std::string                 line;
    std::vector<std::string>    s;
    size_t                      uid;
    t_iclamped                  r;
    double                      error;
    clock_t                     start;
    size_t                      i = 0;

    start = clock();
    while (std::getline(in, line))
    {
        std::vector<t_iclamped> features;
        split(line, s, "\t");
        r.id    = std::strtoul(s[1].c_str(), NULL, 10) - 1;
        r.val   = std::strtof(s[2].c_str(), NULL);
        uid     = std::strtoul(s[0].c_str(), NULL, 10);
        features.insert(features.end(), user_features[uid].begin(), user_features[uid].end());
        features.insert(features.end(), movie_features[r.id].begin(), movie_features[r.id].end());
        features.push_back(t_iclamped{.id=0, .val=((r.val - 1) / 4) * 2 - 1});
        float eval = (1 - recsys.eval(user_ratings[uid - 1], features, r.id)) * 5;
        error   += std::pow(eval - r.val, 2);
        //std::cout << eval << " " << r.val << std::endl;
        //std::cout << ((float)i / 20000.0f) * 100 << "%" << std::endl;
        i++;
    }
    std::cout << "Avg inference time = " << (((clock() - start) / CLOCKS_PER_SEC) * 1000) / 20000.0f << "ms" << std::endl;
    std::cout << "RMSE = " << std::sqrt(error / 20000.0f) << std::endl;
}