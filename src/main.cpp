#include <insolence/insolence.h>
#include <insolence/component/mesh_renderable.h>
#include <insolence/system/point_light_system.h>

struct Game : BaseGameWorld
{
	Camera *camera;
	Mesh *mesh;

	Entity *plane;
	Entity *cube;
	std::vector<Entity*> entities;

	void Initialise()
	{
		srand(time(NULL));
		entity_manager->AddLogicSystem<PointLightSystem>();

		camera = new Camera(GetWindow());
		camera->PanX(4);
		camera->pos.MoveZ(10);
		camera->pos.MoveY(6.f);

		mesh = Mesh::LoadFile("assets/crate.obj");


		for(int i = 0; i < 8; ++i)
		{
			for(int j = 0; j < 4; ++j)
			{
				Entity *e = entity_manager->CreateEntity();
				e->Add<PointLight>();

				e->Get<Transform>()->SetPos(i * 2.f, 0.f, -j * 2.5f);

				e->Get<PointLight>()->light->diffuse = glm::vec3(
						rand() % 256 / 128.f,
						rand() % 256 / 128.f,
						rand() % 256 / 128.f);

				entities.push_back(e);
			}
		}

		plane = entity_manager->CreateEntity();
		plane->Add<MeshRenderable>(mesh);
		plane->Get<Transform>()->SetScale(glm::vec3(30.f, 0.25f, 30.f));
		plane->Get<Transform>()->MoveY(-0.75f);

		cube = entity_manager->CreateEntity();
		cube->Add<MeshRenderable>(mesh);
		cube->Get<Transform>()->SetScale(glm::vec3(0.5f));
	}

	int iiii = 0;

	void Update(const GameTime &gametime)
	{
		if(iiii++ < 2)
			log(Log::INFO, "%s - Log %d", __FUNCTION__, iiii);

		float speed = 0.05f * gametime.GetDeltaTime();
		if(Input::GetKey(JKEY_KEY_LEFT))
			cube->Get<Transform>()->MoveX(-speed);
		if(Input::GetKey(JKEY_KEY_RIGHT))
			cube->Get<Transform>()->MoveX(speed);
		if(Input::GetKey(JKEY_KEY_UP))
			cube->Get<Transform>()->MoveZ(-speed);
		if(Input::GetKey(JKEY_KEY_DOWN))
			cube->Get<Transform>()->MoveZ(speed);

		glm::vec3 camera_pos = cube->Get<Transform>()->GetPos();
		camera->lookat.SetPos(camera_pos);
		camera_pos.y += 3.f;
		camera_pos.z += 5.f;
		camera->pos.SetPos(camera_pos);
	}

	void Unload()
	{
		delete camera;
		delete mesh;
	}
};

int main()
{
	Game *game = new Game();
	game->Run();

	delete game;
	return 0;
}
