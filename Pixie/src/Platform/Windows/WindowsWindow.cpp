#include "WindowsWindow.h"
#include "Pixie/Console.h"

namespace Pixie
{
	WindowsWindow::WindowsWindow(int width, int height, std::string title)
	{
        if (!glfwInit())
            Console::LogError("Could not initialize GLFW!");

        glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

        if (!glfwWindow)
        {
            glfwTerminate();
            Console::LogError("Could not create GLFW window!");   
        }

        glfwMakeContextCurrent(glfwWindow);
	}

	WindowsWindow::~WindowsWindow()
	{
        glfwTerminate();
        delete glfwWindow;
	}

    void WindowsWindow::Update()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }
}