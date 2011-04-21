{ GluonCore::GluonObject(Material)    
    vertexShader string(<<<
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

attribute vec3 vertex;
attribute vec4 color;
attribute vec2 uv0;

varying vec4 out_color;
varying vec2 out_uv0;
varying vec4 out_lighting;

void main()
{
    mat4 modelViewMatrix = modelMatrix * viewMatrix;
    gl_Position = vec4(vertex, 1.0) * (modelViewMatrix * projectionMatrix);
    out_lighting = vec4(vertex, 1.0) * modelViewMatrix;
    out_color = color;
    out_uv0 = uv0;
}
    <<<)

    fragmentShader string(<<<
uniform sampler2D texture0;
uniform vec4 textureParameters;

uniform vec4 diffuseColor;
uniform vec4 ambientColor;
uniform vec4 specularColor;
uniform vec4 emissiveColor;

uniform vec3 lightPosition;
uniform float lightIntensity;
uniform vec4 lightColor;
uniform vec3 lightAmbDiffSpec;
uniform vec3 lightAttenuation;

uniform float saturation;

varying vec4 out_color;
varying vec2 out_uv0;
varying vec4 out_lighting;

void main()
{
    vec4 finalColor = emissiveColor;

    float dist = length(lightPosition - out_lighting.xyz);
    float intensity = lightIntensity / dot(lightAttenuation, vec3(1.0, dist, dist * dist));

    highp vec2 realUV = vec2(textureParameters.x + out_uv0.x * textureParameters.z, textureParameters.y + out_uv0.y * textureParameters.w);

    vec4 diffuse = diffuseColor * texture2D(texture0, realUV);

    vec3 normal = vec3(0.0, 0.0, 1.0);

    /* Ambient Component */
    finalColor += intensity * (lightColor * lightAmbDiffSpec.r) * ambientColor;
    /* Diffuse Component */
    finalColor += intensity * (lightColor * lightAmbDiffSpec.y) * diffuse * max(0.0, dot(normal, lightPosition));
    /* Specular Component */
    //vec3 viewVector = normalize(-lightingPosition.xyz);

    vec4 noSaturationColor = vec4(finalColor.r + finalColor.b + finalColor.g / 3.0);
    finalColor = (finalColor * saturation) + (noSaturationColor * (1.0 - saturation));

    finalColor.a = diffuse.a;

    gl_FragColor = finalColor;
}
    <<<)

}