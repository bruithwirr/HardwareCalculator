#include <iostream>
#include <yaml-cpp/yaml.h>
#include <unordered_map>
#include <cmath>
#include <limits>


struct transaction_req {
    double cpu, ram, disc;
};

double readPositiveDouble(const std::string& prompt);
int readPositiveInt(const std::string& prompt);

int main(int argc, char* argv[]) {
    std::string config_path;
    if (argc ==2) {
        config_path = argv[1];
    }
    else {
        config_path = std::string(PROJECT_ROOT) + "/config.yaml";
    }

    std::unordered_map<std::string, transaction_req> transaction_types;
    double safety_margin;
    try {
        YAML::Node config = YAML::LoadFile(config_path);
        for (const auto& transaction : config["transactions"]) {
            transaction_types[transaction["type"].as<std::string>()] = {transaction["cpu"].as<double>(),
                                                                        transaction["ram"].as<double>(),
                                                                        transaction["disc"].as<double>()};
        }
        safety_margin = config["safety_margin"].as<double>();
    } catch (const YAML::BadFile& err) {
        std::cerr <<"Couldn't open file: "<< err.what() << std::endl;
        return 1;
    } catch (const YAML::Exception& err) {
        std::cerr <<"YAML parse error: "<< err.what() << std::endl;
        return 1;
    }


    double tx_number, time_limit;
    std::string tx_type;
    std::cout << "This is a hardware sizing calculator." << std::endl;
    tx_number = readPositiveInt("Enter the number of transactions: ");
    std::cout << "Enter transaction type: ";
    std::cin >> tx_type;
    while (transaction_types.find(tx_type) == transaction_types.end()) {
        std::cout << "Unknown transaction type. Please try again: " << std::endl;
        std::cin >> tx_type;
    }
    time_limit = readPositiveDouble("What is the time limit to finish all transactions in minutes?: ");
    double cpu_time = tx_number * transaction_types[tx_type].cpu;
    double cores_num = std::ceil((( cpu_time / 1000 )/ (time_limit*60))*safety_margin);
    double ram = cores_num * transaction_types[tx_type].ram * safety_margin;
    double disc_space = tx_number * transaction_types[tx_type].disc * safety_margin;
    std::cout << "You will need " << cores_num << " cores, " << ram /1000 << " MB of RAM and " << disc_space / 1000 <<" MB of disk space"<<   std::endl;

    return 0;
}

double readPositiveDouble(const std::string& prompt) {
    double value;
    std::cout << prompt;
    while (!(std::cin >> value) || value <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a positive number: ";
    }
    return value;
}

int readPositiveInt(const std::string& prompt) {
    double value;
    std::cout << prompt;
    while (!(std::cin >> value) || value <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a positive integer: ";
    }
    return std::ceil(value);
}