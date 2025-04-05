// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellDecorator.h"
#include "SelfSpellDecorator.generated.h"

/**
 * 
 */
UCLASS()
class THE_ASCENDANCE_API USelfSpellDecorator : public USpellDecorator
{
	GENERATED_BODY()

//Casts a spell that applies effects to the caster. If AOE is selected, will apply the AOE at the casters location. 
public:

	class THE_ASCENDANCE_API Builder
	{
		TWeakObjectPtr<USelfSpellDecorator> decorator;

	public:

		Builder(ISpell* data)
		{
			decorator = NewObject<USelfSpellDecorator>();
			decorator->Decorate(data);
			data->SetOwnerSpell(decorator.Get());
		}
		ISpell* Build()
		{
			return decorator.Get();
		}
	};

	virtual bool CastSpell() override;
};
