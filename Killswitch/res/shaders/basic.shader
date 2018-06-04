#shader vertex
#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 vTex;

out vec2 voutTex;

void main()
{
	gl_Position = vec4(pos.xy, 1.0f, 1.0f);
	voutTex = vTex;
}



#shader fragment
#version 330 core
layout(location = 0) out vec4 color;

in vec2 voutTex;
uniform sampler2D finalTexture;

void main()
{
	//color = vec4(1.0f, 0.0f, 1.0f, 1.0f);
	color = texture(finalTexture, voutTex);
}