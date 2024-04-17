// Shoot Them Up, All Rights Reserved


#include "AI/Servises/STUFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Components/STUAIPerceptionComponent.h"


USTUFindEnemyService::USTUFindEnemyService()
{
    NodeName = "Find Enemy";
}

void USTUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if(Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        if(const auto PerceprionComponent = Controller->FindComponentByClass<USTUAIPerceptionComponent>())
        {
            Blackboard -> SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceprionComponent->GetClosestEnemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
