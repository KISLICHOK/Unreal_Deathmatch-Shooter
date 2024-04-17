// Shoot Them Up, All Rights Reserved


#include "Components/STUAIPerceptionComponent.h"
#include "AIController.h"
#include "Components/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "STUUtils.h"
#include "Perception/AISense_Damage.h"

AActor* USTUAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);

    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller) return nullptr;
    
    bool SeedEnemy = false;
    for (const auto PercieveActor : PercieveActors)
    {
        const auto PercievePawn = Cast<APawn>(PercieveActor);
        if (PercievePawn && STUUtils::AreEnemies(Controller, PercievePawn->Controller))
        {
            SeedEnemy = true;
            break;
        }
    }
    
    if (PercieveActors.IsEmpty() || !SeedEnemy)
    {
        GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercieveActors);
        if(PercieveActors.IsEmpty()) return nullptr;
    }
    
    
    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;

    for (const auto PercieveActor : PercieveActors)
    {
        const auto HealthComponent = PercieveActor->FindComponentByClass<USTUHealthComponent>();

        const auto PercievePawn = Cast<APawn>(PercieveActor);
        const auto AreEnemies = PercievePawn && STUUtils::AreEnemies(Controller, PercievePawn->Controller);
        
        if (HealthComponent && !HealthComponent->IsDead() && AreEnemies) //TODO: check if enemies or not
        {
            const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if(CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PercieveActor;
            }
        }
    }

    return BestPawn;
}
