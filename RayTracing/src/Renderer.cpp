#include "Renderer.h"

#include "Walnut/Random.h"

void Renderer::OnResize(uint32_t width, uint32_t height)
{
	if (m_FinalImage) {
		// No resize necessary
		if (m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height) {
			return;
		}

		m_FinalImage->Resize(width, height);
	}
	else {
		m_FinalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}
	
	delete[] m_ImageData;
	m_ImageData = new uint32_t[width * height];
}

void Renderer::Render()
{
	// Render every pixel
	uint32_t height = m_FinalImage->GetHeight();
	uint32_t width = m_FinalImage->GetWidth();

	for (uint32_t y = 0; y < height; ++y) {
		for (uint32_t x = 0; x < width; ++x) {
			glm::vec2 coord = { x / (float)width, y / (float)height };
			
			m_ImageData[x + y * width] = PerPixel(coord);
		}
	}
	m_FinalImage->SetData(m_ImageData);

}

uint32_t Renderer::PerPixel(glm::vec2 coord)
{
	uint8_t r = (uint8_t)(coord.x * 255.0f);
	uint8_t g = (uint8_t)(coord.y * 255.0f);
	
	return 0xff000000 | (g << 8) | r;
}
