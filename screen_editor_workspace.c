/**********************************************************************************************
*
*   raylib - Advance Game template
*   ADAPTED FOR ANIMATION EDITOR WORKSPACE
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include "ragdoll.h"
#include "rlgl.h"
#include <stdio.h>
#include <string.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
// - We will have 4 major objects to keep in mind here...
// -    1. Workspace - Ragdoll with joint transforms
// -    2. Animation list
// -    3. Joint Transform list
// -    4. Keyframe Timeline
//----------------------------------------------------------------------------------
typedef enum AppScreen { 
    NEW_PROJECT = 0,    // Screen to create new project
    EDIT_RAGDOLL,    // Screen for ragdoll creation
    NEW_ANIMATION,
    WORKSPACE,
    PLAYBACK,
    ROTATION
} AppScreen;

static int framesCounter = 0;
static int finishScreen = 0;

// Define the camera to look into our 3d world
static Camera camera = { 0 };

// Ragdoll rotation:
struct Skeleton skeleton;
struct Ragdoll ragdoll;
struct PoseFrame basePoseFrame;

// Editor state
AppScreen currentEditorScreen;

// GUI Position
int guiWidth = 250;
float guiWidthMargin = 40;
int guiHeight = 50;
int guiHeightMargin = 5;
//----------------------------------------------------------------------------------

// - PoseFrame stuff
// Creates an initial base pose frame
void InitBaseFrame(void)
{
    
    basePoseFrame.root.pos = (Vector3){0.0f,0.0f,0.0f};
    basePoseFrame.root.rot = (Vector3){0.0f,0.0f,0.0f};
    
    basePoseFrame.hip.pos = (Vector3){0.0f,0.0f,0.0f};
    basePoseFrame.hip.rot = (Vector3){0.0f,0.0f,0.0f};
    
    basePoseFrame.lHip.pos = (Vector3){0.0f,0.0f,0.0f};
    basePoseFrame.lHip.rot = (Vector3){0.0f,0.0f,0.0f};
    
    basePoseFrame.lKnee.pos = (Vector3){0.0f,0.0f,0.0f};
    basePoseFrame.lKnee.rot = (Vector3){0.0f,0.0f,0.0f};
    
    basePoseFrame.rHip.pos = (Vector3){0.0f,0.0f,0.0f};
    basePoseFrame.rHip.rot = (Vector3){0.0f,0.0f,0.0f};
    
    basePoseFrame.rKnee.pos = (Vector3){0.0f,0.0f,0.0f};
    basePoseFrame.rKnee.rot = (Vector3){0.0f,0.0f,0.0f};
    
    basePoseFrame.torso.pos = (Vector3){0.0f,0.0f,0.0f};
    basePoseFrame.torso.rot = (Vector3){0.0f,0.0f,0.0f};
    
    basePoseFrame.chest.pos = (Vector3){0.0f,0.0f,0.0f};
    basePoseFrame.chest.rot = (Vector3){0.0f,0.0f,0.0f};
    
    basePoseFrame.lShoulder.pos = (Vector3){0.0f,0.0f,0.0f};
    basePoseFrame.lShoulder.rot = (Vector3){0.0f,0.0f,0.0f};
    
    basePoseFrame.lElbow.pos = (Vector3){0.0f,0.0f,0.0f};
    basePoseFrame.lElbow.rot = (Vector3){0.0f,0.0f,0.0f};
    
    basePoseFrame.rShoulder.pos = (Vector3){0.0f,0.0f,0.0f};
    basePoseFrame.rShoulder.rot = (Vector3){0.0f,0.0f,0.0f};
    
    basePoseFrame.rElbow.pos = (Vector3){0.0f,0.0f,0.0f};
    basePoseFrame.rElbow.rot = (Vector3){0.0f,0.0f,0.0f};
    
    basePoseFrame.neck.pos = (Vector3){0.0f,0.0f,0.0f};
    basePoseFrame.neck.rot = (Vector3){0.0f,0.0f,0.0f};
}

// Editor Workspace Initialization logic
void InitEditorWorkspaceScreen(void)
{
    // TODO: Initialize EditorWorkspace screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    currentEditorScreen = WORKSPACE;
    
    //InitRagdoll();
    //InitBaseFrame();
    
    // Create skeleton
    //skeleton = InitBaseSkeleton();
    skeleton = (Skeleton){
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
    
    ragdoll = (Ragdoll){
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
    
    basePoseFrame = (PoseFrame){
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
    
    // Init camera
    camera.position = (Vector3){ 8.0f, 8.0f, 8.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
}

// Editor Workspace Screen Update logic
void UpdateEditorWorkspaceScreen(void)
{
    // TODO: Update Editor Workspace screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        //finishScreen = 1;
        PlaySound(fxCoin);
    }
    
    // Toggle camera movement
    if(IsKeyDown(KEY_LEFT_SHIFT))
    {
        // Update camera
        //UpdateCamera(&camera, CAMERA_ORBITAL || CAMERA_FIRST_PERSON || CAMERA_FREE);
        UpdateCamera(&camera, CAMERA_FREE);
    }
    
    // Enable rotation mode
    if(IsKeyPressed(KEY_R)){
        
    }
    
    // Update editorState
    switch(currentEditorScreen){
        case WORKSPACE:
        {
            // General workspace state
            
        } break;
        case EDIT_RAGDOLL:
        {
            //
        } break;
        case ROTATION:
        {
            //
        } break;
    }
    
    framesCounter = framesCounter + 1;
}

// Draw the GUI
void DrawGUI(void){
    //
    // GUI rotation values
    int xRotation = 0;
    int yRotation = 0;
    int zRotation = 0;
    // Draw GUI
    // GuiValueBox(Rectangle bounds, const char *text, int *value, int minValue, int maxValue, bool editMode);
    DrawRectangle(GetScreenWidth() - guiWidth, 0, GetScreenWidth() - guiWidth, GetScreenHeight(), LIGHTGRAY);
    DrawLine(GetScreenWidth() - guiWidth, 0, GetScreenWidth() - guiWidth, GetScreenHeight(), GRAY);
    
    //value = (int)GuiSliderBar((Rectangle){ x, y, width, height }, "Left Text", "Right Text", value, minValue, maxValue);
    // X Axis
    //xRotation = GuiSliderBar((Rectangle){(GetScreenWidth() - guiWidth + guiWidthMargin), 50, guiWidth - (guiWidthMargin * 2), 20}, "X", TextFormat("x: %i", xRotation), xRotation, -90, 90);
    xRotation = GuiSliderBar((Rectangle){(GetScreenWidth() - guiWidth + guiWidthMargin), 50, guiWidth - (guiWidthMargin * 2), 20}, "X", xRotation, xRotation, -90, 90);
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

//----------------------------------------------------------------------------------
// Editor Workspace Screen Draw logic
// - We need to draw 4 views:
// -    1. A 3D view of the ragdoll
// -    2. A list of current Animations
// -    3. A list of current Joint Transforms
// -    4. A Keyframe timeline
//----------------------------------------------------------------------------------
void DrawEditorWorkspaceScreen(void)
{
    //-----------------------------------------------------------------------------
    // TODO: Draw Editor Workspace screen here!
    //DrawRectangle(GetScreenWidth()-200, 0, 200, GetScreenHeight(), DARKGRAY);
    
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "EDITOR WORKSPACE SCREEN", pos, font.baseSize*3.0f, 4, BLACK);
    DrawText("You can edit animations here!!!", 130, GetScreenHeight() - (font.baseSize*1.1f), 20, BLACK);
    
    
}

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
    rlRotatef( basePoseFrame.hip.rot.x, 1, 0, 0);
    rlRotatef( basePoseFrame.hip.rot.y, 0, 1, 0);
    rlRotatef( basePoseFrame.hip.rot.z, 0, 0, 1);
    
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
    rlRotatef( basePoseFrame.lHip.rot.x, 1, 0, 0);
    rlRotatef( basePoseFrame.lHip.rot.y, 0, 1, 0);
    rlRotatef( basePoseFrame.lHip.rot.z, 0, 0, 1);
    
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
    rlRotatef( basePoseFrame.lKnee.rot.x, 1, 0, 0);
    rlRotatef( basePoseFrame.lKnee.rot.y, 0, 1, 0);
    rlRotatef( basePoseFrame.lKnee.rot.z, 0, 0, 1);
    
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

void DrawEditorWorkspace3DScreen(void)
{
    //-----------------------------------------------------------------------------
    // TODO: Draw Editor Workspace Ragdoll and scenegrid here!
    bool ifPrint = false;
    if(framesCounter >= 10){
        ifPrint = true;
        framesCounter = 0;
    }
    
    BeginMode3D(camera);
      
        // Draw the grid
        DrawGrid(20, 1.0f);
        
        // Draw the ragdoll
        //rlPushMatrix();
            /* rlTranslatef(0.0f, 0.5f, 0.0f);
            rlRotatef(ragdollRotX, 1.0f, 0.0f, 0.0f);
            DrawCube((Vector3){0.0, 0.0, 0.0}, 0.5f, 1.0f, 0.5f, RED); */
            
            DrawRagdoll(skeleton, ragdoll, basePoseFrame, false);
        //rlPopMatrix();
    
    EndMode3D();
    
    //DrawGUI();
}

void DebugMatrixData(void)
{
    //Matrix modelMatrix = rlGetMatrixModelview();
    //Matrix transformMatrix = rlGetMatrixTransform();
}


// NOTES
//rlScalef(x, y, z);
//rlRotatef(angle, x - 0.0f, y - 1.0f, z - 0.0f); - In Degrees
//rlTranslatef(x - 0.0f, y - 0.0f, z -0.0f); 

// Draw cube
// NOTE: Cube position is the center position
//void DrawCube(Vector3 position, float width, float height, float length, Color color)

// Editor Workspace Screen Unload logic
void UnloadEditorWorkspaceScreen(void)
{
    // TODO: Unload Editor Workspace screen variables here!
}

// EditorWorkspace Screen should finish?
int FinishEditorWorkspaceScreen(void)
{
    return finishScreen;
}

// Extra functions...
int PeekEditorWorkspaceScreen(){
    // return a message
    return 0;
}

void PokeEditorWorkspaceScreen(int poke)
{
    // Process incoming message
}