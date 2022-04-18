#pragma once
#include "Pixie/Renderer/Texture.h"

#include <filesystem>

namespace Pixie 
{

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();
	private:
		std::filesystem::path currentDirectory;

		Ref<Texture2D> directoryIcon;
		Ref<Texture2D> fileIcon;
	};

}
