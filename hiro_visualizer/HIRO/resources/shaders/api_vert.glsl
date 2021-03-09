#include "api_definitions.glsl"

// Returns full instance transformation. Returns identity when instancing disabled.
mat4 GetTransfInstance()
{
    return (USING_INSTANCING) ? INSTANCES[gl_InstanceID] * PRE_INSTANCE_MAT : mat4(1.0f);
} 

// Returns full model transformation. Instancing transformations included if enabeld.
mat4 GetTransfModel()
{
    return MODEL_MAT * GetTransfInstance();
} 

// Returns full model-view transformation. Instancing transformations included if enabeld.
mat4 GetTransfView()
{
    return GetViewMat() * GetTransfModel();
} 

// Returns full model-view-projection transformation. Instancing transformations included if enabeld.
mat4 GetTransfProjection()
{
    return GetProjMat() * GetTransfView();
} 
