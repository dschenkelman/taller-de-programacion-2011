#include "ExistingUsernameActivity.h"
#include "CreatePlayerActivity.h"

ExistingUsernameActivity::ExistingUsernameActivity(int width, int height):Activity(width, height)
{
}

void ExistingUsernameActivity::onLoad()
{
	// cabecera
	this->banner = new ImageView("Images/dual.bmp");
	this->banner->setX(5); this->banner->setY(5);
	this->banner->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// titulo
	this->title = new RichTextView("Error", RichTextView::NORMAL);
	this->title->setX(100); this->title->setY(50);
	this->title->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// contenido
	RichTextView* rtv = new RichTextView("Unavailable username", RichTextView::NORMAL);
	rtv->setX((this->getWidth()/2) - 153); rtv->setY(200);

	this->arrowMenu = new OptionArrowMenuView();
	this->arrowMenu->addOption("back");
	this->arrowMenu->setY(this->getHeight() - 50); this->arrowMenu->setX(this->getWidth()/2 - 80);

	this->add(this->banner);
	this->add(this->title);
	this->add(rtv);
	this->add(this->arrowMenu);
}

Activity* ExistingUsernameActivity::notify(SDL_Event e)
{
	Activity* nextActivity = NULL;
	switch(e.type){
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_RETURN:
					if(this->arrowMenu->getSelectedOption() == "back")
					{
						nextActivity = new CreatePlayerActivity(this->getWidth(), this->getHeight());
					}
					break;
			}
			break;
	}

	return nextActivity;
}

ExistingUsernameActivity::~ExistingUsernameActivity(void)
{
}
