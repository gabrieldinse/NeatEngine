// #Type: vertex
#version 450 core
            
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 textureCoordinate;
layout(location = 3) in int textureIndex;
layout(location = 4) in float tilingFactor;
layout(location = 5) in uint entityIndex;

layout (std140, binding = 0) uniform camera {
    mat4 u_cameraViewProjection;
};

out VertexShaderOut
{
    vec2 textureCoordinate;
    vec4 color;
    flat int textureIndex;
    float tilingFactor;
    flat uint entityIndex;
} vertexShaderOut;


void main()
{
    vertexShaderOut.textureCoordinate = textureCoordinate;
    vertexShaderOut.color = color;
    vertexShaderOut.textureIndex = textureIndex;
    vertexShaderOut.tilingFactor = tilingFactor;
    vertexShaderOut.entityIndex = entityIndex;
    gl_Position = u_cameraViewProjection * position;
}

// #Type: fragment
#version 450 core

layout(location = 0) out vec4 color;
layout(location = 1) out uint entityIndex;

layout (binding = 0) uniform sampler2D u_textures[32];

in VertexShaderOut
{
    vec2 textureCoordinate;
    vec4 color;
    flat int textureIndex;
    float tilingFactor;
    flat uint entityIndex;
} fragmentShaderIn;

void main()
{
    vec4 texture_color = fragmentShaderIn.color;
    switch (fragmentShaderIn.textureIndex)
    {
        case 0:  texture_color *= texture(u_textures[0], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 1:  texture_color *= texture(u_textures[1], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 2:  texture_color *= texture(u_textures[2], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 3:  texture_color *= texture(u_textures[3], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 5:  texture_color *= texture(u_textures[5], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 6:  texture_color *= texture(u_textures[6], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 7:  texture_color *= texture(u_textures[7], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 8:  texture_color *= texture(u_textures[8], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 9:  texture_color *= texture(u_textures[9], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 10: texture_color *= texture(u_textures[10], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 11: texture_color *= texture(u_textures[11], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 12: texture_color *= texture(u_textures[12], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 13: texture_color *= texture(u_textures[13], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 14: texture_color *= texture(u_textures[14], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 15: texture_color *= texture(u_textures[15], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 16: texture_color *= texture(u_textures[16], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 17: texture_color *= texture(u_textures[17], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 18: texture_color *= texture(u_textures[18], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 19: texture_color *= texture(u_textures[19], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 20: texture_color *= texture(u_textures[20], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 21: texture_color *= texture(u_textures[21], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 22: texture_color *= texture(u_textures[22], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 23: texture_color *= texture(u_textures[23], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 24: texture_color *= texture(u_textures[24], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 25: texture_color *= texture(u_textures[25], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 26: texture_color *= texture(u_textures[26], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 27: texture_color *= texture(u_textures[27], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 28: texture_color *= texture(u_textures[28], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 29: texture_color *= texture(u_textures[29], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 30: texture_color *= texture(u_textures[30], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
        case 31: texture_color *= texture(u_textures[31], fragmentShaderIn.textureCoordinate * fragmentShaderIn.tilingFactor); break;
    }

    color = texture_color;
    entityIndex = fragmentShaderIn.entityIndex;
}