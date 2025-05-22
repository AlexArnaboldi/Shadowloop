		
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportDoor.generated.h"

class ATeleportFloor;
class UCheckPuzzleComponent;
class ACustomPlayer;
class UTimelineComponent;
class UBoxComponent;

UCLASS()
class SHADOWLOOP_API ATeleportDoor : public AActor
{
	GENERATED_BODY()

protected:
	// ------------------------------ Componets ------------------------------
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Components")
	TObjectPtr<USceneComponent> Root = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Components")
	TObjectPtr<USceneComponent> SetScale = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Components")
	TObjectPtr<UStaticMeshComponent> DoorFrameMesh = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Components")
	TObjectPtr<UStaticMeshComponent> DoorMesh = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Components")
	TObjectPtr<UBoxComponent> Box = nullptr;
protected:
	// ------------------------------ Variables ------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Teleport")
	TObjectPtr<ATeleportFloor> FloorToCheck = nullptr;
	
	UPROPERTY(BlueprintReadWrite, Category= "Components | Setup Door")
	bool bIsTeleport = false;

	// ------------------------- Timeline and opening ------------------------------
	UPROPERTY(EditDefaultsOnly, Category= "Components | Timeline")
	TObjectPtr<UCurveFloat> DoorCurve = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category= "Components | Angle Open/Close")
	float AngleDoorOpenCLose = 0.f;
	
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<ACustomPlayer> Player = nullptr;
private:
	UPROPERTY()
	TObjectPtr<UTimelineComponent> DoorTimeline = nullptr;
	
	FRotator StartRotation = FRotator(0.f, 0.f, 0.f);
	FRotator OpenRotation = FRotator(0.f, 0.f, 0.f);

	bool bIsMoving = false;
	bool bOpenSide = false;
	bool bIsOpen = false;
public:
	bool GetIsLevelUp() const { return bIsTeleport; }
	void SetIsLevelUp(bool InIsLevelUp) { bIsTeleport = InIsLevelUp; }

	ATeleportDoor();

protected:
	virtual void BeginPlay() override;

private:
	void WhichSideOpen();
	
	UFUNCTION()
	void OpenCloseDoorTimeline(float Alpha);
	
	UFUNCTION()
	void FinishTimeline();
	
	// *void TimeLineDoor();*
	UFUNCTION(BlueprintCallable)
	void CallPlayerTeleport();
	
	UFUNCTION(BlueprintCallable)
	void OpenDoor();
	
	UFUNCTION(BlueprintCallable)
	void CloseDoor();
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void LevelSequenceEvent();


// ------------------- Prompt ------------------- //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Components")
	TObjectPtr<UBoxComponent> PromptBox = nullptr;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void Tick(float DeltaSeconds) override;

private:
	UFUNCTION()
	void ActivatePrompt();

	UPROPERTY(EditDefaultsOnly, Category = "Prompt")
	float PromptTolerance = 10.f;

	int PromptOffset = 120;
	bool bIsPlayerInPromptBox = false;
	bool bIsPlayerLookingAtDoor = false;
};
