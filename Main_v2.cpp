#include <iostream>
#include "headers/MultiThreadedBruteForce.h"
#include "headers/dictionary.h"

using namespace std;

int main()
{	//welcome();
	int choice;
	cout<<"Enter the method to be employed; "<<endl;
	cout<<"1 ) Brute Force\n2 ) Dictionary\n3 ) Rule Based \n"<<endl;
	cin>>choice;
	switch(choice)
	{
		case 1:  multiThread();
				 break;
		case 2:  driver();
				 break;
		default: cout<<"Sorry Wrong choice\n";
	}
					
}	

	
