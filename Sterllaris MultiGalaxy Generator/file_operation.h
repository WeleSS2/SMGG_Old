#pragma once


void osfile(std::string path, std::string name)
{
    std::ofstream file(path);
    if (file.is_open())
    {
        file << "static_galaxy_scenario = { \n";
        file << "name = \"" + name + "\" \n";
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
        std::cout << initializers_loaded << "  " << export_mode_multi << std::endl;
        if (!export_mode_multi)
        {
            int id = 0, current_player = 1;

            for (int i = 0; i < v_system_data.size(); ++i)
            {
                for (int j = 0; j < v_system_data[i].size(); ++j)
                {
                    int x = 0;
                    if (v_system_data[i][j].gal_x > 0)
                    {
                        x = -v_system_data[i][j].gal_x;
                    }
                    else
                    {
                        x = abs(v_system_data[i][j].gal_x);
                    }
                    if(v_system_data[i][j].init_type == 10)
                    {
                        if (v_system_data[i][j].player_id == current_player)
                        {
                            file << "system = { id = \""
                                << v_system_data[i][j].gal_id + id
                                << "\" name = \"\" position = { x = "
                                << x
                                << " y = "
                                << v_system_data[i][j].gal_y
                                << " } initializer = " 
                                << empire_init_tab[v_system_data[i][j].init_number] 
                                << " spawn_weight = { base = 1 } }\n";
                            v_system_data[i][j].exported = true;
                            i = 0;
                            j = 0;
                            id = 0;
                            current_player++;
                        }
                    }
                }
                id += v_system_data[i].size();
            }

            id = 0;
            std::cout << v_system_data.size() << std::endl;
            for (int i = 0; i < v_system_data.size(); i++)
            {
                int random_gal = i;
                if (Det_Gen.player_am == 0)
                {
                    random_gal = rand() % v_system_data.size();
                    while (v_galaxy_generation[random_gal].exported)
                    {
                        random_gal = rand() % v_system_data.size();
                    }
                }
                v_galaxy_generation[random_gal].exported = true;
                //std::cout << v_system_data[random_gal].size() << std::endl;
                for (int j = 0; j < v_system_data[random_gal].size(); j++)
                {
                    bool added = false;
                    //std::cout << j << std::endl;
                    int export_local = rand() % v_system_data[random_gal].size();
                    //std::cout << export_local << "   " << v_system_data[random_gal][export_local].exported << std::endl;
                    while (v_system_data[random_gal][export_local].exported == true)
                    {
                        //std::cout << export_local << std::endl;
                        export_local = rand() % v_system_data[random_gal].size();
                        if(j == v_system_data[random_gal].size() - v_galaxy_generation[random_gal].players_am)
                        {
                            j = 100000;
                            break;
                        }
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
                    if (v_system_data[random_gal][export_local].init_type != 10)
                    {
                        file << "system = { id = \""
                            << v_system_data[random_gal][export_local].gal_id + id
                            << "\" name = \"\" position = { x = "
                            << x
                            << " y = "
                            << v_system_data[random_gal][export_local].gal_y
                            << " } ";
                    }

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
                    case 10:
                        file << "initializer = " << empire_init_tab[v_system_data[random_gal][export_local].init_number] << " spawn_weight = { base = 1 }";
                        break;
                    case 99:
                        file << "initializer = smgg_central_black_hole";
                        break;
                    }
                    if (v_system_data[random_gal][export_local].init_type != 10)
                    {
                        file << " }\n";
                    }
                    v_system_data[random_gal][export_local].exported = true;

                }
                for (int j = 0; j < v_hyperlanes[random_gal].size(); ++j)
                {
                    for (int k = 0; k < v_hyperlanes[random_gal][j].size(); ++k)
                    {
                        file << "add_hyperlane = { from = \"" + std::to_string(v_hyperlanes[random_gal][j][k].from + id) + "\" to = \"" + std::to_string(v_hyperlanes[random_gal][j][k].to + id) + "\" }" << std::endl;
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
                case 10:
                    file << "initializer = " << empire_init_tab[v_system_data_copy[i].init_number] << " spawn_weight = { base = 1 }";
                    break;
                case 99:
                    file << "initializer = smgg_central_black_hole";
                    break;
                }
                file << " }\n";
            }
            for (int i = 0; i < v_hyperlanes_copy.size(); i++)
            {
                if (setting_hyperlanes == true)
                {
                        //std::cout << "For 2 loop " << i << std::endl;
                    file << "add_hyperlane = { from = \"" + std::to_string(v_hyperlanes_copy[i].from) + "\" to = \"" + std::to_string(v_hyperlanes_copy[i].to) + "\" }" << std::endl;
                }
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
                    int mapversion = 0;
                    file >> mapversion;
                    file >> export_mode;
                    file >> initializers_loaded;
                    file >> hyperlanes_loaded;
                    file >> galaxies_am;
                    file >> empire_am;
                    file >> fallen_am;
                    file >> maruder_am;
                    if (mapversion >= 60)
                    {
                        file >> Det_Gen.player_am;
                    }
                    for (int i = 0; i < galaxies_am; i++)
                    {
                        //std::cout << "Galaxy number " << i << std::endl;
                        current_gal_id = i;
                        v_galaxy_generation.emplace_back();
                        SystemButtons.emplace_back();
                        int gal_type = 0;
                        file >> gal_type;
                        v_galaxy_generation[i].galtype = gal_type;
                        //std::cout << "Galaxy number before galaxy " << gal_type << std::endl;
                        if (gal_type == 0)
                        {
                            file >> v_galaxy_generation[current_gal_id].star >> v_galaxy_generation[i].gsize
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
                        if (mapversion >= 60)
                        {
                            file >> v_galaxy_generation[i].players_am;
                        }
                        v_system_data.emplace_back();
                        //std::cout << "Galaxy number before systems " << i << std::endl;
                        for (int j = 0; j < v_galaxy_generation[i].i_star; j++)
                        {
                            SystemButtons[i].emplace_back();
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
                                int amount_2 = 0;
                                file >> amount_2;
                                for (int k = 0; k < amount_2; ++k)
                                {
                                    v_hyperlanes[i][j].emplace_back();
                                    file >> v_hyperlanes[i][j][k].from >> v_hyperlanes[i][j][k].to;
                                }
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
                            file >> v_hyperlanes_copy[i].from;
                            file >> v_hyperlanes_copy[i].to;
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
                            int mapversion = 60;
                            file << mapversion << std::endl;
                            file << export_mode << std::endl;
                            std::vector <int> gal_init_1_id;
                            std::vector <bool> gal_init_1_id_exported;
                            file << initializers_loaded << std::endl;
                            file << hyperlanes_loaded << std::endl;
                            file << v_galaxy_generation.size() << std::endl;
                            file << empire_am << std::endl;
                            file << fallen_am << std::endl;
                            file << maruder_am << std::endl;
                            if (mapversion >= 60)
                            {
                                file << Det_Gen.player_am << std::endl;
                            }
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
                                    << " " << v_galaxy_generation[random_gal].randomOffsetXY << " ";
                                if (mapversion >= 60)
                                {
                                    file << v_galaxy_generation[random_gal].players_am;
                                }
                                file <<  std::endl;
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
                                    for (int j = 0; j < v_hyperlanes[random_gal].size(); j++)
                                    {
                                        file << v_hyperlanes[random_gal][j].size() << std::endl;
                                        for (int k = 0; k < v_hyperlanes[random_gal][j].size(); ++k)
                                        {
                                            file << v_hyperlanes[random_gal][j][k].from << "  " << v_hyperlanes[random_gal][j][k].to << std::endl;
                                        }
                                    }
                                }
                                else
                                {
                                    int k_sum = 0;
                                    file << v_hyperlanes[random_gal].size() << std::endl;
                                    for (int j = 0; j < v_hyperlanes[random_gal].size(); j++)
                                    {
                                        file << v_hyperlanes[random_gal][j].size() << std::endl;
                                        for (int k = 0; k < v_hyperlanes[random_gal][j].size(); ++k)
                                        {
                                            file << v_hyperlanes[random_gal][j][k].from << "  " << v_hyperlanes[random_gal][j][k].to << std::endl;

                                            v_hyperlanes_copy.emplace_back();
                                            v_hyperlanes_copy[hyper_sum + k_sum + k].from = v_hyperlanes[random_gal][j][k].from + sum;
                                            v_hyperlanes_copy[hyper_sum + k_sum + k].to = v_hyperlanes[random_gal][j][k].to + sum;
                                            
                                        }
                                        k_sum += v_hyperlanes[random_gal][j].size();
                                    }
                                }
                                for (int j = 0; j < v_hyperlanes[random_gal].size(); ++j)
                                {
                                    hyper_sum += v_hyperlanes[random_gal][j].size();
                                }
                                
                                sum += v_galaxy_generation[random_gal].i_star;
                            }
                            if (mapversion >= 60)
                            {
                                if ((export_mode_multi))
                                {
                                    int current_player = 1;
                                    auto rd = std::random_device{};
                                    auto rng = std::default_random_engine{ rd() };
                                    std::shuffle(std::begin(v_system_data_copy), std::end(v_system_data_copy), rng);
                                    file << sum << std::endl;
                                    if (initializers_loaded)
                                    {
                                        for (int i = 0; i < sum; i++)
                                        {
                                            if (v_system_data_copy[i].init_type == 10)
                                            {
                                                if (v_system_data_copy[i].player_id == current_player)
                                                {
                                                    file << v_system_data_copy[i].gal_id << " " << v_system_data_copy[i].gal_x
                                                        << " " << v_system_data_copy[i].gal_y << " " << v_system_data_copy[i].con
                                                        << " " << v_system_data_copy[i].con_max << " " << v_system_data_copy[i].inicjalizer
                                                        << " " << v_system_data_copy[i].init_type << " " << v_system_data_copy[i].init_number << std::endl;;
                                                    current_player++;
                                                    i = 0;
                                                }
                                            }
                                        }
                                    }
                                    for (int i = 0; i < sum; i++)
                                    {
                                        if (initializers_loaded)
                                        {
                                            if (v_system_data_copy[i].init_type != 10)
                                            {
                                                file << v_system_data_copy[i].gal_id << " " << v_system_data_copy[i].gal_x
                                                    << " " << v_system_data_copy[i].gal_y << " " << v_system_data_copy[i].con
                                                    << " " << v_system_data_copy[i].con_max << " " << v_system_data_copy[i].inicjalizer
                                                    << " " << v_system_data_copy[i].init_type << " " << v_system_data_copy[i].init_number << std::endl;;
                                            }
                                            else
                                            {
                                                file << std::endl;
                                            }
                                        }
                                        else
                                        {
                                            file << v_system_data_copy[i].gal_id << " " << v_system_data_copy[i].gal_x
                                                << " " << v_system_data_copy[i].gal_y << " " << v_system_data_copy[i].con
                                                << " " << v_system_data_copy[i].con_max;
                                        }
                                    }
                                    file << v_hyperlanes_copy.size() << std::endl;

                                    for (int i = 0; i < v_hyperlanes_copy.size(); i++)
                                    {
                                        file << v_hyperlanes_copy[i].from << "  " << v_hyperlanes_copy[i].to << std::endl;
                                    }
                                }
                            }
                            else if ((export_mode_multi) && (mapversion < 60))
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
                                    file << v_hyperlanes_copy[i].from << "  " << v_hyperlanes_copy[i].to << std::endl;
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
    return 0;
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
        if (show_initializers)
        {
            file << "1" << "\n";
        }
        else
        {
            file << "0\n";
        }
        if (local_maps_created)
        {
            file << "1" << "\n";
        }
        else
        {
            file << "0" << "\n";
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
            case 14:
                std::istringstream(fromfile[i]) >> show_initializers;
                break;
            case 15:
                std::istringstream(fromfile[i]) >> local_maps_created;
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

PWSTR File_Operation::SaveMap() {
    std::string path = "";
    IFileSaveDialog* pFileSave;

    // Create the FileOpenDialog object.
    HRESULT hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
        IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));
    if (SUCCEEDED(hr))
    {

        // Setting up a patch
        std::string str_path = constpath + "\\Maps";
        std::wstring widestr = std::filesystem::path(str_path).wstring();
        const wchar_t* widecstr = widestr.c_str();

        PIDLIST_ABSOLUTE pidl;
        hr = ::SHParseDisplayName(widecstr, 0, &pidl, SFGAO_FOLDER, 0);
        if (SUCCEEDED(hr))
        {
            IShellItem* psi;
            hr = ::SHCreateShellItem(NULL, NULL, pidl, &psi);
            if (SUCCEEDED(hr))
            {
                hr = pFileSave->SetFolder(psi);
            }
            ILFree(pidl);
        }

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
                        std::cout << buffer << std::endl;
                        path = buffer;


                        std::ofstream file(path);
                        if (file.is_open())
                        {
                            
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
    return 0;
}

void File_Operation::create_folder()
{
    std::filesystem::create_directory(constpath + "\\Maps");
    std::string path = constpath + "/Maps/Maps_Data.txt";
    std::fstream file(path, std::ios_base::out);

    if (file.is_open())
    {
        file << "Path" << " " << "TXTName" << " " << "Name" << " " << "Status" << "\n";
        file << pathget + "/workshop/content/281990/2602794523/map/setup_scenarios/sps_multigalaxy.txt" << " " << "sps_multigalaxy.txt" << " " << "MultiGalaxy" << " " << "1" << "\n";
    }
    file.close();

    std::ifstream src(pathget + "/workshop/content/281990/2602794523/map/setup_scenarios/sps_multigalaxy.txt", std::ios::binary);
    std::ofstream dest(constpath + "/Maps/sps_multigalaxy.txt", std::ios::binary);
    dest << src.rdbuf();
    local_maps_created = true;
}

void File_Operation::save_maps()
{
    std::string path = constpath + "/Maps/Maps_Data.txt";
    std::fstream file(path, std::ios_base::out);
    if (file.is_open())
    {
        file << "Path" << " " << "TXTName" << " " << "Name" << " " << "Status" << std::endl;
        for (int i = 0; i < v_local_maps.size(); ++i)
        {
            file << v_local_maps[i].map_steam << " " << v_local_maps[i].map_local << " " << v_local_maps[i].map_name << " " << v_local_maps[i].enabled << std::endl;
        }
    }
    file.close();
}

void File_Operation::add_map()
{
    GE.text_render_v2("Galaxy name", 1020, 200);
}

void File_Operation::load_files_from_steammod_folder()
{
    for (const auto& file : std::filesystem::recursive_directory_iterator(pathget + "/workshop/content/281990/2602794523/map/setup_scenarios"))
    {
        std::filesystem::path path{ file.path() };
        std::string path_string{ path.string() };
        char ch0 = '\\\\';
        char ch1 = '\\';
        char ch2 = '/';
        for (int i = 0; i < path_string.length(); ++i) {
            if (path_string[i] == ch1 || path_string[i] == ch0)
            {
                if (path_string[i] == ch1)
                {
                     path_string[i] = ch2;
                }
                else {
                    path_string[i] = ch2;
                    path_string.erase(path_string.begin() + i + 1);
                }
            }
        }
        if(path_string != "D:/SGry/steamapps/workshop/content/281990/2602794523/map/setup_scenarios/huge.txt" && 
            path_string != "D:/SGry/steamapps/workshop/content/281990/2602794523/map/setup_scenarios/large.txt" &&
            path_string != "D:/SGry/steamapps/workshop/content/281990/2602794523/map/setup_scenarios/medium.txt" &&
            path_string != "D:/SGry/steamapps/workshop/content/281990/2602794523/map/setup_scenarios/small.txt" &&
            path_string != "D:/SGry/steamapps/workshop/content/281990/2602794523/map/setup_scenarios/tiny.txt"
            )
        std::cout << path_string << std::endl;
        local_maps pushing;
        pushing.map_local = path_string;
        pushing.enabled = 0;
        v_local_maps.push_back(pushing);
        //file.path() = temp;
    }
}

void File_Operation::map_name()
{
    map_name_bool = true;
    GE.text_render_v2("Map name: ", 1240, 190);
    GE.text_input(center_width + 1420, center_height + 190, 30);
    std::cout << mapname << "--- " << std::endl;
    std::string temp = mapname;
    for (int i = 0; i < temp.length(); ++i)
    {
        if (temp[i] == 32)
        {
            temp.replace(i, 1, "_");
        }
    }
    std::cout << temp << "\n";
    local_maps pushing;
    pushing.map_steam = pathget + "/workshop/content/281990/2602794523/map/setup_scenarios/" + temp + ".txt";
    pushing.map_local = temp + ".txt";
    pushing.map_name = temp;
    pushing.map_name_with_spaces = mapname;
    pushing.enabled = "1";
    F_O.v_local_maps.push_back(pushing);
    Map_Checkbox_Buttons.emplace_back();
    save_maps();
    osfile(pathget + "/workshop/content/281990/2602794523/map/setup_scenarios/" + temp + ".txt", mapname);
    osfile(constpath + "/Maps/" + temp + ".txt", mapname);
}

void File_Operation::overwrite_data_map()
{

}

void File_Operation::maps_menu()
{
    if (!local_maps_created)
    {
        create_folder();
    }
    if (!mapsloaded)
    {
        load_maps();
    }
    gModulatedTexture.setAlpha(233);
    gModulatedTexture.render(center_width + 160, center_height + 120, 1660, 840);
    GE.text_render_v2("Maps", 900, 130);
    GE.text_render_v2("Name", 300, 165);
    GE.text_render_v2("Status", 500, 165);
    GE.render_button_with_text(0, 27, 860, 200, "Save As", 890, 204);
    if (F_O.v_local_maps.size() > 0)
    {
        if (F_O.v_local_maps.size() < 15)
        {
            for (int i = 0; i < F_O.v_local_maps.size(); ++i)
            {
                GE.text_render_v2(F_O.v_local_maps[i].map_name_with_spaces, 240, 210 + (45 * i) - (F_O.top_showed * 45));
                if (F_O.v_local_maps[i].enabled)
                {
                    GE.render_checkbox_v2(2, i, 530, 210 + (45 * i) - (F_O.top_showed * 45), 35, 35);
                    GE.render_color_box(0, 255, 0, 530, 210 + (45 * i) - (F_O.top_showed * 45), 20, 20);
                }
                else
                {
                    GE.render_checkbox_v2(2, i, 530, 210 + (45 * i) - (F_O.top_showed * 45), 35, 35);
                    GE.render_color_box(255, 0, 0, 530, 210 + (45 * i) - (F_O.top_showed * 45), 20, 20);
                }
            }
        }
        else
        {
            for (int i = F_O.top_showed; i < F_O.top_showed + 15; ++i)
            {
                GE.text_render_v2(F_O.v_local_maps[i].map_name_with_spaces, 240, 210 + (45 * i) - (F_O.top_showed * 45));
                if (F_O.v_local_maps[i].enabled)
                {
                    GE.render_checkbox_v2(2, i, 530, 210 + (45 * i) - (F_O.top_showed * 45), 35, 35);
                    GE.render_color_box(0, 255, 0, 530, 210 + (45 * i) - (F_O.top_showed * 45), 20, 20);
                }
                else
                {
                    GE.render_checkbox_v2(2, i, 530, 210 + (45 * i) - (F_O.top_showed * 45), 35, 35);
                    GE.render_color_box(255, 0, 0, 530, 210 + (45 * i) - (F_O.top_showed * 45), 20, 20);
                }
            }
        }
    }
}
// constpath + "\\Maps"

void File_Operation::load_maps()
{
    mapsloaded = true;
    std::vector <std::string> hold;
    std::string line = "";
    std::string path = constpath + "\\Maps\\Maps_Data.txt";
    int i = 0;
    std::ifstream file(path);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            std::string temp = "";
            local_maps pushing;
            file >> pushing.map_steam >> pushing.map_local >> 
                temp >> pushing.enabled;
            pushing.map_name = temp;
            for (int i = 0; i < temp.length(); ++i)
            {
                if (temp[i] == 95)
                {
                    temp.replace(i, 1, " ");
                }
            }
            pushing.map_name_with_spaces = temp;
            if (pushing.map_steam != "")
            {
                v_local_maps.push_back(pushing);
                Map_Checkbox_Buttons.emplace_back();
            }
        }
    }
    file.close();
}