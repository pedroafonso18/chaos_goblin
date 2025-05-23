#include <cstdlib>
#include <string>
#include <filesystem>
#include <array>
#include <memory>
#include <stdexcept>
#include <iostream>

std::string exec_command(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result;
}

std::string get_executable_path() {
    std::filesystem::path exe_path = std::filesystem::current_path();
    
    if (exe_path.filename() == "chaos_goblin") {
        exe_path /= std::filesystem::path("build/chaos"); 
    } else {
        std::filesystem::path parent = exe_path.parent_path();
        if (parent.filename() == "build") {
            exe_path = parent / std::filesystem::path("chaos");
        } else {
            exe_path /= std::filesystem::path("build/chaos");
        }
    }
    
    return exe_path.string();
}

bool crontab_exists(const std::string& cron_entry) {
    try {
        std::string current_crontab = exec_command("crontab -l");
        return current_crontab.find(cron_entry) != std::string::npos;
    } catch (const std::exception& e) {
        return false;
    }
}

int crontab(std::string cron) {
    try {
        std::string exe_path = get_executable_path();
        std::string crontab_entry = cron + " " + exe_path;
        
        if (crontab_exists(crontab_entry)) {
            std::cout << "Crontab entry already exists, skipping." << std::endl;
            return 0;
        }
        
        std::string temp_file = "/tmp/chaos_goblin_crontab";
        std::string cmd = "crontab -l > " + temp_file + " 2>/dev/null || touch " + temp_file;
        system(cmd.c_str());
        
        cmd = "echo \"" + crontab_entry + "\" >> " + temp_file;
        system(cmd.c_str());
        
        cmd = "crontab " + temp_file;
        system(cmd.c_str());
        
        std::remove(temp_file.c_str());
        
        std::cout << "Crontab entry added: " << crontab_entry << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Failed to update crontab: " << e.what() << std::endl;
        return 1;
    }
}