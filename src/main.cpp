#include <iostream>
#include <conio.h>
#include <string>

#include "category.hpp"

using namespace std;

category** cat_list;
int noc = -1;

char menu(int page)
{
	switch(page)
	{
	case 0:
		cout<<"+] New category"<<endl;

	case 1:
		for( int i = 0; i <= noc; ++i)
			cout<<i+1<<"] "<<cat_list[i]->title<<" - "<<cat_list[i]->total_balance<<endl;
		cout<<"0] Exit"<<endl;
		cout<<"\tSelect category..."<<endl;
		break;

	case 2:
		cout<<"1] Add expense"<<endl;
		cout<<"2] Update budget"<<endl;
		cout<<"-] Delete category"<<endl;
		cout<<"*] Rename category"<<endl;
		cout<<"0] Back"<<endl;
		break;
	}
	return _getch();
}

void category_operations(int index)
{
	float amount;
	string buffer;

	// Display category records
	system("cls");
	cat_list[index]->display();
	cout<<endl<<endl;

	// Category menu
	switch(menu(2))
	{
	case '0':
		return;

	case '1':
		cout<<"Enter amount spent :";
		cin>>amount;
		cout<<"Enter remarks :";
		getline( cin>>ws, buffer);
		if(cat_list[index]->withdraw( amount, buffer))
			cout<<"Expense updated"<<endl;
		else
			cout<<"Oops, Your balance :"<<cat_list[index]->total_balance<<endl;
		cout<<endl;
		break;

	case '2':
		cout<<"Increase budget by :";
		cin>>amount;
		cout<<"Enter remarks :";
		getline( cin>>ws, buffer);
		cat_list[index]->deposit( amount, buffer);
		cout<<"Budget updated\n"<<endl;
		break;

	case '-':
		for( ; index < noc; index++)
			swap( cat_list[index], cat_list[index+1]);
		delete cat_list[noc--];
		cout<<"Category deleted";
		break;

	case '*':
		buffer = cat_list[index]->title;
		getline( cin>>ws, cat_list[index]->title);
		cout<<"Category renamed from "<<buffer<<" to "<<cat_list[index]->title;
		break;

	default:
		cout<<'\a';
	}
	_getch();
}

int main(int argc, char const *argv[])
{
	cat_list = new category*[9];
	cat_list[++noc] = new category("Miscellaneous");

	while(true)
	{
		// Plot graph
		system("cls");
		plot_bar( cat_list, noc+1);

		// Home menu
		int i = menu(0);
		switch(i)
		{
		case '0':
			delete[] cat_list;
			return 0;

		case '+':
			if(noc < 8)
			{
				cat_list[++noc] = new category();
				cout<<"New category created : "<<cat_list[noc]->title<<endl;
			}
			else
				cout<<"\n\n\tPlease pull your crap together, 9 categories are enough!"<<endl;
			_getch();
			break;

		default:
			i -= '1';
			if( i >= 0 && i <= noc)
				category_operations(i);
			else
				cout<<'\a';
		}
	}
	return 0;
}