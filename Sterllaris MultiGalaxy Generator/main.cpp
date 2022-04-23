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
24 - Generate Initializers
28 - Clear Map
29 - Random Galaxy
30 - Choose Circle or Ring Shape
31 - Choose x-ARms galaxy schape
35 - Game Settings
36 - Launcher Settings
37 - Random Settings
38 - Patch Settings
39 - Restore default random settings
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
63 - Checkbox Show Initializers

97 - Checkbox Multiplayer
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

140 - 149 Edit options
150 - 200 Boxy dla galaktyk

Inicjalizatory:
0 - system jest wolny lub zablokowany (false = wolny, true = zablokowany)
1 - zwyk³e imperium
2 - Upad³e Imperium
3 - Leviathany
4 - Mega
5 - Maruderzy
10 - player

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


    Detailed Edit buttons 2-3 corrupted WTF
    0 - System Remove +
    1 - Hyperlane Remove +
    8 - Initializer Remove
    9 - Initializer Add
    4 - System Add + 
    5 - System Move ---
    6 - Hyperlane Add + 
    7 - Initializer Change

    11 - "Player", 131
    12 - "Bot", 1310,
    13 - "Fallen", 131
    14 - "Marauder", 1
    15 - "Ruined Mega"
    16 - "Leviathan",
    17 - "Mods", 1310,

    20 - "dyson_sphere_init_01",
    21 - "science_nexus_init_01",
    22 - "sentry_array_init_01",
    23 - "ring_world_init_01",


    30 - "guardians_init_stellarites",
    31 - "guardians_init_dragon",
    32 - "guardians_init_horror",
    33 - "guardians_init_dreadnought",
    34 - "guardians_init_hive",
    35 - "guardians_init_technosphere",
    36 - "guardians_init_fortress",
    37 - "guardians_init_wraith",

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

void LButton::handle_D_S_E_ButtonEvent(SDL_Event& e, int id)
{
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

        if (id < 500)
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
        if (!inside)
        {
            if (!Det_Gen.remove_system)
            {
                D_S_E_Buttons[0].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
            }
            if (!Det_Gen.add_system)
            {
                D_S_E_Buttons[4].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
            }
            if (!Det_Gen.remove_hyperlanes)
            {
                D_S_E_Buttons[1].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
            }
            if (!Det_Gen.add_initializer)
            {
                D_S_E_Buttons[9].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
            }
            if (!Det_Gen.remove_initializer)
            {
                D_S_E_Buttons[8].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
            }
            if (!Det_Gen.add_hyperlanes ){ D_S_E_Buttons[6].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG; }

            if (!Det_Gen.add_initializer_player)   { D_S_E_Buttons[11].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG; }
            if (!Det_Gen.add_initializer_bot)      { D_S_E_Buttons[12].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG; }
            if (!Det_Gen.add_initializer_fallen)   { D_S_E_Buttons[13].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG; }
            if (!Det_Gen.add_initializer_marauder) { D_S_E_Buttons[14].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG; }
            if (!Det_Gen.add_initializer_mega)     { D_S_E_Buttons[15].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG; }
            if (!Det_Gen.add_initializer_leviathan){ D_S_E_Buttons[16].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG; }
            if (!Det_Gen.add_initializer_mods)     { D_S_E_Buttons[17].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG; }
            for (int i = 0; i < 8; ++i)
            {
                if (!Det_Gen.bits_leviathan.test(i))
                {
                    D_S_E_Buttons[30 + i].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
                }
            }
            for (int i = 0; i < 4; ++i)
            {
                if (!Det_Gen.bits_mega.test(i))
                {
                    D_S_E_Buttons[20 + i].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
                }
            }
        }
        else
        {
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                if (id < 500)
                {
                    switch (e.type)
                    {
                    case SDL_MOUSEBUTTONDOWN:
                        switch (id)
                        {
                            Det_Gen.set_default_button();
                        case 0:
                            //std::cout << "Work" << std::endl;
                            Det_Gen.false_all_bools();
                            Det_Gen.remove_system = true;
                            //std::cout << Det_Gen.remove_system << std::endl;
                            break;
                        case 1:
                            Det_Gen.false_all_bools();
                            Det_Gen.remove_hyperlanes = true;
                            break;
                        case 8:
                            Det_Gen.false_all_bools();
                            Det_Gen.remove_initializer = true;
                            break;
                        case 9:
                            Det_Gen.false_all_bools();
                            Det_Gen.add_initializer = true;
                            break;
                        case 4:
                            Det_Gen.false_all_bools();
                            Det_Gen.add_system = true;
                            break;
                        case 5:
                            Det_Gen.false_all_bools();
                            //Det_Gen.move_system = true;
                            break;
                        case 6:
                            Det_Gen.previous_id = 0;
                            Det_Gen.false_all_bools();
                            Det_Gen.add_hyperlanes = true;
                            break;
                        case 7:
                            Det_Gen.false_all_bools();
                            break;
                            /*
                            11 - "Player", 131
                                12 - "Bot", 1310,
                                13 - "Fallen", 131
                                14 - "Marauder", 1
                                15 - "Ruined Mega"
                                16 - "Leviathan",
                                17 - "Mods", 1310,
                            */                        
                        case 11:
                            Det_Gen.false_initializers();
                            Det_Gen.add_initializer_player = true;
                            break;
                        case 12:
                            Det_Gen.false_initializers();
                            Det_Gen.add_initializer_bot = true;
                            break;
                        case 13:
                            Det_Gen.false_initializers();
                            Det_Gen.add_initializer_fallen = true;
                            break;
                        case 14:
                            Det_Gen.false_initializers();
                            Det_Gen.add_initializer_marauder = true;
                            break;
                        case 15:
                            Det_Gen.false_initializers();
                            Det_Gen.add_initializer_mega = true;
                            break;
                        case 16:
                            Det_Gen.false_initializers();
                            Det_Gen.add_initializer_leviathan = true;
                            break;
                        case 17:
                            Det_Gen.false_initializers();
                            Det_Gen.add_initializer_mods = true;
                            break;


                        case 20:
                            Det_Gen.reset_bits();
                            Det_Gen.bits_mega.set(0);
                            break;
                        case 21:
                            Det_Gen.reset_bits();
                            Det_Gen.bits_mega.set(1);
                            break;
                        case 22:
                            Det_Gen.reset_bits();
                            Det_Gen.bits_mega.set(2);
                            break;
                        case 23:
                            Det_Gen.reset_bits();
                            Det_Gen.bits_mega.set(3);
                            break;


                        case 30:
                            Det_Gen.reset_bits();
                            Det_Gen.bits_leviathan.set(0);
                            break;
                        case 31:
                            Det_Gen.reset_bits();
                            Det_Gen.bits_leviathan.set(1);
                            break;
                        case 32:
                            Det_Gen.reset_bits();
                            Det_Gen.bits_leviathan.set(2);
                            break;
                        case 33:
                            Det_Gen.reset_bits();
                            Det_Gen.bits_leviathan.set(3);
                            break;
                        case 34:
                            Det_Gen.reset_bits();
                            Det_Gen.bits_leviathan.set(4);
                            break;
                        case 35:
                            Det_Gen.reset_bits();
                            Det_Gen.bits_leviathan.set(5);
                            break;
                        case 36:
                            Det_Gen.reset_bits();
                            Det_Gen.bits_leviathan.set(6);
                            break;
                        case 37:
                            Det_Gen.reset_bits();
                            Det_Gen.bits_leviathan.set(7);
                            break;
                        }
                        D_S_E_Buttons[id].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG_PRESSED;
                        break;
                    }
                }
            }
        }
}

void LButton::handleSystemButtonEvent(SDL_Event& e, int i, int j)
{
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;

        if (x < SystemButtons[i][j].mPosition.x - 10)
        {
            inside = false;
        }
        else if (x > SystemButtons[i][j].mPosition.x + 15)
        {
            inside = false;
        }
        else if (y < SystemButtons[i][j].mPosition.y - 10)
        {
            inside = false;
        }
        else if (y > SystemButtons[i][j].mPosition.y + 15)
        {
            inside = false;
        }

        if (!inside)
        {
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    if (Det_Gen.add_system)
                    {
                        if ((i == 0)&&(j == 0))
                        {
                            int sys_x = (C_S.donex - 1210) + (x / 5) + 550,
                                sys_y = (C_S.doney - 1210) + (y / 5) + 550;
                            for (int i = 0; i < v_galaxy_generation.size(); ++i)
                            {
                                int dyst = sqrt(pow(sys_x - v_galaxy_generation[i].i_cen_posX, 2) + (pow(sys_y - v_galaxy_generation[i].i_cen_posY, 2)));
                                //std::cout << dyst << " " << v_galaxy_generation[i].i_gsize << std::endl;
                                if (dyst < v_galaxy_generation[i].i_gsize)
                                {
                                    int con_m = rand() % max_hyperlane_am + min_hyperlane_am;
                                    v_system_data[i].emplace_back();
                                    SystemButtons[i].emplace_back();
                                    v_hyperlanes[i].emplace_back();
                                    v_system_data[i][v_galaxy_generation[i].i_star].blocked = false;
                                    v_system_data[i][v_galaxy_generation[i].i_star].con = 0;
                                    v_system_data[i][v_galaxy_generation[i].i_star].con_max = con_m;
                                    v_system_data[i][v_galaxy_generation[i].i_star].exported = false;
                                    v_system_data[i][v_galaxy_generation[i].i_star].gal_id = v_galaxy_generation[i].i_star;
                                    v_system_data[i][v_galaxy_generation[i].i_star].gal_x = sys_x;
                                    v_system_data[i][v_galaxy_generation[i].i_star].gal_y = sys_y;
                                    v_system_data[i][v_galaxy_generation[i].i_star].inicjalizer = false;
                                    v_system_data[i][v_galaxy_generation[i].i_star].init_number = 0;
                                    v_system_data[i][v_galaxy_generation[i].i_star].init_type = 0;
                                    v_galaxy_generation[i].i_star++;
                                    sys_sum++;
                                }
                            }
                        }
                    }
                    if (Det_Gen.move_system)
                    {
                        /*
                        if ((i == 0) && (j == 0))
                        {
                            
                            int sys_x = (C_S.donex - 1210) + (x / 5) + 550,
                                sys_y = (C_S.doney - 1210) + (y / 5) + 550;
                            system_data pushing;
                            pushing.blocked = move_holder.blocked;
                            pushing.con = move_holder.con;
                            pushing.con_max = move_holder.con_max;
                            pushing.exported = move_holder.exported;
                            pushing.gal_id = move_holder.gal_id;
                            pushing.gal_x = sys_x;
                            pushing.gal_y = sys_y;
                            pushing.inicjalizer = move_holder.inicjalizer;
                            pushing.init_number = move_holder.init_number;
                            pushing.init_type = move_holder.init_type;
                            v_system_data[i].insert(v_system_data[i].begin() + move_holder.gal_id, 1, pushing);
                             std::cout << move_holder.gal_id << " Outside " << move_holder.gal_x << " " << move_holder.gal_y << std::endl;
                             std::cout << v_system_data[i][j].gal_id << " " << v_system_data[i][j].gal_x << " " << v_system_data[i][j].gal_y << std::endl;

                        }
                        */
                    }
                }
                if (e.button.button == SDL_BUTTON_RIGHT)
                {
                    C_S.box_open = false;
                    ThrowOutButtons();
                }
                if (e.button.button == SDL_BUTTON_MIDDLE)
                {
                    if ((i == 0) && (j == 0))
                    {
                        if (C_S.scrolling)
                        {
                            if (C_S.done)
                            {
                                C_S.box_open = false;
                                ThrowOutButtons();
                                Det_Gen.false_all_bools();
                                C_S.done = false;
                            }
                            else
                            {
                                C_S.done = true;
                            }
                        }
                    }
                }
            }
        }
        else 
        {
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                switch (e.type)
                {
                case SDL_MOUSEBUTTONDOWN:
                    if (Det_Gen.remove_system)
                    {
                        v_system_data[i].erase(v_system_data[i].begin() + j);
                        for (int a = 0; a < v_system_data[i].size(); ++a)
                        {
                            if (v_system_data[i][a].gal_id >= j)
                            {
                                v_system_data[i][a].gal_id -= 1;
                            }
                        }
                        if (v_galaxy_generation[i].hyperlanes_generated)
                        {
                            v_hyperlanes[i].erase(v_hyperlanes[i].begin() + j);
                            for (int a = 0; a < v_hyperlanes[i].size(); ++a)
                            {
                                //std::cout << "-----------" << std::endl;
                                //std::cout << v_hyperlanes[i][a].size() << std::endl;
                                for (int b = 0; b < v_hyperlanes[i][a].size(); ++b)
                                {
                                    //std::cout << j << "  " << v_hyperlanes[i][a][b].from << "    " << v_hyperlanes[i][a][b].to << std::endl;
                                    if (v_hyperlanes[i][a][b].to == j)
                                    {
                                        v_hyperlanes[i][a].erase(v_hyperlanes[i][a].begin() + b);
                                    }
                                    if (v_hyperlanes[i][a][b].to >= j)
                                    {
                                        v_hyperlanes[i][a][b].to -= 1;
                                    }
                                    if (v_hyperlanes[i][a][b].from >= j)
                                    {
                                        v_hyperlanes[i][a][b].from -= 1;
                                    }

                                    //std::cout << j << "  " << v_hyperlanes[i][a][b].from << "    " << v_hyperlanes[i][a][b].to << std::endl;
                                }
                                //std::cout << "----------" << std::endl;
                            }
                        }
                        v_galaxy_generation[i].i_star--;
                        v_galaxy_generation[i].star = std::to_string(v_galaxy_generation[i].i_star);
                        sys_sum--;
                        //rerender();
                    }
                    else if (Det_Gen.remove_hyperlanes)
                    {
                        if (Det_Gen.previous_id != 0)
                        {
                            for (int a = 0; a < v_hyperlanes[i][j].size(); ++a)
                            {
                                if (v_hyperlanes[i][j][a].from == Det_Gen.previous_id)
                                {
                                    v_hyperlanes[i][j].erase(v_hyperlanes[i][j].begin() + a);
                                }
                                if (v_hyperlanes[i][j][a].to == Det_Gen.previous_id)
                                {
                                    v_hyperlanes[i][j].erase(v_hyperlanes[i][j].begin() + a);
                                }
                            }
                            for (int a = 0; a < v_hyperlanes[i][Det_Gen.previous_id].size(); ++a)
                            {
                                if (v_hyperlanes[i][Det_Gen.previous_id][a].from == j)
                                {
                                    v_hyperlanes[i][Det_Gen.previous_id].erase(v_hyperlanes[i][Det_Gen.previous_id].begin() + a);
                                }
                                if (v_hyperlanes[i][Det_Gen.previous_id][a].to == j)
                                {
                                    v_hyperlanes[i][Det_Gen.previous_id].erase(v_hyperlanes[i][Det_Gen.previous_id].begin() + a);
                                }
                            }
                        }
                        Det_Gen.previous_id = v_system_data[i][j].gal_id;
                    }
                    else if (Det_Gen.remove_initializer)
                    {
                        if (v_system_data[i][j].init_type == 99)
                        {

                        }
                        else if (v_system_data[i][j].init_type == 1)
                        {
                            empire_am--;
                            v_galaxy_generation[i].empire_am--;
                            v_system_data[i][j].inicjalizer = false;
                            v_system_data[i][j].init_number = 0;
                            v_system_data[i][j].init_type = 0;
                        }
                        else if (v_system_data[i][j].init_type == 2)
                        {
                            fallen_am--;
                            v_galaxy_generation[i].fallen_am--;
                            v_system_data[i][j].inicjalizer = false;
                            v_system_data[i][j].init_number = 0;
                            v_system_data[i][j].init_type = 0;
                        }
                        else if (v_system_data[i][j].init_type == 5)
                        {
                            maruder_am--;
                            v_galaxy_generation[i].maruder_am--;
                            v_system_data[i][j].inicjalizer = false;
                            v_system_data[i][j].init_number = 0;
                            v_system_data[i][j].init_type = 0;
                        }
                        else if (v_system_data[i][j].init_type == 3)
                        {
                            Class_lev.exist[v_system_data[i][j].init_number] = false;
                            v_system_data[i][j].inicjalizer = false;
                            v_system_data[i][j].init_number = 0;
                            v_system_data[i][j].init_type = 0;
                        }
                        else if (v_system_data[i][j].init_type == 10)
                        {
                            Det_Gen.player_am--;
                            empire_am--;
                            for (int a = 0; a < v_system_data.size(); ++a)
                            {
                                for (int b = 0; b < v_system_data[a].size(); ++b)
                                {
                                    if (v_system_data[a][b].player_id > v_system_data[i][j].player_id)
                                    {
                                        v_system_data[a][b].player_id--;
                                    }
                                }
                            }
                            v_galaxy_generation[i].players_am--;
                            v_system_data[i][j].inicjalizer = false;
                            v_system_data[i][j].init_number = 0;
                            v_system_data[i][j].init_type = 0;
                            v_system_data[i][j].player_id = 0;
                        }

                    }
                    else if (Det_Gen.add_hyperlanes)
                    {
                        if (Det_Gen.previous_id == 0)
                        {
                            Det_Gen.previous_id = v_system_data[i][j].gal_id;
                        }
                        else
                        {
                            hyperlanes pushing;
                            pushing.from = Det_Gen.previous_id;
                            pushing.to = v_system_data[i][j].gal_id;
                            v_hyperlanes[i][j].push_back(pushing);
                            Det_Gen.previous_id = 0;
                        }
                    }
                    else if (Det_Gen.add_initializer_player)
                    {
                        Det_Gen.player_am++;
                        empire_am++;
                        v_galaxy_generation[i].players_am++;
                        v_system_data[i][j].inicjalizer = true;
                        v_system_data[i][j].init_number = rand() % 6;
                        v_system_data[i][j].init_type = 10;
                        v_system_data[i][j].player_id = Det_Gen.player_am;
                    }
                    else if (Det_Gen.add_initializer_bot)
                    {
                        empire_am++;
                        v_galaxy_generation[i].empire_am++;
                        v_system_data[i][j].inicjalizer = true;
                        v_system_data[i][j].init_number = rand() % 6;
                        v_system_data[i][j].init_type = 1;
                    }
                    else if (Det_Gen.add_initializer_fallen)
                    {
                        fallen_am++;
                        v_galaxy_generation[i].fallen_am++;
                        v_system_data[i][j].inicjalizer = true;
                        v_system_data[i][j].init_number = rand() % 3;
                        v_system_data[i][j].init_type = 2;
                    }
                    else if (Det_Gen.add_initializer_marauder)
                    {
                        maruder_am++;
                        v_galaxy_generation[i].maruder_am++;
                        v_system_data[i][j].inicjalizer = true;
                        v_system_data[i][j].init_number = rand() % 3;
                        v_system_data[i][j].init_type = 5;
                    }
                    else if (Det_Gen.add_initializer_mega)
                    {
                        int temp_number = 0;
                        if (Det_Gen.bits_mega.test(0)) { temp_number = 0; }
                        else if (Det_Gen.bits_mega.test(1)) { temp_number = 1; }
                        else if (Det_Gen.bits_mega.test(2)) { temp_number = 2; }
                        else if (Det_Gen.bits_mega.test(3)) { temp_number = 3; }
                        v_system_data[i][j].inicjalizer = true;
                        v_system_data[i][j].init_number = temp_number;
                        v_system_data[i][j].init_type = 4;
                    }
                    else if (Det_Gen.add_initializer_leviathan)
                    {
                        int temp_number = 0;
                        if (Det_Gen.bits_leviathan.test(0)) { temp_number = 0; }
                        else if (Det_Gen.bits_leviathan.test(1)) { temp_number = 1; }
                        else if (Det_Gen.bits_leviathan.test(2)) { temp_number = 2; }
                        else if (Det_Gen.bits_leviathan.test(3)) { temp_number = 3; }
                        else if (Det_Gen.bits_leviathan.test(4)) { temp_number = 4; }
                        else if (Det_Gen.bits_leviathan.test(5)) { temp_number = 5; }
                        else if (Det_Gen.bits_leviathan.test(6)) { temp_number = 6; }
                        else if (Det_Gen.bits_leviathan.test(7)) { temp_number = 7; }
                        v_system_data[i][j].inicjalizer = true;
                        v_system_data[i][j].init_number = temp_number;
                        v_system_data[i][j].init_type = 3;
                    }
                    else if (Det_Gen.add_initializer_mods)
                    {
                        
                    }
                    else
                    {
                        C_S.box_open = true;
                        C_S.current_system = v_system_data[i][j].gal_id;
                        C_S.current_gal = i;
                        ThrowOutButtons();
                        GE.system_box_x = center_width + ((v_system_data[i][j].gal_x - (C_S.donex - 550)) * 5) + 554;
                        GE.system_box_y = center_height + ((v_system_data[i][j].gal_y - (C_S.doney - 550)) * 5) + 550;

                    }
                    break;
                }
            }
        }
}
void Graphics_Engine::handleKeyboardEvent(SDL_Event& e)
{
        switch (e.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            //std::cout << "Esc entered" << std::endl;
            for (int i = 0; i < D_S_E_Buttons.size(); ++i)
            {
                D_S_E_Buttons[i].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
            }
            Det_Gen.false_all_bools();
            Det_Gen.false_initializers();
            Det_Gen.reset_bits();
            Det_Gen.previous_id = 0;
            gButtons[21].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
            CSHM.remove_galaxies = false;
            gButtons[22].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
            CSHM.redraw_galaxies = false;
            gButtons[19].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
            CSHM.remove_hyperlanes = false;
            gButtons[18].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
            CSHM.redraw_hyperlanes = false;
            if (CSHM.edit_galaxies)
            {
                gButtons[20].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
                CSHM.edit_galaxies = false;
                CSHM.edit_galaxies_loop = false;
                elipse_galaxy_window = false;
                spiral_galaxy_window = false;
                edit = false;
            }
            else if (C_S.box_open == true)
            {
                C_S.box_open = false;
                system_box_x = -1000;
                system_box_y = -1000;
            }
            rerender();
            break;
        }
}

void LButton::handleEvent(SDL_Event* e, int id)
{
    /*
    File_Operation F_O;
    File_Operation* F_O_ptr;
    F_O_ptr = &F_O;
    */


        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

        if (id < 50)
        {
            if (id == 24)
            {
                if (x < mPosition.x)
                {
                    inside = false;
                }

                else if (x > mPosition.x + 300)
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
            else
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
                case 97:
                    if (x > mPosition.x + 32) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
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
                    if (x > mPosition.x + 60) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 114:
                    if (x > mPosition.x + 60) { inside = false; }
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
                    if (x > mPosition.x + 60) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 125:
                    if (x > mPosition.x + 60) { inside = false; }
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
                    if (x > mPosition.x + 60) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 131:
                    if (x > mPosition.x + 60) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 132:
                    if (x > mPosition.x + 60) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                }
                if (CSHM.edit_galaxies)
                {
                case 140:
                    if (x > mPosition.x + 100) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 141:
                    if (x > mPosition.x + 100) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 142:
                    if (x > mPosition.x + 100) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 143:
                    if (x > mPosition.x + 100) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                case 144:
                    if (x > mPosition.x + 100) { inside = false; }
                    else if (y > mPosition.y + 32) { inside = false; }
                    break;
                    if (v_galaxy_generation[current_gal_id].galtype == 1)
                    {
                    case 145:
                        if (x > mPosition.x + 100) { inside = false; }
                        else if (y > mPosition.y + 32) { inside = false; }
                        break;
                    case 146:
                        if (x > mPosition.x + 100) { inside = false; }
                        else if (y > mPosition.y + 32) { inside = false; }
                        break;
                    case 147:
                        if (x > mPosition.x + 100) { inside = false; }
                        else if (y > mPosition.y + 32) { inside = false; }
                        break;
                    case 148:
                        if (x > mPosition.x + 100) { inside = false; }
                        else if (y > mPosition.y + 32) { inside = false; }
                        break;
                    }
                }
            }
            if (id == 63)
            {
                if (x > mPosition.x + 30) { inside = false; }
                else if (y > mPosition.y + 30) { inside = false; }
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
                if (CSHM.remove_galaxies == true)
                {
                    gButtons[21].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG_PRESSED;

                }
                else if (CSHM.redraw_galaxies == true)
                {
                    gButtons[22].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG_PRESSED;
                }
                else if (CSHM.remove_hyperlanes == true)
                {
                    gButtons[19].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG_PRESSED;
                }
                else if (CSHM.redraw_hyperlanes == true)
                {
                    gButtons[18].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG_PRESSED;
                }
                else if (CSHM.edit_galaxies == true)
                {
                    gButtons[20].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG_PRESSED;
                }
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
                            if (C_S.scrolling)
                            {
                                C_S.scrolling = false;
                                Det_Gen.false_all_bools();
                                C_S.box_open = false;
                            }
                            if (current_galaxies_window == false)
                            {
                                DisableOtherWindows();
                                current_galaxies_window = true;
                                rerender();
                                GE.click_effect_remove(id);
                            }
                            else
                            {
                                current_galaxies_window = false;
                                rerender();
                            }
                            break;

                        case 1:
                            //Classinit.initilizers();
                            //initializers_loaded = true;
                            //std::cout << rand() % 20 << std::endl;
                            //F_O.load_files_from_steammod_folder();
                            //F_O.create_folder();
                            break;

                            // Settings
                        case 2:
                            if (C_S.scrolling)
                            {
                                C_S.scrolling = false;
                                Det_Gen.false_all_bools();
                                C_S.box_open = false;
                            }
                            if (settings_window == false)
                            {
                                DisableOtherWindows();
                                settings_window = true;
                                rerender();
                                GE.click_effect_remove(id);
                            }
                            else {
                                settings_window = false;
                                rerender();
                            }
                            break;

                        case 3:
                            F_O.SaveMap();
                            break;

                        case 4:
                            break;
                            // File & Exit
                        case 5:
                            if (C_S.scrolling)
                            {
                                C_S.scrolling = false;
                                Det_Gen.false_all_bools();
                                C_S.box_open = false;
                            }
                            if (saveloadexit_window == false)
                            {
                                DisableOtherWindows();
                                saveloadexit_window = true;
                                rerender();
                                GE.click_effect_remove(id);
                            }

                            else {
                                saveloadexit_window = false;
                                rerender();
                            }
                            break;

                            // Save Permament settings
                        case 6:
                            break;

                            //Import
                        case 10:
                            rerender();
                            LoadFile();
                            rerender();
                            GE.click_effect_remove(id);
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
                            GE.click_effect_remove(id);
                            break;


                            //Play
                        case 12:
                            //std::cout << "Play 1" << std::endl;
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
                                //std::cout << "Play 2" << std::endl;
                                //std::cout << "Work 1" << std::endl;
                                if (initializers == true)
                                {
                                    if (initializers_loaded == false)
                                    {
                                        for (int i = 0; i < v_galaxy_generation.size(); i++)
                                        {
                                            for (int j = 0; j < v_system_data[i].size(); j++)
                                            {
                                                v_system_data[i][j].inicjalizer = 0;
                                                v_system_data[i][j].init_type = 0;
                                                v_system_data[i][j].init_number = 0;
                                            }
                                            set_center(i);
                                        }
                                        //std::cout << "Play 3" << std::endl;
                                        Classinit.initilizers();
                                    }
                                }
                                //std::cout << "Work 1.5" << std::endl;
                                //std::cout << "Play 4" << std::endl;
                                osfile(modfolderpath);
                            }
                            //std::cout << "Play 5" << std::endl;
                            //std::cout << "Work 2" << std::endl;
                            SteamAPI_Init();
                            SteamAPI_RestartAppIfNecessary(281990);
                            //std::cout << "Exit" << std::endl;
                            GE.click_effect_remove(id);
                            break;

                            //Exit
                        case 13:
                            SaveSettings();
                            SaveRandomSettings();
                            close();
                            std::exit(0);
                            GE.click_effect_remove(id);
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
                            GE.click_effect_remove(id);
                            break;

                            // Remove Hyperlanes
                        case 16:
                            remove_hyperlanes(0, 0);
                            rerender();
                            GE.click_effect_remove(id);
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
                            GE.click_effect_remove(id);
                            break;

                            // Remove in Galaxy
                        case 18:
                            if (galaxies_am > 0)
                            {
                                CSHM.redraw_hyperlanes = true;
                                CSHM.remove_galaxies = false;
                                CSHM.redraw_galaxies = false;
                                CSHM.remove_hyperlanes = false;
                                CSHM.edit_galaxies = false;
                            }
                            rerender();
                            break;

                            // Redraw in Galaxy
                        case 19:
                            if (galaxies_am > 0)
                            {
                                CSHM.remove_hyperlanes = true;
                                CSHM.remove_galaxies = false;
                                CSHM.redraw_galaxies = false;
                                CSHM.redraw_hyperlanes = false;
                                CSHM.edit_galaxies = false;
                            }
                            rerender();
                            break;

                            // Edit Selected Galaxy
                        case 20:
                            if (galaxies_am > 0)
                            {
                                edit = true;
                                CSHM.redraw_hyperlanes = false;
                                CSHM.remove_galaxies = false;
                                CSHM.redraw_galaxies = false;
                                CSHM.remove_hyperlanes = false;
                                CSHM.edit_galaxies = true;
                            }
                            rerender();
                            break;


                            // Remove Selected Galaxy
                        case 21:
                            if (galaxies_am > 0)
                            {
                                CSHM.remove_galaxies = true;
                                CSHM.redraw_galaxies = false;
                                CSHM.remove_hyperlanes = false;
                                CSHM.redraw_hyperlanes = false;
                                CSHM.edit_galaxies = false;
                            }
                            rerender();
                            break;


                            // Redraw Selected Galaxy
                        case 22:
                            if (galaxies_am > 0)
                            {
                                CSHM.redraw_galaxies = true;
                                CSHM.remove_galaxies = false;
                                CSHM.remove_hyperlanes = false;
                                CSHM.redraw_hyperlanes = false;
                                CSHM.edit_galaxies = false;
                            }
                            rerender();
                            break;

                            // Edit steam folder patch
                        case 23:
                            edit_patch = true;
                            firstrunsettings();
                            edit_patch = false;
                            GE.click_effect_remove(id);
                            break;

                            // Generate Initializers
                        case 24:
                            Classinit.initilizers();
                            initializers_loaded = true;
                            break;
                            // Clear Map
                        case 28:
                            alpha1 = 0,
                            clear_map();
                            rerender();
                            GE.click_effect_remove(id);
                            break;

                            // Random
                        case 29:
                            //rerender();
                            edit = false;
                            draw_galaxy();
                            random_generator();
                            GE.click_effect_remove(id);
                            break;

                            //Choose Elipse Shape
                        case 30:
                            v_galaxy_generation.emplace_back();
                            galaxies_am++;
                            edit = false;
                            DisableOtherWindows();
                            rerender();
                            add_galaxy_elipse();
                            GE.click_effect_remove(id);
                            break;


                            //Choose Spiral Shape
                        case 31:
                            v_galaxy_generation.emplace_back();
                            galaxies_am++;
                            edit = false;
                            DisableOtherWindows();
                            rerender();
                            add_galaxy_spiral();
                            GE.click_effect_remove(id);
                            break;

                        case 39:
                            LoadRandomDefaultSettings();
                            GE.click_effect_remove(id);
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
                        case 63:
                            if (show_initializers == false)
                            {
                                show_initializers = true;
                                rerender();
                            }
                            else
                            {
                                show_initializers = false;
                                rerender();
                            }
                            break;

                        case 97:
                            if (!export_mode_multi)
                            {
                                export_mode_multi = true;
                                rerender();
                            }
                            else
                            {
                                export_mode_multi = false;
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
                            GE.text_input(center_width + 1403,center_height + 270, 113);
                            CRS.size_from_edited = false;
                            break;
                            // Size to
                        case 114:
                            CRS.size_to_edited = true;
                            GE.text_input(center_width + 1513, center_height + 270, 114);
                            CRS.size_to_edited = false;
                            break;
                            // Hyperlanes from
                        case 115:
                            CRS.hyperlanes_max_length_from_edited = true;
                            GE.text_input(center_width + 1560, center_height + 310, 115);
                            CRS.hyperlanes_max_length_from_edited = false;
                            break;
                            // Hyperlanes to
                        case 116:
                            CRS.hyperlanes_max_length_to_edited = true;
                            GE.text_input(center_width + 1680, center_height + 310, 116);
                            CRS.hyperlanes_max_length_to_edited = false;
                            break;
                            // Circle stars from
                        case 117:
                            CRS.circle_stars_from_edited = true;
                            GE.text_input(center_width + 1500, center_height + 390, 117);
                            CRS.circle_stars_from_edited = false;
                            break;
                            // Circle stars to
                        case 118:
                            CRS.circle_stars_to_edited = true;
                            GE.text_input(center_width + 1580, center_height + 390, 118);
                            CRS.circle_stars_to_edited = false;
                            break;
                            // SPiral stars from
                        case 119:
                            CRS.spiral_stars_from_edited = true;
                            GE.text_input(center_width + 1500, center_height + 480, 119);
                            CRS.spiral_stars_from_edited = false;
                            break;
                            // SPiral stars to
                        case 120:
                            CRS.spiral_stars_to_edited = true;
                            GE.text_input(center_width + 1580, center_height + 480, 120);
                            CRS.spiral_stars_to_edited = false;
                            break;
                            // Square factor
                        case 121:
                            CRS.square_factor_edited = true;
                            GE.text_input(center_width + 1435, center_height + 520, 121);
                            CRS.square_factor_edited = false;
                            break;
                            // Arm max from
                        case 122:
                            CRS.arm_max_width_from_edited = true;
                            GE.text_input(center_width + 1440, center_height + 560, 122);
                            CRS.arm_max_width_from_edited = false;
                            break;
                            // Arm max to
                        case 123:
                            CRS.arm_max_width_to_edited = true;
                            GE.text_input(center_width + 1580, center_height + 560, 123);
                            CRS.arm_max_width_to_edited = false;
                            break;
                            // Arm random from
                        case 124:
                            CRS.arm_random_width_from_edited = true;
                            GE.text_input(center_width + 1505, center_height + 600, 124);
                            CRS.arm_random_width_from_edited = false;
                            break;
                            // Arm random to
                        case 125:
                            CRS.arm_random_width_to_edited = true;
                            GE.text_input(center_width + 1600, center_height + 600, 125);
                            CRS.arm_random_width_to_edited = false;
                            break;
                            // Rotation factor
                        case 126:
                            CRS.rotation_factor_edited = true;
                            GE.text_input(center_width + 1454, center_height + 640, 126);
                            CRS.rotation_factor_edited = false;
                            break;
                            // Arm amount from
                        case 128:
                            CRS.arm_amount_from_edited = true;
                            GE.text_input(center_width + 1417, center_height + 680, 128);
                            CRS.arm_amount_from_edited = false;
                            break;
                            // Arm amount to
                        case 129:
                            CRS.arm_amount_to_edited = true;
                            GE.text_input(center_width + 1580, center_height + 680, 129);
                            CRS.arm_amount_to_edited = false;
                            break;
                            // Size ratio
                        case 130:
                            CRS.size_ratio_edited = true;
                            GE.text_input(center_width + 1380, center_height + 780, 130);
                            CRS.size_ratio_edited = false;
                            break;
                            // Arm ratio
                        case 131:
                            CRS.arm_ratio_edited = true;
                            GE.text_input(center_width + 1685, center_height + 780, 131);
                            CRS.arm_ratio_edited = false;
                            break;
                            // Arm width ratio
                        case 132:
                            CRS.arm_width_ratio_edited = true;
                            GE.text_input(center_width + 1460, center_height + 820, 132);
                            CRS.arm_width_ratio_edited = false;
                            break;
                        case 140:
                            C_E.star = true;
                            GE.text_input(center_width + 1420, center_height + 230, 0);
                            C_E.star = false;
                            if (v_galaxy_generation[current_gal_id].galtype == 0)
                            {
                                edit_circle(0, current_gal_id);
                            }
                            else
                            {
                                edit_spiral(0, current_gal_id);
                            }
                            break;
                        case 141:
                            C_E.gsize = true;
                            GE.text_input(center_width + 1478, center_height + 260, 1);
                            C_E.gsize = false;
                            if (v_galaxy_generation[current_gal_id].galtype == 0)
                            {
                                edit_circle(0, current_gal_id);
                            }
                            else
                            {
                                edit_spiral(0, current_gal_id);
                            }
                            break;
                        case 142:
                            C_E.posX = true;
                            GE.text_input(center_width + 1420, center_height + 290, 2);
                            C_E.posX = false;
                            if (v_galaxy_generation[current_gal_id].galtype == 0)
                            {
                                edit_circle(0, current_gal_id);
                            }
                            else
                            {
                                edit_spiral(0, current_gal_id);
                            }
                            break;
                        case 143:
                            C_E.posY = true;
                            GE.text_input(center_width + 1420, center_height + 320, 3);
                            C_E.posY = false;
                            if (v_galaxy_generation[current_gal_id].galtype == 0)
                            {
                                edit_circle(0, current_gal_id);
                            }
                            else
                            {
                                edit_spiral(0, current_gal_id);
                            }
                            break;
                        case 144:
                            C_E.max_hyp_dist = true;
                            GE.text_input(center_width + 1650, center_height + 350, 4);
                            C_E.max_hyp_dist = false;
                            if (v_galaxy_generation[current_gal_id].galtype == 0)
                            {
                                edit_circle(0, current_gal_id);
                            }
                            else
                            {
                                edit_spiral(0, current_gal_id);
                            }
                            break;
                        case 145:
                            C_E.num_arms = true;
                            GE.text_input(center_width + 1520, center_height + 380, 5);
                            C_E.num_arms = false;
                            edit_spiral(0, current_gal_id);
                            break;
                        case 146:
                            C_E.arm_offset_max = true;
                            
                            GE.text_input(center_width + 1498, center_height + 410, 6);
                            C_E.arm_offset_max = false;
                            
                            edit_spiral(0, current_gal_id);
                            break;
                        case 147:
                            C_E.random_arm_offset = true;
                            GE.text_input(center_width + 1480, center_height + 440, 7);
                            C_E.random_arm_offset = false;
                            edit_spiral(0, current_gal_id);
                            break;
                        case 148:
                            C_E.rotation_factor = true;
                            GE.text_input(center_width + 1470, center_height + 470, 8);
                            C_E.rotation_factor = false;
                            edit_spiral(0, current_gal_id);
                            break;
                            //Settings
                        }
                    }
                    if ((id >= 150) && (id < 200))
                    {
                        if (!C_S.scrolling)
                        {
                            current_gal_id = id - 150;
                            if (CSHM.remove_galaxies == true)
                            {
                                gButtons.erase(gButtons.begin() + id);
                                remove_galaxy_full(current_gal_id);
                                rerender();
                            }
                            else if (CSHM.redraw_galaxies == true)
                            {
                                redraw_galaxy();
                                rerender();
                            }
                            else if (CSHM.remove_hyperlanes == true)
                            {
                                if (v_galaxy_generation[current_gal_id].hyperlanes_generated)
                                {
                                    remove_hyperlanes(1, current_gal_id);
                                }
                                rerender();
                            }
                            else if (CSHM.redraw_hyperlanes == true)
                            {
                                if (v_galaxy_generation[current_gal_id].hyperlanes_generated)
                                {
                                    remove_hyperlanes(1, current_gal_id);
                                }
                                link(1, current_gal_id);
                                rerender();
                            }
                            else if (CSHM.edit_galaxies == true)
                            {
                                if (current_galaxies_window == true)
                                {
                                    current_galaxies_window = false;
                                }
                                CSHM.edit_galaxies_loop = true;
                                rerender();
                            }
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
            case SDL_MOUSEWHEEL:
                if ((x < 1200) && (y < 1080))
                {
                    if (e->wheel.y > 0)
                    {
                        DisableOtherWindows();
                        C_S.scrolling = true;
                        SDL_GetMouseState(&C_S.donex, &C_S.doney);
                        C_S.done = true;
                    }
                    if (e->wheel.y < 0)
                    {
                        C_S.scrolling = false;
                        Det_Gen.false_initializers();
                        Det_Gen.false_all_bools();
                        for (int i = 0; i < D_S_E_Buttons.size(); ++i)
                        {
                            D_S_E_Buttons[i].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
                        }
                        C_S.box_open = false;
                        GE.system_box_x = -1000;
                        GE.system_box_y = -1000;
                        C_S.done = false;
                        current_galaxies_window = true;
                    }
                }
                break;
            }
        }
}
// Different Windows/Surfaces ------------------------------------------------
void SaveLoadExit()
{
    gModulatedTexture.setAlpha(233);
    gModulatedTexture.render(center_width + 1230, center_height + 160, 650, 350);
    GE.render_button_with_text(0, 10, 1610, 230, "Import", 1660, 235);
    GE.render_button_with_text(0, 11, 1610, 290, "Export", 1660, 295);
    GE.render_button_with_text(0, 12, 1610, 350, "Play", 1675, 355);
    GE.render_button_with_text(0, 13, 1610, 410, "Exit", 1680, 415);

    GE.render_checkbox(97, 1512, 238, 30, 30);
    GE.render_checkbox(98, 1512, 278, 30, 30);
    GE.render_checkbox(99, 1512, 318, 30, 30);
    GE.render_checkbox(100, 1512, 358, 30, 30);

    GE.text_render_v2("Multiplayer", 1360, 238);
    GE.text_render_v2("Initializers", 1370, 278);
    GE.text_render_v2("Save", 1433, 318);
    GE.text_render_v2("SMGG Hyperlanes", 1260, 358);
    GE.text_render_v2("File operation and exit.", 1550, 170);
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
    GE.text_with_button(125, "to:", 1580, 600);
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

    GE.render_button_with_text(0, 39, 1680, 1000, "Reset", 1730, 1005);
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
    for (int i = 0; i < v_system_data.size(); i++)
    {
        for (int j = 0; j < v_system_data[i].size(); j++)
        {
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 0);
            SDL_RenderDrawPoint(gRenderer, center_width + (v_system_data[i][j].gal_x + 550), center_height + (v_system_data[i][j].gal_y + 550));
            if (show_initializers)
            {
                if (v_system_data[i][j].inicjalizer)
                {
                    if (v_system_data[i][j].init_type == 1)
                    {
                        GE.render_color_box(255, 170, 170, (v_system_data[i][j].gal_x + 550), (v_system_data[i][j].gal_y + 550), 3, 3);
                    }
                    else if (v_system_data[i][j].init_type == 2)
                    {
                        GE.render_color_box(255, 0, 255, (v_system_data[i][j].gal_x + 550), (v_system_data[i][j].gal_y + 550), 3, 3);
                    }
                    else if (v_system_data[i][j].init_type == 3)
                    {
                        GE.render_color_box(255, 81, 0, (v_system_data[i][j].gal_x + 550), (v_system_data[i][j].gal_y + 550), 3, 3);
                    }
                    else if (v_system_data[i][j].init_type == 4)
                    {
                        GE.render_color_box(0, 255, 255, (v_system_data[i][j].gal_x + 550), (v_system_data[i][j].gal_y + 550), 3, 3);
                    }
                    else if (v_system_data[i][j].init_type == 5)
                    {
                        GE.render_color_box(255, 0, 0, (v_system_data[i][j].gal_x + 550), (v_system_data[i][j].gal_y + 550), 3, 3);
                    }
                    else if (v_system_data[i][j].init_type == 10)
                    {
                        GE.render_color_box(0, 255, 0, (v_system_data[i][j].gal_x + 550), (v_system_data[i][j].gal_y + 550), 3, 3);
                    }
                }
            }
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

    v_galaxy_generation[current_gal_id].galtype = 0;

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
    GE.text_render_v2("Initializers", 1500, 780);
    GE.render_button_with_text_dynamic(0, 24, 1260, 830, 300, 45, "Generate Initializers", 1277, 835);
    GE.text_render_v2("Show", 1280, 890);
    GE.render_checkbox(63, 1360, 890, 30, 30);
}


void edit_button(int mode, int gal_id)
{
        gModulatedTexture.setAlpha(233);
        gModulatedTexture.render(center_width + 1220, center_height + 170, 680, 390);
        if (v_galaxy_generation[gal_id].galtype == 0)
        {
            GE.text_with_button(140, "Systems:", 1240, 230);
            GE.text_with_button(141, "Size (Radius):", 1240, 260);
            GE.text_with_button(142, "Center X:", 1240, 290);
            GE.text_with_button(143, "Center Y:", 1240, 320);
            GE.text_with_button(144, "Max Hyperlanes Distance:", 1240, 350);
        }
        else if (v_galaxy_generation[gal_id].galtype == 1)
        {
            GE.text_with_button(140, "Systems:", 1240, 230);
            GE.text_with_button(141, "Size (Radius):", 1240, 260);
            GE.text_with_button(142, "Center X:", 1240, 290);
            GE.text_with_button(143, "Center Y:", 1240, 320);
            GE.text_with_button(144, "Max Hyperlanes Distance:", 1240, 350);
            GE.text_with_button(145, "Number of Arms:", 1240, 380);
            GE.text_with_button(146, "Arm Max Width:", 1240, 410);
            GE.text_with_button(147, "Random Width:", 1240, 440);
            GE.text_with_button(148, "Arm Rotation:", 1240, 470);
        }
        //std::cout << "Edit entered " << std::endl;
}

void edit_circle(int mode, int gal_id)
{
    remove_galaxy(gal_id);

    alpha1 = 250, alpha2 = 225, alpha3 = 0;
    generate_elipse(gal_id);
    if (v_galaxy_generation[gal_id].hyperlanes_generated)
    {
        link(0, gal_id);
    }

    rerender();
    draw_galaxy();
}

void edit_spiral(int mode, int gal_id)
{
    remove_galaxy(gal_id);

    alpha1 = 250, alpha2 = 225, alpha3 = 0;
    generate_spiral(gal_id);
    if (v_galaxy_generation[gal_id].hyperlanes_generated)
    {
        link(0, gal_id);
    }

    rerender();
    draw_galaxy();
}

void remove_galaxy(int gal_id)
{
    if (gal_id < galaxies_am)
    {
        sys_sum -= v_system_data[gal_id].size();
        v_system_data[gal_id].clear();
        SystemButtons[gal_id].clear();
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
        SystemButtons.erase(SystemButtons.begin() + gal_id);
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
            for (int i = 0; i < v_galaxy_generation.size(); i++)
            {
                v_hyperlanes.emplace_back();
                for (int j = 0; j < v_system_data[i].size(); j++)
                {
                    v_hyperlanes[i].emplace_back();
                }
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
            for (int j = 0; j < v_system_data[gal_id].size(); j++)
            {
                v_hyperlanes[gal_id].emplace_back();
            }
            v_galaxy_generation[gal_id].hyperlanes_generated = false;
        }
    }
}

void clear_map()
{
    for (int i = 0; i < galaxies_am; ++i)
    {
        gButtons.erase(gButtons.begin() + 150 + i);
    }
    v_system_data.clear();
    v_system_data_copy.clear();
    v_galaxy_generation.clear();
    clear_hyperlanes_data();
    v_hyperlanes.clear();
    v_hyperlanes_copy.clear();
    SystemButtons.clear();

    galaxies_am = 0;
    sys_sum = 0;
    empire_am = 0,
    fallen_am = 0,
    maruder_am = 0;
    current_gal_id = NULL;
    initializers_loaded = false;
    hyperlanes_loaded = false;
    mult = 0;
    Det_Gen.player_am = 0;
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
    if (v_galaxy_generation[current_gal_id].hyperlanes_generated)
    {
        link(0, current_gal_id);
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
    /*
    File_Operation F_O;
    File_Operation* F_O_ptr;
    F_O_ptr = &F_O;
    */


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
            if (!local_maps_created)
            {
                F_O.create_folder();
            }
            RandomDefaultSettings();
            LoadRandomDefaultSettings();
            LoadRandomSettings();
            while(!quit)
            {
                SDL_Delay(33);
                //Handle events on queue ASSAD
                while(SDL_PollEvent(&e))
                {
                    //Handle Keyboard events 
                    if (e.type == SDL_KEYDOWN)
                    {
                        GE.handleKeyboardEvent(e);
                    }

                    //Handle button events
                    for (int i = 0; i < gButtons.size(); ++i)
                    {
                        if ((e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEWHEEL) && pathsaved == true)
                        {
                            gButtons[i].handleEvent(&e, i);
                        }
                    }
                    for (int i = 0; i < SystemButtons.size(); ++i)
                    {
                        for (int j = 0; j < SystemButtons[i].size(); ++j)
                        {
                            if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
                            {
                                SystemButtons[i][j].handleSystemButtonEvent(e, i, j);
                            }
                        }
                    }
                    for (int i = 0; i < D_S_E_Buttons.size(); i++)
                    {
                        if ((e.type == SDL_MOUSEBUTTONDOWN) || (e.type == SDL_MOUSEBUTTONUP))
                        {
                            D_S_E_Buttons[i].handle_D_S_E_ButtonEvent(e, i);
                        }
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