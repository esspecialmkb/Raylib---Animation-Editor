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

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
// - We will have 4 major objects to keep in mind here...
// -    1. Workspace - Ragdoll with joint transforms
// -    2. Animation list
// -    3. Joint Transform list
// -    4. Keyframe Timeline
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

// Define the camera to look into our 3d world
static Camera camera = { 0 };

// Ragdoll rotation:
static float ragdollRotX = 0.0f;

// Root node
static float rootTranX = 0.0f;
static float rootTranY = 0.0f;
static float rootTranZ = 0.0f;

static float rootRotX = 0.0f;
static float rootRotY = 0.0f;
static float rootRotZ = 0.0f;

// Hip Node


//----------------------------------------------------------------------------------
// Editor Workspace Screen Functions Definition
//----------------------------------------------------------------------------------

// Editor Workspace Initialization logic
void InitEditorWorkspaceScreen(void)
{
    // TODO: Initialize EditorWorkspace screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    
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
    
    // Update camera
    UpdateCamera(&camera, CAMERA_ORBITAL);
    

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        //finishScreen = 1;
        PlaySound(fxCoin);
    }
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
    //DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), DARKGRAY);
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "EDITOR WORKSPACE SCREEN", pos, font.baseSize*3.0f, 4, BLACK);
    DrawText("You can edit animations here!!!", 130, GetScreenHeight() - (font.baseSize*1.1f), 20, BLACK);
    
    
}

void DrawEditorWorkspace3DScreen(void)
{
    //-----------------------------------------------------------------------------
    // TODO: Draw Editor Workspace Ragdoll and scenegrid here!
    
    BeginMode3D(camera);
      
        // Draw the grid
        DrawGrid(20, 1.0f);
        
        // Draw the ragdoll
        rlPushMatrix();
            rlTranslatef(0.0f, 0.5f, 0.0f);
            rlRotatef(ragdollRotX, 1.0f, 0.0f, 0.0f);
            DrawCube((Vector3){0.0, 0.0, 0.0}, 0.5f, 1.0f, 0.5f, RED);
        rlPopMatrix();
    
    EndMode3D();
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