#include "WSR.hpp"

constexpr int WindowWidth = 960;
constexpr int WindowHeight = 540;
constexpr int Width = 960;
constexpr int Height = 540;

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    Window window(WindowWidth, WindowHeight);
    Renderer softwareRenderer(Width, Height);

    window.SetFramebufferSizeCallback(FrameBufferSizeCallback);

    softwareRenderer.SetColor(Color(255, 0, 0, 0));
    softwareRenderer.DrawTriangle(Point(10, 70), Point(50, 160), Point(70, 80));
    softwareRenderer.SetColor({255, 255, 255, 0});
    softwareRenderer.DrawTriangle({ 180, 50 }, { 150, 1 }, { 70, 180 });
    softwareRenderer.SetColor({ 0, 255, 0, 0 });
    softwareRenderer.DrawTriangle({ 180, 150 }, { 120, 160 }, { 130, 180 });


	while (!window.ShouldClose())
	{
        std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
        
        window.ProcessInput();
        window.UpdateTexture(softwareRenderer.width, softwareRenderer.height, softwareRenderer.data);
        window.Update();
		
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::cout << "Delta Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << std::endl;
	}

	return 0;
}