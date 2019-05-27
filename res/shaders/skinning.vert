#version 330 core

layout(location = 0) in vec3 position; // Position of the vertex
layout(location = 1) in vec3 normal;   // Normal of the vertex
layout(location = 2) in vec2 texCoord; // UV texture coordinates
//
layout(location = 3) in vec4 weights;
layout(location = 4) in ivec4 boneIDs;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
//
uniform mat4 bones[100];

out vec4 normal_worldSpace;
out vec4 position_worldSpace;
out vec4 eye_worldSpace;
out vec2 texc;

void main(){

    mat4 boneTransform = bones[boneIDs[0]]*weights[0] + bones[boneIDs[1]]*weights[1]
    + bones[boneIDs[2]]*weights[2] + bones[boneIDs[3]]*weights[3];



    vec4 posBone = boneTransform*vec4(position, 1.0);
    vec4 normalBone = boneTransform*vec4(normal, 0.0);

    texc = texCoord;
    position_worldSpace = m * posBone;
//    position_worldSpace = m * vec4(position, 1.0);
    normal_worldSpace = vec4(normalize(mat3(transpose(inverse(m))) * normalBone.xyz), 0);
//    normal_worldSpace = vec4(normalize(mat3(transpose(inverse(m))) * normal), 0);
    eye_worldSpace = inverse(v)*vec4(0,0,0,1);
    gl_Position = p*v*m*posBone;
//    gl_Position = p * v * m * vec4(position, 1.0);

}
