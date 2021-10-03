// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrowText.h"

// Sets default values
AArrowText::AArrowText()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_MtrlBillboard = CreateDefaultSubobject<UMaterialBillboardComponent>(TEXT("Billboard"));
	m_Text = CreateDefaultSubobject< UTextRenderComponent>(TEXT("TEXT"));

	SetRootComponent(m_MtrlBillboard);
	m_Text->SetupAttachment(m_MtrlBillboard);
	m_Text->SetText(TEXT("Arrow"));

	//static ConstructorHelpers::FObjectFinder<UMaterialInstance> MtrlAsset(TEXT("MaterialInstanceConstant'/Game/Etc/MT_ArrowInst.MT_ArrowInst'"));
	//if (MtrlAsset.Succeeded())
	//{
	//	m_MtrlBillboard->AddElement(MtrlAsset.Object, nullptr, false, 30.f, 30.f, nullptr);
	//	m_MtrlBillboard->SetMaterial(0, MtrlAsset.Object);
	//	//m_MtrlBillboard->CreateDynamicMaterialInstance(0);
	//}
}

// Called when the game starts or when spawned
void AArrowText::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArrowText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

