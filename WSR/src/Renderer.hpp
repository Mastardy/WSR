#include <GLFW/glfw3.h>

class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	void Update();
	void Resize(int width, int height);

	int width;
	int height;
	GLubyte* data;
};