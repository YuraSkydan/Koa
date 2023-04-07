#include "LayerStack.h"

void LayerStack::UpdateLayers()
{
	for (auto layer : m_Stack)
	{
		layer->OnUpdate();
	}
}

void LayerStack::PushLayer(const std::shared_ptr<Layer>& layer)
{
	layer->OnAttach();
	m_Stack.push_back(layer);
}

void LayerStack::PopLayer(const std::shared_ptr<Layer>& layer)
{
	for (auto it = m_Stack.begin(); it != m_Stack.end(); ++it)
	{
		if (*it == layer)
		{
			layer->OnDetach();
			m_Stack.erase(it);
			break;
		}
	}
}

void LayerStack::PopLayer(Layer* layer)
{
	for (auto it = m_Stack.begin(); it != m_Stack.end(); ++it)
	{
		if (it->get() == layer)
		{
			layer->OnDetach();
			m_Stack.erase(it);
			break;
		}
	}
}

void LayerStack::PopBackLayer()
{
	m_Stack.back()->OnDetach();
	m_Stack.pop_back();
}

LayerStack::~LayerStack()
{
	for (auto layer : m_Stack)
	{
		layer->OnDetach();
	}

	m_Stack.clear();
}