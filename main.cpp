
#include <raylib.h>
#include <cmath>

enum direction { UP, DOWN, LEFT, RIGHT };

int main() {
    // Game window
    InitWindow(960, 450, "Down Below");
    SetTargetFPS(60);

    // Player position and speed
    float x = 480, y = 270, speed = 200;
    direction dir = DOWN;

    // Sprite filenames
    const char* names[] = { "up", "down", "left", "right" };

    const char* walkNames[4][4] = {
        { "up_0", "up_1", "up_2", "up_3" },
        { "down_0", "down_1", "down_2", "down_3" },
        { "left_0", "left_1", "left_2", "left_3" },
        { "right_0", "right_1", "right_2" , "right_3" }
    };

    int frameCount[] = { 4, 4, 4, 4 };

    Texture2D idle[4];
    Texture2D walk[4][4] = {};

    // Load idle sprites
    for (int d = 0; d < 4; d++) {
        idle[d] = LoadTexture(
            TextFormat("assets/sprites/player/idle/%s.png", names[d])
        );
    }

    // Load walking sprites
    for (int d = 0; d < 4; d++) {
        for (int f = 0; f < frameCount[d]; f++) {
            walk[d][f] = LoadTexture(
                TextFormat(
                    "assets/sprites/player/walk/%s.png",
                    walkNames[d][f]
                )
            );
        }
    }

    // Animation variables
    int frame = 0;
    float animTimer = 0;
    float frameTime = 0.15f;
    bool moving = false;

    // Main game loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        float dx = 0;
        float dy = 0;

        // Read movement input
        if (IsKeyDown(KEY_W)) {
            dy -= 1;
        }

        if (IsKeyDown(KEY_S)) {
            dy += 1;
        }

        if (IsKeyDown(KEY_A)) {
            dx -= 1;
        }

        if (IsKeyDown(KEY_D)) {
            dx += 1;
        }

        moving = (dx != 0 || dy != 0);

        // Update player movement and facing direction
        if (moving) {
            if (dx != 0 && dy != 0) {
                // Prefer the most recently pressed direction
                if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S)) {
                    dx = 0;
                }
                else {
                    dy = 0;
                }
            }

            if (dx != 0) {
                if (dx < 0) {
                    dir = LEFT;
                }
                else {
                    dir = RIGHT;
                }
            }
            else if (dy < 0) {
                dir = UP;
            }
            else if (dy > 0) {
                dir = DOWN;
            }

            // Normalize diagonal movement
            float length = sqrtf(dx * dx + dy * dy);

            if (length > 0) {
                x += (dx / length) * speed * dt;
                y += (dy / length) * speed * dt;
            }

            // Advance walking animation
            animTimer += dt;

            if (animTimer >= frameTime) {
                frame = (frame + 1) % frameCount[dir];
                animTimer = 0;
            }
        }
        else {
            // Reset animation when standing still
            frame = 0;
            animTimer = 0;
        }

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        if (moving) {
            DrawTexture(walk[dir][frame], (int)x, (int)y, WHITE);
        }
        else {
            DrawTexture(idle[dir], (int)x, (int)y, WHITE);
        }

        EndDrawing();
    }

    // Free textures
    for (int d = 0; d < 4; d++) {
        UnloadTexture(idle[d]);

        for (int f = 0; f < frameCount[d]; f++) {
            UnloadTexture(walk[d][f]);
        }
    }

    CloseWindow();
    return 0;
}
