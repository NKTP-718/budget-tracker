#include <iomanip>
#include <windows.h>
#include "category.hpp"

#define HEADER 5
#define MARGIN 70
#define NEXTLINE gotoxy( MARGIN, HEADER+(pc++))

static inline void gotoxy( short x, short y)
{
	COORD pt = { x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pt);
}

void plot_bar( category** cat_list, int noc)
{
	using namespace std;

	float overall_expenses = 0;
	short pc = 0; // used in NEXTLINE

	// Calculate overall expense
	for( int i = 0; i < noc; i++)
		overall_expenses += cat_list[i]->total_expenses;

	NEXTLINE;
	cout<<"    "<<setw(((noc*2)>30?(noc*2):17)+3)<<setfill('-')<<right<<"Expense chart"<<setfill(' ');
	NEXTLINE;

	// Plot by percentage
	for( int i = 10; i >= 0; i--)
	{
		cout<<setw(3)<<i*10<<"|";
		for( int j = 0; j < noc; j++)
		{
			if( i <= ((cat_list[j]->total_expenses/overall_expenses)*10))
				cout<<" o";
		}
		NEXTLINE;
	}
	cout<<"    "<<setw(((noc*2)>30?(noc*2):17)+3)<<setfill('-')<<right<<"-"<<setfill(' ');
	NEXTLINE;

	// X-axis labels
	bool labels_not_ended = true;
	for( int i = 0; labels_not_ended; i++)
	{
		cout<<"    ";
		labels_not_ended = false;
		for( int j = 0; j < noc; j++)
		{
			labels_not_ended = labels_not_ended || (i < cat_list[j]->title.length());
			cout<<" "<<(i < cat_list[j]->title.length() ? cat_list[j]->title[i] : ' ');
		}
		NEXTLINE;
	}
	gotoxy( 0, 5);
}