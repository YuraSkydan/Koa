#include "Core/Engine.h"
#include "Sandbox/RenderingExample2D.h"
#include "Sandbox/RenderingExample3D.h"
#include "Sandbox/PhysicsExample.h"
#include "Sandbox/RaytracerExample.h"
#include "Sandbox/PixelPhysicsExample.h"

int main()
{
	Engine engine(200, 200, 2, 2, Engine::WindowContext::Console);

	engine.AttachLayer(std::make_shared<RenderingExample2D>());
	//engine.AttachLayer(std::make_shared<RenderingExample3D>());
	//engine.AttachLayer(std::make_shared<PhysicsExample>());
	//engine.AttachLayer(std::make_shared<RaytracerExample>());
	//engine.AttachLayer(std::make_shared<PixelPhysicsExample>());
	//std::thread render(&Engine::Render, &engine);

	engine.Run();

	//render.join();

	return 0;
}