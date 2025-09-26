# FT_Sprint
 A sprint mechanic for the Mechanics and Gameplay module.

## Overview

This project involves implementing a sprint mechanic, but it currently lacks input for initiating sprints. Create and assign an input action to enable sprinting:
- Create the input action.
- Update the input mapping context.

## Challenges
- Experiment with different input types, such as toggle and hold.
- Connect Xbox controllers for testing; PS controllers can work but are not natively supported.
- Develop gameplay iterations for the sprint mechanic:
  - Easy: Limit sprint duration with stamina, including actions like jumping.
  - Medium: Introduce acceleration and deceleration for variable speed.
  - Hard: Adjust speed to influence the player’s turning radius.

## Hints and Tips

### Find content
Look in All->Content->ThirdPerson->Input.
Scripts are located in All->C++ Classes->FT_Sprint.

###
Check the scripts open properly, if in visual studio you open the script and the solution explorer is blank, and the tab in the top left says miscellaneous files, you need to go to the .uproject file right click->Show more options->Generate Visual Studio Solution.

### Coding
Remember, the header file declares variables and methods.
The C++ file implements the methods. implementing the Methods.

Your main focus should be adding the bindings in FT_SprintCharacter.cpp lines 95-97

For the medium and hard challenges look in the FT_SprintCharacter Constructor (AFT_SprintCharacter::AFT_SprintCharacter()), notice the template shows us how to change key values.

## Changes from me:

### FT_SprintCharacter.h

lines 47-49 added the input action pointer
/** Connah Addition 1: Sprint Input Action */
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
UInputAction* SprintAction;

lines 63-65 added a start and end sprint function declarations
/** Connah Addition 2 methods to ensure we handle sprint enable and disable */
void SprintStart(const FInputActionValue& Value); 
void SprintStop(const FInputActionValue& Value);

### FT_SprintCharacter.cpp
lines 95-97 Added the binding for the input action
//** Connah binding implementation **/ 
EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AFT_SprintCharacter::SprintStart);
EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AFT_SprintCharacter::SprintStop);

Lines 141-155 Added some code for the start and end sprinting
/** Connah methods implementation */
void AFT_SprintCharacter::SprintStart(const FInputActionValue& Value)
{
	// we could set speeds, but i like scalers 
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed * 2;
	// make it so they have a speed up route
	GetCharacterMovement()->MinAnalogWalkSpeed = GetCharacterMovement()->MinAnalogWalkSpeed * 3;
}

void AFT_SprintCharacter::SprintStop(const FInputActionValue& Value)
{
	// Reset the speeds
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed / 2;
	GetCharacterMovement()->MinAnalogWalkSpeed = GetCharacterMovement()->MinAnalogWalkSpeed / 3;
}