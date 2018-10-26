vec4 explode(vec4 position, vec3 direction, float magnitude)
{
//    float magnitude = 2.0;
    vec3 step = direction * ((sin(time) + 1.0) / 2.0) * magnitude;
    return position + vec4(step, 0.0);
}