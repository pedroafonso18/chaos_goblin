#include "Config.hpp"
#include "../../dependencies/toml++/toml.hpp"

#include <string>
#include <iostream>

Config::Config() {
    loadGoblin();
}

void Config::loadGoblin() {
    try {
        auto config = toml::parse_file("../../goblin.toml");
        
        // Access goblin section
        if (auto goblin_table = config["goblin"]) {
            goblin_vars.goblin.enabled = goblin_table["enabled"].value_or(false);
            goblin_vars.goblin.is_scheduled = goblin_table["is_scheduled"].value_or(false);
            goblin_vars.goblin.is_safe = goblin_table["is_safe"].value_or(true);
            goblin_vars.goblin.level = goblin_table["level"].value_or("testing");
            goblin_vars.goblin.crontab = goblin_table["crontab"].value_or("* * * * *");
        }
        
        // Access database section
        if (auto db_table = config["database"]) {
            goblin_vars.database.host = db_table["host"].value_or("");
            goblin_vars.database.name = db_table["name"].value_or("");
            goblin_vars.database.user = db_table["user"].value_or("");
            goblin_vars.database.password = db_table["password"].value_or("");
            goblin_vars.database.level = db_table["level"].value_or("testing");
        }
        
        // Access machine section
        if (auto machine_table = config["machine"]) {
            goblin_vars.machine.ip = machine_table["ip"].value_or("127.0.0.1");
            goblin_vars.machine.user = machine_table["user"].value_or("");
            goblin_vars.machine.password = machine_table["password"].value_or("");
            goblin_vars.machine.docker = machine_table["docker"].value_or(false);
            goblin_vars.machine.level = machine_table["level"].value_or("testing");
        }
    }
    catch (const toml::parse_error& err) {
        std::cerr << "Parsing failed: " << err.description() << "\n"
                  << "Error occurred at: " << err.source().begin << "\n";
    }
}

const Goblin& Config::getEnv() const {
    return goblin_vars;
}