#include <raylib.h>
#include <stdlib.h>
#include "shapes.h"

void DrawLineCustom(int startX, int startY, int endX, int endY, Color color) {
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    int sx = (startX < endX) ? 1 : -1;
    int sy = (startY < endY) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        DrawPixel(startX, startY, color);
        if (startX == endX && startY == endY) break;
        int e2 = err * 2;
        if (e2 > -dy) { err -= dy; startX += sx; }
        if (e2 < dx) { err += dx; startY += sy; }
    }
}

void DrawSquareCustom(int posX, int posY, int size, Color color) {
    for (int y = posY; y < posY + size; y++) {
        for (int x = posX; x < posX + size; x++) {
            DrawPixel(x, y, color);
        }
    }
}

void DrawRectangleCustom(int posX, int posY, int width, int height, Color color) {
    for (int y = posY; y < posY + height; y++) {
        for (int x = posX; x < posX + width; x++) {
            DrawPixel(x, y, color);
        }
    }
}

void DrawCircleCustom(int centerX, int centerY, float radius, Color color) {
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius * 2);

    while (x >= y) {
        DrawPixel(centerX + x, centerY + y, color);
        DrawPixel(centerX + y, centerY + x, color);
        DrawPixel(centerX - y, centerY + x, color);
        DrawPixel(centerX - x, centerY + y, color);
        DrawPixel(centerX - x, centerY - y, color);
        DrawPixel(centerX - y, centerY - x, color);
        DrawPixel(centerX + y, centerY - x, color);
        DrawPixel(centerX + x, centerY - y, color);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (radius * 2);
        }
    }
}