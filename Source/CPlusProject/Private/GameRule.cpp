#include "GameRule.h"



UGameRule::UGameRule()
{

}

void UGameRule::Init()
{
	
}

void UGameRule::BroadcastComplete()
{
	OnComplete.Broadcast();
}

void UGameRule::BroadcastPointsScored(AController* scorer, int points)
{
	OnPointsScored.Broadcast(scorer, points);
}

