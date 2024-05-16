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
 
 
    // GUI Controls Reference
    //----------------------------------------------------------------------------------------------------------
    // Container/separator controls, useful for controls organization
    RAYGUIAPI int GuiWindowBox(Rectangle bounds, const char *title);                                       // Window Box control, shows a window that can be closed
    RAYGUIAPI int GuiGroupBox(Rectangle bounds, const char *text);                                         // Group Box control with text name
    RAYGUIAPI int GuiLine(Rectangle bounds, const char *text);                                             // Line separator control, could contain text
    RAYGUIAPI int GuiPanel(Rectangle bounds, const char *text);                                            // Panel control, useful to group controls
    RAYGUIAPI int GuiTabBar(Rectangle bounds, const char **text, int count, int *active);                  // Tab Bar control, returns TAB to be closed or -1
    RAYGUIAPI int GuiScrollPanel(Rectangle bounds, const char *text, Rectangle content, Vector2 *scroll, Rectangle *view); // Scroll Panel control

    // Basic controls set
    RAYGUIAPI int GuiLabel(Rectangle bounds, const char *text);                                            // Label control, shows text
    RAYGUIAPI int GuiButton(Rectangle bounds, const char *text);                                           // Button control, returns true when clicked
    RAYGUIAPI int GuiLabelButton(Rectangle bounds, const char *text);                                      // Label button control, show true when clicked
    RAYGUIAPI int GuiToggle(Rectangle bounds, const char *text, bool *active);                             // Toggle Button control, returns true when active
    RAYGUIAPI int GuiToggleGroup(Rectangle bounds, const char *text, int *active);                         // Toggle Group control, returns active toggle index
    RAYGUIAPI int GuiToggleSlider(Rectangle bounds, const char *text, int *active);                        // Toggle Slider control, returns true when clicked
    RAYGUIAPI int GuiCheckBox(Rectangle bounds, const char *text, bool *checked);                          // Check Box control, returns true when active
    RAYGUIAPI int GuiComboBox(Rectangle bounds, const char *text, int *active);                            // Combo Box control, returns selected item index

    RAYGUIAPI int GuiDropdownBox(Rectangle bounds, const char *text, int *active, bool editMode);          // Dropdown Box control, returns selected item
    RAYGUIAPI int GuiSpinner(Rectangle bounds, const char *text, int *value, int minValue, int maxValue, bool editMode); // Spinner control, returns selected value
    RAYGUIAPI int GuiValueBox(Rectangle bounds, const char *text, int *value, int minValue, int maxValue, bool editMode); // Value Box control, updates input text with numbers
    RAYGUIAPI int GuiTextBox(Rectangle bounds, char *text, int textSize, bool editMode);                   // Text Box control, updates input text

    RAYGUIAPI int GuiSlider(Rectangle bounds, const char *textLeft, const char *textRight, float *value, float minValue, float maxValue); // Slider control, returns selected value
    RAYGUIAPI int GuiSliderBar(Rectangle bounds, const char *textLeft, const char *textRight, float *value, float minValue, float maxValue); // Slider Bar control, returns selected value
    RAYGUIAPI int GuiProgressBar(Rectangle bounds, const char *textLeft, const char *textRight, float *value, float minValue, float maxValue); // Progress Bar control, shows current progress value
    RAYGUIAPI int GuiStatusBar(Rectangle bounds, const char *text);                                        // Status Bar control, shows info text
    RAYGUIAPI int GuiDummyRec(Rectangle bounds, const char *text);                                         // Dummy control for placeholders
    RAYGUIAPI int GuiGrid(Rectangle bounds, const char *text, float spacing, int subdivs, Vector2 *mouseCell); // Grid control, returns mouse cell position

    // Advance controls set
    RAYGUIAPI int GuiListView(Rectangle bounds, const char *text, int *scrollIndex, int *active);          // List View control, returns selected list item index
    RAYGUIAPI int GuiListViewEx(Rectangle bounds, const char **text, int count, int *scrollIndex, int *active, int *focus); // List View with extended parameters
    RAYGUIAPI int GuiMessageBox(Rectangle bounds, const char *title, const char *message, const char *buttons); // Message Box control, displays a message
    RAYGUIAPI int GuiTextInputBox(Rectangle bounds, const char *title, const char *message, const char *buttons, char *text, int textMaxSize, bool *secretViewActive); // Text Input Box control, ask for text, supports secret
    RAYGUIAPI int GuiColorPicker(Rectangle bounds, const char *text, Color *color);                        // Color Picker control (multiple color controls)
    RAYGUIAPI int GuiColorPanel(Rectangle bounds, const char *text, Color *color);                         // Color Panel control
    RAYGUIAPI int GuiColorBarAlpha(Rectangle bounds, const char *text, float *alpha);                      // Color Bar Alpha control
    RAYGUIAPI int GuiColorBarHue(Rectangle bounds, const char *text, float *value);                        // Color Bar Hue control
    RAYGUIAPI int GuiColorPickerHSV(Rectangle bounds, const char *text, Vector3 *colorHsv);                // Color Picker control that avoids conversion to RGB on each call (multiple color controls)
    RAYGUIAPI int GuiColorPanelHSV(Rectangle bounds, const char *text, Vector3 *colorHsv);                 // Color Panel control that returns HSV color value, used by GuiColorPickerHSV()
    
    // Text drawing functions
    RLAPI void DrawFPS(int posX, int posY);                                                     // Draw current FPS
    RLAPI void DrawText(const char *text, int posX, int posY, int fontSize, Color color);       // Draw text (using default font)
    RLAPI void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text using font and additional parameters
    RLAPI void DrawTextPro(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint); // Draw text using Font and pro parameters (rotation)
    //----------------------------------------------------------------------------------------------------------
 
    // Some Basic Colors
    // NOTE: Custom raylib color palette for amazing visuals on WHITE background
    #define LIGHTGRAY  CLITERAL(Color){ 200, 200, 200, 255 }   // Light Gray
    #define GRAY       CLITERAL(Color){ 130, 130, 130, 255 }   // Gray
    #define DARKGRAY   CLITERAL(Color){ 80, 80, 80, 255 }      // Dark Gray
    #define YELLOW     CLITERAL(Color){ 253, 249, 0, 255 }     // Yellow
    #define GOLD       CLITERAL(Color){ 255, 203, 0, 255 }     // Gold
    #define ORANGE     CLITERAL(Color){ 255, 161, 0, 255 }     // Orange
    #define PINK       CLITERAL(Color){ 255, 109, 194, 255 }   // Pink
    #define RED        CLITERAL(Color){ 230, 41, 55, 255 }     // Red
    #define MAROON     CLITERAL(Color){ 190, 33, 55, 255 }     // Maroon
    #define GREEN      CLITERAL(Color){ 0, 228, 48, 255 }      // Green
    #define LIME       CLITERAL(Color){ 0, 158, 47, 255 }      // Lime
    #define DARKGREEN  CLITERAL(Color){ 0, 117, 44, 255 }      // Dark Green
    #define SKYBLUE    CLITERAL(Color){ 102, 191, 255, 255 }   // Sky Blue
    #define BLUE       CLITERAL(Color){ 0, 121, 241, 255 }     // Blue
    #define DARKBLUE   CLITERAL(Color){ 0, 82, 172, 255 }      // Dark Blue
    #define PURPLE     CLITERAL(Color){ 200, 122, 255, 255 }   // Purple
    #define VIOLET     CLITERAL(Color){ 135, 60, 190, 255 }    // Violet
    #define DARKPURPLE CLITERAL(Color){ 112, 31, 126, 255 }    // Dark Purple
    #define BEIGE      CLITERAL(Color){ 211, 176, 131, 255 }   // Beige
    #define BROWN      CLITERAL(Color){ 127, 106, 79, 255 }    // Brown
    #define DARKBROWN  CLITERAL(Color){ 76, 63, 47, 255 }      // Dark Brown

    #define WHITE      CLITERAL(Color){ 255, 255, 255, 255 }   // White
    #define BLACK      CLITERAL(Color){ 0, 0, 0, 255 }         // Black
    #define BLANK      CLITERAL(Color){ 0, 0, 0, 0 }           // Blank (Transparent)
    #define MAGENTA    CLITERAL(Color){ 255, 0, 255, 255 }     // Magenta
    #define RAYWHITE   CLITERAL(Color){ 245, 245, 245, 255 }   // My own White (raylib logo)
 
 *
 ********************************************************************************************/

/* #include "Include/raylib.h"
#include "Include/rlgl.h"
#define RAYGUI_IMPLEMENTATION
#include "Include/raygui.h"
 */
#include "raylib.h"
#include "rlgl.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


#include <string.h>
//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
typedef enum BoneJoint { ROOT = 0, HIP, L_HIP, L_KNEE, R_HIP, R_KNEE,
    TORSO, CHEST, L_SHOULDER, L_ELBOW, R_SHOULDER, R_ELBOW,
    NECK } BoneJoint;

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
typedef struct ListViewItem{
    char *text;
}ListItemView;

typedef struct ListViewState{
    int listCount;
    int scrollIndex;
    int active;
    int focus;
}ListViewState;

//------------------------------------------------------------------------------------------
// Create global data references

// Ragdoll data
Skeleton _skeleton;
Ragdoll _ragdoll;
PoseFrame _poseFrame;

// Listview state data
ListViewState _boneSelectListState;
ListViewState _keyframeSelectListState;
ListViewState _animationSelectListState;

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
    
    //------------------------------------------------------------------------------------
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
    
    //------------------------------------------------------------------------------------
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
    
    //------------------------------------------------------------------------------------
    // RHip
    rlPushMatrix();     // PUSH 3
    rlTranslatef(skeletonDef.rHip.x, skeletonDef.rHip.y, skeletonDef.rHip.z);
    
    // Apply RHip rotation
    rlRotatef( pose.rHip.rot.x, 1, 0, 0);
    rlRotatef( pose.rHip.rot.y, 0, 1, 0);
    rlRotatef( pose.rHip.rot.z, 0, 0, 1);
    
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // RHip Geometry
    rlPushMatrix();     // PUSH 4
    rlTranslatef(0, -ragdollDef.rHip.y/2, 0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.rHip.x,ragdollDef.rHip.y,ragdollDef.rHip.z}, GREEN);
    rlPopMatrix();      // POP 4
    
    //------------------------------------------------------------------------------------
    // RKnee
    rlPushMatrix(); // PUSH 4
    rlTranslatef(skeletonDef.rKnee.x, skeletonDef.rKnee.y, skeletonDef.rKnee.z);
    
    // Apply RKnee rotation
    rlRotatef( pose.rKnee.rot.x, 1, 0, 0);
    rlRotatef( pose.rKnee.rot.y, 0, 1, 0);
    rlRotatef( pose.rKnee.rot.z, 0, 0, 1);
    
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // RKnee Geometry
    rlPushMatrix(); // PUSH 5
    rlTranslatef(0, -ragdollDef.rKnee.y/2, 0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.rKnee.x,ragdollDef.rKnee.y,ragdollDef.rKnee.z},GREEN);
    rlPopMatrix();  // POP 5
    rlPopMatrix();  // POP 4
    
    // End of RHip Transform chain
    rlPopMatrix();  // POP 3
    
    //------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------
    // Torso
    rlPushMatrix(); // PUSH 3
    rlTranslatef(skeletonDef.torso.x, skeletonDef.torso.y, skeletonDef.torso.z);
    
    // Apply torso rotation
    rlRotatef( pose.torso.rot.x, 1, 0, 0);
    rlRotatef( pose.torso.rot.y, 0, 1, 0);
    rlRotatef( pose.torso.rot.z, 0, 0, 1);
    
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // Torso Geometry
    rlPushMatrix(); // PUSH 4
    rlTranslatef(0, ragdollDef.torso.y/2, 0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.torso.x,ragdollDef.torso.y,ragdollDef.torso.z},GREEN);
    rlPopMatrix();  // POP 4
    
    //------------------------------------------------------------------------------------
    // Chest
    rlPushMatrix(); // PUSH 5
    rlTranslatef(skeletonDef.chest.x, skeletonDef.chest.y, skeletonDef.chest.z);
    
    // Apply torso rotation
    rlRotatef( pose.chest.rot.x, 1, 0, 0);
    rlRotatef( pose.chest.rot.y, 0, 1, 0);
    rlRotatef( pose.chest.rot.z, 0, 0, 1);
    
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // Chest Geometry
    rlPushMatrix(); // PUSH 6
    rlTranslatef(0, ragdollDef.chest.y/2, 0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.chest.x,ragdollDef.chest.y,ragdollDef.chest.z},MAROON);
    rlPopMatrix(); // POP 6
    
    //------------------------------------------------------------------------------------
    // L Shoulder
    rlPushMatrix(); // PUSH 7
    rlTranslatef(skeletonDef.lShoulder.x, skeletonDef.lShoulder.y, skeletonDef.lShoulder.z);
    
    // Apply lShoulder rotation
    rlRotatef( pose.lShoulder.rot.x, 1, 0, 0);
    rlRotatef( pose.lShoulder.rot.y, 0, 1, 0);
    rlRotatef( pose.lShoulder.rot.z, 0, 0, 1);
    
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // L Shoulder Geometry
    rlPushMatrix(); // PUSH 8
    rlTranslatef(0,-ragdollDef.lShoulder.y/2,0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.lShoulder.x,ragdollDef.lShoulder.y,ragdollDef.lShoulder.z},MAROON);
    rlPopMatrix();  // POP 8
    
    //------------------------------------------------------------------------------------
    // L Elbow
    rlPushMatrix(); // PUSH 8
    rlTranslatef(skeletonDef.lElbow.x, skeletonDef.lElbow.y, skeletonDef.lElbow.z);
    
    // Apply lElbow rotation
    rlRotatef( pose.lElbow.rot.x, 1, 0, 0);
    rlRotatef( pose.lElbow.rot.y, 0, 1, 0);
    rlRotatef( pose.lElbow.rot.z, 0, 0, 1);
    
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // L Elbow Geometry
    rlPushMatrix(); // PUSH 9
    rlTranslatef(0,-ragdollDef.lElbow.y/2,0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.lElbow.x,ragdollDef.lElbow.y,ragdollDef.lElbow.z},MAROON);
    rlPopMatrix();  // POP 9
    
    rlPopMatrix(); // End of L Elbow transform chain // POP 8
    rlPopMatrix(); // End of L Shoulder transform chain // POP 7
    
    //------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------
    // R Shoulder
    rlPushMatrix(); // PUSH 7
    rlTranslatef(skeletonDef.rShoulder.x, skeletonDef.rShoulder.y, skeletonDef.rShoulder.z);
    
    // Apply rShoulder rotation
    rlRotatef( pose.rShoulder.rot.x, 1, 0, 0);
    rlRotatef( pose.rShoulder.rot.y, 0, 1, 0);
    rlRotatef( pose.rShoulder.rot.z, 0, 0, 1);
    
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // R Shoulder Geometry
    rlPushMatrix(); // PUSH 8
    rlTranslatef(0,-ragdollDef.rShoulder.y/2,0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.rShoulder.x,ragdollDef.rShoulder.y,ragdollDef.rShoulder.z},MAROON);
    rlPopMatrix();  // POP 8
    
    //------------------------------------------------------------------------------------
    // R Elbow
    rlPushMatrix(); // PUSH 8
    rlTranslatef(skeletonDef.rElbow.x, skeletonDef.rElbow.y, skeletonDef.rElbow.z);
    
    // Apply rElbow rotation
    rlRotatef( pose.rElbow.rot.x, 1, 0, 0);
    rlRotatef( pose.rElbow.rot.y, 0, 1, 0);
    rlRotatef( pose.rElbow.rot.z, 0, 0, 1);
    
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    // R Elbow Geometry
    rlPushMatrix(); // PUSH 9
    rlTranslatef(0,-ragdollDef.rElbow.y/2,0);
    DrawCubeV((Vector3){0.0f,0.0f,0.0f}, (Vector3){ragdollDef.rElbow.x,ragdollDef.rElbow.y,ragdollDef.rElbow.z},MAROON);
    rlPopMatrix();  // POP 9
    
    rlPopMatrix();  // POP 8
    rlPopMatrix(); // End of R Shoulder transform chain // POP 7
    
    //------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------
    // Neck
    rlPushMatrix();
    rlTranslatef(skeletonDef.neck.x, skeletonDef.neck.y, skeletonDef.neck.z);
    
    // Apply neck rotation
    rlRotatef( pose.neck.rot.x, 1, 0, 0);
    rlRotatef( pose.neck.rot.y, 0, 1, 0);
    rlRotatef( pose.neck.rot.z, 0, 0, 1);
    
    DrawSphere((Vector3){0.0f,0.0f,0.0f}, 0.1f, BLUE);
    
    rlPopMatrix(); // End of neck transform chain
    //------------------------------------------------------------------------------------
    
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
    float xRotation = 0;
    float yRotation = 0;
    float zRotation = 0;
    
    switch(_boneSelectListState.active){
        case 0: // hip
        {
            xRotation = _poseFrame.hip.rot.x;
            yRotation = _poseFrame.hip.rot.y;
            zRotation = _poseFrame.hip.rot.z;
        }break;
        
        case 1: // lhip
        {
            xRotation = _poseFrame.lHip.rot.x;
            yRotation = _poseFrame.lHip.rot.y;
            zRotation = _poseFrame.lHip.rot.z;
        }break;
        
        case 2: // lknee
        {
            xRotation = _poseFrame.lKnee.rot.x;
            yRotation = _poseFrame.lKnee.rot.y;
            zRotation = _poseFrame.lKnee.rot.z;
        }break;
        
        case 3: // lhip
        {
            xRotation = _poseFrame.rHip.rot.x;
            yRotation = _poseFrame.rHip.rot.y;
            zRotation = _poseFrame.rHip.rot.z;
        }break;
        
        case 4: // lknee
        {
            xRotation = _poseFrame.rKnee.rot.x;
            yRotation = _poseFrame.rKnee.rot.y;
            zRotation = _poseFrame.rKnee.rot.z;
        }break;
        
        case 5: // torso
        {
            xRotation = _poseFrame.torso.rot.x;
            yRotation = _poseFrame.torso.rot.y;
            zRotation = _poseFrame.torso.rot.z;
        }break;
        
        case 6: // chest
        {
            xRotation = _poseFrame.chest.rot.x;
            yRotation = _poseFrame.chest.rot.y;
            zRotation = _poseFrame.chest.rot.z;
        }break;
        
        case 7: // lShoulder
        {
            xRotation = _poseFrame.lShoulder.rot.x;
            yRotation = _poseFrame.lShoulder.rot.y;
            zRotation = _poseFrame.lShoulder.rot.z;
        }break;
        
        case 8: // lElbow
        {
            xRotation = _poseFrame.lElbow.rot.x;
            yRotation = _poseFrame.lElbow.rot.y;
            zRotation = _poseFrame.lElbow.rot.z;
        }break;
        
        case 9: // rShoulder
        {
            xRotation = _poseFrame.rShoulder.rot.x;
            yRotation = _poseFrame.rShoulder.rot.y;
            zRotation = _poseFrame.rShoulder.rot.z;
        }break;
        
        case 10: // rElbow
        {
            xRotation = _poseFrame.rElbow.rot.x;
            yRotation = _poseFrame.rElbow.rot.y;
            zRotation = _poseFrame.rElbow.rot.z;
        }break;
        
        case 11: // neck
        {
            xRotation = _poseFrame.neck.rot.x;
            yRotation = _poseFrame.neck.rot.y;
            zRotation = _poseFrame.neck.rot.z;
        }break;
        default: break;
    }
    
    
    // Draw GUI
    // GuiValueBox(Rectangle bounds, const char *text, int *value, int minValue, int maxValue, bool editMode);
    DrawRectangle(GetScreenWidth() - guiWidth, 0, GetScreenWidth() - guiWidth, GetScreenHeight(), LIGHTGRAY);
    DrawLine(GetScreenWidth() - guiWidth, 0, GetScreenWidth() - guiWidth, GetScreenHeight(), GRAY);
    
    //value = (int)GuiSliderBar((Rectangle){ x, y, width, height }, "Left Text", "Right Text", value, minValue, maxValue);
    /* xRotation = */
    GuiSliderBar(   (Rectangle){(GetScreenWidth() - guiWidth + guiWidthMargin), 50, guiWidth - (guiWidthMargin * 2), 20},
                    "X", 
                    NULL, 
                    &xRotation, 
                    -90.0, 
                    90.0);
                    
    /* yRotation = */
    GuiSliderBar(   (Rectangle){(GetScreenWidth() - guiWidth + guiWidthMargin), 50 + (20 + 5), guiWidth - (guiWidthMargin * 2), 20},
                    "Y", 
                    NULL, 
                    &yRotation, 
                    -90.0, 
                    90.0);
                    
    /* zRotation */
    GuiSliderBar(   (Rectangle){(GetScreenWidth() - guiWidth + guiWidthMargin), 50 + ((20+5) * 2), guiWidth - (guiWidthMargin * 2), 20},
                    "Z", 
                    NULL, 
                    &zRotation, 
                    -90.0, 
                    90.0);
    
    //GuiValueBox(Rectangle bounds, const char *text, int *value, int minValue, int maxValue, bool editMode);
    //bool value = GuiValueBox((Rectangle){GetScreenWidth() - (guiWidth * 3)+ 20.0f, 50, guiWidth - 40.0f, 20}, "X - Axis",&xRotation, -100, 100, true);
    /* _poseFrame.hip.rot.x = xRotation;
    _poseFrame.hip.rot.y = yRotation;
    _poseFrame.hip.rot.z = zRotation; */
    
    switch(_boneSelectListState.active){
        case 0: // hip
        {
            _poseFrame.hip.rot.x = xRotation;
            _poseFrame.hip.rot.y = yRotation;
            _poseFrame.hip.rot.z = zRotation;
        }break;
        
        case 1: // lhip
        {
            _poseFrame.lHip.rot.x = xRotation;
            _poseFrame.lHip.rot.y = yRotation;
            _poseFrame.lHip.rot.z = zRotation;
        }break;
        
        case 2: // lknee
        {
            _poseFrame.lKnee.rot.x = xRotation;
            _poseFrame.lKnee.rot.y = yRotation;
            _poseFrame.lKnee.rot.z = zRotation;
        }break;
        
        case 3: // rhip
        {
            _poseFrame.rHip.rot.x = xRotation;
            _poseFrame.rHip.rot.y = yRotation;
            _poseFrame.rHip.rot.z = zRotation;
        }break;
        
        case 4: // rknee
        {
            _poseFrame.rKnee.rot.x = xRotation;
            _poseFrame.rKnee.rot.y = yRotation;
            _poseFrame.rKnee.rot.z = zRotation;
        }break;
        
        case 5: // torso
        {
            _poseFrame.torso.rot.x = xRotation;
            _poseFrame.torso.rot.y = yRotation;
            _poseFrame.torso.rot.z = zRotation;
        }break;
        
        case 6: // chest
        {
            _poseFrame.chest.rot.x = xRotation;
            _poseFrame.chest.rot.y = yRotation;
            _poseFrame.chest.rot.z = zRotation;
        }break;
        
        case 7: // lShoulder
        {
            _poseFrame.lShoulder.rot.x = xRotation;
            _poseFrame.lShoulder.rot.y = yRotation;
            _poseFrame.lShoulder.rot.z = zRotation;
        }break;
        
        case 8: // lElbow
        {
            _poseFrame.lElbow.rot.x = xRotation;
            _poseFrame.lElbow.rot.y = yRotation;
            _poseFrame.lElbow.rot.z = zRotation;
        }break;
        
        case 9: // rShoulder
        {
            _poseFrame.rShoulder.rot.x = xRotation;
            _poseFrame.rShoulder.rot.y = yRotation;
            _poseFrame.rShoulder.rot.z = zRotation;
        }break;
        
        case 10: // rElbow
        {
            _poseFrame.rElbow.rot.x = xRotation;
            _poseFrame.rElbow.rot.y = yRotation;
            _poseFrame.rElbow.rot.z = zRotation;
        }break;
        
        case 11: // neck
        {
            _poseFrame.neck.rot.x = xRotation;
            _poseFrame.neck.rot.y = yRotation;
            _poseFrame.neck.rot.z = zRotation;
        }break;
        default: break;
    }
    
    DrawText("Animation Ragdoll!", GetScreenWidth() - guiWidth + 20, 10, 20, MAROON);
    
    //RAYGUIAPI int GuiListViewEx(Rectangle bounds, const char **text, int count, int *scrollIndex, int *active, int *focus); // List View with extended parameters
    char **text = (char *[]) { "hip", "lhip", "lknee", "rhip", "rknee", "torso", "chest", "lshoulder", "lelbow", "rshoulder", "relbow", "neck" };
    
    // (Rectangle){ x,  y,  width,  height  };
    Rectangle bounds = (Rectangle){ (GetScreenWidth() - guiWidth + guiWidthMargin),     50 + ((20+5) * 3),     guiWidth - (guiWidthMargin * 2),    180};
    
    //GuiListViewEx( bounds, /*&text*/    (char *[]) { "x", "y", "z" }, count, &scrollIndex, &active, &focus); // List View with extended parameters
    GuiListViewEx( bounds, &(*text), _boneSelectListState.listCount, &_boneSelectListState.scrollIndex, &_boneSelectListState.active, &_boneSelectListState.focus); // List View with extended parameters
    
    //RLAPI void DrawText(const char *text, int posX, int posY, int fontSize, Color color);       // Draw text (using default font)
    //DrawText(&(*text)[0], GetScreenWidth() - guiWidth + guiWidthMargin, 50 + ((20+5) * 4) + 180, 20, BLACK);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    //const int screenWidth = 800;
    //const int screenHeight = 450;
    
    const int screenWidth = 1366;
    const int screenHeight = 768;
    
    
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic screen manager");
    
    GameScreen currentScreen = WORKSPACE;
    font = LoadFont("resources/mecha.png");
    
    //--------------------------------------------------------------------------------------
    // TODO: Initialize all required variables and load all required data here!
    
    _boneSelectListState = (ListViewState){
        .listCount = 12,
        .scrollIndex = 0,
        .active = 0,
        .focus = 0
    };
    
    _skeleton = (Skeleton){
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
    
    _ragdoll = (Ragdoll){
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
    
    _poseFrame = (PoseFrame){
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
                DrawRagdoll(_skeleton, _ragdoll, _poseFrame, false);
                
                EndMode3D();
                
                DrawGUI(_poseFrame);
                
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
