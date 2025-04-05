// Fill out your copyright notice in the Description page of Project Settings.


#include "TAPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.h"
#include "../../Gamemodes/HubGameMode.h"
#include "../../GameInstance/UIManagerSubsystem.h"
#include "Components/WidgetInteractionComponent.h"

#pragma region "Input Handlers"
void ATAPlayerController::UpdateSensitivity(float horizontal, float vertical)
{
	_horizontalSens = horizontal;
	_verticalSens = vertical;
}

void ATAPlayerController::HandleLook(const FInputActionValue& value)
{
	const FVector rotationVector = value.Get<FVector>();

	AddYawInput(rotationVector.X * _horizontalSens);
	AddPitchInput(rotationVector.Y * _verticalSens);
}

void ATAPlayerController::HandleMove(const FInputActionValue& value)
{
	const FVector movementVector = value.Get<FVector>();

	_playerCharacter->AddMovementInput(_playerCharacter->GetActorForwardVector(), movementVector.Y);
	_playerCharacter->AddMovementInput(_playerCharacter->GetCamera()->GetRightVector(), movementVector.X);
}

void ATAPlayerController::HandleJump()
{
	_playerCharacter->UnCrouch();
	_playerCharacter->Jump();
}
void ATAPlayerController::HandleCastSpell()
{
	_playerCharacter->CastSpell();
}
void ATAPlayerController::HandleDamageSelf()
{
	_playerCharacter->DealDamage(40, FString("Self"));
}
void ATAPlayerController::HandleSpellOne()
{
	_playerCharacter->ChangeSpell(1);
}
void ATAPlayerController::HandleSpellTwo()
{
	_playerCharacter->ChangeSpell(2);
}
void ATAPlayerController::HandleSpellThree()
{
	_playerCharacter->ChangeSpell(3);
}
void ATAPlayerController::HandleSpellFour()
{
	_playerCharacter->ChangeSpell(4);
}
void ATAPlayerController::HandleSpellFive()
{
	_playerCharacter->ChangeSpell(5);
}
void ATAPlayerController::HandleSpellSix()
{
	_playerCharacter->ChangeSpell(6);
}
void ATAPlayerController::HandleChangeSpell()
{
	_playerCharacter->CycleSpell();
}
void ATAPlayerController::HandleToggleSpellSelection()
{
	if (_uiManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller failed to initialise uiManager"));
		return;
	}

	if (Cast<AHubGameMode>(GetWorld()->GetAuthGameMode()) != nullptr)
	{
		_uiManager->ToggleWidget(EWidgetType::GRIMOIRE, this);
		return;
	}

	_uiManager->ToggleWidget(EWidgetType::QUICK_SELECT, this);
}
void ATAPlayerController::HandleTogglePauseMenu()
{
	if (_uiManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller failed to initialise uiManager"));
		return;
	}

	_uiManager->ToggleWidget(EWidgetType::PAUSE_MENU, this);
}
#pragma endregion

void ATAPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (TObjectPtr<UUIManagerSubsystem> uiManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>())
	{
		_uiManager = uiManager;
		_uiManager->CreateWidgets(this);
	}

	_playerCharacter = Cast<APlayerCharacter>(aPawn);

	_playerCharacter->SetController(this);
	_horizontalSens = _playerCharacter->GetHorizontalSensitivity();
	_verticalSens = _playerCharacter->GetVerticalSensitivity();
	_movementComponent = _playerCharacter->GetCharacterMovement();

	_enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(_enhancedInputComponent, TEXT("ENHANCED_INPUT_COMPONENT is an invalid value"));

	UEnhancedInputLocalPlayerSubsystem* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(inputSubsystem, TEXT("INPUT_SUBSYSTEM is an invalid value"));

	checkf(inputMappingContext, TEXT("INPUT_MAPPING_CONTEXT is an invalid value"));
	inputSubsystem->ClearAllMappings();
	inputSubsystem->AddMappingContext(inputMappingContext, 0);

	BindActions(_enhancedInputComponent);
}

void ATAPlayerController::OnUnPossess()
{
	_enhancedInputComponent->ClearActionBindings();

	Super::OnUnPossess();
}

void ATAPlayerController::BindActions(UEnhancedInputComponent* inputComponent)
{
	checkf(actionLook, TEXT("Missing 'Look' Action"));
	inputComponent->BindAction(actionLook, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleLook);

	checkf(actionMove, TEXT("Missing 'Move' Action"));
	inputComponent->BindAction(actionMove, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleMove);

	checkf(actionJump, TEXT("Missing 'Jump' Action"));
	inputComponent->BindAction(actionJump, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleJump);

	checkf(actionTest, TEXT("Missing 'Test' Action"));
	inputComponent->BindAction(actionTest, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleCastSpell);

	checkf(actionDamageSelf, TEXT("Missing 'DamageSelf' Action"));
	inputComponent->BindAction(actionDamageSelf, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleDamageSelf);

	checkf(actionSpellOne , TEXT("Missing 'SpellOne' Action"));
	inputComponent->BindAction(actionSpellOne, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleSpellOne);

	checkf(actionSpellTwo, TEXT("Missing 'SpellTwo' Action"));
	inputComponent->BindAction(actionSpellTwo, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleSpellTwo);

	checkf(actionSpellThree, TEXT("Missing 'SpellThree' Action"));
	inputComponent->BindAction(actionSpellThree, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleSpellThree);

	checkf(actionSpellFour, TEXT("Missing 'SpellFour' Action"));
	inputComponent->BindAction(actionSpellFour, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleSpellFour);

	checkf(actionSpellFive, TEXT("Missing 'SpellFive' Action"));
	inputComponent->BindAction(actionSpellFive, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleSpellFive);

	checkf(actionSpellSix, TEXT("Missing 'SpellSix' Action"));
	inputComponent->BindAction(actionSpellSix, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleSpellSix);

	checkf(actionToggleSpellSelection, TEXT("Missing 'ToggleSpellSelection' Action"));
	inputComponent->BindAction(actionToggleSpellSelection, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleToggleSpellSelection);

	checkf(actionTogglePauseMenu, TEXT("Missing 'TogglePauseMenu' Action"));
	inputComponent->BindAction(actionTogglePauseMenu, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleTogglePauseMenu);
}


//void ATAPlayerController::HandleTurn(const FInputActionValue& value)
//{
//	float val = value.Get<float>();
//
//	AddYawInput(val * _horizontalSens);
//}
// 
//void ATAPlayerController::HandleMenuInteract()
//{
//	if (AVRCharacter* vr = Cast<AVRCharacter>(GetCharacter()))
//	{
//		vr->interactionComponent->PressPointerKey(EKeys::LeftMouseButton);
//		vr->interactionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
//	}
//}
// 
//AVRCharacter* vr = Cast<AVRCharacter>(aPawn);
// 
//if (vr != nullptr)
//{
//	_uiManager->CreateWidgets(this, vr->widgetComponent);
//}
// 
//if (vr != nullptr)
//{
//	_playerCharacter = vr;
//	_isVR = true;
//}
// 
//If the VRCharacter is used, bind VR input mappings.
//if (_isVR == true)
//{
//	checkf(VR_inputMappingContext, TEXT("VR INPUT_MAPPING_CONTEXT is an invalid value"));
//	inputSubsystem->ClearAllMappings();
//	inputSubsystem->AddMappingContext(VR_inputMappingContext, 0);

//	BindVRActions(_enhancedInputComponent);
//}
// 
//void ATAPlayerController::BindVRActions(UEnhancedInputComponent* inputComponent)
//{
//	checkf(VR_actionMove, TEXT("Missing 'VR_actionMove' Action"));
//	inputComponent->BindAction(VR_actionMove, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleMove);
//
//	checkf(VR_actionTurn, TEXT("Missing 'VR_actionTurn' Action"));
//	inputComponent->BindAction(VR_actionTurn, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleTurn);
//
//	checkf(VR_actionCastSpell, TEXT("Missing 'VR_actionCastSpell' Action"));
//	inputComponent->BindAction(VR_actionCastSpell, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleCastSpell);
//
//	checkf(VR_actionToggleSpellSelection, TEXT("Missing 'VR_actionToggleSpellSelection' Action"));
//	inputComponent->BindAction(VR_actionToggleSpellSelection, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleToggleSpellSelection);
//
//	checkf(VR_actionTogglePauseMenu, TEXT("Missing 'VR_actionTogglePauseMenu' Action"));
//	inputComponent->BindAction(VR_actionTogglePauseMenu, ETriggerEvent::Triggered, this, &ATAPlayerController::HandleTogglePauseMenu);
//
//	checkf(VR_actionMenuInteract, TEXT("Missing 'VR_actionMenuInteract' Action"));
//	inputComponent->BindAction(VR_actionMenuInteract, ETriggerEvent::Completed, this, &ATAPlayerController::HandleMenuInteract);
//}
