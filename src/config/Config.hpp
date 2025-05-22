#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

// Here are the config variables for the goblin, E.G : The database, the virtual machine, and etc.
struct Goblin{
    struct Goblin_goblin {
        bool enabled;
        bool is_scheduled;
        bool is_safe;
        std::string level;
        std::string crontab;
    };
    struct Goblin_database {
        std::string host;
        std::string name;
        std::string user;
        std::string password;
        std::string level;
    };
    struct Goblin_machine {
        std::string ip;
        std::string user;
        std::string password;
        bool docker;
        std::string level;
    };
};

class Config {
    private:
        Goblin goblin_vars;
        void loadGoblin();
    public:
        // This will read the yaml file and try to populate the vars (load them)
        Config();
        // This is what will actually return the vars.
        const Goblin& getEnv() const;
};


#endif