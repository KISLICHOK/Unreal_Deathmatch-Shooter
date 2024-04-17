#pragma once
#include "Player/STUPlayerState.h"

class STUUtils
{
public:
	template<typename T>
    static T* GetSTUPlayerComponent(AActor* PlayerPawn)
    {
        if (!PlayerPawn) return nullptr;

        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
    }

	bool static AreEnemies(AController* Controller1, AController* Controller2)
	{
		if(!Controller1 || !Controller2 || Controller1 == Controller2 ) return false;

		const auto PlaterState1 = Cast<ASTUPlayerState>(Controller1->PlayerState);
		const auto PlaterState2 = Cast<ASTUPlayerState>(Controller2->PlayerState);
		
		return PlaterState1 && PlaterState2 && PlaterState1->GetTeamID() != PlaterState2->GetTeamID();
	}

	static FText TextFromInt(int32 Number)
	{
		return FText::FromString(FString::FromInt(Number));
	}
};