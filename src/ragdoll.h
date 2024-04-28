#ifndef RAGDOLL_H
#define RAGDOLL_H

typedef enum BoneJoint = { ROOT = 0, HIP, L_HIP, L_KNEE, R_HIP, R_KNEE,
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
}PoseFrame;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------
// - Skeleton stuff
Skeleton InitBaseSkeleton(void);

//----------------------------------------------------------------
// - PoseFrame stuff
// Creates an initial base pose frame
void InitBaseFrame(void);

// Grabs the current base frame and puts it in a PoseFrame struct
PoseFrame CopyBaseFrame(void);
PoseFrame NewBaseFrame(void);

// BoneTransforms - component of PoseFrame
BoneTransforms NewRotationTransform(float xRot, float yRot, float zRot);
BoneTransforms NewTranslationTransform(float xTran, float yTran, float zTran);
BoneTransforms NewBoneTransform(float xRot, float yRot, float zRot, float xTran, float yTran, float zTran);
//----------------------------------------------------------------
// - PoseFrame stuff
void InitRagdoll(void);
//-----------------------------------------------------------------
// Draw ragdoll with PoseFrame rotations
void DrawRagdoll(Skeleton skeletonDef, Ragdoll ragdollDef, PoseFrame pose); 
void DrawRagdollWireFrame(Skeleton skeletonDef, Ragdoll ragdollDef, PoseFrame pose);

#ifdef __cplusplus
}
#endif

// Global Variables Declaration (shared by several modules)
extern Skeleton skeleton;
extern Ragdoll ragdoll;
extern PoseFrame basePoseFrame;

#endif // RAGDOLL_H