#include <iostream>
#include <yaml-cpp/yaml.h>
#include <unordered_map>
#include <cmath>
#include <limits>


struct transaction_req {
    double cpu, ram, disc;
};

double readPositiveDouble(const std::string& prompt);

int main() {

    std::string config_path = std::string(PROJECT_ROOT) + "/config.yaml"; //namiesto yaml chcel som pouzit base triedu a kazda nova transakcia by bola potomkom base transakcie
    YAML::Node config = YAML::LoadFile(config_path);                        //yaml subor je citatelnejsi a jednoduchsi na pouzitie

    std::unordered_map<std::string, transaction_req> transaction_types;     //chcel som ukladat vsetky typy do vektoru, prechadzat pomocou for. pre tri typt toto je v poriadku
                                                                            //ak tam bude viac typov tak hash map je lepsia
    for (const auto& transaction : config["transactions"]) {
        transaction_types[transaction["type"].as<std::string>()] = {transaction["cpu"].as<double>(),
                                                                        transaction["ram"].as<double>(),
                                                                        transaction["disc"].as<double>()};
    }
    auto safety_margin = config["safety_margin"].as<double>();
    double tx_number, time_limit;
    std::string tx_type;
    std::cout << "This is a hardware calculator." << std::endl;
    tx_number = readPositiveDouble("Enter the number of transactions: ");
    std::cout << "Enter transaction type: ";
    std::cin >> tx_type;
    while (transaction_types.find(tx_type) == transaction_types.end()) {
        std::cout << "Unknown transaction type. Please try again: " << std::endl;
        std::cin >> tx_type;
    }
    time_limit = readPositiveDouble("What is the time limit to finish all transactions in minutes?");
    double cpu_time = tx_number * transaction_types[tx_type].cpu;
    double cores_num = std::ceil((( cpu_time / 1000 )/ (time_limit*60))*safety_margin);
    double ram = cores_num * transaction_types[tx_type].ram * safety_margin;
    double disc_space = tx_number * transaction_types[tx_type].disc * safety_margin;
    std::cout << "You will need " << cores_num << " cores, " << ram /1000 << " MB of RAM and " << disc_space / 1000 <<" MB of disk space"<<   std::endl;
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