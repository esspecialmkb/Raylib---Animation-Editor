/*******************************************************************************************
*
*   raylib [core] examples - basic screen manager
*
*   NOTE: This example illustrates a very simple screen manager based on a states machines
*
*   Example originally created with raylib 4.0, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "rlgl.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <String.h>"
//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
typedef enum BoneJoint { ROOT = 0, HIP, L_HIP, L_KNEE, R_HIP, R_KNEE,
                           TORSO, CHEST, L_SHOULDER, L_ELBOW, R_SHOULDER, R_ELBOW,
                           NECK };
                           
// This struct defines bone positions
typedef struct Skeleton{
    Vector3 root;
    Vector3 hip;
    Vector3 lHip;
    Vector3 lKnee;
    Vector3 rHip;
    Vector3 rKnee;
    Vector3 torso;
    Vector3 chest;
    Vector3 lShoulder;
    Vector3 lElbow;
    Vector3 rShoulder;
    Vector3 rElbow;
    Vector3 neck;
}Skeleton;

// Ragdoll struct describes the size of the body segments
// Segment definitions
typedef struct Ragdoll{
    Vector3 root;
    Vector3 hip;
    Vector3 lHip;
    Vector3 lKnee;
    Vector3 rHip;
    Vector3 rKnee;
    Vector3 torso;
    Vector3 chest;
    Vector3 lShoulder;
    Vector3 lElbow;
    Vector3 rShoulder;
    Vector3 rElbow;
    Vector3 neck;
}Ragdoll;

// This struct defines the ragdoll's current bone transforms
typedef struct BoneTransforms{
    Vector3 pos;
    Vector3 rot;
}BoneTransforms;

// Group of rotations for prototype frame
typedef struct PoseFrame{
    BoneTransforms root;
    BoneTransforms hip;
    BoneTransforms lHip;
    BoneTransforms lKnee;
    BoneTransforms rHip;
    BoneTransforms rKnee;
    BoneTransforms torso;
    BoneTransforms chest;
    BoneTransforms lShoulder;
    BoneTransforms lElbow;
    BoneTransforms rShoulder;
    BoneTransforms rElbow;
    BoneTransforms neck;
}PoseFrame;

//------------------------------------------------------------------------------------------
// Screen state
//------------------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, WORKSPACE, ENDING } GameScreen;

typedef enum AppScreen { 
    LOGO_ = 0, 
    TITLE_, 
    NEW_PROJECT,    // Screen to create new project
    NEW_RAGDOLL,    // Screen for ragdoll creation
    NEW_ANIMATION,
    //WORKSPACE,
    PLAYBACK
} AppScreen;

Font font = { 0 };

//-----------------------------------------------------------------
// Draw ragdoll with PoseFrame rotations
void DrawRagdoll(Skeleton skeletonDef, struct Ragdoll ragdollDef, struct PoseFrame pose, bool print)
{
    //rlLoadIdentity();
    
    rlPushMatrix();     // PUSH 1
    
    // Root Transform
    //rlRotatef(frameTime * 2, 0, 1, 0);
    rlTranslatef(skeletonDef.root.x,skeletonDef.root.y,skeletonDef.root.z);
    if( print == true)
    {
        printf("Root Transform X %.2f\n",skeletonDef.root.x);
    }
    
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, RED);
    
    // Hip Transform
    rlPushMatrix();     // PUSH 2
    
    rlTranslatef(skeletonDef.hip.x, skeletonDef.hip.y, skeletonDef.hip.z);
    if( print == true )
    {
        printf("Hip Transform Y %.2f\n",skeletonDef.hip.y);
    }
    
    // Apply Hip rotation
    rlRotatef( pose.hip.rot.x, 1, 0, 0);
    rlRotatef( pose.hip.rot.y, 0, 1, 0);
    rlRotatef( pose.hip.rot.z, 0, 0, 1);
    
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    //------------------------------------------------------------------------------------
    
    // Hip Geometry
    rlPushMatrix();     // PUSH 3
    rlTranslatef(0.0f, ragdollDef.hip.y/2, 0.0f);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.hip.x,ragdollDef.hip.y,ragdollDef.hip.z}, RED);
    rlPopMatrix();      // POP 3
    
    // LHip
    rlPushMatrix(); // PUSH 3
    rlTranslatef(skeletonDef.lHip.x, skeletonDef.lHip.y, skeletonDef.lHip.z);
    
    // Apply LHip rotation
    rlRotatef( pose.lHip.rot.x, 1, 0, 0);
    rlRotatef( pose.lHip.rot.y, 0, 1, 0);
    rlRotatef( pose.lHip.rot.z, 0, 0, 1);
    
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, GREEN);
    
    // LHip Geometry
    rlPushMatrix(); // PUSH 4
    rlTranslatef(0, -ragdollDef.lHip.y/2, 0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.lHip.x,ragdollDef.lHip.y,ragdollDef.lHip.z}, RED);
    rlPopMatrix();  // POP 4
    
    // LKnee
    rlPushMatrix(); // PUSH 4
    rlTranslatef(skeletonDef.lKnee.x, skeletonDef.lKnee.y, skeletonDef.lKnee.z);
    
    // Apply LKnee rotation
    rlRotatef( pose.lKnee.rot.x, 1, 0, 0);
    rlRotatef( pose.lKnee.rot.y, 0, 1, 0);
    rlRotatef( pose.lKnee.rot.z, 0, 0, 1);
    
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, GREEN);
    
    // LKnee Geometry
    rlPushMatrix(); // PUSH 5
    rlTranslatef(0, -ragdollDef.lKnee.y/2, 0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.lKnee.x,ragdollDef.lKnee.y,ragdollDef.lKnee.z},RED);
    rlPopMatrix();  // POP 5
    rlPopMatrix();  // POP 4
    
    // End of LHip Transform chain
    rlPopMatrix();  // POP3
    
    // RHip
    rlPushMatrix();     // PUSH 3
    rlTranslatef(skeletonDef.rHip.x, skeletonDef.rHip.y, skeletonDef.rHip.z);
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // RHip Geometry
    rlPushMatrix();     // PUSH 4
    rlTranslatef(0, -ragdollDef.rHip.y/2, 0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.rHip.x,ragdollDef.rHip.y,ragdollDef.rHip.z}, GREEN);
    rlPopMatrix();      // POP 4
    
    // RKnee
    rlPushMatrix(); // PUSH 4
    rlTranslatef(skeletonDef.rKnee.x, skeletonDef.rKnee.y, skeletonDef.rKnee.z);
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // RKnee Geometry
    rlPushMatrix(); // PUSH 5
    rlTranslatef(0, -ragdollDef.rKnee.y/2, 0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.rKnee.x,ragdollDef.rKnee.y,ragdollDef.rKnee.z},GREEN);
    rlPopMatrix();  // POP 5
    rlPopMatrix();  // POP 4
    
    // End of RHip Transform chain
    rlPopMatrix();  // POP 3
    
    // Torso
    rlPushMatrix(); // PUSH 3
    rlTranslatef(skeletonDef.torso.x, skeletonDef.torso.y, skeletonDef.torso.z);
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // Torso Geometry
    rlPushMatrix(); // PUSH 4
    rlTranslatef(0, ragdollDef.torso.y/2, 0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.torso.x,ragdollDef.torso.y,ragdollDef.torso.z},GREEN);
    rlPopMatrix();  // POP 4
    
    // Chest
    rlPushMatrix(); // PUSH 5
    rlTranslatef(skeletonDef.chest.x, skeletonDef.chest.y, skeletonDef.chest.z);
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // Chest Geometry
    rlPushMatrix(); // PUSH 6
    rlTranslatef(0, ragdollDef.chest.y/2, 0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.chest.x,ragdollDef.chest.y,ragdollDef.chest.z},MAROON);
    rlPopMatrix(); // POP 6
    
    // L Shoulder
    rlPushMatrix(); // PUSH 7
    rlTranslatef(skeletonDef.lShoulder.x, skeletonDef.lShoulder.y, skeletonDef.lShoulder.z);
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // L Shoulder Geometry
    rlPushMatrix(); // PUSH 8
    rlTranslatef(0,-ragdollDef.lShoulder.y/2,0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.lShoulder.x,ragdollDef.lShoulder.y,ragdollDef.lShoulder.z},MAROON);
    rlPopMatrix();  // POP 8
    
    // L Elbow
    rlPushMatrix(); // PUSH 8
    rlTranslatef(skeletonDef.lElbow.x, skeletonDef.lElbow.y, skeletonDef.lElbow.z);
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // L Elbow Geometry
    rlPushMatrix(); // PUSH 9
    rlTranslatef(0,-ragdollDef.lElbow.y/2,0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.lElbow.x,ragdollDef.lElbow.y,ragdollDef.lElbow.z},MAROON);
    rlPopMatrix();  // POP 9
    
    rlPopMatrix(); // End of L Elbow transform chain // POP 8
    rlPopMatrix(); // End of L Shoulder transform chain // POP 7
    
    // R Shoulder
    rlPushMatrix(); // PUSH 7
    rlTranslatef(skeletonDef.rShoulder.x, skeletonDef.rShoulder.y, skeletonDef.rShoulder.z);
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // R Shoulder Geometry
    rlPushMatrix(); // PUSH 8
    rlTranslatef(0,-ragdollDef.rShoulder.y/2,0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.rShoulder.x,ragdollDef.rShoulder.y,ragdollDef.rShoulder.z},MAROON);
    rlPopMatrix();  // POP 8
    
    // R Elbow
    rlPushMatrix(); // PUSH 8
    rlTranslatef(skeletonDef.rElbow.x, skeletonDef.rElbow.y, skeletonDef.rElbow.z);
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // R Elbow Geometry
    rlPushMatrix(); // PUSH 9
    rlTranslatef(0,-ragdollDef.rElbow.y/2,0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.rElbow.x,ragdollDef.rElbow.y,ragdollDef.rElbow.z},MAROON);
    rlPopMatrix();  // POP 9
    
    rlPopMatrix();  // POP 8
    rlPopMatrix(); // End of R Shoulder transform chain // POP 7
    
    // Neck
    rlPopMatrix(); // End of Chest transform chain  // POP 6
    rlPopMatrix(); // POP 5
    
    // End of Hip Transform chain
    rlPopMatrix(); // POP 4
    // End of Root Transform chain
    rlPopMatrix(); // POP 3
}

// Draw the GUI
void DrawGUI(PoseFrame basePoseFrame){
    //
    // GUI Position
    int guiWidth = 250;
    float guiWidthMargin = 40;
    int guiHeight = 50;
    int guiHeightMargin = 5;
    // GUI rotation values
    /* int xRotation = 0;
    int yRotation = 0;
    int zRotation = 0; */
    
    int xRotation = basePoseFrame.hip.rot.x;
    int yRotation = basePoseFrame.hip.rot.y;
    int zRotation = basePoseFrame.hip.rot.z;
    
    
    // Draw GUI
    // GuiValueBox(Rectangle bounds, const char *text, int *value, int minValue, int maxValue, bool editMode);
    DrawRectangle(GetScreenWidth() - guiWidth, 0, GetScreenWidth() - guiWidth, GetScreenHeight(), LIGHTGRAY);
    DrawLine(GetScreenWidth() - guiWidth, 0, GetScreenWidth() - guiWidth, GetScreenHeight(), GRAY);
    
    //value = (int)GuiSliderBar((Rectangle){ x, y, width, height }, "Left Text", "Right Text", value, minValue, maxValue);
    // X Axis
    //xRotation = GuiSliderBar((Rectangle){(GetScreenWidth() - guiWidth + guiWidthMargin), 50, guiWidth - (guiWidthMargin * 2), 20}, "X", TextFormat("x: %i", xRotation), xRotation, -90, 90);
    GuiSliderBar((Rectangle){(GetScreenWidth() - guiWidth + guiWidthMargin), 50, guiWidth - (guiWidthMargin * 2), 20}, "X", NULL, &xRotation, -90, 90);
    // Y Axis
    //yRotation = GuiSliderBar((Rectangle){(GetScreenWidth() - guiWidth + guiWidthMargin), 75, guiWidth - (guiWidthMargin * 2), 20}, "Y", TextFormat("y: %i", yRotation), yRotation, -90, 90);
    // Z Axis
    //zRotation = GuiSliderBar((Rectangle){(GetScreenWidth() - guiWidth + guiWidthMargin), 100, guiWidth - (guiWidthMargin * 2), 20}, "Z", TextFormat("z: %i", zRotation), zRotation, -90, 90);
    
    //GuiValueBox(Rectangle bounds, const char *text, int *value, int minValue, int maxValue, bool editMode);
    //bool value = GuiValueBox((Rectangle){GetScreenWidth() - (guiWidth * 3)+ 20.0f, 50, guiWidth - 40.0f, 20}, "X - Axis",&xRotation, -100, 100, true);
    basePoseFrame.hip.rot.x = xRotation;
    basePoseFrame.hip.rot.y = yRotation;
    basePoseFrame.hip.rot.z = zRotation;
    
    DrawText("Animation Ragdoll!", GetScreenWidth() - guiWidth + 20, 10, 20, MAROON);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic screen manager");

    GameScreen currentScreen = WORKSPACE;
    font = LoadFont("resources/mecha.png");
    
    //--------------------------------------------------------------------------------------
    // TODO: Initialize all required variables and load all required data here!
    
    Skeleton skeleton = (Skeleton){
        .root = (Vector3){0.0f,0.0f,0.0f},
        .hip = (Vector3){0.0f,2.0f,0.0f},
        .lHip = (Vector3){0.5f,0.0f,0.0f},
        .lKnee = (Vector3){0.0f,-1.0f,0.0f},
        .rHip = (Vector3){-0.5f,0.0f,0.0f},
        .rKnee = (Vector3){0.0f,-1.0f,0.0f},
        .torso = (Vector3){0.0f,0.5f,0.0f},
        .chest = (Vector3){0.0f,1.0f,0.0f},
        .lShoulder = (Vector3){1.0f,1.0f,0.0f},
        .lElbow = (Vector3){0.0f,-1.0f,0.0f},
        .rShoulder = (Vector3){-1.0f,1.0f,0.0f},
        .rElbow = (Vector3){0.0f,-1.0f,0.0f},
        .neck = (Vector3){0.0f,0.0f,0.0f}
    };
    
    Ragdoll ragdoll = (Ragdoll){
        .root =     (Vector3){0.0f,     0.0f,   0.0f},
        .hip =      (Vector3){1.5f,     0.5f,   0.5f},
        .lHip =     (Vector3){0.5f,     1.0f,   0.5f},
        .lKnee =    (Vector3){0.5f,     1.0f,   0.5f},
        .rHip =     (Vector3){0.5f,     1.0f,   0.5f},
        .rKnee =    (Vector3){0.5f,     1.0f,   0.5f},
        .torso =    (Vector3){1.5f,     1.0f,   0.5f},
        .chest =    (Vector3){1.5f,     1.0f,   0.5f},
        .lShoulder = (Vector3){0.5f,    1.0f,   0.5f},
        .lElbow =   (Vector3){0.5f,     1.0f,   0.5f},
        .rShoulder = (Vector3){0.5f,    1.0f,   0.5f},
        .rElbow =   (Vector3){0.5f,     1.0f,   0.5f},
        .neck =     (Vector3){1.0f,     1.5f,   1.0f}
    };
    
    PoseFrame frame = (PoseFrame){
        .root =     (BoneTransforms){
                        .pos = (Vector3){0.0f,     0.0f,   0.0f},
                        .rot = (Vector3){0.0f,     0.0f,   0.0f}    
                    },
        .hip =      (BoneTransforms){
                        .pos = (Vector3){0.0f,     0.0f,   0.0f},
                        .rot = (Vector3){0.0f,     0.0f,   0.0f}    
                    },
        .lHip =     (BoneTransforms){
                        .pos = (Vector3){0.0f,     0.0f,   0.0f},
                        .rot = (Vector3){0.0f,     0.0f,   0.0f}    
                    },
        .lKnee =    (BoneTransforms){
                        .pos = (Vector3){0.0f,     0.0f,   0.0f},
                        .rot = (Vector3){0.0f,     0.0f,   0.0f}    
                    },
        .rHip =     (BoneTransforms){
                        .pos = (Vector3){0.0f,     0.0f,   0.0f},
                        .rot = (Vector3){0.0f,     0.0f,   0.0f}    
                    },
        .rKnee =    (BoneTransforms){
                        .pos = (Vector3){0.0f,     0.0f,   0.0f},
                        .rot = (Vector3){0.0f,     0.0f,   0.0f}    
                    },
        .torso =    (BoneTransforms){
                        .pos = (Vector3){0.0f,     0.0f,   0.0f},
                        .rot = (Vector3){0.0f,     0.0f,   0.0f}    
                    },
        .chest =    (BoneTransforms){
                        .pos = (Vector3){0.0f,     0.0f,   0.0f},
                        .rot = (Vector3){0.0f,     0.0f,   0.0f}    
                    },
        .lShoulder = (BoneTransforms){
                        .pos = (Vector3){0.0f,     0.0f,   0.0f},
                        .rot = (Vector3){0.0f,     0.0f,   0.0f}    
                    },
        .lElbow =   (BoneTransforms){
                        .pos = (Vector3){0.0f,     0.0f,   0.0f},
                        .rot = (Vector3){0.0f,     0.0f,   0.0f}    
                    },
        .rShoulder = (BoneTransforms){
                        .pos = (Vector3){0.0f,     0.0f,   0.0f},
                        .rot = (Vector3){0.0f,     0.0f,   0.0f}    
                    },
        .rElbow =   (BoneTransforms){
                        .pos = (Vector3){0.0f,     0.0f,   0.0f},
                        .rot = (Vector3){0.0f,     0.0f,   0.0f}    
                    },
        .neck =     (BoneTransforms){
                        .pos = (Vector3){0.0f,     0.0f,   0.0f},
                        .rot = (Vector3){0.0f,     0.0f,   0.0f}    
                    }
    };
    
    //--------------------------------------------------------------------------------------
    int framesCounter = 0;          // Useful to count frames
    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = { 0 };
    camera.position = (Vector3){ 8.0f, 8.0f, 8.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update Logic
        //----------------------------------------------------------------------------------
        switch(currentScreen)
        {
            case LOGO:
            {
                // TODO: Update LOGO screen variables here!

                framesCounter++;    // Count frames

                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (framesCounter > 20)
                {
                    currentScreen = TITLE;
                }
            } break;
            case TITLE:
            {
                // TODO: Update TITLE screen variables here!

                // Press enter to change to WORKSPACE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = WORKSPACE;
                }
            } break;
            case WORKSPACE:
            {
                // TODO: Update WORKSPACE screen variables here!
                // Toggle camera movement
                if(IsKeyDown(KEY_LEFT_SHIFT))
                {
                    // Update camera
                    //UpdateCamera(&camera, CAMERA_ORBITAL || CAMERA_FIRST_PERSON || CAMERA_FREE);
                    UpdateCamera(&camera, CAMERA_FREE);
                }

                // Press enter to change to ENDING screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    //currentScreen = ENDING;
                }
            } break;
            case ENDING:
            {
                // TODO: Update ENDING screen variables here!

                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = TITLE;
                }
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(currentScreen)
            {
                case LOGO:
                {
                    // TODO: Draw LOGO screen here!
                    DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
                    DrawText("WAIT for a moment...", 290, 220, 20, GRAY);

                } break;
                case TITLE:
                {
                    // TODO: Draw TITLE screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                    DrawText("PRESS ENTER or TAP to JUMP to WORKSPACE SCREEN", 120, 220, 20, DARKGREEN);

                } break;
                case WORKSPACE:
                {
                    // TODO: Draw WORKSPACE screen here!
                    
                    Vector2 pos = { 20, 10 };
                    DrawTextEx(font, "EDITOR WORKSPACE SCREEN", pos, font.baseSize*3.0f, 4, BLACK);
                    DrawText("You can edit animations here!!!", 130, GetScreenHeight() - (font.baseSize*1.1f), 20, BLACK);
                    
                     BeginMode3D(camera);
      
                        // Draw the grid
                        DrawGrid(20, 1.0f);
                        
                        // Draw the ragdoll
                        DrawRagdoll(skeleton, ragdoll, frame, false);
                    
                    EndMode3D();
                    
                    DrawGUI(frame);
                    
                    // DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    // DrawText("WORKSPACE SCREEN", 20, 20, 40, MAROON);
                    // DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);

                } break;
                case ENDING:
                {
                    // TODO: Draw ENDING screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

                } break;
                default: break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
