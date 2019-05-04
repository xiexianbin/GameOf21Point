#include<iostream.h>

#define LEN_OF_MAX_NAME 21

typedef enum
{
	//扑克牌面值：ACE(A),TWO(2)~TEN(10),JACK(J),QUEEN(Q),KING(K)
	ACE=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
}RankType;

typedef enum
{
	//扑克牌的花色：CAUBS(梅花),DIAMONDS(方块),HEARTS(红桃),SPADES(黑桃)
	CLUBS, DIAMONDS, HEARTS, SPADES
}SuitType;

struct Card
{
	RankType rank;
	SuitType suit;
};

class GameOf21Point
{
private:
	Card d[52];
	int dealPos;
	Card hands[8][21];
	int numOfCard[8];
	char name[8][LEN_OF_MAX_NAME];
	int numOfPlayer;
	
	void Shuffle();
	
	int GetTotalScore(Card hand[21], int n);
	
	void ShowStatus(int num,bool hideFirstCardAndTotalScore=false);

	Card DealOneCard()
	{
		return d[dealPos++];
	}
	
public:
	GameOf21Point();
	virtual~GameOf21Point()
	{
	};
	void Game();
};