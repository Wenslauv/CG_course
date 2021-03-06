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
    if (v0.y == v1.y && v1.y == v2.y) 
        return;

    std::vector<Vector2i> vertices{v0, v1, v2};
    std::sort(vertices.begin(), vertices.end(), [](const Vector2i& l, const Vector2i& r) { return l.y < r.y; });

    const auto& rv0 = vertices[0];
    const auto& rv1 = vertices[1];
    const auto& rv2 = vertices[2];
    const int height = rv2.y - rv0.y;

    
    for( int y = 0; y < height; ++y) {
        const bool is_second_half = y > rv1.y - rv0.y || rv1.y == rv0.y;
        const int segment_height = is_second_half 
            ? rv2.y - rv1.y
            : rv1.y - rv0.y;

        const float alpha = static_cast<float>(y) / height;
        const float beta = static_cast<float>(y - (is_second_half ? rv1.y - rv0.y :  0)) / segment_height;

        Vector2i A = rv0 + (rv2 - rv0)* alpha;
        Vector2i B = is_second_half 
            ? rv1 + (rv2 - rv1) * beta
            : rv0 + (rv1 - rv0) * beta;

        if (A.x > B.x) 
            std::swap(A, B);
        for (int x = A.x; x <= B.x; ++x)  {
            image.set(x, rv0.y + y, color);
        } 
    }
}


void triangle(  Vector3i p0, 
                Vector3i p1, 
                Vector3i p2, 
                TGAImage& image, 
                const TGAColor& color,
                std::vector<int>& zbuff,
                int width)
{
    if (p0.y == p1.y && p1.y == p2.y) 
        return;

    if (p0.y > p1.y) std::swap(p0, p1);
    if (p0.y > p2.y) std::swap(p0, p2);
    if (p1.y > p2.y) std::swap(p1, p2);


    const int height = p2.y - p0.y;

    
    for( int y = 0; y < height; ++y) {
        const bool is_second_half = y > p1.y - p0.y || p1.y == p0.y;
        const int segment_height = is_second_half 
            ? p2.y - p1.y
            : p1.y - p0.y;

        const float alpha = static_cast<float>(y) / height;
        const float beta = static_cast<float>(y - (is_second_half ? p1.y - p0.y :  0)) / segment_height;

        Vector3i A = p0 + Vector3f(p2 - p0)* alpha;
        Vector3i B = is_second_half 
            ? p1 + Vector3f(p2 - p1) * beta
            : p0 + Vector3f(p1 - p0) * beta;

        if (A.x > B.x) 
            std::swap(A, B);
        const float s = static_cast<float>(B.x - A.x);
        for (int x = A.x; x <= B.x; ++x)  {
            const float phi = B.x == A.x 
            ? 1.0
            : static_cast<float>(x - A.x) / s;

            const Vector3f P = Vector3f(A) + Vector3f(B-A) * phi; 
            const int idx = P.x + P.y * width;

            if (zbuff[idx] < P.z) {
                zbuff[idx] = P.z;
                image.set(P.x, P.y, color);
            }
        } 
    }
}



void rasterize( Vector2i v0,
                Vector2i v1, 
                TGAImage& image,
                const TGAColor& color,
                std::vector<int>& ybuffer)
{
    if (v0.x > v1.x) 
        std::swap(v0, v1);

    const auto size = static_cast<float>(v1.x - v0.x);
    for (int i = v0.x; i <= v1.x; ++i) {
        const float delta = ( i - v0.x) / size;
        const int y = v0.y * (1 - delta) + v1.y * delta;
        
        if (ybuffer[i] < y) {
            ybuffer[i] = y;
            image.set(i, 0, color);
        }
    }   
}