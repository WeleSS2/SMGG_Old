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
        file << "num_empires = { min = " + std::to_string(empire_am) + " max = " + std::to_string(empire_am) + " } \n";
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
        if (!export_mode_multi)
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
            int id = 0;
            for (int i = 0; i < v_system_data_copy.size(); i++)
            {
                int x;

                //std::cout << j << "-----"  << std::endl;
                if (v_system_data_copy[i].gal_x > 0)
                {
                    x = -v_system_data_copy[i].gal_x;
                }
                else
                {
                    x = abs(v_system_data_copy[i].gal_x);
                }
                //std::cout << v_system_data_copy[i].gal_id + id << " " << x << " " << v_system_data_copy[i].gal_y << std::endl;
                file << "system = { id = \""
                    << v_system_data_copy[i].gal_id + id
                    << "\" name = \"\" position = { x = "
                    << x
                    << " y = "
                    << v_system_data_copy[i].gal_y
                    << " } ";

                switch (v_system_data_copy[i].init_type)
                {
                case 0:
                    break;
                case 1:
                    file << "initializer = " << empire_init_tab[v_system_data_copy[i].init_number] << " spawn_weight = { base = 1 }";
                    break;
                case 2:
                    file << "initializer = " << C_fallen.fallen_empire_init_tab[v_system_data_copy[i].init_number];
                    break;
                case 3:
                    file << "initializer = " << Class_lev.name[v_system_data_copy[i].init_number];
                    break;
                case 4:
                    file << "initializer = " << mega_ruined_init_tab[v_system_data_copy[i].init_number];
                    break;
                case 5:
                    file << "initializer = " << marauder_init_tab[v_system_data_copy[i].init_number];
                    break;
                case 99:
                    file << "initializer = smgg_central_black_hole";
                    break;
                }
                file << " }\n";
            }
            for (int i = 0; i < v_system_data.size(); i++)
            {
                if (setting_hyperlanes == true)
                {
                    for (int j = 0; j < v_hyperlanes[i].size(); j++)
                    {
                        //std::cout << "For 2 loop " << i << std::endl;
                        file << "add_hyperlane = { from = \"" + std::to_string(v_hyperlanes[i][j].from + id) + "\" to = \"" + std::to_string(v_hyperlanes[i][j].to + id) + "\" }" << std::endl;
                    }
                }
                id += v_system_data[i].size();
            }
        }
        file << "} \n";
        file.close();
    }
    for (int i = 0; i < v_system_data.size(); i++)
    {
        v_galaxy_generation[i].exported = false;
        for (int j = 0; j < v_system_data[i].size(); j++)
        {
            v_system_data[i][j].exported = false;
        }
    }
}

PWSTR LoadFile() {
    //std::cout << "Load file " << std::endl;
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
                    //std::cout << "Import open" << std::endl;
                    std::ifstream file(pszFilePath);
                    file >> export_mode;
                    file >> initializers_loaded;
                    file >> hyperlanes_loaded;
                    file >> galaxies_am;
                    file >> empire_am;
                    file >> fallen_am;
                    file >> maruder_am;
                    for (int i = 0; i < galaxies_am; i++)
                    {
                        //std::cout << "Galaxy number " << i << std::endl;
                        current_gal_id = i;
                        v_galaxy_generation.emplace_back();
                        int gal_type = 0;
                        file >> gal_type;
                        v_galaxy_generation[i].galtype = gal_type;
                        //std::cout << "Galaxy number before galaxy " << gal_type << std::endl;
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
                        v_system_data.emplace_back();
                        //std::cout << "Galaxy number before systems " << i << std::endl;
                        for (int j = 0; j < v_galaxy_generation[i].i_star; j++)
                        {
                            //std::cout << j << std::endl;
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
                        //std::cout << "Galaxy number before hyperlanes " << i << std::endl;
                        if (hyperlanes_loaded == true)
                        {
                            v_galaxy_generation[i].hyperlanes_generated = true;
                            v_hyperlanes.emplace_back();
                            int amount = 0;
                            file >> amount;
                            for (int j = 0; j < amount; j++)
                            {
                                v_hyperlanes[i].emplace_back();
                                file >> v_hyperlanes[i][j].from >> v_hyperlanes[i][j].to;
                            }
                        }
                        sys_sum += std::stoi(v_galaxy_generation[i].star);
                    }
                    //std::cout << "Export mode below" << std::endl;
                    if ((export_mode_multi) && (export_mode == 1))
                    {
                        int size = 0;
                        file >> size;
                        for (int i = 0; i < size; i++)
                        {
                            v_system_data_copy.emplace_back();
                            file >> v_system_data_copy[i].gal_id >> v_system_data_copy[i].gal_x
                                >> v_system_data_copy[i].gal_y >> v_system_data_copy[i].con
                                >> v_system_data_copy[i].con_max ;
                            if (initializers_loaded)
                            {
                                file >> v_system_data_copy[i].inicjalizer
                                    >> v_system_data_copy[i].init_type >> v_system_data_copy[i].init_number;
                            }
                        }
                        int size_hyperlanes = 0;
                        file >> size_hyperlanes;
                        for (int i = 0; i < size_hyperlanes; i++)
                        {
                            v_hyperlanes_copy.emplace_back();
                            file >> v_hyperlanes_copy[i].from >> v_hyperlanes_copy[i].to;
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
                            if (export_mode_multi)
                            {
                                export_mode = 1;
                            }
                            file << export_mode << std::endl;
                            std::vector <int> gal_init_1_id;
                            std::vector <bool> gal_init_1_id_exported;
                            file << initializers_loaded << std::endl;
                            file << hyperlanes_loaded << std::endl;
                            file << v_galaxy_generation.size() << std::endl;
                            file << empire_am << std::endl;
                            file << fallen_am << std::endl;
                            file << maruder_am << std::endl;
                            int sum = 0, hyper_sum = 0;
                            for (int i = 0; i < v_galaxy_generation.size(); i++)
                            {
                                int random_gal = rand() % v_system_data.size();
                                while (v_galaxy_generation[random_gal].exported)
                                {
                                    random_gal = rand() % v_system_data.size();
                                }
                                v_galaxy_generation[random_gal].exported = true;

                                file << v_galaxy_generation[random_gal].galtype << " " << v_galaxy_generation[random_gal].star
                                    << " " << v_galaxy_generation[random_gal].gsize
                                    << " " << v_galaxy_generation[random_gal].cen_posX << " " << v_galaxy_generation[random_gal].cen_posY
                                    << " " << v_galaxy_generation[random_gal].max_hyp_dis << " " << v_galaxy_generation[random_gal].numArms
                                    << " " << v_galaxy_generation[random_gal].armOffsetMax << " " << v_galaxy_generation[random_gal].rotationFactor
                                    << " " << v_galaxy_generation[random_gal].randomOffsetXY <<  std::endl;


                                for (int j = 0; j < v_galaxy_generation[random_gal].i_star; j++)
                                {
                                    //std::cout << v_galaxy_generation[random_gal].i_star << "    " << v_system_data[random_gal].size() << std::endl;
                                    file << v_system_data[random_gal][j].gal_id << " " << v_system_data[random_gal][j].gal_x
                                        << " " << v_system_data[random_gal][j].gal_y << " " << v_system_data[random_gal][j].con
                                        << " " << v_system_data[random_gal][j].con_max << " ";
                                    if (initializers_loaded)
                                    {
                                        file << v_system_data[random_gal][j].inicjalizer
                                            << " " << v_system_data[random_gal][j].init_type << " " << v_system_data[random_gal][j].init_number << std::endl;
                                    }
                                    else
                                    {
                                        file << std::endl;
                                    }
                                    if (export_mode_multi)
                                    {
                                        v_system_data_copy.emplace_back();
                                        //std::cout << sum << std::endl;
                                        v_system_data_copy[sum + j] = v_system_data[random_gal][j];
                                        v_system_data_copy[sum + j].gal_id = v_system_data[random_gal][j].gal_id + sum;
                                    }
                                    v_system_data[random_gal][j].exported = true;
                                }
                                if ((!export_mode_multi)&&(setting_hyperlanes))
                                {
                                    file << v_hyperlanes[random_gal].size() << std::endl;
                                    //file << v_hyperlanes[random_gal].size() << std::endl;
                                    for (int j = 0; j < v_hyperlanes[random_gal].size(); j++)
                                    {
                                        file << v_hyperlanes[random_gal][j].from << "  " << v_hyperlanes[random_gal][j].to << std::endl;
                                    }
                                }
                                else
                                {
                                    file << v_hyperlanes[random_gal].size() << std::endl;
                                    for (int j = 0; j < v_hyperlanes[random_gal].size(); j++)
                                    {
                                        file << v_hyperlanes[random_gal][j].from << "  " << v_hyperlanes[random_gal][j].to << std::endl;
                                        v_hyperlanes_copy.emplace_back();
                                        v_hyperlanes_copy[hyper_sum + j].from = v_hyperlanes[random_gal][j].from + hyper_sum;
                                        v_hyperlanes_copy[hyper_sum + j].to = v_hyperlanes[random_gal][j].to + hyper_sum;
                                    }
                                }
                                sum += v_galaxy_generation[random_gal].i_star;
                                hyper_sum += v_hyperlanes[random_gal].size();
                            }
                            if ((export_mode_multi))
                            {
                                auto rd = std::random_device{};
                                auto rng = std::default_random_engine{ rd() };
                                std::shuffle(std::begin(v_system_data_copy), std::end(v_system_data_copy), rng);
                                file << sum << std::endl;
                                for (int i = 0; i < sum; i++)
                                {
                                    file << v_system_data_copy[i].gal_id << " " << v_system_data_copy[i].gal_x
                                        << " " << v_system_data_copy[i].gal_y << " " << v_system_data_copy[i].con
                                        << " " << v_system_data_copy[i].con_max << " ";
                                    if (initializers_loaded)
                                    {
                                        file << v_system_data_copy[i].inicjalizer
                                            << " " << v_system_data_copy[i].init_type << " " << v_system_data_copy[i].init_number << std::endl;;
                                    }
                                    else
                                    {
                                        file << std::endl;
                                    }
                                }
                                file << v_hyperlanes_copy.size() << std::endl;
                                for (int i = 0; i < v_hyperlanes_copy.size(); i++)
                                {
                                    //if ((v_hyperlanes_copy[i].from != 0) || (v_hyperlanes_copy[i].to != 0))
                                    //{
                                        file << v_hyperlanes_copy[i].from << "  " << v_hyperlanes_copy[i].to << std::endl;
                                    //}
                                }
                            }
                            for (int i = 0; i < v_galaxy_generation.size(); i++)
                            {
                                v_galaxy_generation[i].exported = false;
                                for (int j = 0; j < v_system_data[i].size(); j++)
                                {
                                    v_system_data[i][j].exported = false;
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
    export_mode = 0;
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
        if (export_mode_multi)
        {
            file << "1" << "\n";
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
            case 13:
                std::istringstream(fromfile[i]) >> export_mode_multi;
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
        file << CRS.rotation_factor << "\n";
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
            std::istringstream(fromfile[i]) >> CRS.enable_circle;
            break;
        case 1:
            std::istringstream(fromfile[i]) >> CRS.enable_spiral;
            break;
        case 2:
            std::istringstream(fromfile[i]) >> CRS.enable_resizing;
            break;
        case 3:
            std::istringstream(fromfile[i]) >> CRS.size_from;
            break;
        case 4:
            std::istringstream(fromfile[i]) >> CRS.size_to;
            break;
        case 5:
            std::istringstream(fromfile[i]) >> CRS.hyperlanes_max_length_from;
            break;
        case 6:
            std::istringstream(fromfile[i]) >> CRS.hyperlanes_max_length_to;
            break;
        case 7:
            std::istringstream(fromfile[i]) >> CRS.circle_stars_from;
            break;
        case 8:
            std::istringstream(fromfile[i]) >> CRS.circle_stars_to;
            break;
        case 9:
            std::istringstream(fromfile[i]) >> CRS.spiral_stars_from;
            break;
        case 10:
            std::istringstream(fromfile[i]) >> CRS.spiral_stars_to;
            break;
        case 11:
            std::istringstream(fromfile[i]) >> CRS.rotation_factor;
            break;
        case 12:
            std::istringstream(fromfile[i]) >> CRS.arm_amount_from;
            break;
        case 13:
            std::istringstream(fromfile[i]) >> CRS.arm_amount_to;
            break;
        case 14:
            std::stringstream(fromfile[i]) >> CRS.square_factor;
            break;
        case 15:
            std::stringstream(fromfile[i]) >> CRS.arm_max_width_from;
            break;
        case 16:
            std::stringstream(fromfile[i]) >> CRS.arm_max_width_to;
            break;
        case 17:
            std::stringstream(fromfile[i]) >> CRS.arm_random_width_from;
            break;
        case 18:
            std::stringstream(fromfile[i]) >> CRS.arm_random_width_to;
            break;
        case 19:
            std::stringstream(fromfile[i]) >> CRS.size_ratio;
            break;
        case 20:
            std::stringstream(fromfile[i]) >> CRS.arm_ratio;
            break;
        case 21:
            std::stringstream(fromfile[i]) >> CRS.arm_width_ratio;
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
        file << "13\n";
        file << "16\n";
        file << "3\n";
        file << "4\n";
        file << "6\n";
        file << "3\n";
        file << "5\n";
        file << "2.2\n";
        file << "1\n";
        file << "1.4\n";
        file << "0.02\n";
        file << "0.1\n";
        file << "1.33\n";
        file << "0.45\n";
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
            std::istringstream(fromfile[i]) >> CRS.enable_circle;
            break;
        case 1:
            std::istringstream(fromfile[i]) >> CRS.enable_spiral;
            break;
        case 2:
            std::istringstream(fromfile[i]) >> CRS.enable_resizing;
            break;
        case 3:
            std::istringstream(fromfile[i]) >> CRS.size_from;
            break;
        case 4:
            std::istringstream(fromfile[i]) >> CRS.size_to;
            break;
        case 5:
            std::istringstream(fromfile[i]) >> CRS.hyperlanes_max_length_from;
            break;
        case 6:
            std::istringstream(fromfile[i]) >> CRS.hyperlanes_max_length_to;
            break;
        case 7:
            std::istringstream(fromfile[i]) >> CRS.circle_stars_from;
            break;
        case 8:
            std::istringstream(fromfile[i]) >> CRS.circle_stars_to;
            break;
        case 9:
            std::istringstream(fromfile[i]) >> CRS.spiral_stars_from;
            break;
        case 10:
            std::istringstream(fromfile[i]) >> CRS.spiral_stars_to;
            break;
        case 11:
            std::istringstream(fromfile[i]) >> CRS.rotation_factor;
            break;
        case 12:
            std::istringstream(fromfile[i]) >> CRS.arm_amount_from;
            break;
        case 13:
            std::istringstream(fromfile[i]) >> CRS.arm_amount_to;
            break;
        case 14:
            std::stringstream(fromfile[i]) >> CRS.square_factor;
            break;
        case 15:
            std::stringstream(fromfile[i]) >> CRS.arm_max_width_from;
            break;
        case 16:
            std::stringstream(fromfile[i]) >> CRS.arm_max_width_to;
            break;
        case 17:
            std::stringstream(fromfile[i]) >> CRS.arm_random_width_from;
            break;
        case 18:
            std::stringstream(fromfile[i]) >> CRS.arm_random_width_to;
            break;
        case 19:
            std::stringstream(fromfile[i]) >> CRS.size_ratio;
            break;
        case 20:
            std::stringstream(fromfile[i]) >> CRS.arm_ratio;
            break;
        case 21:
            std::stringstream(fromfile[i]) >> CRS.arm_width_ratio;
            break;
        }
    }

    /*
    std::cout << CRS.enable_circle << std::endl;
    std::cout << CRS.enable_spiral << std::endl; 
    std::cout << CRS.enable_resizing << std::endl;
    std::cout << CRS.size_from << std::endl;
    std::cout << CRS.size_to << std::endl; 
    std::cout << CRS.hyperlanes_max_length_from << std::endl;
    std::cout << CRS.hyperlanes_max_length_to << std::endl; 
    std::cout << CRS.circle_stars_from<< std::endl;
    std::cout << CRS.circle_stars_to << std::endl;
    std::cout << CRS.spiral_stars_from << std::endl;
    std::cout << CRS.spiral_stars_to << std::endl;
    std::cout << CRS.rotation_factor << std::endl; 
    std::cout << CRS.arm_amount_from << std::endl; 
    std::cout << CRS.arm_amount_to << std::endl;
    std::cout << CRS.square_factor << std::endl; 
    std::cout << CRS.arm_max_width_from << std::endl; 
    std::cout << CRS.arm_max_width_to << std::endl; 
    std::cout << CRS.arm_random_width_from << std::endl; 
    std::cout << CRS.arm_random_width_from << std::endl; 
    std::cout << CRS.size_ratio << std::endl; 
    std::cout << CRS.arm_ratio << std::endl;
    std::cout << CRS.arm_width_ratio << std::endl;
    */
}