#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory> 
using namespace std;
class Employee;

class DLC
{
public:
	static void activateCrunchMode(const string& projectName)
	{
		cout << "\n========================================\n";
		cout << " [DLC ALERT] ВКЛЮЧЕН РЕЖИМ КРАНЧА ДЛЯ ПРОЕКТА: " << projectName << "!\n";
		cout << " Сроки горят! Все разработчики пишут код в два раза быстрее,\n";
		cout << " а тестировщики находят вдвое больше багов!\n";
		cout << "========================================\n\n";
	}
	static void applyCrunchBonus(const vector<shared_ptr<Employee>>& employees)
	{
		for (const auto& emp : employees)
		{
			cout << " [CRUNCH] Сотрудник " << emp->getName() << " работает сверхурочно!\n";
		}
		cout << "\n";
	}
};