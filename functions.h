#pragma once

#include "tgaimage.h"
#include "geometry.h"

void line(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color); 

void draw_triangle( const Vector2i& v0, 
                    const Vector2i& v1, 
                    const Vector2i& v2, 
                    TGAImage& image, 
                    const TGAColor& color);
