#version 450

layout(location = 0) out vec4 outColor;


void main(void) { 
  outColor = vec4(gl_FragCoord.x/256.0, gl_FragCoord.y/256.0, 1.0, 1.0);
}

