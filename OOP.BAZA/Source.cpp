#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <thread> // Обязательно для задержки (sleep)
#include <chrono> // Обязательно для указания секунд
using namespace std;

class Employee
{
protected:
	string name;
	int experience;
	string position;
public:
	Employee(string n, int e, string p) : name(n), experience(e), position(p) {}
	virtual void work() = 0;
	virtual double calculateSalary() = 0;
	string getName()
	{
		return name;
	}
	int getExperience()
	{
		return experience;
	}
	string getPosition()
	{
		return position;
	}
};
class Programmer : public Employee
{
protected:
	int CodeLines;
	double ratePerLine;
public:
	Programmer(string n, int e, int l, double r, string p = "Programmer") : Employee(n, e, p), CodeLines(l), ratePerLine(r) {}
	void work()
	{
		cout << "The Progamer writes software code (" << CodeLines << " lines)\n\n";
	}
	double calculateSalary()
	{
		return CodeLines * ratePerLine;
	}
};
class Teamlead : public Programmer
{
	int subordinatesCount;
	double managementBonus;
public:
	Teamlead(string n, int e, int l, double r, int subs, double bonus) : Programmer(n, e, l, r, "Teamlead"), subordinatesCount(subs), managementBonus(bonus) {}
	void work()
	{
		cout << name << " leads a team of " << subordinatesCount << " developers and writes core code (" << CodeLines << " lines)\n\n";
	}
	double calculateSalary()
	{
		return Programmer::calculateSalary() + managementBonus;
	}
};
class Tester : public Employee
{
	int BugsFound;
	double ratePerBug;
public:
	Tester(string n, int e, int b, double r) : Employee(n, e, "Tester"), BugsFound(b), ratePerBug(r) {}
	void work()
	{
		cout << name << " tests system functionality (found " << BugsFound << " bugs)\n\n";
	}
	double calculateSalary()
	{
		return BugsFound * ratePerBug;
	}
};
class ProjectManager : public Employee
{
	double baseRate;
	int completeTasks;
	double taskBonus;
public:
	ProjectManager(string n, int e, double b, int t, double bon) : Employee(n, e, "ProjectManager"), baseRate(b), completeTasks(t), taskBonus(bon) {}
	void work()
	{
		cout << name << " organizes team work and controls deadlines (" << completeTasks << " tasks completed)\n\n";
	}
	double calculateSalary()
	{
		return baseRate + (completeTasks * taskBonus);
	}
};

#include "File.h"
#include "DLC.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "=== СИСТЕМА УПРАВЛЕНИЯ СОТРУДНИКАМИ И ПРОЕКТАМИ ===\n\n";

	char choice;
	cout << "Включить режим жесткого кранча (y/n)? ";
	cin >> choice;

	int delayTime = 5;

	if (choice == 'y')
	{
		DLC::activateCrunchMode("CyberCore");
		delayTime = 2;
	}
	else if (choice == 'n')
	{
		cout << "\n[INFO] Работаем в обычном режиме (без кранчей, паузы по 5 сек).\n\n";
	}
	this_thread::sleep_for(chrono::seconds(delayTime));
	cout << "[LOG] Инициализация сотрудников в системе...\n";
	shared_ptr<Employee> p1 = make_shared<Programmer>("Babenko", 3, 4000, 2.5);
	shared_ptr<Employee> t1 = make_shared<Tester>("Alexandr Ivanov", 2, 45, 50.0);
	shared_ptr<Employee> m1 = make_shared<ProjectManager>("Kristina", 5, 20000.0, 10, 1500.0);
	shared_ptr<Employee> lead = make_shared<Teamlead>("Strashkov", 7, 2500, 3.0, 5, 10000.0);
	Project myProject("CyberCore", 150000.0);
	myProject.addEmployee(p1);
	myProject.addEmployee(t1);
	myProject.addEmployee(m1);
	myProject.addEmployee(lead);

	this_thread::sleep_for(chrono::seconds(delayTime));
	myProject.showParticipants();
	this_thread::sleep_for(chrono::seconds(delayTime));
	myProject.startwork();
	this_thread::sleep_for(chrono::seconds(delayTime));
	cout << "Общий фонд оплаты труда: " << myProject.calculateTotalSalary() << " грн\n\n";

	this_thread::sleep_for(chrono::seconds(delayTime));
	shared_ptr<Employee> topEmp = myProject.findMaxSalaryEmployee();
	if (topEmp)
	{
		cout << "Самый высокооплачиваемый сотрудник:\n";
		cout << " - " << topEmp->getName() << " (" << topEmp->getPosition()
			<< ") с зарплатой: " << topEmp->calculateSalary() << " грн\n\n";
	}

	this_thread::sleep_for(chrono::seconds(delayTime));
	cout << "--- Удаление сотрудника (Alexandr Ivanov) ---\n";
	myProject.removeEmployee("Alexandr Ivanov");
	this_thread::sleep_for(chrono::seconds(delayTime));
	myProject.showParticipants();
	cout << "Новый общий фонд оплаты труда: " << myProject.calculateTotalSalary() << " грн\n";
	return 0;
}