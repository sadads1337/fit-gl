#include "PreparedScenes.h"
#include "GLDirectedLight.h"
#include "GLPointLight.h"
#include "GLSpotLight.h"
#include "GLTextureLoader.h"
#include "MeshGeneratorCollecrion.h"
#include "ShaderCollection.h"

void init_grid(GLScene& scene, ShaderData& data, const size_t grid_size)
{
    const auto& generator = MeshGeneratorCollection::generators["cube"];
    QVector3D pos = {};

    GLMaterial material;
    material.shininess = 32.0f;

    for (std::size_t i = 0; i < grid_size; ++i) {

        for (std::size_t j = 0; j < grid_size; ++j) {
            pos.setX(static_cast<float>(i) * 2.5f);
            pos.setY(-3);
            pos.setZ(static_cast<float>(j) * 2.5f - 10);

            scene.add_object(data, generator, pos, { 185, 255, 208 }, material);
        }
    }
}



void PreparedScenes::init()
{
    scenes.push_back(default_scene_sphere(ShaderCollection::shaders["phong_normal_mapping"]));

    scenes.push_back(default_scene_sphere(ShaderCollection::shaders["phong_wo_normal_mapping"]));
    scenes.push_back(default_scene_sphere(ShaderCollection::shaders["guro_wo_normal_mapping"]));

    scenes.push_back(default_scene_cube(ShaderCollection::shaders["phong_wo_normal_mapping"]));
    scenes.push_back(default_scene_cube(ShaderCollection::shaders["guro_wo_normal_mapping"]));

    scenes.push_back(default_morphing(ShaderCollection::shaders["morphing"]));
}


GLScene PreparedScenes::default_morphing(ShaderData& data)
{
    GLScene scene;
    const auto grid_size = 20u;


    init_grid(scene, data, grid_size);
    return scene;
}

/*GLScene PreparedScenes::default_scene_sphere(ShaderData& data)
{
    GLScene scene;
    const auto& generator = MeshGeneratorCollection::generators["sphere"];


    GLMaterial material;
    material.shininess = 32.0f;
    material.diffuse = { 255, 255, 255 };
    material.ambient = { 255, 255, 255 };

    const auto distance = 1.5f;
    scene.add_object(data, generator, { -distance, 0, -distance }, { 0, 0, 0 }, material);
    scene.add_object(data, generator, { -distance, 0, distance }, { 0, 0, 0 }, material);
    scene.add_object(data, generator, { distance, 0, distance }, { 0, 0, 0 }, material);
    scene.add_object(data, generator, { distance, 0, -distance }, { 0, 0, 0 }, material);
    scene.add_object(data, generator, { 2*distance, 1, -2*distance }, { 0, 0, 0 }, material);
    scene.add_object(data, generator, { -2*distance, 1, -2*distance }, { 0, 0, 0 }, material);
    scene.add_object(data, generator, { 2*distance, 1, 2*distance }, { 0, 0, 0 }, material);
    scene.add_object(data, generator, { -2*distance, 1, 2*distance }, { 0, 0, 0 }, material);


    for(auto& object : scene.objects) {
        object->transform.rotate(270.f, { 1, 0 ,0 });
    }


    auto& light_object_shader = ShaderCollection::shaders["light_source"];
    const auto& light_object_generator = MeshGeneratorCollection::generators["sphere"];

    const auto& light_sphere_gen = std::dynamic_pointer_cast<GLSphereMeshGenerator>(light_object_generator);
    light_sphere_gen->radius_ = 0.2f;

    const auto light = std::make_shared<GLPointLight>(QVector3D{ 0, 0, 0 }, QColor{ 185, 255, 208 });
    scene.add_light(light, light_object_shader, light_sphere_gen);


    return scene;
}*/

GLScene PreparedScenes::default_scene_cube(ShaderData& data)
{
    GLScene scene;
    const auto& generator = MeshGeneratorCollection::generators["cube"];


    GLMaterial material;
    material.shininess = 32.0f;
    material.diffuse = { 255, 255, 255 };
    material.ambient = { 255, 255, 255 };

    const auto distance = 1.5f;
    scene.add_object(data, generator, { -distance, 0, -distance }, { 0, 0, 0 }, material);
    scene.add_object(data, generator, { -distance, 0, distance }, { 0, 0, 0 }, material);
    scene.add_object(data, generator, { distance, 0, distance }, { 0, 0, 0 }, material);
    scene.add_object(data, generator, { distance, 0, -distance }, { 0, 0, 0 }, material);


    for (auto& object : scene.objects) {
        object->transform.rotate(270.f, { 1, 0 ,0 });
    }


    auto& light_object_shader = ShaderCollection::shaders["light_source"];
    const auto& light_object_generator = MeshGeneratorCollection::generators["sphere"];

    const auto& light_sphere_gen = std::dynamic_pointer_cast<GLSphereMeshGenerator>(light_object_generator);
    light_sphere_gen->radius_ = 0.2f;

    const auto light = std::make_shared<GLPointLight>(QVector3D{ 0, 0, 0 }, QColor{ 185, 255, 208 });
    scene.add_light(light, light_object_shader, light_sphere_gen);


    return scene;
}


GLScene PreparedScenes::default_scene_sphere(ShaderData &data)
{
    GLScene scene;
    const auto& generator = MeshGeneratorCollection::generators["sphere"];


    GLMaterial material;
    GLTextureLoader::load_texture(material, ":/Texture/Earth_Albedo.jpg", ":/Texture/Earth_NormalMap.jpg");
    material.shininess = 32.0f;
    material.diffuse = { 255, 255, 255 };
    material.ambient = { 255, 255, 255 };

    const auto distance = 1.5f;
    scene.add_object(data, generator, { -distance, 0, -distance }, { 0, 0, 0 }, material);
    scene.add_object(data, generator, { -distance, 0, distance }, { 0, 0, 0 }, material);
    scene.add_object(data, generator, { distance, 0, distance }, { 0, 0, 0 }, material);
    scene.add_object(data, generator, { distance, 0, -distance }, { 0, 0, 0 }, material);


    for(auto& object : scene.objects) {
        object->transform.rotate(270.f, { 1, 0 ,0 });
    }


    auto& light_object_shader = ShaderCollection::shaders["light_source"];
    const auto& light_object_generator = MeshGeneratorCollection::generators["sphere"];

    const auto& light_sphere_gen = std::dynamic_pointer_cast<GLSphereMeshGenerator>(light_object_generator);
    light_sphere_gen->radius_ = 0.2f;

    const auto light = std::make_shared<GLPointLight>(QVector3D{ 0, 0, 0 }, QColor{ 185, 255, 208 });
    scene.add_light(light, light_object_shader, light_sphere_gen);


    return scene;
}
