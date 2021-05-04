#pragma once

#include <SDL2/SDL.h>

#include <map>
#include <iostream>

class TextureManager
{
public:
	static TextureManager* Instance();

	bool load(std::string fileName, std::string id, SDL_Renderer* renderer);
	void draw(std::string id, int x, int y, int w, int h, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int w, int h, int currentRow, int currentFrame, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawTile(std::string id, int margin, int
		spacing, int x, int y, int width, int height, int currentRow,
		int currentFrame, SDL_Renderer* pRenderer);

	void clearFromTextureMap(std::string id);

	SDL_Texture* getTexture(std::string id);

	void clearAllTextures();

private:
	TextureManager();
	~TextureManager();

	static TextureManager* s_pInstance;

	std::map<std::string, SDL_Texture*> m_textureMap;
};

typedef TextureManager TheTextureManager;

