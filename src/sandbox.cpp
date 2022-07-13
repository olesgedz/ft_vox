#include "sandbox.h"
#include "Chunk.h"
#include "World.h"

bool operator<(glm::vec3&& l, glm::vec3&& other) noexcept
{
	return 1;
}
void Sandbox::place_ent(Engine* eng)
{
//    Entity*  torso = new Entity();
//    Entity*  head = new Entity();
//    Entity*  upperArm1 = new Entity();
//    Entity*  foreArm1 = new Entity();
//    Entity*  upperArm2 = new Entity();
//    Entity*  foreArm2 = new Entity();
//    Entity*  upperLeg1 = new Entity();
//    Entity*  foreLeg1 = new Entity();
//    Entity*  upperLeg2 = new Entity();
//    Entity*  foreLeg2 = new Entity();
//    Model* mod = new Model();
//    Model* lightMod = new Model();
	Chunk::noise =FastNoiseLite();
	Chunk::noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
//	Chunk::noise.SetFractalType(FastNoiseLite::FractalType_FBm);



	Chunk::noise.SetFrequency(0.025f);

}