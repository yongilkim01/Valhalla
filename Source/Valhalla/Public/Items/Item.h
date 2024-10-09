// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemTypes.h"
#include "Item.generated.h"

class UBoxComponent;
class USphereComponent;
/**
* 모든 아이템 관련 클래스들의 최상위 부모 클래스.
*/
UCLASS()
class VALHALLA_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

	virtual void AttachItem(USceneComponent* TargetSceneComp, FName SocketName) {}
	//virtual void Equip(USceneComponent* EquipTargetMesh, FName AttachSocketName);
protected:
	//virtual void BeginPlay() override;
	///**
	// * SphereCollision와 플레이어가 겹쳤을 때 실행되는 메소드.
	// *
	// * @param OverlappedComponent: 겹침이 발생한 구체 컴포넌트.
	// * @param OtherActor: 구체와 겹친 다른 액터.
	// * @param OtherComp: 구체와 겹친 다른 액터의 컴포넌트.
	// * @param OtherBodyIndex: 겹친 바디의 인덱스.
	// * @param bFromSweep: 스윕이 발생했는지 여부.
	// * @param SweepResult: 스윕에 대한 추가 정보(겹침 발생 위치, 히트 결과 등).
	// */
	//UFUNCTION()
	//virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	///**
	// * SphereCollision와 플레이어가 겹침을 끝냈을 때 호출되는 메소드.
	// *
	// * @param OverlappedComponent: 겹침이 끝난 구체 컴포넌트.
	// * @param OtherActor: 구체와 겹침이 끝난 다른 액터.
	// * @param OtherComp: 구체와 겹침이 끝난 다른 액터의 컴포넌트.
	// * @param OtherBodyIndex: 겹친 바디의 인덱스.
	// */
	//UFUNCTION()
	//virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public: // 게터 세터
	FORCEINLINE UBoxComponent* GetItemCollisionBox() const { return ItemCollisionBox; }

protected: // Protected 변수
	/** 아이템 메쉬 멤버 변수 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponComponent")
	UStaticMeshComponent* ItemMesh;
	/** 아이템 콜리전 멤버 변수 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponComponent")
	UBoxComponent* ItemCollisionBox;
	/** 아이템 타입 변수 */
	UPROPERTY(EditDefaultsOnly, Category = "ItemData")
	EItemType ItemType = EItemType::EIT_None;
};
