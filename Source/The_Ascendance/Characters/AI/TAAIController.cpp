// Fill out your copyright notice in the Description page of Project Settings.


#include "TAAIController.h"
#include "Navigation/PathFollowingComponent.h"

void ATAAIController::SetDestination(const FVector destination)
{
	_currentDestination = destination;

	FAIMoveRequest moveTo;
	moveTo.SetAcceptanceRadius(50);
	moveTo.SetGoalLocation(_currentDestination);

	MoveTo(moveTo);
}

void ATAAIController::SetPauseMovement(bool val)
{
	if (val == true)
	{
		PauseMove(FAIRequestID::CurrentRequest);
		return;
	}

	ResumeMove(FAIRequestID::CurrentRequest);
}

void ATAAIController::ClearDestination()
{
	_currentDestination = FVector::ZeroVector;
	StopMovement();
}

FVector ATAAIController::GetCurrentDestination() const
{
	return _currentDestination;
}

bool ATAAIController::HasPath() const
{
	return IsFollowingAPath();
}
