uniform mat4 modelViewProjectionMatrix;
uniform mat4 transformMatrix;
uniform mat3 normalMatrix;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 materialAmbient;
uniform vec4 materialDiffuse;
uniform vec3 materialEmission;
uniform vec3 materialSpecular;
uniform float materialShininess;
uniform bool hasColorVertex;
attribute vec4 inColor;
attribute vec4 inPosition;
attribute vec3 inNormal;
attribute vec2 inTexCoord;
varying vec4 outColor;
varying vec2 outTexCoord;
const float kOne = 1.0;
const float kZero = 0.0;

void main() {
#if 1
    vec4 color = vec4(materialAmbient * lightColor + materialDiffuse.rgb * lightColor, materialDiffuse.a);
#else
    vec3 normal = normalize(normalMatrix * inNormal);
    vec3 light = normalize(normalMatrix * lightPosition - position.xyz);
    if (hasColorVertex) {
        color = materialAmbient * inColor;
    }
    else {
        color = materialAmbient;
    }
    color += materialEmission;
    float diffuse = max(dot(light, normal), kZero);
    if (diffuse != kZero) {
        vec3 view = normalize(position.xyz);
        vec3 halfway = normalize(light - view);
        float specular = pow(max(dot(normal, halfway), kZero), materialShininess);
        if (hasColorVertex) {
            color += materialDiffuse * diffuse * inColor + materialSpecular * specular;
        }
        else {
            color += materialDiffuse * diffuse + materialSpecular * specular;
        }
    }
#endif
    outColor = color;
    outTexCoord = inTexCoord;
    gl_Position = modelViewProjectionMatrix * transformMatrix * inPosition;
}

