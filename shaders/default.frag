#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D tex1;
uniform sampler2D tex2;


void main()
{
    // FragColor = vec4(ourColor, 1.0f);
    // FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0f);
    FragColor = mix(texture(tex1, TexCoord), texture(tex2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
}