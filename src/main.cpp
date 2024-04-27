//
//  solarSystemExample.cpp
//  Raylib Dev
//
//  Created by Michael on 10/10/23.
//  Copyright © 2023 Michael. All rights reserved.
//

//#include "raylib.h"

//*
#include "Include/raylib.h"
#include "Include/rcamera.h"
#include "Include/rlgl.h"
#include "Include/raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "Include/raygui.h"
//#include "Ragdoll.h"
//*/

/*
 #include "../Include/raylib.h"
 #include "../Include/rcamera.h"
 #include "../Include/rlgl.h"
 #include "../Include/raymath.h"
 #define RAYGUI_IMPLEMENTATION
 #include "../Include/raygui.h"
 /*/
#include <string>
#include <math.h>           // Required for: cosf(), sinf()
#include <list>
using namespace std;



// This struct defines bone positions
struct Skeleton{
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
};

Skeleton skeleton = {
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

// Ragdoll struct describes the size of the body segments
// Segment definitions
struct Ragdoll{
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
};
Ragdoll ragdoll = {
    .root = (Vector3){0.0f,0.0f,0.0f},
    .hip = (Vector3){1.5f,0.5f,0.5f},
    .lHip = (Vector3){0.5f,1.0f,0.5f},
    .lKnee = (Vector3){0.5f,1.0f,0.5f},
    .rHip = (Vector3){0.5f,1.0f,0.5f},
    .rKnee = (Vector3){0.5f,1.0f,0.5f},
    .torso = (Vector3){1.5f,1.0f,0.5f},
    .chest = (Vector3){1.5f,1.0f,0.5f},
    .lShoulder = (Vector3){0.5f,1.0f,0.5f},
    .lElbow = (Vector3){0.5f,1.0f,0.5f},
    .rShoulder = (Vector3){0.5f,1.0f,0.5f},
    .rElbow = (Vector3){0.5f,1.0f,0.5f},
    .neck = (Vector3){1.0f,1.5f,1.0f}
};

// This struct defines the ragdoll's current bone transforms
struct BoneTransforms{
    Vector3 pos;
    Vector3 rot;
};
// Group of rotations for prototype frame
struct PoseFrame{
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
}baseFrame;
//struct PoseFrame baseFrame;

// This list of poseframes are for the live timeline
list<PoseFrame> frameList;

//------------------------------------------------------------------------------------
// Module Functions Declaration
//------------------------------------------------------------------------------------
void DrawSphereBasic(Color color);      // Draw sphere without any matrix transformation
void DrawRagdoll(Skeleton skeletonDef, Ragdoll ragdollDef, PoseFrame pose); // Draw ragdoll with PoseFrame rotations
void DrawRagdollWireFrame(Skeleton skeletonDef, Ragdoll ragdollDef, PoseFrame pose);


// We need a function to create our baseframe since it is a compound struct (Structs within a struct)
void initBaseFrame() {
    baseFrame.root.pos = (Vector3){0.0f,0.0f,0.0f};
    baseFrame.root.rot = (Vector3){0.0f,0.0f,0.0f};
    
    baseFrame.hip.pos = (Vector3){0.0f,0.0f,0.0f};
    baseFrame.hip.rot = (Vector3){0.0f,0.0f,0.0f};
    
    baseFrame.lHip.pos = (Vector3){0.0f,0.0f,0.0f};
    baseFrame.lHip.rot = (Vector3){0.0f,0.0f,0.0f};
    
    baseFrame.lKnee.pos = (Vector3){0.0f,0.0f,0.0f};
    baseFrame.lKnee.rot = (Vector3){0.0f,0.0f,0.0f};
    
    baseFrame.rHip.pos = (Vector3){0.0f,0.0f,0.0f};
    baseFrame.rHip.rot = (Vector3){0.0f,0.0f,0.0f};
    
    baseFrame.rKnee.pos = (Vector3){0.0f,0.0f,0.0f};
    baseFrame.rKnee.rot = (Vector3){0.0f,0.0f,0.0f};
    
    baseFrame.torso.pos = (Vector3){0.0f,0.0f,0.0f};
    baseFrame.torso.rot = (Vector3){0.0f,0.0f,0.0f};
    
    baseFrame.chest.pos = (Vector3){0.0f,0.0f,0.0f};
    baseFrame.chest.rot = (Vector3){0.0f,0.0f,0.0f};
    
    baseFrame.lShoulder.pos = (Vector3){0.0f,0.0f,0.0f};
    baseFrame.lShoulder.rot = (Vector3){0.0f,0.0f,0.0f};
    
    baseFrame.lElbow.pos = (Vector3){0.0f,0.0f,0.0f};
    baseFrame.lElbow.rot = (Vector3){0.0f,0.0f,0.0f};
    
    baseFrame.rShoulder.pos = (Vector3){0.0f,0.0f,0.0f};
    baseFrame.rShoulder.rot = (Vector3){0.0f,0.0f,0.0f};
    
    baseFrame.rElbow.pos = (Vector3){0.0f,0.0f,0.0f};
    baseFrame.rElbow.rot = (Vector3){0.0f,0.0f,0.0f};
    
    baseFrame.neck.pos = (Vector3){0.0f,0.0f,0.0f};
    baseFrame.neck.rot = (Vector3){0.0f,0.0f,0.0f};
}

// We need a function to create a copy of the current baseFrame to save it
PoseFrame copyBaseFrame(){
    struct PoseFrame newFrame = {};
    
    newFrame = baseFrame;
    
    return newFrame;
}

//------------------------------------------------------------------------------------
// Matrix references
/*
 
 MatrixMultiply(Matrix left, Matrix right)
 MatrixTranslate(float x, y, z)
 
 - all angles are in radians -
 MatrixRotateXYZ(Vector3 angle)
 MatrixRotate(Vector3 axis, float angle)
 MatrixRotateX(float angle)
 MatrixRotateY(float angle)
 MatrixRotateZ(float angle)
 
 MatrixLookAt(Vector3 eye, Vector3 target, Vector3 up)
 */
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    // GUI Position
    int guiWidth = 250;
    float guiWidthMargin = 40;
    int guiHeight = 50;
    int guiHeightMargin = 5;
    
    // Prepare the base frame struct object which holds live rotation data for all joints
    initBaseFrame();
    
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Simple ragdoll with push/pop matrix transformations");
    
    // Define the camera to look into our 3d world
    //--------------------------------------------------------------------------------------
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 16.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    
    
    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    float frameTime = 0;
    //--------------------------------------------------------------------------------------
    // GUI rotation values
    int xRotation = 0;
    int yRotation = 0;
    int zRotation = 0;
    
    // GUI State data
    int currentBone = 0;
    
    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        GuiUnlock();
        // Update
        //----------------------------------------------------------------------------------
        float deltaFrame = GetFrameTime();
        
        
        // We will use this prototype to update a camera
        // UpdateCameraPro(Camera *camera, Vector3 movement, Vector3 rotation, float zoom)
        
        //UpdateCamera(&camera, CAMERA_ORBITAL);
        //UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        BeginMode3D(camera);
        
        // Reference functions to draw a cube
        // DrawCubeV(Vector3 position, Vector3 size, Color color)
        // DrawCubeWiresV(Vector3 position, Vector3 size, Color color)
        
        // Draw our Ragdoll
        DrawRagdoll(skeleton, ragdoll, baseFrame);
        
        // Draw the floor grid
        DrawGrid(20, 1.0f);
        EndMode3D();
        
        // Draw GUI
        // GuiValueBox(Rectangle bounds, const char *text, int *value, int minValue, int maxValue, bool editMode);
        DrawRectangle(GetScreenWidth() - guiWidth, 0, GetScreenWidth() - guiWidth, GetScreenHeight(), LIGHTGRAY);
        DrawLine(GetScreenWidth() - guiWidth, 0, GetScreenWidth() - guiWidth, GetScreenHeight(), GRAY);
        
        //value = (int)GuiSliderBar((Rectangle){ x, y, width, height }, "Left Text", "Right Text", value, minValue, maxValue);
        // X Axis
        xRotation = GuiSliderBar((Rectangle){(GetScreenWidth() - guiWidth + guiWidthMargin), 50, guiWidth - (guiWidthMargin * 2), 20}, "X", to_string(xRotation).c_str(), xRotation, -90, 90);
        // Y Axis
        yRotation = GuiSliderBar((Rectangle){(GetScreenWidth() - guiWidth + guiWidthMargin), 75, guiWidth - (guiWidthMargin * 2), 20}, "Y", to_string(yRotation).c_str(), yRotation, -90, 90);
        // Z Axis
        zRotation = GuiSliderBar((Rectangle){(GetScreenWidth() - guiWidth + guiWidthMargin), 100, guiWidth - (guiWidthMargin * 2), 20}, "Z", to_string(zRotation).c_str(), zRotation, -90, 90);
        
        //GuiValueBox(Rectangle bounds, const char *text, int *value, int minValue, int maxValue, bool editMode);
        //bool value = GuiValueBox((Rectangle){GetScreenWidth() - (guiWidth * 3)+ 20.0f, 50, guiWidth - 40.0f, 20}, "X - Axis",&xRotation, -100, 100, true);
        baseFrame.hip.rot.x = xRotation;
        baseFrame.hip.rot.y = yRotation;
        baseFrame.hip.rot.z = zRotation;
        
        DrawText("Animation Ragdoll!", GetScreenWidth() - guiWidth + 20, 10, 20, MAROON);
        //if(value){
        //DrawText( to_string(xRotation).c_str() ,GetScreenWidth() - guiWidth + 20, 100, 20, MAROON);
        //}
        
        DrawFPS(10, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
        frameTime = frameTime + deltaFrame;
    }
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    return 0;
}

//--------------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//--------------------------------------------------------------------------------------------

// Draw ragdoll
void DrawRagdoll(Skeleton skeletonDef, Ragdoll ragDollDef, PoseFrame pose){
    
    //rlLoadIdentity();
    
    rlPushMatrix();     // PUSH 1
    
    // Root Transform
    //rlRotatef(frameTime * 2, 0, 1, 0);
    rlTranslatef(skeletonDef.root.x,skeletonDef.root.y,skeletonDef.root.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, LIGHTGRAY);
    
    // Hip Transform
    rlPushMatrix();     // PUSH 2
    
    rlTranslatef(skeletonDef.hip.x, skeletonDef.hip.y, skeletonDef.hip.z);
    
    // Apply Hip rotation
    rlRotatef(baseFrame.hip.rot.x, 1, 0, 0);
    rlRotatef(baseFrame.hip.rot.y, 0, 1, 0);
    rlRotatef(baseFrame.hip.rot.z, 0, 0, 1);
    
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, RED);
    
    // Hip Geometry
    rlPushMatrix();     // PUSH 3
    rlTranslatef(0.0f, ragDollDef.hip.y/2, 0.0f);
    DrawCubeV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.hip.x,ragDollDef.hip.y,ragDollDef.hip.z}, RED);
    rlPopMatrix();      // POP 3
    
    // LHip
    rlPushMatrix(); // PUSH 3
    rlTranslatef(skeletonDef.lHip.x, skeletonDef.lHip.y, skeletonDef.lHip.z);
    
    // Apply LHip rotation
    rlRotatef(baseFrame.lHip.rot.x, 1, 0, 0);
    rlRotatef(baseFrame.lHip.rot.y, 0, 1, 0);
    rlRotatef(baseFrame.lHip.rot.z, 0, 0, 1);
    
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, GREEN);
    
    // LHip Geometry
    rlPushMatrix(); // PUSH 4
    rlTranslatef(0, -ragDollDef.lHip.y/2, 0);
    DrawCubeV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.lHip.x,ragDollDef.lHip.y,ragDollDef.lHip.z}, RED);
    rlPopMatrix();  // POP 4
    
    // LKnee
    rlPushMatrix(); // PUSH 4
    rlTranslatef(skeletonDef.lKnee.x, skeletonDef.lKnee.y, skeletonDef.lKnee.z);
    
    // Apply LKnee rotation
    rlRotatef(baseFrame.lKnee.rot.x, 1, 0, 0);
    rlRotatef(baseFrame.lKnee.rot.y, 0, 1, 0);
    rlRotatef(baseFrame.lKnee.rot.z, 0, 0, 1);
    
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, GREEN);
    
    // LKnee Geometry
    rlPushMatrix(); // PUSH 5
    rlTranslatef(0, -ragDollDef.lKnee.y/2, 0);
    DrawCubeV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.lKnee.x,ragDollDef.lKnee.y,ragDollDef.lKnee.z},RED);
    rlPopMatrix();  // POP 5
    rlPopMatrix();  // POP 4
    
    // End of LHip Transform chain
    rlPopMatrix();  // POP3
    
    // RHip
    rlPushMatrix();     // PUSH 3
    rlTranslatef(skeletonDef.rHip.x, skeletonDef.rHip.y, skeletonDef.rHip.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // RHip Geometry
    rlPushMatrix();     // PUSH 4
    rlTranslatef(0, -ragDollDef.rHip.y/2, 0);
    DrawCubeV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.rHip.x,ragDollDef.rHip.y,ragDollDef.rHip.z}, GREEN);
    rlPopMatrix();      // POP 4
    
    // RKnee
    rlPushMatrix(); // PUSH 4
    rlTranslatef(skeletonDef.rKnee.x, skeletonDef.rKnee.y, skeletonDef.rKnee.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // RKnee Geometry
    rlPushMatrix(); // PUSH 5
    rlTranslatef(0, -ragDollDef.rKnee.y/2, 0);
    DrawCubeV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.rKnee.x,ragDollDef.rKnee.y,ragDollDef.rKnee.z},GREEN);
    rlPopMatrix();  // POP 5
    rlPopMatrix();  // POP 4
    
    // End of RHip Transform chain
    rlPopMatrix();  // POP 3
    
    // Torso
    rlPushMatrix(); // PUSH 3
    rlTranslatef(skeletonDef.torso.x, skeletonDef.torso.y, skeletonDef.torso.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // Torso Geometry
    rlPushMatrix(); // PUSH 4
    rlTranslatef(0, ragDollDef.torso.y/2, 0);
    DrawCubeV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.torso.x,ragDollDef.torso.y,ragDollDef.torso.z},GREEN);
    rlPopMatrix();  // POP 4
    
    // Chest
    rlPushMatrix(); // PUSH 5
    rlTranslatef(skeletonDef.chest.x, skeletonDef.chest.y, skeletonDef.chest.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // Chest Geometry
    rlPushMatrix(); // PUSH 6
    rlTranslatef(0, ragDollDef.chest.y/2, 0);
    DrawCubeV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.chest.x,ragDollDef.chest.y,ragDollDef.chest.z},MAROON);
    rlPopMatrix(); // POP 6
    
    // L Shoulder
    rlPushMatrix(); // PUSH 7
    rlTranslatef(skeletonDef.lShoulder.x, skeletonDef.lShoulder.y, skeletonDef.lShoulder.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // L Shoulder Geometry
    rlPushMatrix(); // PUSH 8
    rlTranslatef(0,-ragDollDef.lShoulder.y/2,0);
    DrawCubeV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.lShoulder.x,ragDollDef.lShoulder.y,ragDollDef.lShoulder.z},MAROON);
    rlPopMatrix();  // POP 8
    
    // L Elbow
    rlPushMatrix(); // PUSH 8
    rlTranslatef(skeletonDef.lElbow.x, skeletonDef.lElbow.y, skeletonDef.lElbow.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // L Elbow Geometry
    rlPushMatrix(); // PUSH 9
    rlTranslatef(0,-ragDollDef.lElbow.y/2,0);
    DrawCubeV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.lElbow.x,ragDollDef.lElbow.y,ragDollDef.lElbow.z},MAROON);
    rlPopMatrix();  // POP 9
    
    rlPopMatrix(); // End of L Elbow transform chain // POP 8
    rlPopMatrix(); // End of L Shoulder transform chain // POP 7
    
    // R Shoulder
    rlPushMatrix(); // PUSH 7
    rlTranslatef(skeletonDef.rShoulder.x, skeletonDef.rShoulder.y, skeletonDef.rShoulder.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // R Shoulder Geometry
    rlPushMatrix(); // PUSH 8
    rlTranslatef(0,-ragDollDef.rShoulder.y/2,0);
    DrawCubeV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.rShoulder.x,ragDollDef.rShoulder.y,ragDollDef.rShoulder.z},MAROON);
    rlPopMatrix();  // POP 8
    
    // R Elbow
    rlPushMatrix(); // PUSH 8
    rlTranslatef(skeletonDef.rElbow.x, skeletonDef.rElbow.y, skeletonDef.rElbow.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // R Elbow Geometry
    rlPushMatrix(); // PUSH 9
    rlTranslatef(0,-ragDollDef.rElbow.y/2,0);
    DrawCubeV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.rElbow.x,ragDollDef.rElbow.y,ragDollDef.rElbow.z},MAROON);
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

// Draw ragdoll
void DrawRagdollWireFrame(Skeleton skeletonDef, Ragdoll ragDollDef, PoseFrame pose){
    
    //rlLoadIdentity();
    
    rlPushMatrix();     // PUSH 1
    
    // Root Transform
    //rlRotatef(frameTime * 2, 0, 1, 0);
    rlTranslatef(skeletonDef.root.x,skeletonDef.root.y,skeletonDef.root.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, LIGHTGRAY);
    
    // Hip Transform
    rlPushMatrix();     // PUSH 2
    
    rlTranslatef(skeletonDef.hip.x, skeletonDef.hip.y, skeletonDef.hip.z);
    
    // Apply Hip rotation
    rlRotatef(baseFrame.hip.rot.x, 1, 0, 0);
    rlRotatef(baseFrame.hip.rot.y, 0, 1, 0);
    rlRotatef(baseFrame.hip.rot.z, 0, 0, 1);
    
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, RED);
    
    // Hip Geometry
    rlPushMatrix();     // PUSH 3
    rlTranslatef(0.0f, ragDollDef.hip.y/2, 0.0f);
    DrawCubeWiresV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.hip.x,ragDollDef.hip.y,ragDollDef.hip.z}, RED);
    rlPopMatrix();      // POP 3
    
    // LHip
    rlPushMatrix(); // PUSH 3
    rlTranslatef(skeletonDef.lHip.x, skeletonDef.lHip.y, skeletonDef.lHip.z);
    
    // Apply LHip rotation
    rlRotatef(baseFrame.lHip.rot.x, 1, 0, 0);
    rlRotatef(baseFrame.lHip.rot.y, 0, 1, 0);
    rlRotatef(baseFrame.lHip.rot.z, 0, 0, 1);
    
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, GREEN);
    
    // LHip Geometry
    rlPushMatrix(); // PUSH 4
    rlTranslatef(0, -ragDollDef.lHip.y/2, 0);
    DrawCubeWiresV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.lHip.x,ragDollDef.lHip.y,ragDollDef.lHip.z}, RED);
    rlPopMatrix();  // POP 4
    
    // LKnee
    rlPushMatrix(); // PUSH 4
    rlTranslatef(skeletonDef.lKnee.x, skeletonDef.lKnee.y, skeletonDef.lKnee.z);
    
    // Apply LKnee rotation
    rlRotatef(baseFrame.lKnee.rot.x, 1, 0, 0);
    rlRotatef(baseFrame.lKnee.rot.y, 0, 1, 0);
    rlRotatef(baseFrame.lKnee.rot.z, 0, 0, 1);
    
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, GREEN);
    
    // LKnee Geometry
    rlPushMatrix(); // PUSH 5
    rlTranslatef(0, -ragDollDef.lKnee.y/2, 0);
    DrawCubeWiresV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.lKnee.x,ragDollDef.lKnee.y,ragDollDef.lKnee.z},RED);
    rlPopMatrix();  // POP 5
    rlPopMatrix();  // POP 4
    
    // End of LHip Transform chain
    rlPopMatrix();  // POP3
    
    // RHip
    rlPushMatrix();     // PUSH 3
    rlTranslatef(skeletonDef.rHip.x, skeletonDef.rHip.y, skeletonDef.rHip.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // RHip Geometry
    rlPushMatrix();     // PUSH 4
    rlTranslatef(0, -ragDollDef.rHip.y/2, 0);
    DrawCubeWiresV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.rHip.x,ragDollDef.rHip.y,ragDollDef.rHip.z}, GREEN);
    rlPopMatrix();      // POP 4
    
    // RKnee
    rlPushMatrix(); // PUSH 4
    rlTranslatef(skeletonDef.rKnee.x, skeletonDef.rKnee.y, skeletonDef.rKnee.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // RKnee Geometry
    rlPushMatrix(); // PUSH 5
    rlTranslatef(0, -ragDollDef.rKnee.y/2, 0);
    DrawCubeWiresV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.rKnee.x,ragDollDef.rKnee.y,ragDollDef.rKnee.z},GREEN);
    rlPopMatrix();  // POP 5
    rlPopMatrix();  // POP 4
    
    // End of RHip Transform chain
    rlPopMatrix();  // POP 3
    
    // Torso
    rlPushMatrix(); // PUSH 3
    rlTranslatef(skeletonDef.torso.x, skeletonDef.torso.y, skeletonDef.torso.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // Torso Geometry
    rlPushMatrix(); // PUSH 4
    rlTranslatef(0, ragDollDef.torso.y/2, 0);
    DrawCubeWiresV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.torso.x,ragDollDef.torso.y,ragDollDef.torso.z},GREEN);
    rlPopMatrix();  // POP 4
    
    // Chest
    rlPushMatrix(); // PUSH 5
    rlTranslatef(skeletonDef.chest.x, skeletonDef.chest.y, skeletonDef.chest.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // Chest Geometry
    rlPushMatrix(); // PUSH 6
    rlTranslatef(0, ragDollDef.chest.y/2, 0);
    DrawCubeWiresV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.chest.x,ragDollDef.chest.y,ragDollDef.chest.z},MAROON);
    rlPopMatrix(); // POP 6
    
    // L Shoulder
    rlPushMatrix(); // PUSH 7
    rlTranslatef(skeletonDef.lShoulder.x, skeletonDef.lShoulder.y, skeletonDef.lShoulder.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // L Shoulder Geometry
    rlPushMatrix(); // PUSH 8
    rlTranslatef(0,-ragDollDef.lShoulder.y/2,0);
    DrawCubeWiresV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.lShoulder.x,ragDollDef.lShoulder.y,ragDollDef.lShoulder.z},MAROON);
    rlPopMatrix();  // POP 8
    
    // L Elbow
    rlPushMatrix(); // PUSH 8
    rlTranslatef(skeletonDef.lElbow.x, skeletonDef.lElbow.y, skeletonDef.lElbow.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // L Elbow Geometry
    rlPushMatrix(); // PUSH 9
    rlTranslatef(0,-ragDollDef.lElbow.y/2,0);
    DrawCubeWiresV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.lElbow.x,ragDollDef.lElbow.y,ragDollDef.lElbow.z},MAROON);
    rlPopMatrix();  // POP 9
    
    rlPopMatrix(); // End of L Elbow transform chain // POP 8
    rlPopMatrix(); // End of L Shoulder transform chain // POP 7
    
    // R Shoulder
    rlPushMatrix(); // PUSH 7
    rlTranslatef(skeletonDef.rShoulder.x, skeletonDef.rShoulder.y, skeletonDef.rShoulder.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // R Shoulder Geometry
    rlPushMatrix(); // PUSH 8
    rlTranslatef(0,-ragDollDef.rShoulder.y/2,0);
    DrawCubeWiresV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.rShoulder.x,ragDollDef.rShoulder.y,ragDollDef.rShoulder.z},MAROON);
    rlPopMatrix();  // POP 8
    
    // R Elbow
    rlPushMatrix(); // PUSH 8
    rlTranslatef(skeletonDef.rElbow.x, skeletonDef.rElbow.y, skeletonDef.rElbow.z);
    DrawSphere(Vector3{0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // R Elbow Geometry
    rlPushMatrix(); // PUSH 9
    rlTranslatef(0,-ragDollDef.rElbow.y/2,0);
    DrawCubeWiresV(Vector3{0.0f,0.0f,0.0f}, Vector3{ragDollDef.rElbow.x,ragDollDef.rElbow.y,ragDollDef.rElbow.z},MAROON);
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

// Draw sphere without any matrix transformation
// NOTE: Sphere is drawn in world position ( 0, 0, 0 ) with radius 1.0f
void DrawSphereBasic(Color color)
{
    int rings = 16;
    int slices = 16;
    
    // Make sure there is enough space in the internal render batch
    // buffer to store all required vertex, batch is reseted if required
    rlCheckRenderBatchLimit((rings + 2)*slices*6);
    
    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);
    
    for (int i = 0; i < (rings + 2); i++)
    {
        for (int j = 0; j < slices; j++)
        {
            rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*i))*sinf(DEG2RAD*(j*360/slices)),
                       sinf(DEG2RAD*(270+(180/(rings + 1))*i)),
                       cosf(DEG2RAD*(270+(180/(rings + 1))*i))*cosf(DEG2RAD*(j*360/slices)));
            rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*sinf(DEG2RAD*((j+1)*360/slices)),
                       sinf(DEG2RAD*(270+(180/(rings + 1))*(i+1))),
                       cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*cosf(DEG2RAD*((j+1)*360/slices)));
            rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*sinf(DEG2RAD*(j*360/slices)),
                       sinf(DEG2RAD*(270+(180/(rings + 1))*(i+1))),
                       cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*cosf(DEG2RAD*(j*360/slices)));
            
            rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*i))*sinf(DEG2RAD*(j*360/slices)),
                       sinf(DEG2RAD*(270+(180/(rings + 1))*i)),
                       cosf(DEG2RAD*(270+(180/(rings + 1))*i))*cosf(DEG2RAD*(j*360/slices)));
            rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i)))*sinf(DEG2RAD*((j+1)*360/slices)),
                       sinf(DEG2RAD*(270+(180/(rings + 1))*(i))),
                       cosf(DEG2RAD*(270+(180/(rings + 1))*(i)))*cosf(DEG2RAD*((j+1)*360/slices)));
            rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*sinf(DEG2RAD*((j+1)*360/slices)),
                       sinf(DEG2RAD*(270+(180/(rings + 1))*(i+1))),
                       cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*cosf(DEG2RAD*((j+1)*360/slices)));
        }
    }
    rlEnd();
}