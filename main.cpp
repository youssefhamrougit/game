#include <raylib.h>
#include <math.h> 
#include <cmath>

enum direction  { UP , DOWN , LEFT , RIGHT };

int main() {
    // Game window
    InitWindow(960, 450, "Down Below");
    SetTargetFPS(60);

    // Player position and speed
    float x = 480, y = 270, speed = 200;
    direction dir = DOWN;
    const char* names[] = { "up" , "down" , "left" , "right" };
    Texture2D idle[4]; 
    Texture2D walk[4][4] = {} ;

    for (int d=0 ; d<4 ; d++){
        idle[d] = LoadTexture( TextFormat("assets/sprites/player/idle/%s.png" , names[d]) ); 
    }

    // Main game loop
    while (!WindowShouldClose()) {
        float dt= GetFrameTime();
        // Movement
        if (IsKeyDown(KEY_W)) {
            y -= speed * dt;
            dir = UP;
        }

        if (IsKeyDown(KEY_S)) {
            y += speed * dt;
            dir = DOWN;
        }

        if (IsKeyDown(KEY_A)) {
            x -= speed * dt;
            dir = LEFT;
        }

        if (IsKeyDown(KEY_D)) {
            x += speed * dt;
            dir = RIGHT;
        }

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(idle[dir], (int)x, (int)y, WHITE);

        EndDrawing();
    }
    for (int d=0 ; d<4 ; d++){ 
        UnloadTexture(idle[d]);
}
    CloseWindow();
    return 0;
}
