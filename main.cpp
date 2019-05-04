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
		cout<<endl<<endl<<"\t\t"<<"您想在玩一次吗<y, n>?";
		cin>>ch;
	}

	cout<<endl<<"     ====================================================================="<<endl<<endl;
	cout<<"\t\t\t你已成功退出游戏!!谢谢使用!!"<<endl<<endl;
	cout<<"     ====================================================================="<<endl<<endl;
	
	return 0;
}