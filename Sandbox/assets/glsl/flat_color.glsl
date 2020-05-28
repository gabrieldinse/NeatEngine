
#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_position;
         
uniform mat4 u_viewProjection;
uniform mat4 u_transform;
         
void main()
{
	gl_Position =  vec4(a_position, 1.0) * u_transform * u_viewProjection;	
}

#type fragment
#version 330 core
			
layout(location = 0) out vec4 color;
         
uniform vec4 u_color;
         
in vec3 v_position;
         
void main()
{
	color = u_color;
}