#include "WindowsWindow.h"
#include "Pixie/Console.h"
#include "Pixie/Event/ApplicationEvent.h"

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

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            Console::LogError("Failed to initialize OpenGL context");
        }

        glfwSetWindowUserPointer(glfwWindow, &data);


        glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent e;
            data.EventCallback(e);
        });
	}

	WindowsWindow::~WindowsWindow()
	{
        glfwTerminate();
        delete glfwWindow;
	}

    void WindowsWindow::OnUpdate()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    void WindowsWindow::SetEventCallback(std::function<void(Event&)> callback)
    {
        data.EventCallback = callback;
    }
}