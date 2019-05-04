#include<iostream.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

#include "GameOf21Point.h"

ostream &operator<<(ostream &o,const Card &c)
{
	if(c.suit==CLUBS)
		o<<"梅花";
	else if(c.suit==DIAMONDS)
		o<<"方块";
	else if(c.suit==HEARTS)
		o<<"红桃";
	else if(c.suit==SPADES)
		o<<"KING";
	
	if(c.rank==ACE)
		o<<"A";
	else if(c.rank==JACK)
		o<<"J";
	else if(c.rank==QUEEN)
		o<<"Q";
	else if(c.rank==KING)
		o<<"K";
	else cout<<(int)c.rank;
	
	return o;
}

void GameOf21Point::Shuffle()
{
	srand(time(NULL));
	
	for(int i=51;i>0;i--)
	{
		int pos=rand()%(i+1);
		Card t;
		t=d[pos];
		d[pos]=d[i];
		d[i]=t;
	}
}

int GameOf21Point::GetTotalScore(Card hand[21], int n)
{
	int p;
	int totalScore=0;
	
	for(p=0;p<n;p++)
	{
		if(hand[p].rank==ACE)
			totalScore+=1;
		else if(hand[p].rank==TEN || hand[p].rank==JACK || hand[p].rank==QUEEN ||hand[p].rank==KING)
			totalScore+=10;
		else
			totalScore+=(int)hand[p].rank;
	}
	
	for(p=0;p<n && totalScore>21;p++)
		if(hand[p].rank==ACE)
			totalScore-=10;
		
		return totalScore;
}

void GameOf21Point::ShowStatus(int n,bool hideFirstCardAndTotalScore)
{
	cout<<"\t\t"<<name[n]<<":";
	if(hideFirstCardAndTotalScore)
		cout<<" <隐藏>";
	else
	{
		if(hands[n][0].suit==CLUBS)
			cout<<" 梅花";
		else if(hands[n][0].suit==DIAMONDS)
			cout<<" 方块";
		else if(hands[n][0].suit==HEARTS)
			cout<<" 红桃";
		else if(hands[n][0].suit==SPADES)
			cout<<" 黑桃";
		
		if(hands[n][0].rank==ACE)
			cout<<"A";
		else if(hands[n][0].rank==JACK)
			cout<<"J";
		else if(hands[n][0].rank==QUEEN)
			cout<<"Q";
		else if(hands[n][0].rank==KING)
			cout<<"K";
		else 
			cout<<(int)hands[n][0].rank;
	}
	
	
	for(int i=1;i<numOfCard[n];i++)
	{
		if(hands[n][i].suit==CLUBS)
			cout<<" 梅花";
		else if(hands[n][i].suit==DIAMONDS)
			cout<<" 方块";
		else if(hands[n][i].suit==HEARTS)
			cout<<" 红桃";
		else if(hands[n][i].suit==SPADES)
			cout<<" 黑桃";
		
		if(hands[n][i].rank==ACE)
			cout<<"A";
		else if(hands[n][i].rank==JACK)
			cout<<"J";
		else if(hands[n][i].rank==QUEEN)
			cout<<"Q";
		else if(hands[n][i].rank==KING)
			cout<<"K";
		else 
			cout<<(int)hands[n][i].rank;
	}
	
	if(!hideFirstCardAndTotalScore)
		cout<<" 总分数"<<GetTotalScore(hands[n],numOfCard[n]);
	cout<<endl;
	
	if(GetTotalScore(hands[n],numOfCard[n])>21)
		cout<<"\t\t"<<name[n]<<"引爆!"<<endl;
}

GameOf21Point::GameOf21Point()
{
	int curPos=0;
	dealPos=0;
	int i=0;
	
	for(int suitpos=0;suitpos<4;suitpos++)
	{
		for(int rankPos=1;rankPos<=13;rankPos++)
		{
			d[curPos].suit=(SuitType)suitpos;
			d[curPos].rank=(RankType)rankPos;
			curPos++;
		}
	}

	cout<<endl;
	cout<<"\t\t\t"<<"     21点游戏 欢迎您的使用! "<<endl<<endl;
	cout<<"     ====================================================================="<<endl<<endl;

	cout<<"\t\t多少人加入游戏?<1~7>:";
	cin>>numOfPlayer;
	while(numOfPlayer<1||numOfPlayer>7)
	{
		cout<<"\t\t玩家人数限定在1~7人，请重新输入人数<1~7>:";
		cin>>numOfPlayer;
	}
	
	for(i=0;i<=numOfPlayer;i++)
		numOfCard[i]=0;
	
	strcpy(name[0],"庄家");
	cout<<endl;
	for(i=1;i<=numOfPlayer;i++)
	{
		cout<<"\t\t输入第"<<i<<"位玩家的姓名:";
		cin>>name[i];
	}
	cout<<endl;
	cout<<"\t\t\t\t游戏开始!"<<endl<<endl;
}

void GameOf21Point::Game()
{
	int i,j;
	
	Shuffle();
	
	for(i=1;i<=2;i++)
	{
		hands[0][numOfCard[0]]=DealOneCard();
		numOfCard[0]++;
	}
	
	ShowStatus(0,true);
	
	for(i=1;i<=numOfPlayer;i++)
		for(j=0;j<2;j++)
		{
			hands[i][numOfCard[i]]=DealOneCard();
			numOfCard[i]++;
		}
		
		for(i=1;i<=numOfPlayer;i++)
			ShowStatus(i);
		
		cout<<endl;
		
		for(i=1;i<=numOfPlayer;i++)
		{
			char ch;
			cout<<"\t\t"<<name[i]<<"，你想要一张牌吗<y, n>?";
			cin>>ch;
			
			while(ch!='y'&&ch!='n')
			{
				cout<<"\t\t"<<name[i]<<"，你输入错误，请重新输入<y, n>?";
				cin>>ch;
			}
			
			while(GetTotalScore(hands[i],numOfCard[i])<=21&&ch=='y')
			{
				hands[i][numOfCard[i]]=DealOneCard();
				numOfCard[i]++;
				ShowStatus(i);
				
				if(GetTotalScore(hands[i],numOfCard[i])>21)
					break;
				cout<<"\t\t"<<name[i]<<"，你还想再要一张牌吗<y, n>?";
				cin>>ch;
			}
		}
		
		ShowStatus(0);
		while(GetTotalScore(hands[0],numOfCard[0])<=16)
		{
			hands[0][numOfCard[0]]=DealOneCard();
			numOfCard[0]++;
			ShowStatus(0);
		}
		cout<<endl;
		
		if(GetTotalScore(hands[0],numOfCard[0])>21)
		{
			for(i=1;i<=numOfPlayer;i++)
			{
				if(GetTotalScore(hands[i],numOfCard[i])<=21)
					cout<<"\t\t"<<name[i]<<"，恭喜你，你赢了!"<<endl;
				else 
					cout<<"\t\t"<<name[i]<<"，你们打成了平局。"<<endl;
			}
		}
		else
		{
			for(i=1;i<=numOfPlayer;i++)
			{
				if(GetTotalScore(hands[i],numOfCard[i])<=21 && GetTotalScore(hands[i],numOfCard[i])>GetTotalScore(hands[0],numOfCard[0]))
					cout<<"\t\t"<<name[i]<<"，恭喜你，你赢了!"<<endl;
				else if(GetTotalScore(hands[i],numOfCard[i])==GetTotalScore(hands[0],numOfCard[0]))
					cout<<"\t\t"<<name[i]<<"，你们打成了平局。"<<endl;
				else
					cout<<"\t\t"<<name[i]<<"，对不起，你输了。"<<endl;
			}
		}
}
