// Shoot Them Up, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
    GENERATED_BODY()

public:
    ASTUBasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    float RespawnTime = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    TObjectPtr<USoundCue> PickupTakenSound;

    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    virtual bool GivePickupTo(APawn * PlayerPawn);

public:
    virtual void Tick(float DeltaTime) override;
    bool CouldBeTaken() const;

private:
    FTimerHandle RespawnTimerHandle;
    float RotationYaw = 0.0f;

    void PickupWasTaken();
    void Respawn();
    void GenerateRotationYaw();
};
