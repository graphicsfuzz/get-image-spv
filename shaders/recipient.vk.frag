#version 450

#ifdef GL_ES
#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
precision highp int;
#else
precision mediump float;
precision mediump int;
#endif
#endif

#ifndef REDUCER
#define _GLF_ZERO(X, Y)          (Y)
#define _GLF_ONE(X, Y)           (Y)
#define _GLF_FALSE(X, Y)         (Y)
#define _GLF_TRUE(X, Y)          (Y)
#define _GLF_IDENTITY(X, Y)      (Y)
#define _GLF_DEAD(X)             (X)
#define _GLF_FUZZED(X)           (X)
#define _GLF_WRAPPED_LOOP(X)     X
#define _GLF_WRAPPED_IF_TRUE(X)  X
#define _GLF_WRAPPED_IF_FALSE(X) X
#define _GLF_SWITCH(X)           X
#endif

// END OF GENERATED HEADER

layout(location = 0) out vec4 _GLF_color;

precision mediump float;

layout(binding = 0) uniform _GLF_UniformBufferObject0 {
    vec2 resolution;
} _GLF_ubo0;
vec3 pickColor(int i)
{
    return vec3(float(i) / 100.0);
}
void main()
{
    float height = _GLF_ubo0.resolution.y;
    float width = _GLF_ubo0.resolution.x;
    float c_re = (gl_FragCoord.x - width / 2.0) * 4.0 / width;
    float c_im = (gl_FragCoord.y - height / 2.0) * 4.0 / width;
    float x = 0.0, y = 0.0;
    int iteration = 0;
    for(
        int k = 0;
        k < 1000;
        k ++
    )
        {
            if(x * x + y * y > 4.0)
                {
                    break;
                }
            float x_new = x * x - y * y + c_re;
            y = 2.0 * x * y + c_im;
            x = x_new;
            iteration ++;
        }
    if(iteration < 1000)
        {
            _GLF_color = vec4(pickColor(iteration), 1.0);
        }
    else
        {
            _GLF_color = vec4(0.0, 0.0, 0.0, 1.0);
        }
}
