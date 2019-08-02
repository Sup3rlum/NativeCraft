#version 450

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D ssao;

uniform mat4x4 View;

void main()
{             
    // retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = (transpose(View) * vec4(texture(gNormal, TexCoords).rgb * 2.0 - 1.0, 0.0)).rgb;
    vec3 Albedo = texture(gAlbedo, TexCoords).rgb;
	float AmbientOcclusion = texture(ssao, TexCoords).r;
    
    // then calculate lighting as usual
    vec3 ambient = vec3(0.3f * Albedo * AmbientOcclusion);

	vec3 lightDir = normalize(vec3(1,1,1));

	float diffFactor = max(dot(lightDir, Normal), 0.0);
	vec3 diffuse = Albedo * diffFactor * AmbientOcclusion;

    FragColor = vec4(ambient + diffuse, 1.0);
}