#include "Window.h"

int main(void)
{
    Pixie::Window* window = Pixie::Window::Create(640, 480, "Pixie Engine");

    while (exit)
    {
        window->Update();
    }

    delete window;
    return 0;
}