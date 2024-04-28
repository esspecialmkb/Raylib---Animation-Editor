//  Implementation of Ragdoll.h

#include "raylib.h"
#include "ragdoll.h"

Skeleton skeleton = {0};
Ragdoll ragdoll = {0};
PoseFrame baseFrame = {0};

//----------------------------------------------------------------
// - Skeleton stuff
Skeleton InitBaseSkeleton(void)
{
    skeleton = {
        .root =     (Vector3){0.0f,     0.0f,   0.0f},
        .hip =      (Vector3){0.0f,     2.0f,   0.0f},
        .lHip =     (Vector3){0.5f,     0.0f,   0.0f},
        .lKnee =    (Vector3){0.0f,     -1.0f,  0.0f},
        .rHip =     (Vector3){-0.5f,    0.0f,   0.0f},
        .rKnee =    (Vector3){0.0f,     -1.0f,  0.0f},
        .torso =    (Vector3){0.0f,     0.5f,   0.0f},
        .chest =    (Vector3){0.0f,     1.0f,   0.0f},
        .lShoulder = (Vector3){1.0f,    1.0f,   0.0f},
        .lElbow =   (Vector3){0.0f,     -1.0f,  0.0f},
        .rShoulder = (Vector3){-1.0f,   1.0f,   0.0f},
        .rElbow =   (Vector3){0.0f,     -1.0f,  0.0f},
        .neck =     (Vector3){0.0f,     0.0f,   0.0f}
    };
}

//----------------------------------------------------------------
// - PoseFrame stuff
// Creates an initial base pose frame
void InitBaseFrame(void)
{
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

// Grabs the current base frame and puts it in a PoseFrame struct
PoseFrame CopyBaseFrame(void)
{
    PoseFrame copy = {0};
}

PoseFrame NewBaseFrame(void)
{
    PoseFrame copy = {0};
}

// BoneTransforms - component of PoseFrame
BoneTransforms NewRotationTransform(float xRot, float yRot, float zRot)
{
    BoneTransforms result = {
        .rot = (Vector3){ xRot, yRot, zRot },
        .pos = (Vector3){ 0.0f, 0.0f, 0.0f }
    };
    
    return result;
}

BoneTransforms NewTranslationTransform(float xTran, float yTran, float zTran)
{
    BoneTransforms result = {
        .rot = (Vector3){ 0.0f, 0.0f, 0.0f },
        .pos = (Vector3){ xTran, yTran, zTran  }
    };
    
    return result;
}

BoneTransforms NewBoneTransform(float xRot, float yRot, float zRot, float xTran, float yTran, float zTran)
{
    BoneTransforms result = {
        .rot = (Vector3){ xRot, yRot, zRot },
        .pos = (Vector3){ xTran, yTran, zTran }
    };
    
    return result;
}

//----------------------------------------------------------------
// - PoseFrame stuff
void InitRagdoll(void)
{
    ragdoll = {
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
}

//-----------------------------------------------------------------
// Draw ragdoll with PoseFrame rotations
void DrawRagdoll(Skeleton skeletonDef, Ragdoll ragdollDef, PoseFrame pose)
{
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
void DrawRagdollWireFrame(Skeleton skeletonDef, Ragdoll ragdollDef, PoseFrame pose);