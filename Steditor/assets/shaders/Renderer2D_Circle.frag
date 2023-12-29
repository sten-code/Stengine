#version 450

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_EntityID;

struct VertexOutput
{
	vec3 LocalPosition;
	vec4 Color;
	float Thickness;
	float Fade;
};

layout (location = 0) in VertexOutput Input;
layout (location = 4) in flat int v_EntityID;

void main()
{
	float dist = 1.0 - length(Input.LocalPosition);
	float circle = smoothstep(0.0, Input.Fade, dist);
	circle *= smoothstep(Input.Thickness + Input.Fade, Input.Thickness, dist);
	
	if (circle == 0.0)
		discard;

	o_Color = Input.Color;
	o_Color.a *= circle;

	o_EntityID = v_EntityID;
}