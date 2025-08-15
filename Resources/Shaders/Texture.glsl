// #Type: vertex
#version 450 core
            
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 textureCoordinate;
layout(location = 3) in int textureIndex;
layout(location = 4) in float tilingFactor;

uniform mat4 u_cameraTransform;

out VS_OUT
{
    vec2 textureCoordinate;
    vec4 color;
    flat int textureIndex;
    float tilingFactor;
} vs_out;


void main()
{
    vs_out.textureCoordinate = textureCoordinate;
    vs_out.color = color;
    vs_out.textureIndex = textureIndex;
    vs_out.tilingFactor = tilingFactor;
    gl_Position = u_cameraTransform * position;
}

// #Type: fragment
#version 450 core

layout(location = 0) out vec4 color;

uniform sampler2D u_textures[32];

in VS_OUT
{
    vec2 textureCoordinate;
    vec4 color;
    flat int textureIndex;
    float tilingFactor;
} fs_in;
   
   
void main()
{
    vec4 texture_color = fs_in.color;
    switch (fs_in.textureIndex)
    {
        case 0:  texture_color *= texture(u_textures[0], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 1:  texture_color *= texture(u_textures[1], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 2:  texture_color *= texture(u_textures[2], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 3:  texture_color *= texture(u_textures[3], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 5:  texture_color *= texture(u_textures[5], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 6:  texture_color *= texture(u_textures[6], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 7:  texture_color *= texture(u_textures[7], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 8:  texture_color *= texture(u_textures[8], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 9:  texture_color *= texture(u_textures[9], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 10: texture_color *= texture(u_textures[10], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 11: texture_color *= texture(u_textures[11], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 12: texture_color *= texture(u_textures[12], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 13: texture_color *= texture(u_textures[13], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 14: texture_color *= texture(u_textures[14], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 15: texture_color *= texture(u_textures[15], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 16: texture_color *= texture(u_textures[16], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 17: texture_color *= texture(u_textures[17], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 18: texture_color *= texture(u_textures[18], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 19: texture_color *= texture(u_textures[19], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 20: texture_color *= texture(u_textures[20], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 21: texture_color *= texture(u_textures[21], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 22: texture_color *= texture(u_textures[22], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 23: texture_color *= texture(u_textures[23], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 24: texture_color *= texture(u_textures[24], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 25: texture_color *= texture(u_textures[25], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 26: texture_color *= texture(u_textures[26], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 27: texture_color *= texture(u_textures[27], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 28: texture_color *= texture(u_textures[28], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 29: texture_color *= texture(u_textures[29], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 30: texture_color *= texture(u_textures[30], fs_in.textureCoordinate * fs_in.tilingFactor); break;
        case 31: texture_color *= texture(u_textures[31], fs_in.textureCoordinate * fs_in.tilingFactor); break;
    }
    color = texture_color;
}