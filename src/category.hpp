#ifndef CATEGORY_H
#define CATEGORY_H

#include <iostream>

struct record
{
	float amount;
	std::string remarks;
	record* next;
	record( float amount, std::string remarks);
	void display();
};

class category
{
private:
	record* ledger;
	float total_expenses;
public:
	float total_balance;
	std::string title;

	category();
	category(std::string title);

	void display();
	void deposit( float amount, std::string remarks = "No remarks");
	bool withdraw( float amount, std::string remarks = "No remarks");
	bool transfer( float amount, category target);

	friend void plot_bar( category **cat_list, int noc);
};

void plot_bar( category** cat_list, int noc);


#endif // CATEGORY_H