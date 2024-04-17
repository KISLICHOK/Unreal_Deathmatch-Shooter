// Shoot Them Up, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animations/STUAnimNotify.h"
#include "STUReloadFinishedAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*);

UCLASS()
class SHOOTTHEMUP_API USTUReloadFinishedAnimNotify : public USTUAnimNotify
{
    GENERATED_BODY()

};
