#pragma once
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "BaseObject.h"
#include "Common_Function.h"
#include "BulletObject.h"
#include <vector>

#define WIDTH_MAIN_OBJECT 77
#define HEIGHT_MAIN_OBJECT 52

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();
	
	void HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2]);
	void HandleMove();

	void SetBulletList(std::vector<BulletObject*> Bullet_list) { p_Bullet_list_ = Bullet_list; }
	std::vector<BulletObject*> GetBulletList() const { return p_Bullet_list_; }
	void MakeBullet(SDL_Surface* g_screen);
	void RemoveBullet(const int& idx);
private:
	int x_val;
	int y_val;

	std::vector<BulletObject*> p_Bullet_list_;
};

#endif //MAIN_OBJECT_H_