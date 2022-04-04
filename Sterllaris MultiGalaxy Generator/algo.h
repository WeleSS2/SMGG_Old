#pragma once

//Inside code ----------------------------------------------------------------------------------------------------------------------------

float RandFloat() {
    return ((float)rand() / (float)RAND_MAX);
}

float xand(float angle, float distance)
{

    float starX = cos(angle) * distance;

    float randomOffsetX = RandFloat() * randomOffsetXY;

    starX += randomOffsetX;
    return starX;
}

float yand(float angle, float distance)
{
    float starY = sin(angle) * distance;

    float randomOffsetY = RandFloat() * randomOffsetXY;

    starY += randomOffsetY;
    return starY;
}

void generate_spiral(int gal_id) 
{
    //std::cout << "Spiral entered" << std::endl;
    if (edit == false)
    {
        v_system_data.emplace_back();
    }
    generate_center(gal_id);
    numArms = v_galaxy_generation[gal_id].i_numArms;
    armOffsetMax = v_galaxy_generation[gal_id].f_armOffsetMax;
    rotationFactor = v_galaxy_generation[gal_id].f_rotationFactor;
    randomOffsetXY = v_galaxy_generation[gal_id].f_randomOffsetXY;
    armSeparationDistance = 2 * PI / numArms;
    int bythe = v_galaxy_generation[gal_id].i_gsize, temp_edit = 0;
    int max = 0, dist = 6, limit = 0;
    bool is_ok = true;
    for (int i = 1; i < v_galaxy_generation[gal_id].i_star; i++) {
        //std::cout << i << std::endl;
        // Choose a distance from the center of the galaxy.
        float distance = RandFloat();
        distance = pow(distance, 2);
        if (distance < 0.05)
        {
            int chance = rand() % 100;
            if (chance > 10)
            {
                while (distance < 0.5)
                {
                    distance = RandFloat();
                    distance = pow(distance, 2);
                }
            }
        }
        else if (distance < 0.1)
        {
            int chance = rand() % 100;
            if (chance > 35)
            {
                while (distance < 0.1)
                {
                    distance = RandFloat();
                    distance = pow(distance, 2);
                }
            }
        }
        else if (distance < 0.15)
        {
            int chance = rand() % 100;
            if (chance > 60)
            {
                while (distance < 0.15)
                {
                    distance = RandFloat();
                    distance = pow(distance, 2);
                }
            }
        }
        else if (distance < 0.25)
        {
            int chance = rand() % 100;
            if (chance > 85)
            {
                while (distance < 0.25)
                {
                    distance = RandFloat();
                    distance = pow(distance, 2);
                }
            }
        }
        else if (distance < 0.35)
        {
            int chance = rand() % 100;
            if (chance > 95)
            {
                while (distance < 0.35)
                {
                    distance = RandFloat();
                    distance = pow(distance, 2);
                }
            }
        }
        // Choose an angle between 0 and 2 * PI.
        float angle = RandFloat() * 2 * PI;
        float armOffset = RandFloat() * armOffsetMax;
        armOffset = armOffset - armOffsetMax / 2;
        armOffset = armOffset * (1 / distance);

        if (armOffset < 0)
        {
            armOffset = abs(armOffset);
        }
        float squaredArmOffset = pow(armOffset, CRS.square_factor);
        if (armOffset < 0)
            squaredArmOffset = squaredArmOffset * -1;
        armOffset = squaredArmOffset;
        float rotation = distance * rotationFactor;
        angle = (int)(angle / armSeparationDistance) * armSeparationDistance + armOffset +rotation;


        // Convert polar coordinates to 2D cartesian coordinates.


        float j = 1;
        float tx = xand(angle, distance) * bythe;
        float ty = yand(angle, distance) * bythe;

        if (i == 1)
        {
            //std::cout << angle << " Angle " << std::endl;
            //std::cout << distance << " Distance" << std::endl;
            //std::cout << bythe << " Bythe" << std::endl;
            //std::cout << tx << " " << ty << std::endl;
            //std::cout << "----------------" << std::endl;
        }

        int zx = static_cast<int>(tx) + v_galaxy_generation[gal_id].i_cen_posX;
        int zy = static_cast<int>(ty) + v_galaxy_generation[gal_id].i_cen_posY;

        bool remove = false;
        // Minimal distance between points
        for (int j = 0; ((j < v_system_data[gal_id].size()) && (remove == false)); ++j)
        {
            if ((zx - v_system_data[gal_id][j].gal_x < dist) && (zx - v_system_data[gal_id][j].gal_x > -dist))
            {
                if ((zy - v_system_data[gal_id][j].gal_y < dist) && (zy - v_system_data[gal_id][j].gal_y > -dist))
                {
                    i--;
                    remove = true;
                }
            }
            if (limit == 1000000)
            {
                break;
            }
            limit++;
        }
        if (limit == 1000000)
        {
            //std::cout << "Galaxy removed" << std::endl;
            is_ok = false;
            galaxy_canceled = true;
            if (CSHM.edit_galaxies_loop)
            {
                CSHM.edit_galaxies_loop = false;
            }
            rerender();
            SDL_Delay(2000);
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
            galaxy_canceled = false;
            rerender();
            break;
        }
        if (remove == false)
        {
            // Now we can assign xy coords.
            int con_m = rand() % max_hyperlane_am + min_hyperlane_am;
            v_system_data[gal_id].emplace_back();
            v_system_data[gal_id][i].gal_id = i;
            v_system_data[gal_id][i].con_max = con_m;
            v_system_data[gal_id][i].con = 0;
            v_system_data[gal_id][i].gal_x = zx;
            v_system_data[gal_id][i].gal_y = zy;
            v_system_data[gal_id][i].inicjalizer = false;
            v_system_data[gal_id][i].init_type = 0;
        }
        remove = false;
        max++;
    }
    if (is_ok == true)
    {
        sys_sum += v_galaxy_generation[gal_id].i_star;
    }
    //std::cout << "Spiral leaved" << std::endl;
}

// Generate eclipse galaxy
void generate_elipse(int gal_id)
{
    if (edit == false)
    {
        v_system_data.emplace_back();
    }
    generate_center(gal_id);
    int border = 500, temp_edit = 0;
    int star = v_galaxy_generation[gal_id].i_star;
    int gsize = v_galaxy_generation[gal_id].i_gsize;
    int cen_posX = v_galaxy_generation[gal_id].i_cen_posX;
    int cen_posY = v_galaxy_generation[gal_id].i_cen_posY;
    bool is_ok = true;
    srand(time(NULL));
    for (int i = 1; i < star; i++)
    {
        int x = rand() % (2 * gsize) - (gsize - cen_posX);
        int y = rand() % (2 * gsize) - (gsize - cen_posY);
        // Repeat if wrong coordinates
        while (((x >= 500) || (x <= -500)) || ((y >= 500) || (y <= -500)) || (sqrt(pow(x - cen_posX, 2) + pow(y - cen_posY, 2)) >= gsize))
        {
            int a = rand() % (2 * gsize) - (gsize - cen_posX);
            int b = rand() % (2 * gsize) - (gsize - cen_posY);
            x = a;
            y = b;
        }
        int dist = 6, limit = 0;
        // Sprawdzenie czy jakiœ punkt jest w zasiêgu x < 10 lub y < 10
        for (int j = 0; j < v_system_data[gal_id].size(); ++j)
        {
            if ((x - v_system_data[gal_id][j].gal_x < dist) && (x - v_system_data[gal_id][j].gal_x > -dist))
            {
                if ((y - v_system_data[gal_id][j].gal_y < dist) && (y - v_system_data[gal_id][j].gal_y > -dist))
                {
                    while (
                        ((x - v_system_data[gal_id][j].gal_x < dist) && (x - v_system_data[gal_id][j].gal_x > -dist))
                        ||
                        ((y - v_system_data[gal_id][j].gal_y < dist) && (y - v_system_data[gal_id][j].gal_y > -dist))
                        ||
                        ((x >= 500) || (x <= -500)) || ((y >= 500) || (y <= -500))
                        ||
                        (sqrt(pow(x - cen_posX, 2) + pow(y - cen_posY, 2)) >= gsize)
                        )
                    {
                        x = rand() % (2 * gsize) - (gsize - cen_posX);
                        y = rand() % (2 * gsize) - (gsize - cen_posY);
                        limit++;
                        if (limit == 100000)
                        {
                            break;
                        }
                    }
                    j = 0;
                }
            }
            if (limit == 100000)
            {
                break;
            }
        }
        if (limit == 100000)
        {
            is_ok = false;
            galaxy_canceled = true;
            if (CSHM.edit_galaxies_loop)
            {
                CSHM.edit_galaxies_loop = false;
            }
            rerender();
            SDL_Delay(2000);
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
            galaxy_canceled = false;
            rerender();
            break;
        }
        int con_m = rand() % max_hyperlane_am + min_hyperlane_am;
        v_system_data[gal_id].emplace_back();
        v_system_data[gal_id][i].gal_id = i;
        v_system_data[gal_id][i].con_max = con_m;
        v_system_data[gal_id][i].con = 0;
        v_system_data[gal_id][i].gal_x = x;
        v_system_data[gal_id][i].gal_y = y;
        v_system_data[gal_id][i].inicjalizer = false;
        v_system_data[gal_id][i].init_type = 0;
    }
    if (is_ok == true)
    {
        sys_sum += star;
    }
}

void generate_center(int gal_id)
{
    int con_m = rand() % max_hyperlane_am + min_hyperlane_am;
    v_system_data[gal_id].emplace_back();
    v_system_data[gal_id][0].gal_id = 0;
    v_system_data[gal_id][0].con_max = con_m;
    v_system_data[gal_id][0].con = 0;
    v_system_data[gal_id][0].gal_x = v_galaxy_generation[gal_id].i_cen_posX;
    v_system_data[gal_id][0].gal_y = v_galaxy_generation[gal_id].i_cen_posY;
    v_system_data[gal_id][0].inicjalizer = true;
    v_system_data[gal_id][0].init_type = 99;
}

void set_center(int gal_id)
{
    v_system_data[gal_id][0].inicjalizer = true;
    v_system_data[gal_id][0].init_type = 99;
}


// Stellaris like linking (Closest + 1 random)
void link(int mode, int gal_id)
{
    v_hyperlanes.emplace_back();
    link_wave(mode, gal_id, -10);
    clear_hyperlanes_data();
    check_systems(mode, gal_id);
    clear_hyperlanes_data();
    v_galaxy_generation[gal_id].hyperlanes_generated = true;
}

void link_wave(int mode, int gal_id, int random_sys)
{
    v_dist_id.clear();
    bool not_check = false;
    if (random_sys == -10)
    {
        not_check = true;
        random_sys = 0;
        
    }
    int a = 0;
    for (int j = 0; j < v_galaxy_generation[gal_id].i_star; j++)
    {
        if ((v_system_data[gal_id][random_sys].gal_x - v_system_data[gal_id][j].gal_x < v_galaxy_generation[gal_id].i_max_hyp_dis) && (v_system_data[gal_id][random_sys].gal_x - v_system_data[gal_id][j].gal_x > -v_galaxy_generation[gal_id].i_max_hyp_dis) && (v_system_data[gal_id][random_sys].gal_x - v_system_data[gal_id][j].gal_x != 0))
        {
            if ((v_system_data[gal_id][random_sys].gal_y - v_system_data[gal_id][j].gal_y < v_galaxy_generation[gal_id].i_max_hyp_dis) && (v_system_data[gal_id][random_sys].gal_y - v_system_data[gal_id][j].gal_y > -v_galaxy_generation[gal_id].i_max_hyp_dis) && (v_system_data[gal_id][random_sys].gal_y - v_system_data[gal_id][j].gal_y != 0))
            {
                if (v_system_data[gal_id][j].con < v_system_data[gal_id][j].con_max)
                {
                    int t_dist = sqrt(pow(v_system_data[gal_id][j].gal_x - v_system_data[gal_id][random_sys].gal_x, 2) + pow(v_system_data[gal_id][j].gal_y - v_system_data[gal_id][random_sys].gal_y, 2));
                    v_dist_id.emplace_back();
                    v_dist_id[a].distance = t_dist;
                    v_dist_id[a].from = v_system_data[gal_id][random_sys].gal_id;
                    v_dist_id[a].to = v_system_data[gal_id][j].gal_id;
                    a++;
                }
            }
        }
    }
    if (v_system_data[gal_id][random_sys].con_max > v_dist_id.size())
    {
        for (int j = 0; j < v_galaxy_generation[gal_id].i_star; j++)
        {
            if ((v_system_data[gal_id][random_sys].gal_x - v_system_data[gal_id][j].gal_x < v_galaxy_generation[gal_id].i_max_hyp_dis * 2) && (v_system_data[gal_id][random_sys].gal_x - v_system_data[gal_id][j].gal_x > -v_galaxy_generation[gal_id].i_max_hyp_dis * 2) && (v_system_data[gal_id][random_sys].gal_x - v_system_data[gal_id][j].gal_x != 0))
            {
                if ((v_system_data[gal_id][random_sys].gal_y - v_system_data[gal_id][j].gal_y < v_galaxy_generation[gal_id].i_max_hyp_dis * 2) && (v_system_data[gal_id][random_sys].gal_y - v_system_data[gal_id][j].gal_y > -v_galaxy_generation[gal_id].i_max_hyp_dis * 2) && (v_system_data[gal_id][random_sys].gal_y - v_system_data[gal_id][j].gal_y != 0))
                {
                    if (v_system_data[gal_id][j].con < v_system_data[gal_id][j].con_max)
                    {
                        int t_dist = sqrt(pow(v_system_data[gal_id][j].gal_x - v_system_data[gal_id][random_sys].gal_x, 2) + pow(v_system_data[gal_id][j].gal_y - v_system_data[gal_id][random_sys].gal_y, 2));
                        v_dist_id.emplace_back();
                        v_dist_id[a].distance = t_dist;
                        v_dist_id[a].from = v_system_data[gal_id][random_sys].gal_id;
                        v_dist_id[a].to = v_system_data[gal_id][j].gal_id;
                        a++;
                    }
                }
            }
        }
    }
    std::sort(v_dist_id.begin(), v_dist_id.end(), less_than_key());
    if (mode == 1)
    {
        if (v_dist_id.size() > v_system_data[gal_id][random_sys].con_max)
        {
            v_dist_id.erase(v_dist_id.begin() + rand() % v_system_data[gal_id][random_sys].con_max);
        }
    }
    wave.clear();

    //std::cout << "Work correctly " << std::endl;
    s_wave wave_push;
    wave_push.id = random_sys;
    wave.push_back(wave_push);

    for (int i = 0; i < v_system_data[gal_id][random_sys].con_max; i++)
    {
        hyperlanes pushing;
        pushing.from = random_sys;
        pushing.to = v_dist_id[i].to;
        v_hyperlanes[gal_id].push_back(pushing);

        s_wave wave_push;
        wave_push.id = v_dist_id[i].to;
        //std::cout << v_dist_id[i].to << std::endl;
        wave.push_back(wave_push);


        v_system_data[gal_id][random_sys].con++;
        v_system_data[gal_id][v_dist_id[i].to].con++;
    }
    if (wave.size() > 0)
    {
        for (int i = 0; i < wave.size(); i++)
        {
            //std::cout << wave[i].id << "    " << wave.size() <<  std::endl;
        }
        v_dist_id.clear();
        link_wave_sub(mode, gal_id, 1);
    }
}

void link_wave_sub(int mode, int gal_id, int from)
{
    v_dist_id.clear();
    //std::cout << "Link_wave_check start " << gal_id << "    " << from << "    " << start_star << "    " << wave.size() << std::endl;
    //std::cout << v_galaxy_generation[gal_id].i_star << "    " << start_star + v_galaxy_generation[gal_id].i_star << std::endl;
    int current_wave = wave.size();
    for (int i = from; i < current_wave; i++)
    {
        //std::cout << i << "    " << wave[i].id << std::endl;
        int a = 0;
        //std::cout << v_galaxy_generation[current_gal_id].i_max_hyp_dis << " ----------------- "  << std::endl;
        //std::cout << v_system_data[wave[i].id].gal_id << std::endl;
        for (int j = 0; j < v_galaxy_generation[gal_id].i_star; j++)
        {
            if ((v_system_data[gal_id][wave[i].id].blocked == false) && (v_system_data[gal_id][j].blocked == false))
            {
                if ((v_system_data[gal_id][wave[i].id].gal_x - v_system_data[gal_id][j].gal_x < v_galaxy_generation[gal_id].i_max_hyp_dis) && (v_system_data[gal_id][wave[i].id].gal_x - v_system_data[gal_id][j].gal_x > -v_galaxy_generation[gal_id].i_max_hyp_dis) && (v_system_data[gal_id][wave[i].id].gal_x - v_system_data[gal_id][j].gal_x != 0))
                {
                    if ((v_system_data[gal_id][wave[i].id].gal_y - v_system_data[gal_id][j].gal_y < v_galaxy_generation[gal_id].i_max_hyp_dis) && (v_system_data[gal_id][wave[i].id].gal_y - v_system_data[gal_id][j].gal_y > -v_galaxy_generation[gal_id].i_max_hyp_dis) && (v_system_data[gal_id][wave[i].id].gal_y - v_system_data[gal_id][j].gal_y != 0))
                    {
                        if (v_system_data[gal_id][j].con < v_system_data[gal_id][j].con_max)
                        {
                            int t_dist = sqrt(pow(v_system_data[gal_id][j].gal_x - v_system_data[gal_id][wave[i].id].gal_x, 2) + pow(v_system_data[gal_id][j].gal_y - v_system_data[gal_id][wave[i].id].gal_y, 2));
                            v_dist_id.emplace_back();
                            v_dist_id[a].distance = t_dist;
                            v_dist_id[a].from = v_system_data[gal_id][wave[i].id].gal_id;
                            v_dist_id[a].to = v_system_data[gal_id][j].gal_id;
                            a++;
                        }
                    }
                }
            }
        }
        if (v_system_data[gal_id][wave[i].id].con == 0)
        {
            for (int j = 0; j < v_galaxy_generation[gal_id].i_star; j++)
            {
                if ((v_system_data[gal_id][wave[i].id].blocked == false) && (v_system_data[gal_id][j].blocked == false))
                {
                    if ((v_system_data[gal_id][wave[i].id].gal_x - v_system_data[gal_id][j].gal_x < v_galaxy_generation[gal_id].i_max_hyp_dis) && (v_system_data[gal_id][wave[i].id].gal_x - v_system_data[gal_id][j].gal_x > -v_galaxy_generation[gal_id].i_max_hyp_dis) && (v_system_data[gal_id][wave[i].id].gal_x - v_system_data[gal_id][j].gal_x != 0))
                    {
                        if ((v_system_data[gal_id][wave[i].id].gal_y - v_system_data[gal_id][j].gal_y < v_galaxy_generation[gal_id].i_max_hyp_dis) && (v_system_data[gal_id][wave[i].id].gal_y - v_system_data[gal_id][j].gal_y > -v_galaxy_generation[gal_id].i_max_hyp_dis) && (v_system_data[gal_id][wave[i].id].gal_y - v_system_data[gal_id][j].gal_y != 0))
                        {
                            if (v_system_data[gal_id][j].con < v_system_data[gal_id][j].con_max)
                            {
                                int t_dist = sqrt(pow(v_system_data[gal_id][j].gal_x - v_system_data[gal_id][wave[i].id].gal_x, 2) + pow(v_system_data[gal_id][j].gal_y - v_system_data[gal_id][wave[i].id].gal_y, 2));
                                v_dist_id.emplace_back();
                                v_dist_id[a].distance = t_dist;
                                v_dist_id[a].from = v_system_data[gal_id][wave[i].id].gal_id;
                                v_dist_id[a].to = v_system_data[gal_id][j].gal_id;
                                a++;
                            }
                        }
                    }
                }
            }
        }
        std::sort(v_dist_id.begin(), v_dist_id.end(), less_than_key());
        if (mode == 1)
        {
            if (v_dist_id.size() > v_system_data[gal_id][wave[i].id].con_max)
            {
                v_dist_id.erase(v_dist_id.begin() + rand() % v_system_data[gal_id][wave[i].id].con_max);
            }
        }
        //std::cout << " Now save " << std::endl;
        link_wave_save(mode, gal_id, wave[i].id);
        v_dist_id.clear();
    }
    if (wave.size() != current_wave)
    {
        //std::cout << " Now repeat " << std::endl;
        v_dist_id.clear();
        link_wave_sub(mode, gal_id, current_wave);
    }
}

int link_wave_check(int mode, int gal_id, int mult, int i)
{
    v_dist_id.clear();
    //std::cout << "Link_wave_check start " << gal_id << "    " << from << "    " << start_star << std::endl;
    //std::cout << v_galaxy_generation[current_gal_id].i_max_hyp_dis << " ----------------- "  << std::endl;
    //std::cout << v_system_data[wave[i].id].gal_id << std::endl;
    bool found = false;
    int a = 0;
    for (int j = 0; j < v_galaxy_generation[gal_id].i_star; j++)
    {
        if ((v_system_data[gal_id][i].gal_x - v_system_data[gal_id][j].gal_x < v_galaxy_generation[gal_id].i_max_hyp_dis * mult) && (v_system_data[gal_id][i].gal_x - v_system_data[gal_id][j].gal_x > -v_galaxy_generation[gal_id].i_max_hyp_dis * mult) && (v_system_data[gal_id][i].gal_x - v_system_data[gal_id][j].gal_x != 0))
        {
            if ((v_system_data[gal_id][i].gal_y - v_system_data[gal_id][j].gal_y < v_galaxy_generation[gal_id].i_max_hyp_dis * mult) && (v_system_data[gal_id][i].gal_y - v_system_data[gal_id][j].gal_y > -v_galaxy_generation[gal_id].i_max_hyp_dis * mult) && (v_system_data[gal_id][i].gal_y - v_system_data[gal_id][j].gal_y != 0))
            {
                if (v_system_data[gal_id][j].blocked == true)
                {
                    int t_dist = sqrt(pow(v_system_data[gal_id][j].gal_x - v_system_data[gal_id][i].gal_x, 2) + pow(v_system_data[gal_id][j].gal_y - v_system_data[gal_id][i].gal_y, 2));
                    v_dist_id.emplace_back();
                    v_dist_id[a].distance = t_dist;
                    v_dist_id[a].from = v_system_data[gal_id][i].gal_id;
                    v_dist_id[a].to = v_system_data[gal_id][j].gal_id;
                    found = true;
                    a++;
                }
            }
        }
    }
    std::sort(v_dist_id.begin(), v_dist_id.end(), less_than_key());
    if (mode == 1)
    {
        if (v_dist_id.size() > v_system_data[gal_id][i].con_max)
        {
            if (v_dist_id.size() > 1)
            {
                v_dist_id.erase(v_dist_id.begin() + rand() % v_system_data[gal_id][i].con_max);
            }
        }
    }
    else
    {
        if (v_dist_id.size() > 1)
        {
            v_dist_id.erase(v_dist_id.begin() + 1, v_dist_id.begin() + v_dist_id.size());
        }
    }
    if (found == true)
    {
        //std::cout << "Found " << std::endl;
        link_wave_save(mode, gal_id, i);
        clear_hyperlanes_data();
        v_system_data[gal_id][i].blocked = true;
        link_wave(mode, gal_id, i);
        return 1;
    }
    else
    {
        return 0;
    }
}

void link_wave_save(int mode, int gal_id, int i)
{
    if (v_dist_id.size() > 0)
    {
        if (v_system_data[gal_id][i].con_max < v_dist_id.size())
        {
            int z = 0;
            while (v_system_data[gal_id][i].con <= v_system_data[gal_id][i].con_max)
            {
                int t_dist = sqrt(pow(v_system_data[gal_id][i].gal_x - v_system_data[gal_id][v_dist_id[z].to].gal_x, 2) + pow(v_system_data[gal_id][i].gal_y - v_system_data[gal_id][v_dist_id[z].to].gal_y, 2));
                if (t_dist > 50)
                {
                    std::cout << "Distance is above 100!" << std::endl;
                }
                    hyperlanes pushing;
                    pushing.from = i;
                    pushing.to = v_dist_id[z].to;
                    v_hyperlanes[gal_id].push_back(pushing);

                    s_wave wave_push;
                    wave_push.id = v_dist_id[z].to;
                    wave.push_back(wave_push);

                    v_system_data[gal_id][i].con++;
                    v_system_data[gal_id][v_dist_id[z].to].con++;

                    if (v_system_data[gal_id][v_dist_id[z].to].con >= v_system_data[gal_id][v_dist_id[z].to].con_max)
                    {
                        v_system_data[gal_id][v_dist_id[z].to].blocked = true;
                    }

                    mult++;
                    z++;
                //std::cout << "Error " << z << std::endl;
            }
        }
        else
        {
            for (int z = 0; z < v_dist_id.size(); z++)
            {
                int t_dist = sqrt(pow(v_system_data[gal_id][i].gal_x - v_system_data[gal_id][v_dist_id[z].to].gal_x, 2) + pow(v_system_data[gal_id][i].gal_y - v_system_data[gal_id][v_dist_id[z].to].gal_y, 2));
                if (t_dist > 50)
                {
                    std::cout << "Distance is above 100!" << std::endl;
                }
                    hyperlanes pushing;
                    pushing.from = i;
                    pushing.to = v_dist_id[z].to;
                    v_hyperlanes[gal_id].push_back(pushing);

                    s_wave wave_push;
                    wave_push.id = v_dist_id[z].to;
                    wave.push_back(wave_push);

                    v_system_data[gal_id][i].con++;
                    v_system_data[gal_id][v_dist_id[z].to].con++;

                    if (v_system_data[gal_id][v_dist_id[z].to].con >= v_system_data[gal_id][v_dist_id[z].to].con_max)
                    {
                        v_system_data[gal_id][v_dist_id[z].to].blocked = true;
                    }

                    mult++;
            }
        }
        v_system_data[gal_id][i].blocked = true;
    }
}

void check_systems(int mode, int gal_id)
{
    //std::cout << "Check systems for " << this_gal_id << std::endl;
    int check = 0;
    for (int j = 0; j < v_galaxy_generation[gal_id].i_star; j++)
    {
        if (v_system_data[gal_id][j].con == 0)
        {
            //std::cout << "1 System nuber " << j << std::endl;
                clear_hyperlanes_data();
                check = link_wave_check(mode, gal_id, 1, j);
                if (check == 1)
                {
                    j = 0;
                }
            //std::cout << v_system_data[j].con << "   " << v_system_data[j].con_max << std::endl;
            //std::cout << j << std::endl;
        }
    }
    for (int j = 0; j < v_galaxy_generation[gal_id].i_star; j++)
    {
        if (v_system_data[gal_id][j].con == 0)
        {
            //std::cout << "1 System nuber " << j << std::endl;
            clear_hyperlanes_data();
            check = link_wave_check(mode, gal_id, 2, j);
            if (check == 1)
            {
                j = 0;
            }
            //std::cout << v_system_data[j].con << "   " << v_system_data[j].con_max << std::endl;
            //std::cout << j << std::endl;
        }
    }
}

void clear_hyperlanes_data()
{
    wave.clear();
    v_dist_id.clear();
}
// Initilizers
/*
Iteracja pêtli przez galaktyki
Do ka¿dej sprawdŸ ile ma gwiazd i jaka jest jej wielkosc
Wydziel ile imperiow, fallenow i maruderow ma w niej byc
*/
void void_dens()
{
    for (int i = 0; i < v_galaxy_generation.size(); i++)
    {
        // 200 / 200 = 15 EmpireD = 60, FallenD = 220, MaruderD = 350
        float a = v_galaxy_generation[i].i_star, b = v_galaxy_generation[i].i_gsize;
            v_galaxy_generation[i].density = b / a;
    }
}


void c_init::initilizers()
{
    int starsum = 0;
    for (int i = 0; i < v_galaxy_generation.size(); i++)
    {
        starsum += v_galaxy_generation[i].i_star;
    }
    //Wyznaczanie iloœci imperiów
    if (Empires_Random == true)
    {
        empire_am = rand() % (starsum / 30) + (starsum / 50);
        if (starsum > 300)
        {
            fallen_am = rand() % (starsum / 300) + (starsum / 300);
        }
        else
        {
            fallen_am = 2;
        }

        if (starsum > 350)
        {
            maruder_am = rand() % (starsum / 350) + (starsum / 350);
        }
        else
        {
            maruder_am = 1;
        }
    }
    if (fallen_am > 3)
    {
        fallen_am = 3;
    }
    for (int i = 0; i < v_galaxy_generation.size(); i++)
    {
        // 200 / 200 = 15 EmpireD = 60, FallenD = 220, MaruderD = 350
        float a = v_galaxy_generation[i].i_star, c = starsum,
            perc_star = a / c;
        int gal_empire_am = round(empire_am * perc_star),
            gal_fallen_am = round(fallen_am * perc_star),
            gal_mega_am = round(starsum / 250 * perc_star),
            gal_marauder_am = round(starsum / 350 * perc_star),
            gal_leviathan_am = 0;
        if (generate_multiple_leviathans == true)
        {
            gal_leviathan_am = round(starsum / 150 * perc_star);
        }
        else
        {
            gal_leviathan_am = round(8 * perc_star);
        }

        if (starsum > 1500)
        {
            gal_mega_am = round(((starsum/750) * 4) * perc_star);
        }
        dist = v_galaxy_generation[i].density * 40;
        fallen_dist = v_galaxy_generation[i].density * 100;
        leviathan_dist = v_galaxy_generation[i].density * 75;
        marauder_dist = v_galaxy_generation[i].density * 120;
        if (dist < 30)
        {
            dist = 30;
        }
        if (fallen_dist < 100)
        {
            fallen_dist = 100;
        }
        if (leviathan_dist < 75)
        {
            leviathan_dist = 75;
        }
        if (marauder_dist < 120)
        {
            marauder_dist = 120;
        }
        if (i > 0)
        {
            prev_star_sum += v_galaxy_generation[i - 1].i_star;
        }

        // Empire Generation
        everything_filled = false;
        for (int f = 0; f < gal_empire_am; f++)
        {
            placed = true;
            min_together(i);
            if (everything_filled == true)
            {
                break;
            }
            if (placed == false)
            {
                if (v_system_data[i][random_sys].init_type == 0)
                {
                    v_system_data[i][random_sys].inicjalizer = true;
                    f--;
                }
                else
                {
                    f--;
                }
            }
            else
            {
                int temp = rand() % 6;
                v_system_data[i][random_sys].inicjalizer = true;
                v_system_data[i][random_sys].init_type = 1;
                v_system_data[i][random_sys].init_number = temp;
            }
        }
        // Fallen Generation
        everything_filled = false;
        for (int f = 0; f < gal_fallen_am; f++)
        {
            placed = true, specific_init = true;
            min_together(i);
            if (everything_filled == true)
            {
                break;
            }
            if (placed == true)
            {
                c_init::min_dist_specific(i , fallen_dist, 2);
                if (specific_init == true)
                {
                    if (v_system_data[i][random_sys].init_type == 0)
                    {
                        v_system_data[i][random_sys].inicjalizer = true;
                        v_system_data[i][random_sys].init_type = 2;
                        int temp = rand() % 3, limit = 0;
                        if (C_fallen.exist[temp] == true)
                        {
                            while (C_fallen.exist[temp] == true)
                            {
                                temp = rand() % 3;
                                limit++;
                                if (limit > 1000)
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            v_system_data[i][random_sys].init_number = temp;
                        }
                        C_fallen.exist[temp] = true;
                    }
                }
            }
            else
            {
                if (v_system_data[i][random_sys].init_type == 0)
                {
                    v_system_data[i][random_sys].inicjalizer = true;
                    f--;
                }
                else
                {
                    f--;
                }
            }
        }
        // Leviathan Generation
        everything_filled = false;
        for (int f = 0; f < gal_leviathan_am; f++)
        {
            placed = true, specific_init = true;
            min_together(i);
            if (everything_filled == true)
            {
                break;
            }
            if (placed == true)
            {
                c_init::min_dist_specific(i, fallen_dist, 3);
                if (specific_init == true)
                {
                    if (v_system_data[i][random_sys].init_type == 0)
                    {
                        int temp = rand() % 8;
                        int limit = 0;
                        bool generate = true;
                        
                        while (Class_lev.exist[temp] == true)
                        {
                            //std::cout << "While 2 loop " << i << std::endl;
                            temp = rand() % 8;
                            limit++;
                            if ((limit > 1000) && (generate_multiple_leviathans == false))
                            {
                                generate = false;
                                break;
                            }
                            else if (limit > 1000)
                            {
                                break;
                            }
                        }
                        if (generate == true)
                        {
                            v_system_data[i][random_sys].inicjalizer = true;
                            v_system_data[i][random_sys].init_type = 3;
                            v_system_data[i][random_sys].init_number = temp;
                            Class_lev.exist[temp] = true;
                        }
                    }
                }
            }
            else
            {
                if (v_system_data[i][random_sys].init_type == 0)
                {
                    v_system_data[i][random_sys].inicjalizer = true;
                    f--;
                }
                else {
                    f--;
                }
            }
        }
        // Mega Generation
        for (int f = 0; f < gal_mega_am; f++)
        {
            random_sys = rand() % v_galaxy_generation[i].i_star;
            if (v_system_data[i][random_sys].init_type == 0)
            {
                int temp = rand() % 4;
                v_system_data[i][random_sys].inicjalizer = true;
                v_system_data[i][random_sys].init_type = 4;
                v_system_data[i][random_sys].init_number = temp;
            }
        }

        // Marauder Generation
        everything_filled = false;
        for (int f = 0; f < gal_marauder_am; f++)
        {
            placed = true, specific_init = true;
            min_together(i);
            if (everything_filled == true)
            {
                break;
            }
            if (placed == true)
            {
                c_init::min_dist_specific(i, fallen_dist, 5);
                if (specific_init == true)
                {
                    if (v_system_data[i][random_sys].init_type == 0)
                    {
                        int temp = rand() % 3;
                        v_system_data[i][random_sys].inicjalizer = true;
                        v_system_data[i][random_sys].init_type = 5;
                        v_system_data[i][random_sys].init_number = temp;
                    }
                }
            }
            else
            {
                if (v_system_data[i][random_sys].init_type == 0)
                {
                    v_system_data[i][random_sys].inicjalizer = true;
                    f--;
                }
                else
                {
                    f--;
                }
            }
        }

        //Ulamek upadlych na galaktyke
        //Przydzielic upadle wstepnie
    }
    prev_star_sum = 0;
}

void c_init::min_together(int gal_id)
{
    int limit = 0;
    random_sys = rand() % v_galaxy_generation[gal_id].i_star;
    while (v_system_data[gal_id][random_sys].inicjalizer == true)
    {
        random_sys = rand() % v_galaxy_generation[gal_id].i_star;
        if (limit > 10000)
        {
            for (int j = 0; j < v_galaxy_generation[gal_id].i_star; j++)
            {
                if (v_system_data[gal_id][j].inicjalizer == false)
                {
                    random_sys = v_system_data[gal_id][j].gal_id;
                }
                else
                {
                    everything_filled = true;
                }
            }
        }
        limit++;
    }
    c_init::min_dist(gal_id);
}


void c_init::min_dist(int gal_id)
{
    bool end = false;
    while ((placed == true) && (end == false))
    {
        for (int j = 0; j < v_galaxy_generation[gal_id].i_star; j++)
        {
            if (j != random_sys)
            {
                if (sqrt(pow(v_system_data[gal_id][random_sys].gal_x - v_system_data[gal_id][j].gal_x, 2)) + (pow(v_system_data[gal_id][random_sys].gal_y - v_system_data[gal_id][j].gal_y, 2)) < dist)
                {
                    if (v_system_data[gal_id][j].inicjalizer == true)
                    {
                        placed = false;
                        break;
                    }
                }
            }
            if (j == v_galaxy_generation[gal_id].i_star - 1)
                end = true;
        }
    }
}

void c_init::min_dist_specific(int gal_id, int min_distance, int init_id)
{
    bool end = false;
    while ((specific_init == true) && (end == false))
    {
        for (int j = 0; j < v_galaxy_generation[gal_id].i_star; j++)
        {
            if ((sqrt(pow(v_system_data[gal_id][random_sys].gal_x - v_system_data[gal_id][j].gal_x, 2)) + (pow(v_system_data[gal_id][random_sys].gal_y - v_system_data[gal_id][j].gal_y, 2) < min_distance)))
            {
                if (v_system_data[gal_id][j].inicjalizer == true)
                {
                    if (v_system_data[gal_id][j].init_type == init_id)
                    {
                        specific_init = false;
                        break;
                    }
                }
            }
            if (j == v_galaxy_generation[gal_id].i_star - 1)
                end = true;
        }
    }
}

void random_generator()
{
    int Chance = rand() % 3;
    if (!CRS.enable_circle)
    {
        int Chance = rand() % 3 + 1;
    }
    if (!CRS.enable_spiral)
    {
        int Chance = 0;
    }
    int R_size = rand() % (CRS.size_to - CRS.size_from) + CRS.size_from,
        R_center_x = rand() % (1000 - (R_size * 2)) - (500 - R_size),
        R_center_y = rand() % (1000 - (R_size * 2)) - (500 - R_size),
        R_star_amount = 0;
    int limit = 0;
    bool generate = true;
    while ((R_center_x - R_size < -500) || (R_center_x + R_size > 500) || (R_center_y - R_size < -500) || (R_center_y + R_size > 500))
    {
        R_size = rand() % (CRS.size_to - CRS.size_from) + CRS.size_from;
        R_center_x = rand() % (1000 - (R_size * 2)) - (500 - R_size);
        R_center_y = rand() % (1000 - (R_size * 2)) - (500 - R_size);
    }
    int j = 0, min = 100, start_size = R_size;
    while (j < v_galaxy_generation.size())
    {
        while ((sqrt(
            pow(R_center_x - v_galaxy_generation[j].i_cen_posX, 2) +
            pow(R_center_y - v_galaxy_generation[j].i_cen_posY, 2)
        ) <= v_galaxy_generation[j].i_gsize + R_size + min))
        {
            if ((CRS.enable_resizing) && ((CRS.size_from - limit /5) > CRS.size_from / 5))
            {
                R_size = rand() % (CRS.size_to - CRS.size_from) + CRS.size_from - limit / 5;
            }
            else
            {
                R_size = rand() % (CRS.size_to - CRS.size_from) + CRS.size_from;
            }
            R_center_x = rand() % (1000 - (R_size * 2)) - (500 - R_size);
            R_center_y = rand() % (1000 - (R_size * 2)) - (500 - R_size);
            limit++;
            if (limit > 2000)
            {
                generate = false;
                no_space_found = true;
                rerender();
                no_space_found = false;
                rerender();
                break;
            }
            if (min > 25)
            {
                min--;
            }
            j = 0;
        }
        if (limit > 2000)
        {
            limit = 0;
            generate = false;
            break;
        }
        else
        {
            j++;
        }
    }
    //std::cout << R_size << " " << R_center_x << " " << R_center_y << " " << CRS.size_from << " " << (CRS.size_to - CRS.size_from) <<std::endl;
    if (generate == true)
    {
        //std::cout << "Generate = true  " << v_galaxy_generation.size() << std::endl;
        if ((Chance == 0) && (CRS.enable_circle))
        {
            v_galaxy_generation.emplace_back();
            //std::cout << "Circle Entered" << std::endl;
            float temp_star_am, temp_size;
            temp_star_am = (R_size * (rand() % (CRS.circle_stars_to - CRS.circle_stars_from) + CRS.circle_stars_from) / 10);
            temp_size = R_size;
            int R_max_hyperlane_distance = (rand() % (CRS.hyperlanes_max_length_to - CRS.hyperlanes_max_length_from) + CRS.hyperlanes_max_length_from) * (temp_size / temp_star_am);
            int R_star_amount = round(temp_star_am);
            current_gal_id = galaxies_am;
            v_galaxy_generation[galaxies_am].galtype = 0;
            v_galaxy_generation[galaxies_am].star = std::to_string(R_star_amount);
            v_galaxy_generation[galaxies_am].gsize = std::to_string(R_size);
            v_galaxy_generation[galaxies_am].cen_posX = std::to_string(R_center_x);
            v_galaxy_generation[galaxies_am].cen_posY = std::to_string(R_center_y);
            v_galaxy_generation[galaxies_am].max_hyp_dis = std::to_string(R_max_hyperlane_distance);

            v_galaxy_generation[current_gal_id].i_star = std::stoi(v_galaxy_generation[current_gal_id].star);
            v_galaxy_generation[current_gal_id].i_gsize = std::stoi(v_galaxy_generation[current_gal_id].gsize);
            v_galaxy_generation[current_gal_id].i_cen_posX = std::stoi(v_galaxy_generation[current_gal_id].cen_posX);
            v_galaxy_generation[current_gal_id].i_cen_posY = std::stoi(v_galaxy_generation[current_gal_id].cen_posY);
            v_galaxy_generation[current_gal_id].i_max_hyp_dis = std::stoi(v_galaxy_generation[current_gal_id].max_hyp_dis);
            generate_elipse(current_gal_id);
            rerender();
            draw_galaxy();
            galaxies_am++;
        }
        else if ((Chance > 0) && (CRS.enable_spiral))
        {
            v_galaxy_generation.emplace_back();
            //std::cout << "Spiral gen entered" << std::endl;
            std::random_device rd;
            std::default_random_engine eng(rd());
            std::uniform_real_distribution<> distr((CRS.arm_max_width_to - CRS.arm_max_width_from), CRS.arm_max_width_from);
            std::uniform_real_distribution<> random((CRS.arm_random_width_to - CRS.arm_random_width_from), CRS.arm_random_width_from);
            int R_numArms = rand() % (CRS.arm_amount_to - CRS.arm_amount_from) + CRS.arm_amount_from,
                R_rotationFactor = rand() % (CRS.rotation_factor * 2) - CRS.rotation_factor;
            float R_armOffsetMax = distr(eng),
                R_randomOffsetXY = random(eng);
            while(R_rotationFactor == 0)
            {
                int local_chance = rand() % 10;
                if (local_chance > 0)
                {
                    R_rotationFactor = rand() % 12 - 6;
                }
                else
                {
                    break;
                }
            }
            float temp_star_am, temp_size;
            temp_star_am = (((pow(R_size, CRS.size_ratio) * (rand() % (CRS.spiral_stars_to - CRS.spiral_stars_from) + CRS.spiral_stars_from)) / 10.0) / 1000.0);
            temp_size = R_size;
            R_star_amount = ((temp_star_am * (rand() % 50 + 350)) * (pow(R_armOffsetMax, CRS.arm_width_ratio)) *(pow(R_numArms, CRS.arm_ratio)));
            int R_max_hyperlane_distance = (rand() % (CRS.hyperlanes_max_length_to - CRS.hyperlanes_max_length_from) + CRS.hyperlanes_max_length_from) * (temp_size / R_star_amount);
            current_gal_id = galaxies_am;
            //std::cout << CRS.arm_random_width_to << " " << CRS.arm_random_width_from << " " << R_star_amount << " " << R_size << " " << R_center_x << " " << R_center_y << " " << R_max_hyperlane_distance << " " << R_numArms << " " << R_rotationFactor << " " << R_armOffsetMax << " " << R_randomOffsetXY << " " << std::endl;
            v_galaxy_generation[galaxies_am].galtype = 1;
            v_galaxy_generation[galaxies_am].star = std::to_string(R_star_amount);
            v_galaxy_generation[galaxies_am].gsize = std::to_string(R_size);
            v_galaxy_generation[galaxies_am].cen_posX = std::to_string(R_center_x);
            v_galaxy_generation[galaxies_am].cen_posY = std::to_string(R_center_y);
            v_galaxy_generation[galaxies_am].max_hyp_dis = std::to_string(R_max_hyperlane_distance);
            v_galaxy_generation[galaxies_am].numArms = std::to_string(R_numArms);
            v_galaxy_generation[galaxies_am].rotationFactor = std::to_string(R_rotationFactor);
            v_galaxy_generation[galaxies_am].armOffsetMax = std::to_string(R_armOffsetMax);
            v_galaxy_generation[galaxies_am].randomOffsetXY = std::to_string(R_randomOffsetXY);

            v_galaxy_generation[current_gal_id].i_star = std::stoi(v_galaxy_generation[current_gal_id].star);
            v_galaxy_generation[current_gal_id].i_gsize = std::stoi(v_galaxy_generation[current_gal_id].gsize);
            v_galaxy_generation[current_gal_id].i_cen_posX = std::stoi(v_galaxy_generation[current_gal_id].cen_posX);
            v_galaxy_generation[current_gal_id].i_cen_posY = std::stoi(v_galaxy_generation[current_gal_id].cen_posY);
            v_galaxy_generation[current_gal_id].i_max_hyp_dis = std::stoi(v_galaxy_generation[current_gal_id].max_hyp_dis);
            v_galaxy_generation[current_gal_id].i_numArms = std::stoi(v_galaxy_generation[current_gal_id].numArms);
            v_galaxy_generation[current_gal_id].f_armOffsetMax = std::stof(v_galaxy_generation[current_gal_id].armOffsetMax);
            v_galaxy_generation[current_gal_id].f_randomOffsetXY = std::stof(v_galaxy_generation[current_gal_id].randomOffsetXY);
            v_galaxy_generation[current_gal_id].f_rotationFactor = std::stof(v_galaxy_generation[current_gal_id].rotationFactor);
            generate_spiral(current_gal_id);
            rerender();
            draw_galaxy();
            galaxies_am++;
        }
    }
}