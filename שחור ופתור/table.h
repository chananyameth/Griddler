template <class T> void write(ofstream & f, T x)
{
	f.write(reinterpret_cast<char *>(&x), sizeof(T));
}
template <class T> void read(ifstream & f, T& x)
{
	f.read(reinterpret_cast<char *>(&x), sizeof(T));
}

class Griddler //black and slove
{
	//////////////////////////
	//table simple functions//
	//////////////////////////
private:
	void print_row_num(short i)
	{
		for (short j=0; j<x/2 + XZ - HMN_x[i]; j++)
			cout<<0<<" ";
		for (short j=0; j<HMN_x[i]; j++)
			cout<<num_x[i][j]<<" ";
		cout<<endl;
	}
	void print_column_num(short i)
	{
		for (short j=0; j<y/2 + YZ - HMN_y[i]; j++)
			cout<<0<<" ";
		for (short j=0; j<HMN_y[i]; j++)
			cout<<num_y[i][j]<<" ";
		cout<<endl;
	}
	void set_row(short& i, short& num, short& sum, short& index)
	{
		cout<<"Row number "<<i+1<<":\n";
		while(num!=-1 && index<x/2+XZ && sum<x)
		{
			cin>>num;
			if(num == -1)
			{}
			else if(num <= 0 || num > x)
			{
				cout<<"ReEnter a valid number.\n";
				index--;
			}
			else if(sum+num > x)
			{
				cout<<"ReEnter again the number. The sum is bigger than x.\n";
				index--;
			}
			else
			{
				num_x[i][index] = num;
				sum += num + 1;
			}
			index++;
		}
		cout<<"Row number "<<i+1<<" is: ";
		HMN_x[i] = num==-1?index-1:index;
		print_row_num(i);
		num = 0;
		index = 0;
		sum=0;
	}
	void set_column(short& i, short& num, short& sum, short& index)
	{
		cout<<"Column number "<<i+1<<":\n";
		while(num!=-1 && index<y/2+YZ && sum<y)
		{
			cin>>num;
			if(num == -1)
			{}
			else if(num <= 0 || num > y)
			{
				cout<<"ReEnter a valid number.\n";
				index--;
			}
			else if(sum+num > y)
			{
				cout<<"ReEnter again the number. The sum is bigger than y.\n";
				index--;
			}
			else
			{
				num_y[i][index] = num;
				sum += num + 1;
			}
			index++;
		}
		cout<<"Column number "<<i+1<<" is: ";
		HMN_y[i] = num==-1?index-1:index;
		print_column_num(i);
		num = 0;
		index = 0;
		sum=0;
	}
public:
	string name;
	short** table;//full=1, empty=0, ?=-1
	short** num_x;
	short** num_y;
	short x;
	short y;
	bool XZ, YZ;//if zugy - 0. if e'zugy - 1.
	short *HMN_x, *HMN_y;//How Many Numbers

	Griddler()
	{
		name = "";
		table = NULL;
		num_x = NULL;
		num_y = NULL;
		x = 0;
		y = 0;
		XZ = 0;
		YZ = 0;
		HMN_x = NULL;
		HMN_y = NULL;
	}
	Griddler(bool)
	{
		//name
		cout<<"Enter the name for the griddler: ";
		cin.ignore();
		getline(cin,name);

		//reset size
		x:cout<<"Enter size of x: ";
		cin>>x;
		if(x<1) goto x;
		y:cout<<"Enter size of y: ";
		cin>>y;
		if(y<1) goto y;

		//reset table
		table = new short*[x];
		for (short i=0; i<x; i++)
			table[i] = new short[y];
		for (short i=0; i<x; i++)
			for (short j=0; j<y; j++)
				table[i][j] = -1;//-1 = ?

		//reset numbers
		num_x = new short*[y];
		num_y = new short*[x];
		HMN_x = new short[y];
		HMN_y = new short[x];

		for (short i=0; i<y; i++)
			num_x[i] = new short[x/2 + 1];
		for (short i=0; i<x; i++)
			num_y[i] = new short[y/2 + 1];

		for (short i=0; i<y; i++)
			for (short j=0; j<x/2 + 1; j++)
				num_x[i][j] = 0;
		for (short i=0; i<x; i++)
			for (short j=0; j<y/2 + 1; j++)
				num_y[i][j] = 0;

		//input numbers & set rows and columns
		short num=0, sum=0;
		char y_n;
		short number, index=0;

		XZ = x%2==0 ? 0 : 1;
		YZ = y%2==0 ? 0 : 1;

		cout<<"\n\nEnter rows's numbers - (the end is: -1):\n";
		for(short i=0; i<y; i++)
			set_row(i,num,sum,index);
		do
		{
			cout<<"\n\nWrite \"y\" to set again a row, and \"n\" if no. ";
			cin>>y_n;
			if(y_n == 'y')
			{
				cout<<"\nEnter number of the row: ";
				cin>>number;
				set_row(--number,num,sum,index);
			}
		}while(y_n=='y' || y_n!='n');

		cout<<"\n\nEnter columns's numbers - (the end is: -1):\n";
		index=0;
		for(short i=0; i<x; i++)
			set_column(i,num,sum,index);
		do
		{
			cout<<"\n\nWrite \"y\" to set again a column, and \"n\" if no. ";
			cin>>y_n;
			if(y_n == 'y')
			{
				cout<<"\nEnter number of the column: ";
				cin>>number;
				set_column(--number,num,sum,index);
			}
		}while(y_n == 'y');
	}
	~Griddler()
	{
		for (short i=0; i<x; i++)
			delete[] table[i];
		delete[] table;

		for (short i=0; i<y; i++)
			delete[] num_x[i];
		for (short i=0; i<x; i++)
			delete[] num_y[i];
		delete[] num_x;
		delete[] num_y;
	}
	void print_num_table()
	{
		//columns
		for(short i=0; i<y/2+YZ; i++,cout<<endl)
		{
			//indentation
			for (short j=1; j<x/2+XZ; j++)
			{
				cout<<"   ";
			}
			cout<<"  ";

			for(short j=0; j<x; j++)
			{
				if(i<y/2+YZ-HMN_y[j])
					cout<<0<<" "<<" ";
				else
					cout<<num_y[j][i-((y/2+YZ)-(HMN_y[j]))]<<" "<<(num_y[j][i-((y/2+YZ)-(HMN_y[j]))]/10<1 ? " " : "");
			}
		}

		//rows
		for (short i=0; i<y; i++,cout<<endl)
			for (short j=0; j<x/2+XZ; ++j)
			{
				if(j<x/2+XZ-HMN_x[i])
					cout<<0<<" "<<" ";
				else
					cout<<num_x[i][j-((x/2+XZ)-(HMN_x[i]))]<<" "<<(num_x[i][j-((x/2+XZ)-(HMN_x[i]))]/10<1 ? " " : "");
			}
		cout<<endl;
	}
	bool save()
	{
		ofstream f("..\\saved puzzles\\" + name + ".pzl");
		if(!f) return false;

		//x, y
		write(f, x);
		write(f, y);

		//table
		for (short i=0; i<x; i++)
			for (short j=0; j<y; j++)
				write(f, table[i][j]);

		//num_x
		for (short i=0; i<y; i++)
			for (short j=0; j<x/2 + 1; j++)
				write(f, num_x[i][j]);
		//num_y
		for (short i=0; i<x; i++)
			for (short j=0; j<y/2 + 1; j++)
				write(f, num_y[i][j]);

		//HMN_x
		for (short i=0; i<y; i++)
			write(f, HMN_x[i]);

		//HMN_y
		for (short i=0; i<x; i++)
			write(f, HMN_y[i]);

		f.close();
		return true;
	}
	bool open(string N)
	{
		ifstream f;
		f.open("..\\saved puzzles\\" + N + ".pzl");
		if(!f) return false;

		name = N;

		//x, y
		read(f, x);
		read(f, y);

		num_x = new short*[y];
		num_y = new short*[x];
		HMN_x = new short[y];
		HMN_y = new short[x];
		
		table = new short*[x];
		for (short i=0; i<x; i++)
			table[i] = new short[y];
		for (short i=0; i<x; i++)
			for (short j=0; j<y; j++)
				read(f, table[i][j]);

		for (short i=0; i<y; i++)
			num_x[i] = new short[x/2 + 1];
		for (short i=0; i<x; i++)
			num_y[i] = new short[y/2 + 1];

		for (short i=0; i<y; i++)
			for (short j=0; j<x/2 + 1; j++)
				num_x[i][j] = 0;
		for (short i=0; i<x; i++)
			for (short j=0; j<y/2 + 1; j++)
				num_y[i][j] = 0;

		XZ = x%2==0 ? 0 : 1;
		YZ = y%2==0 ? 0 : 1;

		//num_x
		for (short i=0; i<y; i++)
			for (short j=0; j<x/2 + 1; j++)
				read(f, num_x[i][j]);
		//num_y
		for (short i=0; i<x; i++)
			for (short j=0; j<y/2 + 1; j++)
				read(f, num_y[i][j]);

		//HMN_x
		for (short i=0; i<y; i++)
			read(f, HMN_x[i]);

		//HMN_y
		for (short i=0; i<x; i++)
			read(f, HMN_y[i]);

		f.close();
		return true;
	}


	//////////////////////////
	//table simple functions//
	//////////////////////////
private:
	bool fun_1(short i, string r_c)//row or column
	{
		switch(r_c)
		{
		case "row":
			break;
		case "column":
			break;
		}
	}
public:
	bool solve()
	{
		for (int i=0; i<y; i++)
		{
			fun_1(i,"row");
		}
		for (int i=0; i<x; i++)
		{
			fun_1(i,"column");
		}
		return true;
	}
};