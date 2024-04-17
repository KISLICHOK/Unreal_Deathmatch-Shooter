// Shoot Them Up, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STURespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTURespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTURespawnComponent();
	
	void Respawn(int32 RespawnTime);
	int32 GetRespawnCpuntDown() const {return RespawnCountDown;}
	bool IsRespawnInProgress() const;
	
protected:
	virtual void BeginPlay() override;

private:	
	FTimerHandle RespawnTimerHandle;
	int32 RespawnCountDown = 0;

	void RespawnTimerUpdate();
};
