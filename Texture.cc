#include "Texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <stdexcept>

Texture::Texture(const char *filename) {
    glGenTextures(1, &_texture);

    auto surf = std::shared_ptr<SDL_Surface>(
            IMG_Load(filename),
            SDL_FreeSurface);
    if (surf == nullptr)
        throw std::runtime_error(
                std::string("Can't download texture: ") +
                std::string(SDL_GetError()));

    auto tex_surf = std::shared_ptr<SDL_Surface>(
            SDL_CreateRGBSurfaceWithFormat(
                    0, surf->w, surf->h, 32, SDL_PIXELFORMAT_ABGR8888),
            SDL_FreeSurface);
    if (tex_surf == nullptr)
        throw std::runtime_error(
                std::string("Can't download temporary texture: ") +
                std::string(SDL_GetError()));

    SDL_BlitSurface(surf.get(), nullptr, tex_surf.get(), nullptr);

    glBindTexture(GL_TEXTURE_2D, _texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tex_surf->w, tex_surf->h,
                      GL_RGBA, GL_UNSIGNED_BYTE, tex_surf->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture::~Texture() {
    glDeleteTextures(1, &_texture);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, _texture);
}
