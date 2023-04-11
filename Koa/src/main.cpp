#include "Core/Engine.h"
#include "Sandbox/RenderingExample.h"
#include "Sandbox/PhysicsExample.h"
#include "Sandbox/RaytracerExample.h"

#include <span>

int main()
{
	std::span<int> test;
	

	Engine engine;

	//engine.AttachLayer(std::make_shared<RenderingExample>());
	engine.AttachLayer(std::make_shared<PhysicsExample>());
	//engine.AttachLayer(std::make_shared<RaytracerExample>());
	//std::thread render(&Engine::Render, &engine);

	engine.Run();

	//render.join();

	return 0;
}