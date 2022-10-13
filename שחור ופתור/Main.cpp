#include<iostream>
#include<fstream>
#include<vector>
#include<direct.h>
#include<string>
using namespace std;

#include"table.h"


void main()
{
	_mkdir("..\\saved puzzles");
	bool boo;
	string name;
	cout<<"open? y=1 , n=0: ";
	cin>>boo;

	if(boo)
	{
		Griddler g;
		cout<<"name: ";
		cin>>name;
		g.open(name);
	}
	else
	{
		Griddler g(1);
		g.print_num_table();
		cout<<"save? y=1 , n=0: ";
		cin>>boo;
		if(boo)
			g.save();
	}

	system("pause");
}

/*for (unsigned char i = 0; i < 255; i++)
{
cout<<(int)i<<": "<<i;
i%2==1 ? cout<<endl<<endl : cout<<"	";
}*/