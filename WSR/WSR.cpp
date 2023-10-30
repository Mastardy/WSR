#include "WSR.hpp"

constexpr int WindowWidth = 960;
constexpr int WindowHeight = 540;
constexpr int Width = 720;
constexpr int Height = 415;

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    Window window(WindowWidth, WindowHeight);
    Renderer softwareRenderer(Width, Height);

    window.SetFramebufferSizeCallback(FrameBufferSizeCallback);

    softwareRenderer.SetColor({255, 0, 0, 0});
    softwareRenderer.DrawTriangle(Point(Width/2, Height/3), Point(Width/4, Height*2/3), Point(Width*3/4, Height*2/3));

	while (!window.ShouldClose())
	{
        std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
        
        window.ProcessInput();
        window.UpdateTexture(softwareRenderer.width, softwareRenderer.height, softwareRenderer.data);
        window.Update();
		
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        //std::cout << "Delta Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << std::endl;
	}

	return 0;
}