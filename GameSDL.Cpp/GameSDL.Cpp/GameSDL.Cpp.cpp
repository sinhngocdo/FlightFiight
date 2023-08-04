// GameSDL.Cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "PlayerPower.h"
#include "TextObject.h"

#undef main

TTF_Font* g_font_text = NULL;
TTF_Font* g_font_menu = NULL;


bool Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        return false;
    }
    g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    if (g_screen == NULL)
    {
        return false;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        return false;
    }
    //read file wav audio
    g_sound_bullet[0] = Mix_LoadWAV(g_name_audio_bullet_main_fire);
    g_sound_bullet[1] = Mix_LoadWAV(g_name_audio_bullet_main_laser);
    g_sound_exp[0] = Mix_LoadWAV(g_name_audio_exp_threats);
    g_sound_exp[1] = Mix_LoadWAV(g_name_audio_exp_main);

    if (g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[0] == NULL || g_sound_exp[1] == NULL)
    {
        return false;
    }

    if (TTF_Init() == -1)
    {
        return false;
    }

    g_font_text = TTF_OpenFont("XeroxSansSerifWideBoldOblique.ttf", 20);
    g_font_menu = TTF_OpenFont("XeroxSansSerifWideBoldOblique.ttf", 50);
    if (g_font_text == NULL || g_font_menu == NULL)
    {
        return false;
    }

    return true;

}


int main(int arc, char* argv[])
{
    bool is_run_screen = true;
    int bkgn_x = 0;
    bool is_quit = false;

    if (Init() == false) 
    {
        return 0;
    }
    g_Bground = SDLCommonFunc::LoadImage(g_name_bk_ground);
    if (g_Bground == NULL)
    {
        return 0;
    }

    //make player power
    PlayerPower player_power;
    player_power.Init();

    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);

    TextObject mark_game;
    mark_game.SetColor(TextObject::WHITE_TEXT);


    //make player main object
    MainObject plane_object;
    plane_object.SetRect(POS_X_START_MAIN_OBJ, POS_Y_START_MAIN_OBJ);
    bool ret = plane_object.LoadImg(g_name_main_obj);
    if (ret == false) {
        std::cout << "Fail to open this file" << std::endl;
        return 0;
    }

    //init explosion object
    ExplosionObject exp_main;
    ret = exp_main.LoadImg(g_name_exp_main);
    exp_main.Set_clip();
    if (ret == false)
    {
        return 0;
    }

    //init explosion threat
    ExplosionObject exp_threat;
    ret = exp_threat.LoadImg(g_name_exp_threats);
    exp_threat.Set_clip();
    if (ret == false)
    {
        return 0;
    }



    //make threatsobject
    ThreatsObject* p_threats = new ThreatsObject[NUM_THREAT];

    for (int t = 0; t < NUM_THREAT; t++)
    {
        ThreatsObject* p_threat = (p_threats + t);
        if (p_threat)
        {
            ret = p_threat->LoadImg(g_name_threats);
            if (ret == false) {
                std::cout << "Fail to open this file" << std::endl;
                return 0;
            }

            int rand_y = rand() % 400;
            if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
            {
                rand_y = SCREEN_HEIGHT * 0.3;
            }

            p_threat->SetRect(SCREEN_WIDTH + t * VAL_OFFSET_START_POST_THREAT, rand_y);
            p_threat->set_x_val(SPEED_THREAT);

            BulletObject* p_Bullet = new BulletObject();
            p_threat->InitBullet(p_Bullet);
        }
    }

    unsigned int die_number = 0;
    unsigned int mark_value = 0;

    int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_menu);
    if (ret_menu == 1)
    {
        is_quit = true;
    }

    
    while (!is_quit)
    {
        while (SDL_PollEvent(&g_event))
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
                break;
            }
            plane_object.HandleInputAction(g_event, g_sound_bullet);

        }

        //Apply Background

        //case background1
        /*bkgn_x -= SPEED_SCREEN;
        SDLCommonFunc::ApplySurface(g_Bground, g_screen, bkgn_x, 0);
        SDLCommonFunc::ApplySurface(g_Bground, g_screen, bkgn_x + SCREEN_WIDTH, 0);
        if (bkgn_x <= -SCREEN_WIDTH)
        {
            bkgn_x = 0;
        }*/

        //case background2
        if (is_run_screen == true)
        {
            bkgn_x -= SPEED_SCREEN;
            if (bkgn_x <= -(WIDTH_BACKGROUND - SCREEN_WIDTH))
            {
                is_run_screen = false;
            }
            else
            {
                SDLCommonFunc::ApplySurface(g_Bground, g_screen, bkgn_x, 0);
            }
        }
        else
        {
            SDLCommonFunc::ApplySurface(g_Bground, g_screen, bkgn_x, 0);
        }


        //show player power
        player_power.Render(g_screen);

        //implement main object
        plane_object.HandleMove();
        plane_object.Show(g_screen);
        plane_object.MakeBullet(g_screen);
        
        //implement run Threats
        for (int tt = 0; tt < NUM_THREAT; tt++)
        {
            ThreatsObject* p_threat = (p_threats + tt);
            if (p_threat)
            {
                p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(g_screen);
                p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);


                //check collision bullet -> main
                bool is_col_tt;
                std::vector<BulletObject*> Bullet_list_threat = p_threat->GetBulletList();
                for (int tm = 0; tm < Bullet_list_threat.size(); tm++)
                {
                    BulletObject* p_Bullet_tt = Bullet_list_threat.at(tm);
                    if (p_Bullet_tt != NULL)
                    {
                        is_col_tt = SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_Bullet_tt->GetRect());
                        if (is_col_tt)
                        {
                            p_threat->ResetBullet(p_Bullet_tt);
                            break;
                        }
                    }
                }


                //check collision main and threat
                bool is_col = SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_threat->GetRect());
                if (is_col || is_col_tt)
                {
                    for (int ex = 0; ex < 4; ex++)
                    {
                        int x_pos = (plane_object.GetRect().x + plane_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
                        int y_pos = (plane_object.GetRect().y + plane_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;

                        exp_main.Set_frame(ex);
                        exp_main.SetRect(x_pos, y_pos);
                        exp_main.ShowEx(g_screen);
                        //update screen
                        if (SDL_Flip(g_screen) == -1)
                        {
                            return 0;
                        }
                    }
                    Mix_PlayChannel(-1, g_sound_exp[1], 0);

                    die_number++;
                    if (die_number <= 2)
                    {
                        SDL_Delay(1000);
                        plane_object.SetRect(POS_X_START_MAIN_OBJ, POS_Y_START_MAIN_OBJ);
                        player_power.Decrease();
                        player_power.Render(g_screen);
                        if (SDL_Flip(g_screen) == -1)
                        {
                            delete[] p_threats;
                            SDLCommonFunc::CleanUp();
                            SDL_Quit();
                            return 0;
                        }
                    }
                    else
                    {
                        if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK) == IDOK)
                        {
                            delete[] p_threats;
                            SDLCommonFunc::CleanUp();
                            SDL_Quit();
                            return 1;
                        }
                    }
                }

                //check collision bullet -> threat
                std::vector<BulletObject*> Bullet_list = plane_object.GetBulletList();
                for (int im = 0; im < Bullet_list.size(); im++)
                {
                    BulletObject* p_Bullet = Bullet_list.at(im);
                    if (p_Bullet != NULL)
                    {
                        bool ret_col = SDLCommonFunc::CheckCollision(p_Bullet->GetRect(), p_threat->GetRect());
                        if (ret_col)
                        {
                            mark_value++;
                            for (int et = 0; et < 4; et++)
                            {
                                int x_pos = (p_threat->GetRect().x + p_threat->GetRect().w * 0.5) - EXP_WIDTH * 0.5;
                                int y_pos = (p_threat->GetRect().y + p_threat->GetRect().h * 0.5) - EXP_HEIGHT * 0.5;

                                exp_threat.Set_frame(et);
                                exp_threat.SetRect(x_pos, y_pos);
                                exp_threat.ShowEx(g_screen);
                                //update screen
                                if (SDL_Flip(g_screen) == -1)
                                {
                                    return 0;
                                }
                            }

                            p_threat->Reset(SCREEN_WIDTH + tt * 400);
                            plane_object.RemoveBullet(im);

                            Mix_PlayChannel(-1, g_sound_exp[0], 0);
                        }
                    }
                }

                

            }
        }

        //show time for game 
        std::string str_time = "Time : ";
        UINT32 time_val = SDL_GetTicks()/1000;
        std::string str_val = std::to_string(time_val);
        str_time += str_val;
        
        time_game.SetText(str_time);
        time_game.SetRect(SCREEN_WIDTH - 200, 10);
        time_game.CreateGameText(g_font_text, g_screen);

        //Show mark to screen
        std::string val_str_mark = std::to_string(mark_value);
        std::string strMark("Mark: ");
        strMark += val_str_mark;
        mark_game.SetText(strMark);
        mark_game.CreateGameText(g_font_text, g_screen);

        //update screen
        if (SDL_Flip(g_screen) == -1)
        {
            return 0;
        }
    }

    delete[] p_threats;

    SDLCommonFunc::CleanUp();
    SDL_Quit();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
