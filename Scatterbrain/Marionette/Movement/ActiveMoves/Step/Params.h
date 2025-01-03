#pragma once

// Step will use this params on start.

struct FAM_Step_Params
{
	FVector TargetPoint; // The place where the foot should end up.
	uint8 Act;
	uint8 Sup;

	float StepSpeed;
};