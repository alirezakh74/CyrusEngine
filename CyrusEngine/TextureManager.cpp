#include "TextureManager.h"

#include <SDL2/SDL_image.h>

TextureManager* TextureManager::s_pInstance = 0;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

TextureManager* TextureManager::Instance()
{
	if (s_pInstance == 0)
	{
		s_pInstance = new TextureManager();
	}

	return s_pInstance;
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* renderer)
{
	if (m_textureMap[id] != nullptr)
	{
		return true;
	}

	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0)
	{
		std::cout << "load image failed " << IMG_GetError() << std::endl;
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

	return false;
}

void TextureManager::draw(std::string id, int x, int y, int w, int h, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect, destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.x = x;
	destRect.y = y;
	srcRect.w = destRect.w = w;
	srcRect.h = destRect.h = h;

	SDL_RenderCopyEx(renderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int w, int h, int currentRow, int currentFrame, int rotation, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect, destRect;

	srcRect.x = (currentFrame - 1) * w;
	srcRect.y = (currentRow - 1) * h;

	destRect.x = x;
	destRect.y = y;

	srcRect.w = destRect.w = w;
	srcRect.h = destRect.h = h;

	SDL_RenderCopyEx(renderer, m_textureMap[id], &srcRect, &destRect, rotation, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int w, int h, int currentRow, int currentFrame, int rotation, float scale, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect, destRect;

	srcRect.x = (currentFrame - 1) * w;
	srcRect.y = (currentRow - 1) * h;

	destRect.x = x;
	destRect.y = y;

	srcRect.w = w;
	srcRect.h = h;

	destRect.w = w * scale;
	destRect.h = h * scale;

	SDL_RenderCopyEx(renderer, m_textureMap[id], &srcRect, &destRect, rotation, 0, flip);

}

void TextureManager::drawTile(std::string id, int margin, int
	spacing, int x, int y, int width, int height, int currentRow,
	int currentFrame, SDL_Renderer* pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = margin + (spacing + width) * currentFrame; // current frame means columns
	srcRect.y = margin + (spacing + height) * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	//srcRect = { 2, 2, 32, 32 };

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
		&destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::clearFromTextureMap(std::string id)
{
	// here we should destroy texture, while book didn't do this(memory leaks)
	SDL_DestroyTexture(m_textureMap.find(id)->second);
	m_textureMap.erase(id);
}

SDL_Texture* TextureManager::getTexture(std::string id)
{
	return m_textureMap[id];
}

void TextureManager::clearAllTextures()
{
	for (auto itr = m_textureMap.begin(); itr != m_textureMap.end(); ++itr)
	{
		SDL_DestroyTexture(itr->second);
		m_textureMap.erase(itr);
	}
	m_textureMap.clear();
}
