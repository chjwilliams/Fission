#version 330 core


layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;

in DATA
{
    vec4 position;
    vec2 uv;
    float tid;
    vec4 color;
} fs_in;

uniform sampler2D[16] textures;

void main()
{
    float intensity = 1.0 / length(fs_in.position.xy - light_pos);
    vec4 texColor = fs_in.color;
    if (fs_in.tid > 0.0)
    {
        int tid = int(fs_in.tid - 0.5);
        for (int i = 0; i < 16; i++)
        {
            if (i == tid)
            {
                texColor = fs_in.color * texture(textures[i], fs_in.uv);
                break;
            }
        }
        
    }
    
    color = texColor ;//* (intensity * 150);
}



