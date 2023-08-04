
#include "MainObject.h"

MainObject::MainObject() {
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val = 0;
	y_val = 0;
}

MainObject::~MainObject() {
	;
}

void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2]) 
{
	//todo
	if (events.type == SDL_KEYDOWN) {
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			y_val -= HEIGHT_MAIN_OBJECT / SPEED_MAIN_OBJ;
			//todo
			break;
		case SDLK_DOWN:
			y_val += HEIGHT_MAIN_OBJECT / SPEED_MAIN_OBJ;
			//todo
			break;
		case SDLK_RIGHT:
			x_val += WIDTH_MAIN_OBJECT / SPEED_MAIN_OBJ;
			//todo
			break;
		case SDLK_LEFT:
			x_val -= WIDTH_MAIN_OBJECT / SPEED_MAIN_OBJ;
			//todo
			break;

		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			y_val += HEIGHT_MAIN_OBJECT / SPEED_MAIN_OBJ;
			break;
		case SDLK_DOWN:
			y_val -= HEIGHT_MAIN_OBJECT / SPEED_MAIN_OBJ;
			break;
		case SDLK_RIGHT:
			x_val -= WIDTH_MAIN_OBJECT / SPEED_MAIN_OBJ;
			break;
		case SDLK_LEFT:
			x_val += WIDTH_MAIN_OBJECT / SPEED_MAIN_OBJ;
			break;
		default:
			break;
		}
	}
	else if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		BulletObject* p_Bullet = new BulletObject();
		if (events.button.button == SDL_BUTTON_LEFT) {
			p_Bullet->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER);
			p_Bullet->LoadImg(g_name_bullet_main_laser);
			p_Bullet->set_type(BulletObject::LASER);
			Mix_PlayChannel(-1, bullet_sound[1], 0);
		}
		else if(events.button.button == SDL_BUTTON_RIGHT)
		{
			p_Bullet->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_Bullet->LoadImg(g_name_bullet_main_fire);
			p_Bullet->set_type(BulletObject::SPHERE);
			Mix_PlayChannel(-1, bullet_sound[0], 0);
		}
		p_Bullet->SetRect(this->rect_.x + this->rect_.w - 10 , this->rect_.y + this->rect_.h*0.7);
		p_Bullet->set_is_move(true);
		p_Bullet->set_x_val(SPEED_BULLET_MAIN);
		p_Bullet_list_.push_back(p_Bullet);
	}
	else if (events.type == SDL_MOUSEBUTTONUP)
	{

	}
	else
	{
		;//
	}
}

void MainObject::MakeBullet(SDL_Surface* des)
{
	for (int i = 0; i < p_Bullet_list_.size(); i++)
	{
		BulletObject* p_Bullet = p_Bullet_list_.at(i);
		if (p_Bullet != NULL)
		{
			if (p_Bullet->get_is_move()) 
			{
				p_Bullet->Show(des);
				p_Bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			else
			{
				if (p_Bullet != NULL) {
					p_Bullet_list_.erase(p_Bullet_list_.begin() + i);
					delete p_Bullet;
					p_Bullet = NULL;
				}
			}
		}
	}
}

void MainObject::HandleMove() {
	rect_.x += x_val;

	if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH ) {
		rect_.x -= x_val;
	}

	rect_.y += y_val;

	if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 200) {
		rect_.y -= y_val;
	}
	///todo
}

void MainObject::RemoveBullet(const int& idx)
{
	for (int i = 0; i < p_Bullet_list_.size(); i++)
	{
		if (idx < p_Bullet_list_.size())
		{
			BulletObject* p_Bullet = p_Bullet_list_.at(idx);
			p_Bullet_list_.erase(p_Bullet_list_.begin() + idx);

			if (p_Bullet != NULL)
			{
				delete p_Bullet;
				p_Bullet = NULL;
			}
		}
	}
}