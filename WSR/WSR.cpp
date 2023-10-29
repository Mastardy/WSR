#include "WSR.hpp"

constexpr int Width = 960;
constexpr int Height = 540;

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    Window window(Width, Height);
    Renderer softwareRenderer(720, 415);

    window.SetFramebufferSizeCallback(FrameBufferSizeCallback);
       
    Line line(Point(5, 5), Point(200, 200), Color(0, 0, 0, 0));
    line.Render(softwareRenderer);

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