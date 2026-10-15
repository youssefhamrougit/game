
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

    //attack 
    const int attack_frames = 5; 
    Texture2D attackLeft[attack_frames] ; 
    Texture2D attackRight[attack_frames] ; 
    bool attack = false ; 
    int attackFrame = 0 ; 
    float attackTimer = 0.0f ; 
    float attackFrameTime = 0.08f ; 

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
    // load attacking animations 
    for (int f = 0; f < attack_frames; f++) {
    attackLeft[f]  = LoadTexture(TextFormat("assets/sprites/player/attack_left/attack_left/attack_%d.png", f));
    attackRight[f] = LoadTexture(TextFormat("assets/sprites/player/attack_right/attack_right/attack_%d.png", f));
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
        if (!attack){
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

        // attack 
        if (IsKeyPressed(KEY_F) && !attack) { 
            attack = true ; 
            attackFrame = 0 ; 
            attackTimer = 0.0f ; 
        }
        if (attack) { 
            attackTimer += dt ; 
            if (attackTimer >= attackFrameTime ){ 
                attackFrame++ ; 
                attackTimer = 0.0f ; 
                if (attackFrame >= attack_frames){ 
                    attack = false ; 
                    attackFrame = 0 ; 
                }
            }
        }


        // Draw
        BeginDrawing();
        ClearBackground(WHITE);

        if (attack){ 
            if (dir == LEFT){ 
                DrawTexturePro(attackLeft[attackFrame] ,
                    { 0 , 0 , (float)attackLeft[attackFrame].width , (float)attackLeft[attackFrame].height } ,
                    { x-2 , y-2 , (float)idle[LEFT].width * 2.7f, (float)idle[LEFT].height * 2.7f } ,
                    { 0 , 0 } ,
                    0.0f ,
                    WHITE  ) ; 
            } else if (dir == RIGHT){ 
                DrawTexturePro(attackRight[attackFrame] ,
                    { 0 , 0 , (float)attackRight[attackFrame].width , (float)attackRight[attackFrame].height } ,
                    { x-2 , y-2 , (float)idle[RIGHT].width * 2.7f, (float)idle[RIGHT].height * 2.7f } , 
                    { 0 , 0 } ,
                    0.0f ,
                    WHITE  ) ; 
            } else { 
                DrawTexturePro(idle[dir] , { 0 , 0 , (float)idle[dir].width , (float)idle[dir].height } ,
                { x-2 , y-2 , (float)idle[dir].width * 2.7f , (float)idle[dir].height * 2.7f } , 
                { 0 , 0 } , 
                0.0f ,
                WHITE) ; 
            }
        } else if (moving) {
            DrawTexturePro(walk[dir][frame], 
                { 0 , 0 , (float)walk[dir][frame].width , (float)walk[dir][frame].height } ,
                { x , y , (float)walk[dir][frame].width * 2.0f , (float)walk[dir][frame].height * 2.0f } ,
                { 0 , 0 } , 
                0.0f ,
                WHITE);
        }
        else {
            DrawTexturePro(idle[dir], 
                { 0 , 0 , (float)idle[dir].width , (float)idle[dir].height } , 
                { x , y , (float)idle[dir].width * 2.0f , (float)idle[dir].height * 2.0f } ,
                { 0 , 0 } , 
                0.0f , 
                WHITE) ; 
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
    for (int f=0 ; f < attack_frames ; f++){ 
        UnloadTexture(attackLeft[f]) ; 
        UnloadTexture(attackRight[f]) ; 
    }

    CloseWindow();
    return 0;
}
