#include <iostream>
#include <yaml-cpp/yaml.h>
#include <unordered_map>
#include <cmath>


struct transaction_req {
    double cpu, ram, mem;
};

int main() {

    std::string config_path = std::string(PROJECT_ROOT) + "/config.yaml"; //namiesto yaml chcel som pouzit base triedu a kazda nova transakcia by bola potomkom base transakcie
    YAML::Node config = YAML::LoadFile(config_path);                        //yaml subor je citatelnejsi a jednoduchsi na pouzitie

    std::unordered_map<std::string, transaction_req> transaction_types;     //chcel som ukladat vsetky typy do vektoru, prechadzat pomocou for. pre tri typt toto je v poriadku
                                                                            //ak tam bude viac typov tak hash map je lepsia
    for (const auto& transaction : config["transactions"]) {
        transaction_types[transaction["type"].as<std::string>()] = {transaction["cpu"].as<double>(),
                                                                        transaction["ram"].as<double>(),
                                                                        transaction["mem"].as<double>()};
    }
    double tx_number, time_limit;
    std::string tx_type;
    std::cout << "This is a hardware calculator." << std::endl << "Enter number of transactions: " <<std::endl;
    std::cin >> tx_number;
    std::cout << "Enter transaction type: ";
    std::cin >> tx_type;
    while (transaction_types.find(tx_type) == transaction_types.end()) {
        std::cout << "Unknown transaction type. Please try again: " << std::endl;
        std::cin >> tx_type;
    }
    std::cout << "What is the time limit to finish all transactions in minutes?" << std::endl;
    std::cin >> time_limit;
    double cpu_time = tx_number * transaction_types[tx_type].cpu;
    double cores_num = std::ceil((( cpu_time / 1000 )/ (time_limit*60))*1.2);
    double ram = cores_num * transaction_types[tx_type].ram;
    double memory = tx_number * transaction_types[tx_type].mem;
    std::cout << "You will need " << cores_num << " cores, " << ram /1000 << " MB of RAM and " << memory / 1000 <<" MB of memory"<<   std::endl;
}