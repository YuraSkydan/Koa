#include "PixelPhysics.h"
#include "../Transform.h"
#include "../../Core/Time.h"

PixelPhysics::PixelPhysics(Entity* owner)
	:Component(owner)
{ }

void PixelPhysics::Update()
{
	velocity.y += -10.0f * Time::DeltaTime();
}