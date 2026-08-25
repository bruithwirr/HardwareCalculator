#pragma once

#include <limits>
#include <iostream>
#include <cmath>

struct transaction_req {
    double cpu, ram, disc;
};


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

double calculateCPUCores (int tx_number,double tx_cpu,double time_limit, double safety_margin) {
    double cpu_time = tx_number * tx_cpu;
    double cores_num = std::ceil((( cpu_time / 1000 )/ (time_limit*60))*safety_margin);
    return cores_num;
}

double calculateRAM (double cores_num, double tx_ram, double safety_margin) {
    double ram = cores_num * tx_ram * safety_margin;
    return ram;
}

double calculateDiscSpace (int tx_number, double tx_disc, double safety_margin) {
    double disc_space = tx_number * tx_disc * safety_margin;
    return disc_space;
}