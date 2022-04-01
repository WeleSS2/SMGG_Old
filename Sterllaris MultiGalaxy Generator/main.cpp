/*
gButtons 0 = Add Galaxy
gButtons 1 = Galaxies Options
gButtons 2 = 
gButtons 3 = Settings
gButtons 4 = 
gButtons 5 = Files&Play
gButtons 6 = 
gButtons 7 = Game Settings
gButtons 8 = Laucher Settings
gButtons 9 = Patch Settings
gButtons 10 = Import
gButtons 11 = Export
gButtons 12 = Save&Play
gButtons 13 = Exit

15 - Generate Hyperlanes
16 - Redraw Hyperlanes
17 - Remove Hyperlanes
18 - Redraw in Galaxy
19 - Remove in Galaxy
20 = edit
21 = remove
22 = redraw galaxy
23 - Edit Patch button
28 - Clear Map
29 - Random Galaxy
30 - Choose Circle or Ring Shape
31 - Choose x-ARms galaxy schape
35 - Game Settings
36 - Launcher Settings
37 - Random Settings
38 - Patch Settings
From 50 CUSTOM SIZE:
50 - Empire am
51 - Fallen am
52 - Maruder am
53 - Checkbox random
54 - Checkbox Multiple Leviathans
55 - Min hyperlanes am
56 - Max hyperlanes am
60 - Checkbox disable failed generate warn
61 - Checkbox disable wrong text warn
62 - Checkbox Show Hyperlanes


98 - Checkbox initializers
99 - Checkbox save to a game
100 - Checkbox SMGG Hyperlanes

110 - Checkbox Enable Circle
111 - Checkbox Enable Spiral
112 - Checkbox Galaxy Resizing
113 - Galaxy size from
114 - Galaxy size to
115 - Hyperlanes max length from
116 - Hyperlanes max length to
117 - Circle stars from
118 - Circle stars to
119 - Spiral stars from
120 - Spiral stars from
121 - Square factor
122 - Arm max width from
123 - Arm max width to
124 - Arm random width from
125 - Arm random width to
126 - Rotation factor
128 - Arm amount from
129 - Arm amount to
130 - Size ratio
131 - Arm ratio
132 - Arm width ratio

150 - 200 Boxy dla galaktyk

Inicjalizatory:
0 - system jest wolny lub zablokowany (false = wolny, true = zablokowany)
1 - zwyk³e imperium
2 - Upad³e Imperium
3 - Leviathany
4 - Mega
5 - Maruderzy

Laczenie hiperliniami
Zasieg
1      1 
1.5   1-2
2     1-3
2.5   2-3
3     2-4
3.5   2-5
4     3-5
4.5   3-6
5     3-7


Dodac nebule 
nebula = {
        name = ""
        position = {
            x = -223.1665
            y = -74.00922
        }
        radius = 30
    }



*/



#include "include.h"

void Graphics_Engine::handleKeyboardEvent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            if (CSHM.remove_galaxies == true)
            {
                CSHM.remove_galaxies = false;
            }
            else if (CSHM.redraw_galaxies == true)
            {
                CSHM.redraw_galaxies = false;
            }
            else if (CSHM.remove_hyperlanes == true)
            {
                CSHM.remove_hyperlanes = false;
            }
            else if (CSHM.redraw_hyperlanes == true)
            {
                CSHM.redraw_hyperlanes = false;
            }
            break;
        }
    }
}

void LButton::handleEvent(SDL_Event* e, int id)
{
    if ((e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP  || e->type == SDL_MOUSEMOTION) && pathsaved == true)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

        if (id < 50)
        {
            if (x < mPosition.x)
            {
                inside = false;
            }

            else if (x > mPosition.x + BUTTON_WIDTH)
            {
                inside = false;
            }
            else if (y < mPosition.y)
            {
                inside = false;
            }
            else if (y > mPosition.y + BUTTON_HEIGHT)
            {
                inside = false;
            }
        }
        else if ((id >= 50) && (id < 150))
        {
            if (x < mPosition.x)
            {
                inside = false;
            }
            else if (y < mPosition.y)
            {
                inside = false;
            }
            switch (id){
                if (empiresettings_window == true){
                case 50:
                    if (x > mPosition.x + 340){ inside = false; } 
                    else if (y > mPosition.y + 40){ inside = false; }
                    break;

                case 51:
                    if (x > mPosition.x + 410) { inside = false; }
                    else if (y > mPosition.y + 40) { inside = false; }
                    break;

                case 52:
                    if (x > mPosition.x + 340) { inside = false; }
                    else if (y > mPosition.y + 40) { inside = false; }
                    break;
                case 53:
                    if (x > mPosition.x + 32) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 54:
                    if (x > mPosition.x + 32) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 55:
                    if (x > mPosition.x + 120) { inside = false; }
                    else if (y > mPosition.y + 35) { inside = false; }
                    break;
                case 56:
                    if (x > mPosition.x + 120) { inside = false; }
                    else if (y > mPosition.y + 35) { inside = false; }
                    break;
                }
                if (saveloadexit_window == true)
                {
                case 98:
                    if (x > mPosition.x + 32) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 99:
                    if (x > mPosition.x + 32) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 100:
                    if (x > mPosition.x + 32) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                }
                if (launchersettings_window == true)
                {
                case 60:
                    if (x > mPosition.x + 32) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 61:
                    if (x > mPosition.x + 32) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                }
                if (current_galaxies_window == true)
                {
                case 62:
                    if (x > mPosition.x + 32) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                }
                if (random_window == true)
                {
                case 110:
                    if (x > mPosition.x + 32) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 111:
                    if (x > mPosition.x + 32) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 112:
                    if (x > mPosition.x + 32) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 113:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 114:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 115:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 116:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 117:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 118:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 119:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 120:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 121:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 122:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 123:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 124:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 125:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 126:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 127:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 128:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 129:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 130:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 131:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 132:
                    if (x > mPosition.x + 50) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                }
            }
        }
        else if (( id >= 150) && ( id < 200))
        {
            if (x < mPosition.x)
            {
                inside = false;
            }

            else if (x > mPosition.x + 35)
            {
                inside = false;
            }
            else if (y < mPosition.y)
            {
                inside = false;
            }
            else if (y > mPosition.y + 35)
            {
                inside = false;
            }
        }
        if (!inside)
        {
            if (id < 1000)
            {
                mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
            }
            else
            {
                mCurrentSprite = BUTTON_SPRITE_MOUSE_SMALL;
            }
        }
        else
        {
            switch (e->type)
            {
            case SDL_MOUSEBUTTONDOWN:
                if (e->button.button == SDL_BUTTON_LEFT)
                {
                    if (id < 150)
                    {
                        mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG_PRESSED;
                        switch (id)
                        {
                            // Galaxies
                        case 0:
                            if (current_galaxies_window == false)
                            {
                                DisableOtherWindows();
                                current_galaxies_window = true;
                                rerender();
                            }
                            else
                            {
                                current_galaxies_window = false;
                                rerender();
                            }
                            break;

                        case 1:
                            break;

                            // Settings
                        case 2:
                            if (settings_window == false)
                            {
                                DisableOtherWindows();
                                settings_window = true;
                                rerender();
                            }
                            else {
                                settings_window = false;
                                rerender();
                            }
                            break;

                        case 3:
                            break;

                        case 4:
                            break;
                            // File & Exit
                        case 5:
                            if (saveloadexit_window == false)
                            {
                                DisableOtherWindows();
                                saveloadexit_window = true;
                                rerender();
                            }
                            else {
                                saveloadexit_window = false;
                                rerender();
                            }
                            break;

                            // Save Permament settings
                        case 6:
                            SaveSettings();
                            break;

                            //Import
                        case 10:
                            rerender();
                            LoadFile();
                            rerender();
                            break;


                            //Export
                        case 11:
                            if (galaxies_am != 0)
                            {
                                if (initializers_loaded == false)
                                {
                                    if (initializers == true)
                                    {
                                        Classinit.initilizers();
                                        initializers_loaded = true;
                                    }
                                }
                                if (hyperlanes_loaded == false)
                                {
                                    if (setting_hyperlanes == true)
                                    {
                                        hyperlanes_loaded = true;
                                        for (int i = 0; i < galaxies_am; i++)
                                        {
                                            if (v_galaxy_generation[i].hyperlanes_generated == false)
                                            {
                                                link(0, i);
                                            }
                                        }
                                    }
                                }
                                SaveFile();
                                initializers_loaded = false;
                                hyperlanes_loaded = false;
                            }
                            break;


                            //Play
                        case 12:
                            if (savetoagame == true)
                            {
                                if (setting_hyperlanes == true)
                                {
                                    for (int i = 0; i < galaxies_am; i++)
                                    {
                                        if (v_galaxy_generation[i].hyperlanes_generated == false)
                                        {
                                            link(0, i);
                                        }
                                    }
                                    //check_hyperlanes_for_every_galaxy();
                                }
                                //std::cout << "Work 1" << std::endl;
                                if (initializers == true)
                                {
                                    if (initializers_loaded == false)
                                    {
                                        Classinit.initilizers();
                                    }
                                }
                                //std::cout << "Work 1.5" << std::endl;
                                osfile(modfolderpath);
                            }
                            //std::cout << "Work 2" << std::endl;
                            SteamAPI_Init();
                            SteamAPI_RestartAppIfNecessary(281990);
                            //std::cout << "Exit" << std::endl;
                            break;

                            //Exit
                        case 13:
                            SaveSettings();
                            SaveRandomSettings();
                            close();
                            std::exit(0);
                            break;

                            // Generate Hyperlanes
                        case 15:
                            for (int i = 0; i < galaxies_am; i++)
                            {
                                if (v_galaxy_generation[i].hyperlanes_generated == false)
                                {
                                    link(0, i);
                                }
                            }
                            break;

                            // Remove Hyperlanes
                        case 16:
                            remove_hyperlanes(0, 0);
                            rerender();
                            break;

                            // Redraw Hyperlanes
                        case 17:
                            remove_hyperlanes(0, 0);
                            for (int i = 0; i < galaxies_am; i++)
                            {
                                if (v_galaxy_generation[i].hyperlanes_generated == false)
                                {
                                    link(1, i);
                                }
                            }
                            rerender();
                            break;

                            // Remove in Galaxy
                        case 18:
                            if (galaxies_am > 0)
                            {
                                CSHM.redraw_hyperlanes = true;
                                CSHM.remove_galaxies = false;
                                CSHM.redraw_galaxies = false;
                                CSHM.remove_hyperlanes = false;
                            }
                            break;

                            // Redraw in Galaxy
                        case 19:
                            if (galaxies_am > 0)
                            {
                                CSHM.remove_hyperlanes = true;
                                CSHM.remove_galaxies = false;
                                CSHM.redraw_galaxies = false;
                                CSHM.redraw_hyperlanes = false;
                            }
                            break;

                            // Edit Selected Galaxy
                        case 20:
                            if (galaxies_am > 0)
                            {
                                choose_galaxy_background_window = true;
                                choose_galaxy();
                                choose_galaxy_background_window = false;
                                current_galaxies_window = false;
                                edit = true;
                                rerender();
                                draw_galaxy();
                                edit_button();
                            }
                            break;


                            // Remove Selected Galaxy
                        case 21:
                            if (galaxies_am > 0)
                            {
                                CSHM.remove_galaxies = true;
                                CSHM.redraw_galaxies = false;
                                CSHM.remove_hyperlanes = false;
                                CSHM.redraw_hyperlanes = false;
                            }
                            break;


                            // Redraw Selected Galaxy
                        case 22:
                            if (galaxies_am > 0)
                            {
                                CSHM.redraw_galaxies = true;
                                CSHM.remove_galaxies = false;
                                CSHM.remove_hyperlanes = false;
                                CSHM.redraw_hyperlanes = false;
                            }
                            break;

                            // Edit steam folder patch
                        case 23:
                            edit_patch = true;
                            firstrunsettings();
                            edit_patch = false;
                            break;

                            // Clear Map
                        case 28:
                            alpha1 = 0,
                            clear_map();
                            rerender();
                            break;

                            // Random
                        case 29:
                            rerender();
                            draw_galaxy();
                            random_generator();
                            break;

                            //Choose Elipse Shape
                        case 30:
                            v_galaxy_generation.emplace_back();
                            galaxies_am++;
                            DisableOtherWindows();
                            rerender();
                            add_galaxy_elipse();
                            break;


                            //Choose Arms Shape
                        case 31:
                            v_galaxy_generation.emplace_back();
                            galaxies_am++;
                            DisableOtherWindows();
                            rerender();
                            add_galaxy_spiral();
                            break;



                        case 50:
                            empire_am = 0;
                            rerender();
                            GE.text_input(center_width + 1455, center_height + 240, 20);
                            break;

                        case 51:
                            fallen_am = 0;
                            rerender();
                            GE.text_input(center_width + 1540, center_height + 280, 21);
                            break;

                        case 52:
                            maruder_am = 0;
                            rerender();
                            GE.text_input(center_width + 1490, center_height + 320, 22);
                            break;

                            // Checkboxes
                        case 53:
                            if (Empires_Random == false)
                            {
                                Empires_Random = true;
                                rerender();
                            }
                            else
                            {
                                Empires_Random = false;
                                rerender();
                            }
                            break;

                        case 54:
                            if (generate_multiple_leviathans == false)
                            {
                                generate_multiple_leviathans = true;
                                rerender();
                            }
                            else
                            {
                                generate_multiple_leviathans = false;
                                rerender();
                            }
                            break;

                        case 55:
                            GE.text_input(center_width + 1590, center_height + 502, 55);
                            break;

                        case 56:
                            GE.text_input(center_width + 1683, center_height + 502, 56);
                            break;

                        case 60:
                            if (disable_failed_galaxy_warn == false)
                            {
                                disable_failed_galaxy_warn = true;
                                rerender();
                            }
                            else
                            {
                                disable_failed_galaxy_warn = false;
                                rerender();
                            }
                            break;
                        case 61:
                            if (disable_wrong_text_warn == false)
                            {
                                disable_wrong_text_warn = true;
                                rerender();
                            }
                            else
                            {
                                disable_wrong_text_warn = false;
                                rerender();
                            }
                            break;
                        case 62:
                            if (show_hyperlanes == false)
                            {
                                show_hyperlanes = true;
                                rerender();
                            }
                            else
                            {
                                show_hyperlanes = false;
                                rerender();
                            }
                            break;

                        case 98:
                            if (initializers == false)
                            {
                                initializers = true;
                                rerender();
                            }
                            else
                            {
                                initializers = false;
                                rerender();
                            }
                            break;

                        case 99:
                            if (savetoagame == false)
                            {
                                savetoagame = true;
                                rerender();
                            }
                            else
                            {
                                savetoagame = false;
                                rerender();
                            }
                            break;
                        case 100:
                            if (setting_hyperlanes == false)
                            {
                                setting_hyperlanes = true;
                                rerender();
                            }
                            else
                            {
                                setting_hyperlanes = false;
                                rerender();
                            }
                            break;

                        case 110:
                            if (CRS.enable_circle == false)
                            {
                                CRS.enable_circle = true;
                                rerender();
                            }
                            else
                            {
                                CRS.enable_circle = false;
                                rerender();
                            }
                            break;
                        case 111:
                            if (CRS.enable_spiral == false)
                            {
                                CRS.enable_spiral = true;
                                rerender();
                            }
                            else
                            {
                                CRS.enable_spiral = false;
                                rerender();
                            }
                            break;
                        case 112:
                            if (CRS.enable_resizing == false)
                            {
                                CRS.enable_resizing = true;
                                rerender();
                            }
                            else
                            {
                                CRS.enable_resizing = false;
                                rerender();
                            }
                            break;
                            // SIze from
                        case 113:
                            CRS.size_from_edited = true;
                            GE.text_input(center_width + 1403,center_height + 272, 113);
                            CRS.size_from_edited = false;
                            break;
                            // Size to
                        case 114:
                            CRS.size_to_edited = true;
                            GE.text_input(center_width + 1513, center_height + 272, 114);
                            CRS.size_to_edited = false;
                            break;
                            // Hyperlanes from
                        case 115:
                            CRS.hyperlanes_max_length_from_edited = true;
                            GE.text_input(center_width + 1560, center_height + 312, 115);
                            CRS.hyperlanes_max_length_from_edited = false;
                            break;
                            // Hyperlanes to
                        case 116:
                            CRS.hyperlanes_max_length_to_edited = true;
                            GE.text_input(center_width + 1680, center_height + 312, 116);
                            CRS.hyperlanes_max_length_to_edited = false;
                            break;
                            // Circle stars from
                        case 117:
                            CRS.circle_stars_from_edited = true;
                            GE.text_input(center_width + 1500, center_height + 392, 117);
                            CRS.circle_stars_from_edited = false;
                            break;
                            // Circle stars to
                        case 118:
                            CRS.circle_stars_to_edited = true;
                            GE.text_input(center_width + 1580, center_height + 392, 118);
                            CRS.circle_stars_to_edited = false;
                            break;
                            // SPiral stars from
                        case 119:
                            CRS.spiral_stars_from_edited = true;
                            GE.text_input(center_width + 1500, center_height + 482, 119);
                            CRS.spiral_stars_from_edited = false;
                            break;
                            // SPiral stars to
                        case 120:
                            CRS.spiral_stars_to_edited = true;
                            GE.text_input(center_width + 1580, center_height + 482, 120);
                            CRS.spiral_stars_to_edited = false;
                            break;
                            // Square factor
                        case 121:
                            CRS.square_factor_edited = true;
                            GE.text_input(center_width + 1435, center_height + 522, 121);
                            CRS.square_factor_edited = false;
                            break;
                            // Arm max from
                        case 122:
                            CRS.arm_max_width_from_edited = true;
                            GE.text_input(center_width + 1440, center_height + 562, 122);
                            CRS.arm_max_width_from_edited = false;
                            break;
                            // Arm max to
                        case 123:
                            CRS.arm_max_width_to_edited = true;
                            GE.text_input(center_width + 1580, center_height + 562, 123);
                            CRS.arm_max_width_to_edited = false;
                            break;
                            // Arm random from
                        case 124:
                            CRS.arm_random_width_from_edited = true;
                            GE.text_input(center_width + 1495, center_height + 602, 124);
                            CRS.arm_random_width_from_edited = false;
                            break;
                            // Arm random to
                        case 125:
                            CRS.arm_random_width_to_edited = true;
                            GE.text_input(center_width + 1600, center_height + 602, 125);
                            CRS.arm_random_width_to_edited = false;
                            break;
                            // Rotation factor
                        case 126:
                            CRS.rotation_factor_edited = true;
                            GE.text_input(center_width + 1454, center_height + 642, 126);
                            CRS.rotation_factor_edited = false;
                            break;
                            // Arm amount from
                        case 128:
                            CRS.arm_amount_from_edited = true;
                            GE.text_input(center_width + 1417, center_height + 682, 128);
                            CRS.arm_amount_from_edited = false;
                            break;
                            // Arm amount to
                        case 129:
                            CRS.arm_amount_to_edited = true;
                            GE.text_input(center_width + 1580, center_height + 682, 129);
                            CRS.arm_amount_to_edited = false;
                            break;
                            // Size ratio
                        case 130:
                            CRS.size_ratio_edited = true;
                            GE.text_input(center_width + 1380, center_height + 782, 130);
                            CRS.size_ratio_edited = false;
                            break;
                            // Arm ratio
                        case 131:
                            CRS.arm_ratio_edited = true;
                            GE.text_input(center_width + 1685, center_height + 782, 131);
                            CRS.arm_ratio_edited = false;
                            break;
                            // Arm width ratio
                        case 132:
                            CRS.arm_width_ratio_edited = true;
                            GE.text_input(center_width + 1460, center_height + 822, 132);
                            CRS.arm_width_ratio_edited = false;
                            break;
                            //Settings
                        }
                    }
                    if ((id >= 150) && (id < 200))
                    {
                        current_gal_id = id - 150;
                        if (CSHM.remove_galaxies == true)
                        {
                            remove_galaxy_full(current_gal_id);
                            std::cout << "-----" << std::endl;
                            rerender();
                        }
                        else if (CSHM.redraw_galaxies == true)
                        {
                            redraw_galaxy();
                            rerender();
                        }
                        else if (CSHM.remove_hyperlanes == true)
                        {
                            remove_hyperlanes(1, current_gal_id);
                            rerender();
                        }
                        else if (CSHM.redraw_hyperlanes == true)
                        {
                            remove_hyperlanes(1, current_gal_id);
                            link(1, current_gal_id);
                            rerender();
                        }
                    }
                }
                if (e->button.button == SDL_BUTTON_RIGHT)
                {
                    switch (id)
                    {
                        // Clear Galaxies to import
                    case 1:
                        break;
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (e->button.button == SDL_BUTTON_LEFT)
                    switch (id)
                    {
                        // Game Settings
                    case 35:
                        if (empiresettings_window == false)
                        {
                            DisableOtherWindows();
                            empiresettings_window = true;
                            rerender();
                        }
                        else {
                            empiresettings_window = false;
                            rerender();
                        }
                        break;

                        // Laucher Settings
                    case 36:
                        if (launchersettings_window == false)
                        {
                            DisableOtherWindows();
                            launchersettings_window = true;
                            rerender();
                        }
                        else {
                            launchersettings_window = false;
                            rerender();
                        }
                        break;
                    case 37:
                        if (random_window == false)
                        {
                            DisableOtherWindows();
                            random_window = true;
                            rerender();
                        }
                        else {
                            random_window = false;
                            rerender();
                        }
                        break;
                    case 38:
                        if (patchsettings_window == false)
                        {
                            DisableOtherWindows();
                            patchsettings_window = true;
                            rerender();
                        }
                        else {
                            patchsettings_window = false;
                            rerender();
                        }
                        break;
                    }
                break;
            }
        }
    }
}
// Different Windows/Surfaces ------------------------------------------------
void SaveLoadExit()
{
    gModulatedTexture.setAlpha(233);
    gModulatedTexture.render(center_width + 1230, center_height + 160, 650, 350);
    gButtons[10].setPosition(center_width + 1610, center_height + 230);
    gButtons[10].render(); 
    gButtons[11].setPosition(center_width + 1610, center_height + 290);
    gButtons[11].render();
    gButtons[12].setPosition(center_width + 1610, center_height + 350);
    gButtons[12].render();
    gButtons[13].setPosition(center_width + 1610, center_height + 410);
    gButtons[13].render();
    gButtons[98].setPosition(center_width + 1512, center_height + 238);
    gCheckboxTexture.render(center_width + 1513, center_height + 239, 30, 30);
    gButtons[99].setPosition(center_width + 1512, center_height + 278);
    gCheckboxTexture.render(center_width + 1513, center_height + 279, 30, 30);
    gButtons[100].setPosition(center_width + 1512, center_height + 318);
    gCheckboxTexture.render(center_width + 1513, center_height + 319, 30, 30);
    GE.text_render("Import", center_width + 1660, center_height + 235);
    GE.text_render("Export", center_width + 1660, center_height + 295);
    GE.text_render("Play", center_width + 1675, center_height + 355);
    GE.text_render("Exit", center_width + 1680, center_height + 415);
    GE.text_render("Save", center_width + 1433, center_height + 278);
    GE.text_render("Initializers", center_width + 1370, center_height + 238);
    GE.text_render("SMGG Hyperlanes", center_width + 1260, center_height + 318);
    GE.text_render("File operation and exit.", center_width + 1550, center_height + 170);
}

void EmpireSettings()
{
    gModulatedTexture.setAlpha(233);
    gModulatedTexture.render(center_width + 1220, center_height + 170, 680, 550);
    gButtons[50].setPosition(center_width + 1235, center_height + 235);
    gButtons[51].setPosition(center_width + 1235, center_height + 275);
    gButtons[52].setPosition(center_width + 1235, center_height + 315);
    gButtons[53].setPosition(center_width + 1354, center_height + 360);
    gCheckboxTexture.render(center_width + 1355, center_height + 361, 30, 30);
    gButtons[54].setPosition(center_width + 1643, center_height + 410);
    gCheckboxTexture.render(center_width + 1643, center_height + 410, 30, 30);
    gButtons[55].setPosition(center_width + 1555, center_height + 505);
    gButtons[56].setPosition(center_width + 1605, center_height + 505);
    GE.text_render("Game settings, set them here.", center_width + 1240, center_height + 190);
    GE.text_render("Empire amount:", center_width + 1240, center_height + 240);
    GE.text_render("Fallen Empire amount:", center_width + 1240, center_height + 280);
    GE.text_render("Maruders amount:", center_width + 1240, center_height + 320);
    GE.text_render("Random", center_width + 1240, center_height + 360);
    GE.text_render("Generate Multiple Leviathans", center_width + 1240, center_height + 410);
    GE.text_render("Option in this line is temporary disabled", center_width + 1240, center_height + 460);
    GE.text_render("Hyperlanes amount: From:", center_width + 1240, center_height + 510);
    GE.text_render(" to:", center_width + 1640, center_height + 510);
}

void Settings()
{
    gModulatedTexture.setAlpha(233);
    gModulatedTexture.render(center_width + 1420, center_height + 170, 275, 530);
    GE.render_button_with_text(0, 35, 1470, 260, "Game", 1525, 266);
    GE.render_button_with_text(0, 36, 1470, 330, "Launcher", 1500, 336);
    GE.render_button_with_text(0, 37, 1470, 400, "Random", 1507, 406);
    GE.render_button_with_text(0, 38, 1470, 470, "Patch", 1525, 476);

    GE.text_render("Settings", center_width + 1500, center_height + 180);

}

void LauncherSettings()
{
    gModulatedTexture.setAlpha(233);
    gModulatedTexture.render(center_width + 1220, center_height + 170, 680, 550);
    gButtons[60].setPosition(center_width + 1661, center_height + 251);
    gCheckboxTexture.render(center_width + 1662, center_height + 252, 30, 30);
    gButtons[61].setPosition(center_width + 1649, center_height + 291);
    gCheckboxTexture.render(center_width + 1650, center_height + 292, 30, 30);
    GE.text_render("Disable random galaxy warn", center_width + 1270, center_height + 250);
    GE.text_render("Disable incorrect text warn", center_width + 1270, center_height + 290);
    GE.text_render("Launcher settings", center_width + 1460, center_height + 190);
}

void RandomSettings()
{
    gModulatedTexture.setAlpha(233);
    gModulatedTexture.render(center_width + 1220, center_height + 170, 680, 900);

    GE.text_render_v2("Random Generator Settings", 1360, 185);
    GE.line(1223, 225, 1897, 225);

    GE.text_render_v2("Enable Circle", 1240, 230);
    GE.text_render_v2("Enable Spiral", 1600, 230);
    GE.render_checkbox(110, 1431, 231, 30, 30);
    GE.render_checkbox(111, 1791, 231, 30, 30);
    GE.line(1223, 265, 1897, 265);

    GE.text_render_v2("Galaxy resizing", 1610, 270);
    GE.render_checkbox(112, 1831, 271, 30, 30);
    GE.text_with_button(113, "Galaxy size:", 1240, 270);
    GE.text_with_button(114, "to:", 1480, 270);
    GE.line(1223, 305, 1897, 305);

    GE.text_with_button(115, "Hyperlanes max length:", 1240, 310);
    GE.text_with_button(116, "to:", 1640, 310);
    GE.line(1223, 345, 1897, 345);

    GE.line(1223, 385, 1897, 385);

    GE.text_with_button(117, "Circle stars factor:", 1240, 390);
    GE.text_with_button(118, "to:", 1540, 390);
    GE.line(1223, 425, 1897, 425);

    GE.text_render_v2("Spiral galaxies settings", 1380, 435);
    GE.line(1223, 475, 1897, 475);

    GE.text_with_button(119, "Spiral stars factor:", 1240, 480);
    GE.text_with_button(120, "to:", 1540, 480);
    GE.line(1223, 515, 1897, 515);

    GE.text_with_button(121, "Square factor:", 1240, 520);
    GE.line(1223, 555, 1897, 555);

    GE.text_with_button(122, "Arm max width:", 1240, 560);
    GE.text_with_button(123, "to:", 1540, 560);
    GE.line(1223, 595, 1897, 595);

    GE.text_with_button(124, "Arm random width:", 1240, 600);
    GE.text_with_button(125, "to:", 1560, 600);
    GE.line(1223, 635, 1897, 635);

    GE.text_with_button(126, "Rotation factor:", 1240, 640);
    GE.line(1223, 675, 1897, 675);

    GE.text_with_button(128, "Arm amount:", 1240, 680);
    GE.text_with_button(129, "to:", 1540, 680);
    GE.line(1223, 715, 1897, 715);

    GE.text_render_v2("Detailed spiral stars amount generation", 1280, 730);
    GE.line(1223, 775, 1897, 775);

    GE.text_with_button(130, "Size ratio:", 1240, 780);
    GE.text_with_button(131, "Arm ratio:", 1540, 780);
    GE.line(1223, 815, 1897, 815);

    GE.text_with_button(132, "Arm width ratio:", 1240, 820);
    GE.line(1223, 855, 1897, 855);
}

void PatchSettings()
{
    gModulatedTexture.setAlpha(240);
    gModulatedTexture.render(center_width + 180, center_height + 140, 1540, 800);
    gButtons[23].setPosition(center_width + 590, center_height + 165);
    gButtons[23].render();
    GE.text_render("Edit", center_width + 650, center_height + 171);
    GE.text_render("Current steam folder patch", center_width + 200, center_height + 170);
    GE.text_render(pathget, center_width + 200, center_height + 210);
    GE.text_render("Current mod folder patch", center_width + 200, center_height + 280);
    GE.text_render(pathget + "/workshop/content/281990/2602794523/map/setup_scenarios/sps_multigalaxy.txt", center_width + 200, center_height + 320);
}

void draw_galaxy()
{
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 0);
    for (int i = 0; i < v_system_data.size(); i++)
    {
        for (int j = 0; j < v_system_data[i].size(); j++)
        {
            SDL_RenderDrawPoint(gRenderer, center_width + (v_system_data[i][j].gal_x + 550), center_height + (v_system_data[i][j].gal_y + 550));
        }
    }
    if (v_system_data.size() > 0)
    {
        for (int i = 0; i < galaxies_am; ++i)
        {
            GE.render_button_with_text(1, i + 150, v_galaxy_generation[i].i_cen_posX + 535, v_galaxy_generation[i].i_cen_posY + 535, std::to_string(i), v_galaxy_generation[i].i_cen_posX + 540, v_galaxy_generation[i].i_cen_posY + 540);
        }
    }
}

void add_galaxy_elipse()
{
    elipse_galaxy_window = true;
    current_gal_id = galaxies_am - 1;
    gModulatedTexture.setAlpha(233);
    gModulatedTexture.render(center_width + 1220, center_height + 170, 680, 250);
    GE.text_render("Systems:", center_width + 1280, center_height + 230);
    GE.text_render("Size (Radius):", center_width + 1280, center_height + 260);
    GE.text_render("Center X:", center_width + 1280, center_height + 290);
    GE.text_render("Center Y:", center_width + 1280, center_height + 320);
    GE.text_render("Max Hyperlanes Distance:", center_width + 1280, center_height + 350);

    GE.text_input(center_width + 1410, center_height + 230, 0);
    GE.text_input(center_width + 1465, center_height + 260, 1);
    GE.text_input(center_width + 1410, center_height + 290, 2);
    GE.text_input(center_width + 1410, center_height + 320, 3);
    GE.text_input(center_width + 1635, center_height + 350, 4);

    v_galaxy_generation[current_gal_id].galtype = 1;

    elipse_galaxy_window = false;

    alpha1 = 250, alpha2 = 225, alpha3 = 0;
    generate_elipse(current_gal_id);
    rerender();
}

void elipse_background()
{
    int i = current_gal_id;
    gModulatedTexture.setAlpha(233);
    gModulatedTexture.render(center_width + 1220, center_height + 170, 680, 250);
    GE.text_render("Systems:", center_width + 1280, center_height + 230);
    GE.text_render("Size (Radius):", center_width + 1280, center_height + 260);
    GE.text_render("Center X:", center_width + 1280, center_height + 290);
    GE.text_render("Center Y:", center_width + 1280, center_height + 320);
    GE.text_render("Max Hyperlanes Distance:", center_width + 1280, center_height + 350);



    if (edit == false)
    {
        GE.text_render(v_galaxy_generation[i].star, center_width + 1410, center_height + 230);
        GE.text_render(v_galaxy_generation[i].gsize, center_width + 1465, center_height + 260);
        GE.text_render(v_galaxy_generation[i].cen_posX, center_width + 1410, center_height + 290);
        GE.text_render(v_galaxy_generation[i].cen_posY, center_width + 1410, center_height + 320);
        GE.text_render(v_galaxy_generation[i].max_hyp_dis, center_width + 1635, center_height + 350);
    }
    else
    {
        GE.text_render(v_galaxy_generation[i].star, center_width + 1800, center_height + 230);
        GE.text_render(v_galaxy_generation[i].gsize, center_width + 1800, center_height + 260);
        GE.text_render(v_galaxy_generation[i].cen_posX, center_width + 1800, center_height + 290);
        GE.text_render(v_galaxy_generation[i].cen_posY, center_width + 1800, center_height + 320);
        GE.text_render(v_galaxy_generation[i].max_hyp_dis, center_width + 1800, center_height + 350);
    }
}

void add_galaxy_spiral()
{
    spiral_galaxy_window = true;
    current_gal_id = galaxies_am - 1;
    gModulatedTexture.setAlpha(233);
    gModulatedTexture.render(center_width + 1220, center_height + 170, 680, 390);
    GE.text_render("Systems:", center_width + 1280, center_height + 230);
    GE.text_render("Size (Radius):", center_width + 1280, center_height + 260);
    GE.text_render("Center X:", center_width + 1280, center_height + 290);
    GE.text_render("Center Y:", center_width + 1280, center_height + 320);
    GE.text_render("Max Hyperlanes Distance:", center_width + 1280, center_height + 350);
    GE.text_render("Number of Arms:", center_width + 1280, center_height + 380);
    GE.text_render("Arm Max Width:", center_width + 1280, center_height + 410);
    GE.text_render("Random Width:", center_width + 1280, center_height + 440);
    GE.text_render("Arm Rotation:", center_width + 1280, center_height + 470);

    GE.text_input(center_width + 1410, center_height + 230, 0);
    GE.text_input(center_width + 1465, center_height + 260, 1);
    GE.text_input(center_width + 1410, center_height + 290, 2);
    GE.text_input(center_width + 1410, center_height + 320, 3);
    GE.text_input(center_width + 1635, center_height + 350, 4);
    GE.text_input(center_width + 1510, center_height + 380, 5);
    GE.text_input(center_width + 1492, center_height + 410, 6);
    GE.text_input(center_width + 1480, center_height + 440, 7);
    GE.text_input(center_width + 1465, center_height + 470, 8);
    v_galaxy_generation[current_gal_id].galtype = 1;

    spiral_galaxy_window = false;

    alpha1 = 250, alpha2 = 225, alpha3 = 0;
    
    generate_spiral(current_gal_id);
    rerender();
}

void spiral_background()
{
    int i = current_gal_id;
    gModulatedTexture.setAlpha(233);
    gModulatedTexture.render(center_width + 1220, center_height + 170, 680, 390);
    GE.text_render_v2("Systems:", 1280, 230);
    GE.text_render_v2("Size (Radius):", 1280, 260);
    GE.text_render_v2("Center X:", 1280, 290);
    GE.text_render_v2("Center Y:", 1280, 320);
    GE.text_render_v2("Max Hyperlanes Distance:", 1280, 350);
    GE.text_render_v2("Number of Arms:", 1280, 380);
    GE.text_render_v2("Arm Max Width:", 1280, 410);
    GE.text_render_v2("Random Width:", 1280, 440);
    GE.text_render_v2("Arm Rotation:", 1280, 470);

    if (edit == false)
    {
        GE.text_render_v2(v_galaxy_generation[i].star, 1410, 230);
        GE.text_render_v2(v_galaxy_generation[i].gsize, 1465, 260);
        GE.text_render_v2(v_galaxy_generation[i].cen_posX, 1410, 290);
        GE.text_render_v2(v_galaxy_generation[i].cen_posY, 1410, 320);
        GE.text_render_v2(v_galaxy_generation[i].max_hyp_dis, 1635, 350);
        GE.text_render_v2(v_galaxy_generation[i].numArms, 1510, 380);
        GE.text_render_v2(v_galaxy_generation[i].armOffsetMax, 1492, 410);
        GE.text_render_v2(v_galaxy_generation[i].randomOffsetXY, 1480, 440);
        GE.text_render_v2(v_galaxy_generation[i].rotationFactor, 1465, 470);
    }
    else
    {
        GE.text_render_v2(v_galaxy_generation[i].star, 1800, 230);
        GE.text_render_v2(v_galaxy_generation[i].gsize, 1800, 260);
        GE.text_render_v2(v_galaxy_generation[i].cen_posX, 1800, 290);
        GE.text_render_v2(v_galaxy_generation[i].cen_posY, 1800, 320);
        GE.text_render_v2(v_galaxy_generation[i].max_hyp_dis, 1800, 350);
        GE.text_render_v2(v_galaxy_generation[i].numArms, 1800, 380);
        GE.text_render_v2(v_galaxy_generation[i].armOffsetMax, 1800, 410);
        GE.text_render_v2(v_galaxy_generation[i].randomOffsetXY, 1800, 440);
        GE.text_render_v2(v_galaxy_generation[i].rotationFactor, 1800, 470);
    }
}

void current_galaxies_buttons()
{
    gModulatedTexture.setAlpha(233);
    gModulatedTexture.render(center_width + 1220, center_height + 170, 680, 860);
    
    GE.text_render_v2("Galaxies Options", 1450, 180);
    GE.text_render_v2("Existing Galaxies", 1240, 230);
    GE.text_render_v2("Add New Galaxy", 1630, 230);
    GE.render_button_with_text(0, 20, 1260, 300, "Edit", 1325, 305);
    GE.render_button_with_text(0, 21, 1260, 420, "Remove", 1295, 425);
    GE.render_button_with_text(0, 22, 1260, 360, "Redraw", 1295, 365);
    GE.render_button_with_text(0, 29, 1660, 270, "Random", 1700, 275);
    GE.render_button_with_text(0, 30, 1660, 330, "Circle", 1707, 335);
    GE.render_button_with_text(0, 31, 1660, 390, "Spiral", 1712, 395);
    GE.render_button_with_text(0, 28, 1660, 460, "Clear Map", 1685, 465);
    

    GE.text_render_v2("Hyperlanes Options", 1420, 520);
    GE.text_render_v2("Map", 1320, 550);
    GE.text_render_v2("Galaxy", 1700,  550);
    GE.text_render_v2("Show", 1515, 570);
    GE.render_button_with_text(0, 15, 1260, 590, "Generate", 1285, 595);
    GE.render_button_with_text(0, 16, 1260, 710, "Remove", 1295, 715);
    GE.render_button_with_text(0, 17, 1260, 650, "Redraw", 1295, 655);
    GE.render_button_with_text(0, 18, 1660, 590, "G. Redraw", 1680, 595);
    GE.render_button_with_text(0, 19, 1660, 650, "G. Remove", 1677, 655);
    GE.render_checkbox(62, 1540, 605, 30, 30);
}

void choose_galaxy()
{
    //std::cout << "choose_galaxy in" << std::endl;
    GE.text_render_v2("Galaxy ID", 1285, 480);
    GE.text_input(center_width + 1320, center_height + 510, 99);
    //std::cout << "choose_galaxy out" << std::endl;
}

void choose_galaxy_background()
{
    GE.text_render_v2("Galaxy ID", 1285, 480);
}

void edit_button()
{
    if(v_galaxy_generation[current_gal_id].galtype == 0)
    {
        elipse_galaxy_window = true;
        rerender();
        draw_galaxy();

        GE.text_input(center_width + 1420, center_height + 230, 0);
        GE.text_input(center_width + 1478, center_height + 260, 1);
        GE.text_input(center_width + 1420, center_height + 290, 2);
        GE.text_input(center_width + 1420, center_height + 320, 3);
        GE.text_input(center_width + 1665, center_height + 350, 4);


        remove_galaxy(current_gal_id);

        
        alpha1 = 250, alpha2 = 225, alpha3 = 0;
        generate_elipse(current_gal_id);
        
        elipse_galaxy_window = false;
        edit = false;
        rerender();
        draw_galaxy();
    }
    else if (v_galaxy_generation[current_gal_id].galtype == 1)
    {
        spiral_galaxy_window = true;
        rerender();
        draw_galaxy();
        

        GE.text_input(center_width + 1420, center_height + 230, 0);
        GE.text_input(center_width + 1478, center_height + 260, 1);
        GE.text_input(center_width + 1420, center_height + 290, 2);
        GE.text_input(center_width + 1420, center_height + 320, 3);
        GE.text_input(center_width + 1665, center_height + 350, 4);
        GE.text_input(center_width + 1520, center_height + 380, 5);
        GE.text_input(center_width + 1498, center_height + 410, 6);
        GE.text_input(center_width + 1480, center_height + 440, 7);
        GE.text_input(center_width + 1470, center_height + 470, 8);


        remove_galaxy(current_gal_id);

        alpha1 = 250, alpha2 = 225, alpha3 = 0;
        generate_spiral(current_gal_id);

        spiral_galaxy_window = false;
        edit = false;
        rerender();
        draw_galaxy();
    }
}

void remove_galaxy(int gal_id)
{
    if (gal_id < galaxies_am)
    {
        sys_sum -= v_system_data[gal_id].size();
        v_system_data[gal_id].clear();
        if (v_hyperlanes.size() > 0)
        {
            if (v_hyperlanes[gal_id].size() > 0)
            {
                v_hyperlanes[gal_id].clear();
            }
        }
    }
}

void remove_galaxy_full(int gal_id)
{
   // std::cout << "remove_galaxy_full in" << gal_id << std::endl;
    if (gal_id < galaxies_am)
    {
        sys_sum -= v_system_data[gal_id].size();
        v_system_data.erase(v_system_data.begin() + gal_id);
        v_galaxy_generation.erase(v_galaxy_generation.begin() + gal_id);
        if (v_hyperlanes.size() > 0)
        {
            if (v_hyperlanes[gal_id].size() > 0)
            {
                v_hyperlanes.erase(v_hyperlanes.begin() + gal_id);
            }
        }
        galaxies_am--;
    }
    //std::cout << "remove_galaxy_full out" << std::endl;
}

void remove_hyperlanes(int mode, int gal_id)
{
    if (gal_id < galaxies_am)
    {
        //std::cout << "remove_hyperlanes in" << gal_id << std::endl;
        clear_hyperlanes_data();
        if (mode == 0)
        {
            v_hyperlanes.clear();
            for (int i = 0; i < galaxies_am; i++)
            {
                for (int j = 0; j < v_system_data[i].size(); j++)
                {
                    v_system_data[i][j].blocked = false;
                    v_system_data[i][j].con = 0;
                }
                v_galaxy_generation[i].hyperlanes_generated = false;
            }
        }
        else if (mode == 1)
        {
            v_hyperlanes[gal_id].clear();
            for (int j = 0; j < v_system_data[gal_id].size(); j++)
            {
                v_system_data[gal_id][j].blocked = false;
                v_system_data[gal_id][j].con = 0;
            }
            v_galaxy_generation[gal_id].hyperlanes_generated = false;
        }
    }
}

void clear_map()
{
    v_system_data.clear();
    v_system_data_copy.clear();
    v_galaxy_generation.clear();
    clear_hyperlanes_data();
    v_hyperlanes.clear();

    galaxies_am = 0;
    sys_sum = 0;
    empire_am = 0,
    fallen_am = 0,
    maruder_am = 0;
    current_gal_id = NULL;
    initializers_loaded = false;
    hyperlanes_loaded = false;
    mult = 0;
}

void redraw_galaxy()
{
    edit = true;
    if (v_galaxy_generation[current_gal_id].galtype == 0)
    {
        remove_galaxy(current_gal_id);

        alpha1 = 250, alpha2 = 225, alpha3 = 0;
        generate_elipse(current_gal_id);

        rerender();
        draw_galaxy();
    }
    else if (v_galaxy_generation[current_gal_id].galtype == 1)
    {
        remove_galaxy(current_gal_id);

        alpha1 = 250, alpha2 = 225, alpha3 = 0;
        generate_spiral(current_gal_id);

        rerender();
        draw_galaxy();
    }
    edit = false;
}

// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args) {

    // Initialize SDL. SDL_Init will return -1 if it fails.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        system("pause");
        // End the program
        return 1;
    }
    HideConsole();
    debug();
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SCREEN_WIDTH = DM.w;
    SCREEN_HEIGHT = DM.h;
    center_width = ((SCREEN_WIDTH - 1920) / 2);
    center_height = ((SCREEN_HEIGHT - 1080) / 2);
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        //Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            alpha1 = 0, alpha2 = 225, alpha3 = 0;
            bool quit = false;
            SDL_Event e;
            loadsettings();
            srand(time(NULL));
            if (pathsaved != 1)
            {
                firstrunsettings();
                SaveSettings();
            }
            RandomDefaultSettings();
            LoadRandomDefaultSettings();
            LoadRandomSettings();
            while(!quit)
            {
                //Handle events on queue ASSAD
                while (SDL_WaitEvent(&e) != 0)
                {
                    SDL_Delay(10);
                    //Handle Keyboard events 
                    GE.handleKeyboardEvent(e);
                    //Handle button events
                    for (int i = 0; i < gButtons.size(); ++i)
                    {
                        gButtons[i].handleEvent(&e, i);
                        //mButtons[i].handleEvent(&e, i + 1000);
                    }
                    rerender();
                }
            }
        }
    }
    // End the program
    return 0;
}

void HideConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool IsConsoleVisible()
{
    return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}