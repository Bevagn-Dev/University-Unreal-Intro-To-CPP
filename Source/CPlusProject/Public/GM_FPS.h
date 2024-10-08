#pragma once
 
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GM_FPS.generated.h"
 
UCLASS(Abstract)
class CPLUSPROJECT_API AGM_FPS : public AGameMode
{
	GENERATED_BODY()
 
public:
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;
 
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
 
protected:
	TArray<TObjectPtr<AActor>> _PlayerStarts;
 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<AController>> _PlayerControllers;
 
	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;
 
	virtual void OnMatchStateSet() override;
 
	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Match Management")
	int _CountdownTimer;
	FTimerHandle _TimerDecreaseCountdown;
	UPROPERTY(EditAnywhere, Category="Match Management")
	TSubclassOf<APawn> _MatchPawn;
 
	UFUNCTION()
	void DecreaseCountdown();
};