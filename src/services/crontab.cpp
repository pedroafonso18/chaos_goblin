#include <cstdlib>
#include <string>
#include <filesystem>
#include <array>
#include <memory>
#include <stdexcept>
#include <iostream>

// Helper function to execute a command and get its output
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

// Get the path of the executable
std::string get_executable_path() {
    // Get the binary's directory using filesystem
    std::filesystem::path exe_path = std::filesystem::current_path();
    
    // Navigate to the expected build directory
    // Adjust this logic based on your project structure
    if (exe_path.filename() == "chaos_goblin") {
        exe_path /= std::filesystem::path("build/chaos"); 
    } else {
        // Try to find build directory
        std::filesystem::path parent = exe_path.parent_path();
        if (parent.filename() == "build") {
            exe_path = parent / std::filesystem::path("chaos");
        } else {
            exe_path /= std::filesystem::path("build/chaos");
        }
    }
    
    return exe_path.string();
}

// Check if a crontab entry already exists
bool crontab_exists(const std::string& cron_entry) {
    try {
        std::string current_crontab = exec_command("crontab -l");
        return current_crontab.find(cron_entry) != std::string::npos;
    } catch (const std::exception& e) {
        // If crontab -l fails, it likely means no crontab exists
        return false;
    }
}

int crontab(std::string cron) {
    try {
        // Get the actual path to the executable
        std::string exe_path = get_executable_path();
        std::string crontab_entry = cron + " " + exe_path;
        
        // Check if the entry already exists
        if (crontab_exists(crontab_entry)) {
            std::cout << "Crontab entry already exists, skipping." << std::endl;
            return 0;
        }
        
        // Create a temporary file with the new crontab entry
        std::string temp_file = "/tmp/chaos_goblin_crontab";
        std::string cmd = "crontab -l > " + temp_file + " 2>/dev/null || touch " + temp_file;
        system(cmd.c_str());
        
        // Append our entry to the file
        cmd = "echo \"" + crontab_entry + "\" >> " + temp_file;
        system(cmd.c_str());
        
        // Install the new crontab
        cmd = "crontab " + temp_file;
        system(cmd.c_str());
        
        // Clean up
        std::remove(temp_file.c_str());
        
        std::cout << "Crontab entry added: " << crontab_entry << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Failed to update crontab: " << e.what() << std::endl;
        return 1;
    }
}