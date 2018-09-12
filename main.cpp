#include <iostream>
#include <cstring>
#include "vec.h"

using namespace std;

int main()
{
	int el_num, at_num;
	vec *at_l;
	vec cell[3],cell_norm;
	string *el_l;
	int *at_type, *el_type_num;
	string tmp;
	string flag_cell = "PRIMVEC", flag_atom = "PRIMCOORD";
	const double a2b = 1.8897259886;
	int t1,t2;

	// Get cell parameter
	getline(cin,tmp);
	while(tmp.find(flag_cell) == string::npos)
		getline(cin,tmp);
	cin>>cell[0]>>cell[1]>>cell[2];

	// Get number of atoms and atom position
	getline(cin,tmp);
	while(tmp.find(flag_atom) == string::npos)
		getline(cin,tmp);
	cin>>at_num;
	getline(cin,tmp);
	at_l = new vec[at_num];
	el_l = new string[at_num];
	at_type = new int[at_num];
	el_type_num = new int[at_num];
	el_num = 0;
	for(t1=0; t1<at_num; t1++)
	{
		cin>>tmp>>at_l[t1];
		for(t2=0; t2<el_num; t2++)
			if(tmp == el_l[t2])
			{
				at_type[t1] = t2;
				el_type_num[t2]++;
				break;
			}
		if (t2 >= el_num)
		{
			el_l[el_num] = tmp;
			at_type[t1] = el_num;
			el_type_num[el_num] = 1;
			el_num++;
		}
		getline(cin,tmp);
	}

	// prepare output
	cell_norm.x[0] = cell[0].norm() * a2b, cell[0] = cell[0] / cell_norm.x[0] * a2b;
	cell_norm.x[1] = cell[1].norm() * a2b, cell[1] = cell[1] / cell_norm.x[1] * a2b;
	cell_norm.x[2] = cell[2].norm() * a2b, cell[2] = cell[2] / cell_norm.x[2] * a2b;
	for(t1=0; t1<at_num; t1++)
		at_l[t1] = at_l[t1] * a2b;
	// print
	cout<<"#Definition of the unit cell"<<endl<<"acell"<<endl;
	cout<<cell_norm<<endl;
	cout<<"rprim"<<endl;
	cout<<cell[0]<<endl<<cell[1]<<endl<<cell[2]<<endl;
	cout<<"chkprim 0"<<endl;
	cout<<endl<<"#Definition of the atom types"<<endl;
	cout<<"ntypat "<<el_num<<endl;
	cout<<"znucl";
	for(t1=0; t1<el_num; t1++)
		cout<<" X";
	cout<<endl;
	cout<<endl<<"#Definition of the atoms"<<endl;
	cout<<"natom "<<at_num<<endl;
	cout<<"typat";
	for(t1=0; t1<el_num; t1++)
		cout<<' '<<el_type_num[t1]<<'*'<<t1+1;
	cout<<endl;
	cout<<"xcart"<<endl;
	for(t1=0; t1<el_num; t1++)
		for(t2=0; t2<at_num; t2++)
			if(at_type[t2] == t1)
				cout<<at_l[t2]<<endl;
	return 0;
}
