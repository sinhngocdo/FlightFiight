#pragma once

#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_
#include "Common_Function.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>


#define WIDTH_THREAT 80
#define HEIGHT_THREAT 33
#define UNDER_LIMIT_THREAT 200

class ThreatsObject : public BaseObject
{
public:
	ThreatsObject();
	~ThreatsObject();

	void HandleMove(const int& x_border, const int& y_border);
	void HandeInputAction(SDL_Event events);

	void set_x_val(const int& val) { x_val_ = val; }
	void set_y_val(const int& val) { y_val_ = val; }
	int get_x_val() const { return x_val_; }
	int get_y_val() const { return y_val_; }

	void SetBulletList(std::vector<BulletObject*> Bullet_list) { p_Bullet_list_ = Bullet_list; }
	std::vector<BulletObject*> GetBulletList() const { return p_Bullet_list_; }

	void InitBullet(BulletObject* p_Bullet);
	void MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit);
	void Reset(const int& x_border);
	void ResetBullet(BulletObject* p_Bullet);
private:
	int x_val_;
	int y_val_;

	std::vector<BulletObject*> p_Bullet_list_;
};


#endif // !THREATS_OBJECT_H_
