#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class Project
{
    string projectName;
    double budget;
    vector<shared_ptr<Employee>> employees;
public:
    Project(string n, double b) : projectName(n), budget(b) {}

    void addEmployee(shared_ptr<Employee> emp)
    {
        employees.push_back(emp);
    }

    void removeEmployee(string empName)
    {
        for (auto it = employees.begin(); it != employees.end(); ++it)
        {
            if ((*it)->getName() == empName)
            {
                employees.erase(it);
                break;
            }
        }
    }

    void showParticipants()
    {
        cout << "Project: " << projectName << " | Budget: " << budget << "\nParticipants:\n";
        for (auto& emp : employees)
        {
            cout << " - " << emp->getName() << " (" << emp->getPosition() << "), Experience: " << emp->getExperience() << " years, Salary: " << emp->calculateSalary() << "\n";
        }
        cout << "\n";
    }

    double calculateTotalSalary()
    {
        double total = 0;
        for (auto& emp : employees)
        {
            total += emp->calculateSalary();
        }
        return total;
    }

    void startwork()
    {
        cout << "--- Starting work on project: " << projectName << " ---\n";
        for (auto& emp : employees)
        {
            emp->work();
        }
        cout << "-------------------------------\n\n";
    }

    shared_ptr<Employee> findMaxSalaryEmployee()
    {
        if (employees.empty())
        {
            return nullptr;
        }
        auto maxEmp = employees[0];
        double maxSal = maxEmp->calculateSalary();
        for (size_t i = 1; i < employees.size(); ++i)
        {
            double sal = employees[i]->calculateSalary();
            if (sal > maxSal)
            {
                maxSal = sal;
                maxEmp = employees[i];
            }
        }
        return maxEmp;
    }
};