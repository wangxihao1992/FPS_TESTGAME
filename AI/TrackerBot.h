// This code was written by 康子秋

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TrackerBot.generated.h"
// 
 class UHealthComponent;
 class UStaticMeshComponent;
 class UMaterialInstanceDynamic;
 class USoundCue;
 class USphereComponent;

UCLASS()
class FPS_TESTGAME_API ATrackerBot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATrackerBot();

	UPROPERTY(VisibleDefaultsOnly, category = "component")
		UStaticMeshComponent * BotMeshComp;
	UPROPERTY(VisibleDefaultsOnly, category = "component")
		UHealthComponent * HealthComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "component")
		USphereComponent * SphereComp;

	//UPROPERTY(VisibleDefaultsOnly, category = "component")
	 //   class UFloatingPawnMovement * FloatMoveComp;

	//下一个寻路导航点
	FVector NextPathPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "BaseVolume")
		float MovementForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseVolume")
		bool bUseVelocityChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseVolume")
		float RequiredDistanceToTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseVolume")
		float ExplosionDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseVolume")
		float ExplosionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseVolume")
		float DamageSelfVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem * ExplosionEffect;		//爆炸特效
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParticleSound")
		USoundCue * ExplosionSound;		//爆炸音效
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParticleSound")
		USoundCue * SelfDestructSound;		//自杀音效
	
	UMaterialInstanceDynamic* MatInst;

	FTimerHandle TimeHandle_SelfDamage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector FindNextPathPoint();
	UFUNCTION()
	void HanldTakeDamage(UHealthComponent* HealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void SelfDestruct();

	void DamageSelf();

	bool bExploded;
	bool bStartedSelfDestruction;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) ;
};
