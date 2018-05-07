#version 450 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Position;    //VERTICES EN COORDENADAS DE VISTA


//ESTRUCTURA PARA GUARDAR EL MATERIAL. AHORA UTILIZAMOS TEXTURAS PARA GUARDAR LAS PROPIEDADES DIFUSAS Y ESPECULARES DEL MATERIAL 
struct TMaterial {
    sampler2D Diffuse;
    sampler2D Specular;
    sampler2D Normal;
    float     Shininess;
};  

//ESTRUCTURA PARA GUARDAR LAS LUCES (POSICION, Y PROPIEDADES AMBIENTAL, DIFUSA Y ESPECULAR DE LA LUZ)
struct TLight {
    vec3 Position;

    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

//ESTADO DE OPENGL: MATERIAL Y LUZ (DEL TIPO DE LAS ESTRUCTURAS ANTERIORES)
uniform TMaterial Material;
uniform TLight Light[20];
uniform int cantidad_luces;

//FUNCION QUE CALCULA EL MODELO DE REFLEXION DE PHONG
vec3  Phong () 
{
    //CALCULAR LOS DIFERENTES VECTORES	 
	vec3 n = normalize(vec3(texture(Material.Normal, TexCoords)));
    
	vec3 v = normalize(-Position);
	
    //COMPONENTE AMBIENTAL
    vec3 sumaLuces = Light[0].Ambient * vec3(texture(Material.Diffuse, TexCoords));
    
    //revisar en la teoria que hace cada cosa, porque algo nos estamos dejando
        for(int i=0;i<cantidad_luces;i++){
            vec3 s = normalize(Light[i].Position - Position);
            vec3 r = reflect(-s, n);
            
            //COMPONENTE DIFUSA 
            vec3 Diffuse = Light[i].Diffuse * max(dot(s, n), 0) * vec3(texture(Material.Diffuse, TexCoords));  
            
            //COMPONENTE ESPECULAR  
            vec3 Specular = Light[i].Specular * pow(max(dot(r, v), 0), 1) * vec3(texture(Material.Specular, TexCoords));//pow(max(dot(r, v), 0.0), 1): el 1 es un valor default ya que actualmente no hay brillos
           sumaLuces+= Diffuse + Specular;  
        }  
    return sumaLuces;  
} 

void main()
{
    //FragColor = vec4(0,1,0, 1.0f);
    FragColor = vec4 (Phong(), 1.0);
} 