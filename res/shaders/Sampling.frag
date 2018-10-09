float SampleShadowMap(sampler2D shadowMap, vec2 coords, float compare){
    return step(texture(shadowMap,coords.xy).r, compare);
}

float SampleShadowMapLinear(sampler2D shadowMap, vec2 coords, float compare, vec2 texelSize){
    vec2 pixelPos = coords/texelSize + vec2(0.5);
    vec2 fracPart = fract(pixelPos);
    vec2 startTexel = (pixelPos - fracPart) * texelSize;

    float blTexel = SampleShadowMap(shadowMap, startTexel, compare);
    float brTexel = SampleShadowMap(shadowMap, startTexel + vec2(texelSize.x, 0.0), compare);
    float tlTexel = SampleShadowMap(shadowMap, startTexel + vec2(0.0, texelSize.y), compare);
    float trTexel = SampleShadowMap(shadowMap, startTexel + texelSize, compare);

    float mixA = mix(blTexel, tlTexel, fracPart.y);
    float mixB = mix(brTexel, trTexel, fracPart.y);

    return mix(mixA, mixB, fracPart.x);
}

float SampleShadowMapPCF(sampler2D shadowMap, vec2 coords, float compare, vec2 texelSize, int level){

    float shadow = 0.0f;
    float count = 0.0f;

    //We sample all the first texels around this fragment's texel. Forming a cube.
    for(int x = -level /*Start at further left of the exact x texel of this fragment*/;
        x <= level /*Upto the right*/;
        ++x){
        for(int y = -level/*Start at further top of the exact y texel of this fragment*/;
            y <= level /*Upto the bottom*/;
            ++y){
            /*
             * Get depth of the fragment relative to the light in orthographic projection.
             * Each texel in the shadow map contains depth data in the .r attribute instead
             * of color like a normal texture.
             *
             * This is essentially the nearest fragment that the light could see. If the current fragment
             * we are test is way further away than the nearest fragment then there is
             * something infront of it.
             * */
            shadow += SampleShadowMapLinear(
                    shadowMap,
                    (coords + vec2(x,y) * texelSize), /*Get the exact texel in the current loop. Remember
                    * the .xy only point to the current fragments texel not the one we want in the current
                    * loop. */
                    compare,
                    texelSize
            );
            count++;
        }
    }

    shadow /= count; /*Find average of the shadows we are collecting from the sample*/

    return shadow;
}

float SampleVarianceShadowMap(sampler2D shadowMap, vec2 coords, float compare){
    vec2 moments = texture(shadowMap,coords).xy;

    float p = step(compare, moments.x);
    float variance = max(moments.y - moments.x * moments.x, 0.00002);

    float d = compare - moments.x;
    float pMax = variance / (variance * d*d);

    return max(max(p, pMax) , 1.0);
}