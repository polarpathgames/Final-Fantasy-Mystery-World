#include "MainMenu.h"
#include "j1Scene.h"
#include "j1App.h"
#include "j1Scene.h"
#include "j1EntityManager.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1UIManager.h"
#include "j1Map.h"
#include "GUI_Button.h"
#include "j1FadeToBlack.h"
#include "GUI_Label.h"
#include "GUI_Image.h"

MainMenu::MainMenu(){}

MainMenu::~MainMenu(){}

bool MainMenu::Awake()
{
	return true;
}

bool MainMenu::Start()
{
	SDL_Rect background_rect = { 0, 0, 1024, 768 };
	background = App->ui_manager->AddImage(0, 0, &background_rect, nullptr, this, nullptr);

	exit_button = (GUI_Button*)App->ui_manager->AddButton(350, 300, {1659, 1575,33,33}, { 0, 0,100,100 }, { 0, 0,10,10 }, this, nullptr);
	//exit_text = (GUI_Label*)App->ui_manager->AddLabel(10, 10, "exit", this, exit_button);
	//exit_button->SetText(exit_text);

	labels.push_back(exit_text);





	return true;
}

bool MainMenu::PreUpdate()
{
	return true;
}

bool MainMenu::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{


	App->fade_to_black->FadeToBlack((j1Module*)App->main_menu, (j1Module*)App->scene);

	}
	

	App->input->GetMousePosition(mouse_x, mouse_y);

	return true;
}

bool MainMenu::PostUpdate()
{
	return true;
}

bool MainMenu::CleanUp()
{
	App->ui_manager->DestroyUI();
	return true;
}

void MainMenu::Interact(GUI* interaction)
{
	if (interaction == exit_button)
		App->ui_manager->DestroyUI();
}

