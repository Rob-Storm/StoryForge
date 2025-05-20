#include "DamageHelper.h"

int32 UDamageHelper::GetDamageVelocity(const FVector& Velocity, float DamageThreshold, float DamageScale, int32 MaxDamage)
{
	//float Speed = Velocity.Size();
	float Speed = Velocity.Z;

	float RawDamage = (Speed - DamageThreshold) * DamageScale;

	int32 FinalDamage = FMath::Clamp(FMath::FloorToInt(RawDamage), 0, MaxDamage);

	return FinalDamage;
}
