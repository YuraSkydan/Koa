#pragma once
#include <memory>
#include <vector>
#include "Layer.h"

class LayerStack
{
public:
	std::vector<std::shared_ptr<Layer>> m_Stack;

public:
	LayerStack() = default;

	void UpdateLayers();

	void PushLayer(const std::shared_ptr<Layer>& layer);
	void PopLayer(const std::shared_ptr<Layer>& layer);
	void PopLayer(Layer* layer);
	void PopBackLayer();

	~LayerStack();
};