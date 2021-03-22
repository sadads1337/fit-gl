#version 330
// in vec4 col;
in vec3 GuroColor;
in vec3 Normal;
in vec3 FragPos;
uniform bool wireframe;

void main()
{
    if(wireframe)
    {
	    gl_FragColor = vec4(1, 0.682, 0, 1.0f);
    }
    else {
        gl_FragColor = vec4(GuroColor, 1.0f);
        // gl_FragColor = col;
    }
    
}
