#include <iostream>

#include "../config/Config.hpp"

int main() {
    // Load Goblin variables
    Config config;
    const Goblin& vars = config.getEnv();

    if (vars.goblin.is_safe) {
        // TODO: Safe crontab usage.
    } else {
        // TODO: Unsafe usage.
    }
}
