#include <SDL/SDL.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include "Surface.h"
#include "ProcessLogger.h"
#include "Exception.h"

Surface::Surface() {
}

SDL_Surface* Surface::OnLoad(const std::string& File) {
    logger << "Loading " << File << std::endl;

    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;

    if ((Surf_Temp = SDL_LoadBMP(File.c_str())) == NULL) {
        throw Exception::CreateAndLog(POSITION, std::string("loadImage: ") + File);
    }

    Surf_Return = SDL_DisplayFormat(Surf_Temp);
    SDL_FreeSurface(Surf_Temp);

    return Surf_Return;
}

bool Surface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {
    if (Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }

    SDL_Rect DestR;

    DestR.x = X;
    DestR.y = Y;

    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

    return true;
}

bool Surface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H) {
    if (Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }

    SDL_Rect DestR;
    DestR.x = X;
    DestR.y = Y;
    SDL_Rect SrcR;
    SrcR.x = X2;
    SrcR.y = Y2;
    SrcR.w = W;
    SrcR.h = H;

    SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

    return true;
}

bool Surface::Transparent(SDL_Surface* Surf_Dest, int R, int G, int B) {
    if (Surf_Dest == NULL)
        return false;

    SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(Surf_Dest->format, R, G, B));

    return true;
}

void Surface::ClearSurface(SDL_Surface* surface, Uint32 colour){
    SDL_FillRect(surface, NULL, colour);
}