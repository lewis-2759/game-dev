#version 440

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;


//uniforms

uniform Material material;
uniform vec3 lightPos0;
uniform vec3 cameraPos;


//Functions
vec3 calcAmbient(Material material)
{
return material.ambient;
}


vec3 calcDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0)
{
	//position to light noramlized
	//from on right, where it goes to on left
	vec3 posToLightDirVec = normalize(lightPos0 - vs_position);
	float diffuse = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
	vec3 diffuseFinal = material.diffuse * diffuse;

	return diffuseFinal;
}

vec3 calcSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0, vec3 cameraPos)
{
	vec3 lightToPosDirVec = normalize(vs_position - lightPos0);	//light to pos so light - pos
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(cameraPos - vs_position); //position to camera
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec),0), 30); //last num is strength
	vec3 specularFinal = material.specular * specularConstant * texture(material.specularTex, vs_texcoord).rgb;

	return specularFinal;
}


void main()
{
	//fs_color = vec4(vs_color, 1.f);

	//ambient light
	vec3 ambientFinal = calcAmbient(material);

	//diffuse light
	vec3 diffuseFinal = calcDiffuse(material, vs_position, vs_normal, lightPos0);

	//specular light
	vec3 specularFinal = calcSpecular(material, vs_position, vs_normal, lightPos0, cameraPos);



	//attenuation



	//final light
	fs_color = texture(material.diffuseTex, vs_texcoord) 
	* (vec4(ambientFinal, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));
}