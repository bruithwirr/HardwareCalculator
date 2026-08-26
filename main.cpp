#include <iostream>
#include <yaml-cpp/yaml.h>
#include <unordered_map>


#include "hardware_calculations.h"




int main(int argc, char* argv[]) {
    std::string config_path;

    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " [config-file]\n";
        return 1;
    }

    if (argc == 2) {
        config_path = argv[1];
    }
    else {
        config_path ="../config.yaml";
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




    std::string tx_type;
    std::cout << "This is a hardware sizing calculator." << std::endl;
    int tx_number = readPositiveInt("Enter the number of transactions: ");
    std::cout << "Enter transaction type: ";
    std::cin >> tx_type;
    while (transaction_types.find(tx_type) == transaction_types.end()) {
        std::cout << "Unknown transaction type. Please try again: " << std::endl;
        std::cin >> tx_type;
    }
    double time_limit = readPositiveDouble("What is the time limit to finish all transactions in minutes?: ");

    auto tx = transaction_types[tx_type];

    double cores_num = calculateCPUCores(tx_number, tx.cpu, time_limit, safety_margin);
    double ram = calculateRAM(cores_num, tx.ram, safety_margin);
    double disc_space = calculateDiscSpace(tx_number, tx.disc, safety_margin);

    std::cout << "You will need " << cores_num << " cores, " << ram /1000 << " MB of RAM and " << disc_space / 1000 <<" MB of disk space"<<   std::endl;

    return 0;
}



