#pragma once

class Transaction {
public:
    Transaction(double cpu, double ram, double mem ) : cpu_(cpu), ram_(ram), mem_(mem) {}
    virtual ~Transaction() = default;
protected:
    double cpu_;
    double ram_;
    double mem_;
};

class CPUTransaction : public Transaction {
public:
    CPUTransaction(double cpu_coef, double cpu, double ram, double mem) : Transaction(cpu*cpu_coef, ram,mem){}
    ~CPUTransaction() override = default;
};

class RAMTransaction : public Transaction {
public:
    RAMTransaction(double ram_coef, double cpu, double ram, double mem) : Transaction(cpu, ram*ram_coef,mem){}
    ~RAMTransaction() override = default;
};

class MEMTransaction : public Transaction {
public:
    MEMTransaction(double mem_coef, double cpu, double ram, double mem) : Transaction(cpu, ram,mem*mem_coef){}
    ~MEMTransaction() override = default;
};

