#include "functions.h"

#include <cmath>
#include <vector>
#include <algorithm>


void line(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color)
{
    bool transpose = false;
    if (std::abs(x0-x1) < std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        transpose = true;
    }
    
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    
    const int dx = x1 - x0;
    const int dy = y1 - y0;
    const int delta_e = std::abs(dy) * 2;
    int error = 0;
    int y = y0;
    for (int x = x0; x <= x1; ++x) {
        image.set(transpose ? y : x,
                  transpose ? x : y,
                  color);
        
        error += delta_e;
        
        if (error > dx ){
            y += (y1 > y0 ? 1 : -1);
            error -= dx*2;
        }
    }
    
}

void line( const Vector2i& v0, const Vector2i& v1, TGAImage& image, const TGAColor& color ) 
{
    line(v0.x, v0.y, v1.x, v1.y, image, color);
}



void draw_triangle( const Vector2i& v0, 
                    const Vector2i& v1, 
                    const Vector2i& v2, 
                    TGAImage& image, 
                    const TGAColor& color) 
{
    std::vector<Vector2i> vertices{v0, v1, v2};
    std::sort(vertices.begin(), vertices.end(), [](const Vector2i& l, const Vector2i& r) { return l.y < r.y; });

    const auto& rv0 = vertices[0];
    const auto& rv1 = vertices[1];
    const auto& rv2 = vertices[2];
    const int height = rv2.y - rv0.y;
    

    int segment_height = rv1.y-rv0.y + 1;
    for( int y = rv0.y; y <= rv1.y; ++y) {
        const float alpha = static_cast<float>(y - rv0.y) / height;
        const float beta = static_cast<float>(y - rv0.y) / segment_height;

        Vector2i A = rv0 + (rv2 - rv0)* alpha;
        Vector2i B = rv0 + (rv1 - rv0) * beta;
        if (A.x > B.x) std::swap(A, B);
        for (int x = A.x; x <= B.x; ++x)  {
            image.set(x, y, TGAColor(255, 0,   0,   255));
        } 
    }

    segment_height = rv2.y - rv1.y + 1;
    for(int y = rv1.y; y <= rv2.y; ++y) {
        const float alpha = static_cast<float>(y - rv0.y) / height;
        const float beta = static_cast<float>(y - rv1.y) / segment_height;

        Vector2i A = rv0 + (rv2 - rv0)* alpha;
        Vector2i B = rv1 + (rv2 - rv1) * beta;
        if (A.x > B.x) std::swap(A, B);
        for (int x = A.x; x <= B.x; ++x)  {
            image.set(x, y, TGAColor(255, 0,   0,   255));
        }
    }
}