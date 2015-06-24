
#include "BoxelPrivatePCH.h"
#include "VoxelObject.h"

using namespace std;
//using namespace Vox;


AVoxelObject::AVoxelObject() : listener(this) {
	PrimaryActorTick.bCanEverTick = true;
}

void AVoxelObject::BeginPlay() {
	Super::BeginPlay();


}

void AVoxelObject::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	// TODO: remove this
	UE_LOG(LogBoxel, Log, TEXT("Ticked"));
}