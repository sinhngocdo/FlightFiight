
#include "ThreatsObject.h"

ThreatsObject::ThreatsObject() {
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;

	x_val_ = 0;
	y_val_ = 0;
}

ThreatsObject::~ThreatsObject() {
	if (p_Bullet_list_.size() > 0)
	{
		for (int i = 0; i < p_Bullet_list_.size(); i++)
		{
			BulletObject* p_Bullet = p_Bullet_list_.at(i);
			if (p_Bullet != NULL)
			{
				delete p_Bullet;
				p_Bullet = NULL;
			}
		}
		p_Bullet_list_.clear();
	}
}

void ThreatsObject::MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for (unsigned int i= 0; i < unsigned(p_Bullet_list_.size()); i++)
	{
		BulletObject* p_Bullet = p_Bullet_list_.at(i);
		if (p_Bullet)
		{
			if (p_Bullet->get_is_move())
			{
				p_Bullet->Show(des);
				p_Bullet->HandleMoveRightToLeft();
			}
			else
			{
				p_Bullet->set_is_move(true);
				p_Bullet->SetRect(rect_.x, rect_.y + int(rect_.h * 0.5));
			}
		}
	}
}

void ThreatsObject::InitBullet(BulletObject* p_Bullet)
{
	if (p_Bullet != NULL)
	{
		bool ret = p_Bullet->LoadImg(g_name_bullet_threats);
		if (ret)
		{
			p_Bullet->set_is_move(true);
			p_Bullet->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_Bullet->set_type(BulletObject::SPHERE);
			p_Bullet->SetRect(rect_.x, rect_.y + int(rect_.h * 0.5));
			p_Bullet->set_x_val(SPEED_BULLET_THREATS);
			p_Bullet_list_.push_back(p_Bullet);
		}
	}
}

void ThreatsObject::HandleMove(const int& x_border, const int& y_border) {
	//todo
	rect_.x -= x_val_;
	if (rect_.x < 0)
	{
		rect_.x = SCREEN_WIDTH;
		int rand_y = rand() % 400;
		if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
		{
			rand_y = int(SCREEN_HEIGHT * 0.3);
		}
		rect_.y = rand_y;
	}
}

void ThreatsObject::HandeInputAction(SDL_Event events) {
	//todo
}


void ThreatsObject::Reset(const int& x_border)
{
	rect_.x = x_border;
	int rand_y = rand() % 400;
	if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
	{
		rand_y = int(SCREEN_HEIGHT * 0.3);
	}
	rect_.y = rand_y;

	for (int i = 0; i < p_Bullet_list_.size(); i++)
	{
		BulletObject* p_Bullet = p_Bullet_list_.at(i);
		if (p_Bullet != NULL)
		{
			ResetBullet(p_Bullet);
		}
	}

}


void ThreatsObject::ResetBullet(BulletObject* p_Bullet)
{
	p_Bullet->SetRect(rect_.x, rect_.y + int(rect_.h * 0.5));
}