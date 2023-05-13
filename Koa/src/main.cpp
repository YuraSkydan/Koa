#include "Core/Engine.h"
#include "Sandbox/RenderingExample.h"
#include "Sandbox/PhysicsExample.h"
#include "Sandbox/RaytracerExample.h"
#include "Sandbox/PixelPhysicsExample.h"

int main()
{
	Engine engine(50, 50, 10, 10, Engine::WindowContext::Console);

	//engine.AttachLayer(std::make_shared<RenderingExample>());
	//engine.AttachLayer(std::make_shared<PhysicsExample>());
	//engine.AttachLayer(std::make_shared<RaytracerExample>());
	engine.AttachLayer(std::make_shared<PixelPhysicsExample>());
	//std::thread render(&Engine::Render, &engine);

	engine.Run();

	//render.join();

	return 0;
}