// Shoot Them Up, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pikups/STUBasePickup.h"
#include "STUHealthPickup.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickup : public ASTUBasePickup
{
    GENERATED_BODY()

protected:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "100"), Category = "Pickup")
    float HealthAmount = 100.0f;

};
