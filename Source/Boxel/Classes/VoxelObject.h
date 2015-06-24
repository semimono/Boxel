#pragma once

#include "GameFramework/Actor.h"
#include "WorldListener.h"
#include "VoxelObject.generated.h"


UCLASS()
class BOXEL_API AVoxelObject : public AActor
{
	GENERATED_BODY()

public:
	AVoxelObject();

	virtual void BeginPlay() override;

	virtual void Tick(float deltaSeconds) override;

private:
	VoxelWorldListener listener;
	
};
