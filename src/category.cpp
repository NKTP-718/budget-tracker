#include <string>
#include <iomanip>
#include "category.hpp"

record::record( float amount, std::string remarks)
{
	this->amount = amount;
	this->remarks = remarks;
	this->next = NULL;
}
void record::display()
{
	// title( width : 50 - left aligned) amount( width : 5 - right aligned)
	std::cout<<std::setw(50)<<std::left<<this->remarks<<std::setw(5)<<std::right<<this->amount<<std::endl;
}

category::category()
{
	float amount;
	this->ledger = NULL;
	this->total_balance = 0;
	this->total_expenses = 0;

	std::cout<<"Enter title : ";
	std::getline( std::cin>>std::ws, this->title);
	std::cout<<"Set initial budget : ";
	std::cin>>amount;

	this->deposit( amount, "Initial budget");
}
category::category(std::string title)
{
	this->title = title;
	this->ledger = NULL;
	this->total_balance = 0;
	this->total_expenses = 0;
}
void category::display()
{
	std::cout<<std::setw(55)<<std::setfill('-')<<std::right<<this->title<<std::endl;
	if(ledger)
		for( record* i = this->ledger; i; i = i->next)
		 	i->display();
	else
		std::cout<<std::setw(55)<<std::setfill(' ')<<std::right<<"No expenses yet!"<<std::endl;
}
void category::deposit( float amount, std::string remarks)
{
	this->total_balance += amount;

	if(!this->ledger)
	{
		this->ledger = new record( amount, remarks);
		return;
	}

	record* i = this->ledger;
	for( ; i->next; i = i->next);
	i->next = new record( amount, remarks);
}
bool category::withdraw( float amount, std::string remarks)
{
	if(this->total_balance >= amount)
	{
		this->deposit( -amount, remarks);
		this->total_expenses += amount;
		return true;
	}
	return false;
}
bool category::transfer( float amount, category target)
{
	if(this->withdraw( amount, "Used for "+target.title))
	{
		target.deposit( amount, "Taken from "+this->title);
		return true;
	}
	return false;
}