#version 330

// uniform highp float morphFactor;
struct LightSource
{
   vec3 position;
   vec4 color;   
   float intensity;
};

in vec3 posAttr;
in vec4 colAttr;
in vec3 normalAttr;

uniform highp mat4 model;
uniform highp mat4 normal_matrix;
uniform highp mat4 view;
uniform highp mat4 projection;

uniform vec4 color;
uniform vec4 ambient;

uniform vec3 cameraPos;

uniform LightSource lights[10];
uniform int lightsCount;

out vec3 FragPos;
out vec3 Normal;
out vec3 GuroColor;

vec3 getDiffuseColor()
{
   return color.xyz;
}

float attenuation(float dist)
{
   return 1.0f / (1.0f + 0.01f * dist + 0.01f * dist*dist);
}

vec3 getLighting()
{
   vec3 dirToFrag = normalize(FragPos - cameraPos);
   vec3 norm = normalize(Normal);
   
   vec3 result = vec3(0);
   vec3 baseColor = getDiffuseColor();
   
   for(int i = 0; i < lightsCount; ++i) {
      vec3 dirToLight = normalize(lights[i].position - FragPos);

      vec3 diffuse = baseColor * vec3(lights[i].color);
      diffuse = diffuse * max(dot(dirToLight, norm), 0.0f);

      vec3 reflectDir = reflect(-dirToLight, norm);
      float spec = pow(max(dot(-dirToFrag, reflectDir), 0.0), 8.0);
      result += (diffuse + spec) * attenuation(length(lights[i].position - FragPos));
   }

   result = result + ambient.rgb * 0.089f;
   return result;
}
// out vec4 col;

void main()
{
    // highp vec4 newPos = vec4(posAttr * (1 - morphFactor ) + 
                             // morphFactor * normalize(posAttr), 1.);
    
    FragPos = vec3(model * vec4(posAttr, 1.0));
    //Normal = mat3(transpose(inverse(model))) * normalAttr;
    Normal = mat3(normal_matrix) * normalAttr;

    GuroColor = getLighting();

    gl_Position = projection * view * model * vec4(posAttr, 1.0);


    // col = colAttr;
}
