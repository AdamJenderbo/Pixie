#include "LayerStack.h"

namespace Pixie
{
	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layers.push_back(layer);
		layer->OnAttach();
	}
}