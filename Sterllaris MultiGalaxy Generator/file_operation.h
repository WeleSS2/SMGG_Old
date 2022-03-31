#pragma once


void osfile(std::string path)
{
    std::ofstream file(path);
    if (file.is_open())
    {
        file << "static_galaxy_scenario = { \n";
        file << "name = \"MultiGalaxy\" \n";
        file << "priority = 10 \n";
        file << "radius = 500 \n";
        file << "num_empires = { min = " + std::to_string(empire_am/2) + " max = " + std::to_string(empire_am) + " } \n";
        file << "num_empire_default = " + std::to_string(empire_am) + " \n";
        file << "fallen_empire_default = " + std::to_string(fallen_am) + " \n";
        file << "fallen_empire_max = " + std::to_string(fallen_am) + " \n";
        file << "marauder_empire_default = " + std::to_string(maruder_am) + " \n";
        file << "marauder_empire_max = " + std::to_string(maruder_am) + " \n";
        file << "advanced_empire_default = 1 \n";
        file << "colonizable_planet_odds = 1.0 \n";
        file << "primitive_odds = 1.0 \n";
        file << "crisis_strength = 0.75 \n";
        file << "extra_crisis_strength = { 5.5 6 6.5 7 7.5 8 8.5 9 9.5 10 11 12 13 14 15 17.5 20 22.5 25 30 35 40 45 50} \n";

        file << "num_wormhole_pairs = { min = 0 max = 10 } \n";
        file << "num_wormhole_pairs_default = 1 \n";
        file << "num_gateways = { min = 0 max = 10 } \n";
        file << "num_gateways_default = 1 \n";

        file << "random_hyperlanes = ";
        if ((setting_hyperlanes == true) || (hyperlanes_loaded == true))
        {
            file << "no \n";
        }
        else
        {
            file << "yes \n";
        }
        file << "core_radius = 0 \n";
        //std::cout << initializers_loaded << "  " << hyperlanes_loaded << std::endl;
        if (initializers_loaded == false)
        {
            int id = 0;
            std::cout << v_system_data.size() << std::endl;
            for (int i = 0; i < v_system_data.size(); i++)
            {
                int random_gal = rand() % v_system_data.size();
                while (v_galaxy_generation[random_gal].exported)
                {
                    random_gal = rand() % v_system_data.size();
                }
                v_galaxy_generation[random_gal].exported = true;
                //std::cout << v_system_data[random_gal].size() << std::endl;
                for (int j = 0; j < v_system_data[random_gal].size(); j++)
                {
                    //std::cout << j << std::endl;
                    int export_local = rand() % v_system_data[random_gal].size();
                    //std::cout << export_local << "   " << v_system_data[random_gal][export_local].exported << std::endl;
                    while (v_system_data[random_gal][export_local].exported == true)
                    {
                        //std::cout << export_local << std::endl;
                        export_local = rand() % v_system_data[random_gal].size();
                        //std::cout << "While 1 loop " << i << std::endl;
                    }
                    int x;

                    //std::cout << j << "-----"  << std::endl;
                    if (v_system_data[random_gal][export_local].gal_x > 0)
                    {
                        x = -v_system_data[random_gal][export_local].gal_x;
                    }
                    else
                    {
                        x = abs(v_system_data[random_gal][export_local].gal_x);
                    }
                    //std::cout << v_system_data[random_gal][export_local].gal_id + id << " " << x << " " << v_system_data[random_gal][export_local].gal_y << std::endl;
                    file << "system = { id = \""
                        << v_system_data[random_gal][export_local].gal_id + id
                        << "\" name = \"\" position = { x = "
                        << x
                        << " y = "
                        << v_system_data[random_gal][export_local].gal_y
                        << " } ";

                    switch (v_system_data[random_gal][export_local].init_type)
                    {
                    case 0:
                        break;
                    case 1:
                        file << "initializer = " << empire_init_tab[v_system_data[random_gal][export_local].init_number] << " spawn_weight = { base = 1 }";
                        break;
                    case 2:
                        file << "initializer = " << C_fallen.fallen_empire_init_tab[v_system_data[random_gal][export_local].init_number];
                        break;
                    case 3:
                        file << "initializer = " << Class_lev.name[v_system_data[random_gal][export_local].init_number];
                        break;
                    case 4:
                        file << "initializer = " << mega_ruined_init_tab[v_system_data[random_gal][export_local].init_number];
                        break;
                    case 5:
                        file << "initializer = " << marauder_init_tab[v_system_data[random_gal][export_local].init_number];
                        break;
                    case 99:
                        file << "initializer = smgg_central_black_hole";
                        break;
                    }
                    file << " }\n";
                    v_system_data[random_gal][export_local].exported = true;

                }
                if (setting_hyperlanes == true)
                {
                    for (int i = 0; i < v_hyperlanes[random_gal].size(); i++)
                    {
                        //std::cout << "For 2 loop " << i << std::endl;
                        file << "add_hyperlane = { from = \"" + std::to_string(v_hyperlanes[random_gal][i].from + id) + "\" to = \"" + std::to_string(v_hyperlanes[random_gal][i].to + id) + "\" }" << std::endl;
                    }
                }
                id += v_system_data[random_gal].size();
            }
        }
        else
        {
            for (int i = 0; i < v_system_data_copy.size(); i++)
            {
                int export_local = i;
                int x;

                if (v_system_data_copy[export_local].gal_x > 0)
                {
                    x = -v_system_data_copy[export_local].gal_x;
                }
                else
                {
                    x = abs(v_system_data_copy[export_local].gal_x);
                }

                file << "system = { id = \""
                    << v_system_data_copy[export_local].gal_id
                    << "\" name = \"\" position = { x = "
                    << x
                    << " y = "
                    << v_system_data_copy[export_local].gal_y
                    << " } ";
                switch (v_system_data_copy[export_local].init_type)
                {
                case 0:
                    break;
                case 1:
                    file << "initializer = " << empire_init_tab[v_system_data_copy[export_local].init_number] << " spawn_weight = { base = 1 }";
                    break;
                case 2:
                    file << "initializer = " << C_fallen.fallen_empire_init_tab[v_system_data_copy[export_local].init_number];
                    break;
                case 3:
                    file << "initializer = " << Class_lev.name[v_system_data_copy[export_local].init_number];
                    break;
                case 4:
                    file << "initializer = " << mega_ruined_init_tab[v_system_data_copy[export_local].init_number];
                    break;
                case 5:
                    file << "initializer = " << marauder_init_tab[v_system_data_copy[export_local].init_number];
                    break;
                case 99:
                    file << "initializer = smgg_central_black_hole";
                    break;
                }
                file << " }\n";
            }
        }
        file << "} \n";
        file.close();
    }
    for (int i = 0; i < v_system_data.size(); i++)
    {
        for (int j = 0; j < v_system_data[i].size(); j++)
        {
            v_system_data[i][j].exported = false;
        }
    }
}

PWSTR LoadFile() {
    IFileOpenDialog* pFileOpen;
    PWSTR pszFilePath = NULL;
    // Create the FileOpenDialog object.
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
        IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
    if (SUCCEEDED(hr))
    {
        //IShellItem *psiDocuments = NULL;
        //hr = SHCreateItemInKnownFolder(FOLDERID_Documents, 0, NULL, IID_PPV_ARGS(&psiDocuments));

        //if (SUCCEEDED(hr)) {
        //	hr = pFileOpen->SetFolder(psiDocuments);
        //	psiDocuments->Release();
        //}
        // Show the Open dialog box.
        hr = pFileOpen->Show(NULL);

        // Get the file name from the dialog box.
        if (SUCCEEDED(hr))
        {
            IShellItem* pItem;
            hr = pFileOpen->GetResult(&pItem);
            if (SUCCEEDED(hr))
            {
                PWSTR pszFilePath;
                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                if (SUCCEEDED(hr))
                {
                    clear_map();


                    std::ifstream file(pszFilePath);
                    file >> initializers_loaded;
                    file >> hyperlanes_loaded;
                    file >> galaxies_am;
                    file >> empire_am;
                    file >> fallen_am;
                    file >> maruder_am;
                    for (int i = 0; i < galaxies_am; i++)
                    {
                        current_gal_id = i;
                        v_galaxy_generation.emplace_back();
                        int gal_type = 0;
                        file >> gal_type;
                        if (gal_type == 0)
                        {
                            file >> v_galaxy_generation[i].star >> v_galaxy_generation[i].gsize
                                >> v_galaxy_generation[i].cen_posX >> v_galaxy_generation[i].cen_posY
                                >> v_galaxy_generation[i].max_hyp_dis;

                            v_galaxy_generation[current_gal_id].i_star = std::stoi(v_galaxy_generation[current_gal_id].star);
                            v_galaxy_generation[current_gal_id].i_gsize = std::stoi(v_galaxy_generation[current_gal_id].gsize);
                            v_galaxy_generation[current_gal_id].i_cen_posX = std::stoi(v_galaxy_generation[current_gal_id].cen_posX);
                            v_galaxy_generation[current_gal_id].i_cen_posY = std::stoi(v_galaxy_generation[current_gal_id].cen_posY);
                            v_galaxy_generation[current_gal_id].i_max_hyp_dis = std::stoi(v_galaxy_generation[current_gal_id].max_hyp_dis);
                        }
                        else
                        {

                            file >> v_galaxy_generation[i].star >> v_galaxy_generation[i].gsize
                                >> v_galaxy_generation[i].cen_posX >> v_galaxy_generation[i].cen_posY
                                >> v_galaxy_generation[i].max_hyp_dis >> v_galaxy_generation[i].numArms
                                >> v_galaxy_generation[i].armOffsetMax >> v_galaxy_generation[i].rotationFactor
                                >> v_galaxy_generation[i].randomOffsetXY;

                            v_galaxy_generation[current_gal_id].i_star = std::stoi(v_galaxy_generation[current_gal_id].star);
                            v_galaxy_generation[current_gal_id].i_gsize = std::stoi(v_galaxy_generation[current_gal_id].gsize);
                            v_galaxy_generation[current_gal_id].i_cen_posX = std::stoi(v_galaxy_generation[current_gal_id].cen_posX);
                            v_galaxy_generation[current_gal_id].i_cen_posY = std::stoi(v_galaxy_generation[current_gal_id].cen_posY);
                            v_galaxy_generation[current_gal_id].i_max_hyp_dis = std::stoi(v_galaxy_generation[current_gal_id].max_hyp_dis);


                            v_galaxy_generation[current_gal_id].i_numArms = std::stoi(v_galaxy_generation[current_gal_id].numArms);
                            v_galaxy_generation[current_gal_id].f_armOffsetMax = std::stof(v_galaxy_generation[current_gal_id].armOffsetMax);
                            v_galaxy_generation[current_gal_id].f_randomOffsetXY = std::stof(v_galaxy_generation[current_gal_id].randomOffsetXY);
                            v_galaxy_generation[current_gal_id].f_rotationFactor = std::stof(v_galaxy_generation[current_gal_id].rotationFactor);
                        }
                        sys_sum += std::stoi(v_galaxy_generation[i].star);
                    }
                    //std::cout << starsum << std::endl;
                    for (int i = 0; i < galaxies_am; i++)
                    {
                        v_system_data.emplace_back();
                        for (int j = 0; j < v_galaxy_generation[i].i_star; j++)
                        {
                            system_data pushing;
                            file >> pushing.gal_id >> pushing.gal_x
                                >> pushing.gal_y >> pushing.con
                                >> pushing.con_max;

                            v_system_data[i].push_back(pushing);

                            if (initializers_loaded == true)
                            {
                                file >> v_system_data[i][j].inicjalizer
                                    >> v_system_data[i][j].init_type >> v_system_data[i][j].init_number;
                            }
                        }
                    }
                    if (hyperlanes_loaded == true)
                    {
                        for (int j = 0; j < galaxies_am; j++)
                        {
                            v_galaxy_generation[j].hyperlanes_generated = true;
                            v_hyperlanes.emplace_back();
                            int amount = 0;
                            file >> amount;
                            for (int i = 0; i < amount; i++)
                            {
                                v_hyperlanes[j].emplace_back();
                                file >> v_hyperlanes[j][i].from >> v_hyperlanes[j][i].to;
                            }
                        }
                    }
                }
            }
        }
        pFileOpen->Release();
    }
    return pszFilePath;
}

PWSTR SaveFile() {
    std::string path = "";
    IFileSaveDialog* pFileSave;

    // Create the FileOpenDialog object.
    HRESULT hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
        IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));
    if (SUCCEEDED(hr))
    {
        // Set default extension
        hr = pFileSave->SetDefaultExtension(L"txt");
        if (SUCCEEDED(hr))
        {
            // Show the Open dialog box.
            hr = pFileSave->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem* pItem;
                hr = pFileSave->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                        //MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
                        char buffer[500];
                        wcstombs(buffer, pszFilePath, 500);
                        path = buffer;


                        std::ofstream file(path);
                        if (file.is_open())
                        {
                            file << initializers_loaded << std::endl;
                            file << hyperlanes_loaded << std::endl;
                            file << v_galaxy_generation.size() << std::endl;
                            file << empire_am << std::endl;
                            file << fallen_am << std::endl;
                            file << maruder_am << std::endl;
                            for (int i = 0; i < v_galaxy_generation.size(); i++)
                            {
                                file << v_galaxy_generation[i].galtype << " " << v_galaxy_generation[i].star
                                    << " " << v_galaxy_generation[i].gsize
                                    << " " << v_galaxy_generation[i].cen_posX << " " << v_galaxy_generation[i].cen_posY
                                    << " " << v_galaxy_generation[i].max_hyp_dis << " " << v_galaxy_generation[i].numArms
                                    << " " << v_galaxy_generation[i].armOffsetMax << " " << v_galaxy_generation[i].rotationFactor
                                    << " " << v_galaxy_generation[i].randomOffsetXY <<  std::endl;
                            }
                            for (int i = 0; i < galaxies_am; i++)
                            {
                                for (int j = 0; j < v_galaxy_generation[i].i_star; j++)
                                {
                                    //std::cout << v_galaxy_generation[i].i_star << "    " << v_system_data[i].size() << std::endl;
                                    int exp = rand() % v_system_data[i].size();
                                    while (v_system_data[i][exp].exported == true)
                                    {
                                        //std::cout << j << "   " << v_system_data[i][exp].exported << "   " << exp << std::endl;
                                        exp = rand() % v_system_data[i].size();
                                    }

                                    file << v_system_data[i][j].gal_id << " " << v_system_data[i][j].gal_x
                                        << " " << v_system_data[i][j].gal_y << " " << v_system_data[i][j].con
                                        << " " << v_system_data[i][j].con_max << " ";
                                    if (initializers_loaded == true)
                                    {
                                        file << v_system_data[i][j].inicjalizer
                                            << " " << v_system_data[i][j].init_type << " " << v_system_data[i][j].init_number;
                                    }
                                    file << std::endl;
                                    v_system_data[i][exp].exported = true;
                                }
                            }
                            if (setting_hyperlanes == true)
                            {
                                for (int j = 0; j < galaxies_am; j++)
                                {
                                    file << v_hyperlanes[j].size() << std::endl;
                                    for (int i = 0; i < v_hyperlanes[j].size(); i++)
                                    {
                                        file << v_hyperlanes[j][i].from << "  " << v_hyperlanes[j][i].to << std::endl;
                                    }
                                }
                            }
                            file.close();
                        }
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pFileSave->Release();
        }
    }
}

void firstrunsettings() {
    gModulatedTexture.setAlpha(255);
    gModulatedTexture.render(250, 410, 1250, 100);
    GE.text_render("You must paste your path to a steamapps folder, after that just press enter to save it", center_width + 260, center_height + 420);
    GE.text_input(260, 460, 100);
    if (pathsaved != 1)
    {
        firstrun_create_directory();
    }
    savepath();
}

void firstrun_create_directory()
{
    namespace fs = std::filesystem;
    fs::create_directory(constpath);
}

void firstrunbackground()
{
    gModulatedTexture.setAlpha(255);
    gModulatedTexture.render(250, 410, 1250, 100);
    gPromptTextTexture.loadFromRenderedText("You must paste your path to a steamapps folder, after that just press enter to save it", SilverTextColor);
    gPromptTextTexture.renderButton(260, 420);
}

void savepath()
{
    char ch1 = '\\';
    char ch2 = '/';
    for (int i = 0; i < pathget.length(); ++i) {
        if (pathget[i] == ch1)
        {
            pathget[i] = ch2;
        }
    }

    std::string pathconst = "/workshop/content/281990/2602794523/map/setup_scenarios/sps_multigalaxy.txt";

    modfolderpath = pathget + pathconst;
    std::string settingspath = constpath + "/settings.txt";

    std::ofstream file(settingspath);
    if (file.is_open())
    {
        file << "1\n";
        file << modfolderpath + "\n";
        file << pathget + "\n";
        file.close();
    }
    pathsaved = true;

    SDL_RenderClear(gRenderer);
    rerender();
    file.close();
}

void SaveSettings()
{
    std::string path = constpath + "/settings_inside.txt";
    std::fstream file(path, std::ios_base::out);

    if (file.is_open())
    {
        if (Empires_Random == true)
        {
            file << "1\n";
        }
        else
        {
            file << "0\n";
        }
        if (savetoagame == true)
        {
            file << "1\n";
        }
        else
        {
            file << "0\n";
        }
        if(disable_failed_galaxy_warn == true)
        {
            file << "1\n";
        }
        else
        {
            file << "0\n";
        }
        if(disable_wrong_text_warn == true)
        {
            file << "1\n";
        }
        else
        {
            file << "0\n";
        }
        if (generate_multiple_leviathans == true)
        {
            file << "1\n";
        }
        else
        {
            file << "0\n";
        }
        if (initializers == true)
        {
            file << "1\n";
        }
        else
        {
            file << "0\n";
        }
        if (setting_hyperlanes == true)
        {
            file << "1\n";
        }
        else
        {
            file << "0\n";
        }
        if (min_hyperlane_am != 0)
        {
            file << std::to_string(min_hyperlane_am) << "\n";
        }
        else
        {
            file << "0\n";
        }
        if (max_hyperlane_am != 0)
        {
            file << std::to_string(max_hyperlane_am) << "\n";
        }
        else
        {
            file << "0\n";
        }
        if (show_hyperlanes != 0)
        {
            file << std::to_string(show_hyperlanes) << "\n";
        }
        else 
        {
            file << "0\n";
        }
    }

    file.close();
}


void loadsettings()
{
    std::string line;
    std::vector<std::string>fromfile;
    std::string path = constpath + "/settings.txt";
    std::ifstream file(path);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            fromfile.push_back(line);
        }
    }
    file.close();

    std::string path2 = constpath + "/settings_inside.txt";
    std::ifstream file2(path2);
    if (file2.is_open())
    {
        while (getline(file2, line))
        {
            fromfile.push_back(line);
        }
    }
    file2.close();

    for (int i = 0; i < fromfile.size(); i++)
    {
        switch (i)
        {
            case 0:
                std::istringstream(fromfile[i]) >> pathsaved;
                break;
            case 1:
                modfolderpath = fromfile[i];
                break;
            case 2:
                pathget = fromfile[i];
                break;
            case 3:
                std::istringstream(fromfile[i]) >> Empires_Random;
                break;
            case 4:
                std::istringstream(fromfile[i]) >> savetoagame;
                break;
            case 5:
                std::istringstream(fromfile[i]) >> disable_failed_galaxy_warn;
                break;
            case 6:
                std::istringstream(fromfile[i]) >> disable_wrong_text_warn;
                break;
            case 7:
                std::istringstream(fromfile[i]) >> generate_multiple_leviathans;
                break;
            case 8:
                std::istringstream(fromfile[i]) >> initializers;
                break;
            case 9:
                std::istringstream(fromfile[i]) >> setting_hyperlanes;
                break;
            case 10:
                std::istringstream(fromfile[i]) >> min_hyperlane_am;
                break;
            case 11:
                std::istringstream(fromfile[i]) >> max_hyperlane_am;
                break;
            case 12:
                std::istringstream(fromfile[i]) >> show_hyperlanes;
                break;
        }
    }
}

void SaveRandomSettings()
{
    std::ofstream file(constpath + "/random.txt");
    if (file.is_open())
    {
        file << CRS.enable_circle << "\n";
        file << CRS.enable_spiral << "\n";
        file << CRS.enable_resizing << "\n";
        file << CRS.size_from << "\n";
        file << CRS.size_to << "\n";
        file << CRS.hyperlanes_max_length_from << "\n";
        file << CRS.hyperlanes_max_length_to << "\n";
        file << CRS.circle_stars_from << "\n";
        file << CRS.circle_stars_to << "\n";
        file << CRS.spiral_stars_from << "\n";
        file << CRS.spiral_stars_to << "\n";
        file << CRS.rotation_factor_from << "\n";
        file << CRS.rotation_factor_to << "\n";
        file << CRS.arm_amount_from << "\n";
        file << CRS.arm_amount_to << "\n";
        file << CRS.square_factor << "\n";
        file << CRS.arm_max_width_from << "\n";
        file << CRS.arm_max_width_to << "\n";
        file << CRS.arm_random_width_from << "\n";
        file << CRS.arm_random_width_to << "\n";
        file << CRS.size_ratio << "\n";
        file << CRS.arm_ratio << "\n";
        file << CRS.arm_width_ratio << "\n";
    }
    file.close();
}

void LoadRandomSettings()
{
    std::string line;
    std::vector<std::string>fromfile;
    std::string path = constpath + "/random.txt";
    std::ifstream file(path);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            fromfile.push_back(line);
        }
    }
    file.close();
    for (int i = 0; i < fromfile.size(); i++)
    {
        switch (i)
        {
        case 0:
            std::istringstream(fromfile[i]) >> CRS.enable_spiral;
            break;
        case 1:
            std::istringstream(fromfile[i]) >> CRS.enable_resizing;
            break;
        case 2:
            std::istringstream(fromfile[i]) >> CRS.size_from;
            break;
        case 3:
            std::istringstream(fromfile[i]) >> CRS.size_to;
            break;
        case 4:
            std::istringstream(fromfile[i]) >> CRS.hyperlanes_max_length_from;
            break;
        case 5:
            std::istringstream(fromfile[i]) >> CRS.hyperlanes_max_length_to;
            break;
        case 6:
            std::istringstream(fromfile[i]) >> CRS.circle_stars_from;
            break;
        case 7:
            std::istringstream(fromfile[i]) >> CRS.circle_stars_to;
            break;
        case 8:
            std::istringstream(fromfile[i]) >> CRS.spiral_stars_from;
            break;
        case 9:
            std::istringstream(fromfile[i]) >> CRS.spiral_stars_to;
            break;
        case 10:
            std::istringstream(fromfile[i]) >> CRS.rotation_factor_from;
            break;
        case 11:
            std::istringstream(fromfile[i]) >> CRS.rotation_factor_to;
            break;
        case 12:
            std::istringstream(fromfile[i]) >> CRS.arm_amount_from;
            break;
        case 13:
            std::istringstream(fromfile[i]) >> CRS.arm_amount_to;
            break;
        case 14:
            std::istringstream(fromfile[i]) >> CRS.square_factor;
            break;
        case 15:
            std::istringstream(fromfile[i]) >> CRS.arm_max_width_from;
            break;
        case 16:
            std::istringstream(fromfile[i]) >> CRS.arm_max_width_to;
            break;
        case 17:
            std::istringstream(fromfile[i]) >> CRS.arm_random_width_from;
            break;
        case 18:
            std::istringstream(fromfile[i]) >> CRS.arm_random_width_from;
            break;
        case 19:
            std::istringstream(fromfile[i]) >> CRS.size_ratio;
            break;
        case 20:
            std::istringstream(fromfile[i]) >> CRS.arm_ratio;
            break;
        case 21:
            std::istringstream(fromfile[i]) >> CRS.arm_width_ratio;
            break;
        }
    }
}

void RandomDefaultSettings()
{
    std::ofstream file(constpath + "/random_default.txt");
    if (file.is_open())
    {
        file << "1\n";
        file << "1\n";
        file << "1\n";
        file << "250\n";
        file << "400\n";
        file << "25\n";
        file << "50\n";
        file << "9\n";
        file << "13\n";
        file << "7\n";
        file << "9\n";
        file << "1.5\n";
        file << "0.75\n";
        file << "0.9\n";
        file << "0.01\n";
        file << "0.1\n";
        file << "6\n";
        file << "3\n";
        file << "5\n";
        file << "1.25\n";
        file << "0.25\n";
        file << "0.45\n";
    }
    file.close();
}

void LoadRandomDefaultSettings()
{
    std::string line;
    std::vector<std::string>fromfile;
    std::string path = constpath + "/random_default.txt";
    std::ifstream file(path);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            fromfile.push_back(line);
        }
    }
    file.close();
    for (int i = 0; i < fromfile.size(); i++)
    {
        switch (i)
        {
        case 0:
            std::istringstream(fromfile[i]) >> CRS.enable_spiral;
            break;
        case 1:
            std::istringstream(fromfile[i]) >> CRS.enable_resizing;
            break;
        case 2:
            std::istringstream(fromfile[i]) >> CRS.size_from;
            break;
        case 3:
            std::istringstream(fromfile[i]) >> CRS.size_to;
            break;
        case 4:
            std::istringstream(fromfile[i]) >> CRS.hyperlanes_max_length_from;
            break;
        case 5:
            std::istringstream(fromfile[i]) >> CRS.hyperlanes_max_length_to;
            break;
        case 6:
            std::istringstream(fromfile[i]) >> CRS.circle_stars_from;
            break;
        case 7:
            std::istringstream(fromfile[i]) >> CRS.circle_stars_to;
            break;
        case 8:
            std::istringstream(fromfile[i]) >> CRS.spiral_stars_from;
            break;
        case 9:
            std::istringstream(fromfile[i]) >> CRS.spiral_stars_to;
            break;
        case 10:
            std::istringstream(fromfile[i]) >> CRS.rotation_factor_from;
            break;
        case 11:
            std::istringstream(fromfile[i]) >> CRS.rotation_factor_to;
            break;
        case 12:
            std::istringstream(fromfile[i]) >> CRS.arm_amount_from;
            break;
        case 13:
            std::istringstream(fromfile[i]) >> CRS.arm_amount_to;
            break;
        case 14:
            std::istringstream(fromfile[i]) >> CRS.square_factor;
            break;
        case 15:
            std::istringstream(fromfile[i]) >> CRS.arm_max_width_from;
            break;
        case 16:
            std::istringstream(fromfile[i]) >> CRS.arm_max_width_to;
            break;
        case 17:
            std::istringstream(fromfile[i]) >> CRS.arm_random_width_from;
            break;
        case 18:
            std::istringstream(fromfile[i]) >> CRS.arm_random_width_from;
            break;
        case 19:
            std::istringstream(fromfile[i]) >> CRS.size_ratio;
            break;
        case 20:
            std::istringstream(fromfile[i]) >> CRS.arm_ratio;
            break;
        case 21:
            std::istringstream(fromfile[i]) >> CRS.arm_width_ratio;
            break;
        }
    }
}