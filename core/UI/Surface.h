#pragma once
#include <string>
namespace core {

    class Surface {
    public:
        Surface();

    public:
        static SDL_Surface* OnLoad(const std::string& File);

        static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);

        static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);
        static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);
        static void ClearSurface(SDL_Surface* surface, Uint32 colour);
    };
}