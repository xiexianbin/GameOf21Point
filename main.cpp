#include<iostream.h>

#include "GameOf21Point.h"

int main()
{
	char ch;
	ch='y';

	while(ch=='y')
	{
		GameOf21Point game;
		game.Game();
		cout<<endl<<endl<<"\t\t"<<"��������һ����<y, n>?";
		cin>>ch;
	}

	cout<<endl<<"     ====================================================================="<<endl<<endl;
	cout<<"\t\t\t���ѳɹ��˳���Ϸ!!ллʹ��!!"<<endl<<endl;
	cout<<"     ====================================================================="<<endl<<endl;
	
	return 0;
}