#pragma once
void rerender()
{
    SDL_RenderClear(gRenderer);
    ThrowOutButtons();
    base();
    layer_1();
    SDL_RenderPresent(gRenderer);
    if ((no_space_found == true) && (disable_failed_galaxy_warn == false))
    {
        SDL_Delay(1000);
    }
}

void base()
{
    background();
    left(alpha1);
    top_menu(alpha2);
    right_panel(alpha3);
    buttons_render();
    if (pathsaved == 0)
    {
        firstrunbackground();
    }
    if (elipse_galaxy_window == true)
    {
        elipse_background();
    }

    if (spiral_galaxy_window == true)
    {
        spiral_background();
    }

    if (current_galaxies_window == true)
    {
        if (!C_S.scrolling)
        {
            current_galaxies_buttons();
            GE.text_render("CS", center_width + 1290, center_height + 260);
            GE.text_render(std::to_string(sys_sum), center_width + 1345, center_height + 260);
            if (show_hyperlanes == true)
            {
                GE.text_render_v2("X", 1545, 605);
            }
            if ((no_space_found == true) && (disable_failed_galaxy_warn == false))
            {
                No_space_found();
            }
            if ((min_hyperlane_am == 0) || (max_hyperlane_am == 0))
            {
                gModulatedTexture.setAlpha(250);
                gModulatedTexture.render(center_width + 810, center_height + 260, 800, 200);
                GE.text_render("You must setup maximum and minimum hyperlanes ", center_width + 820, center_height + 270);
                GE.text_render("amount before generating a galaxies, that is in:", center_width + 820, center_height + 305);
                GE.text_render("Settings > Game > Hyperlanes Amount (From: x) (To: x)", center_width + 820, center_height + 340);
            }
            if (show_initializers)
            {
                GE.text_render_v2("X", 1365, 891);
            }
        }
    }

    if (saveloadexit_window == true)
    {
        if (!C_S.scrolling)
        {
            SaveLoadExit();
            if (export_mode_multi)
            {
                GE.text_render("X", center_width + 1518, center_height + 239);
            }
            if (initializers == true)
            {
                GE.text_render("X", center_width + 1518, center_height + 279);
            }
            if (savetoagame == true)
            {
                GE.text_render("X", center_width + 1518, center_height + 319);
            }
            if (setting_hyperlanes == true)
            {
                GE.text_render("X", center_width + 1518, center_height + 359);
            }
        }
    }

    if (empiresettings_window == true)
    {
        EmpireSettings();
        if (empire_am != 0)
        {
            GE.text_render(std::to_string(empire_am), center_width + 1455, center_height + 240);
        }
        if (fallen_am != 0)
        {
            GE.text_render(std::to_string(fallen_am), center_width + 1540, center_height + 280);
        }
        if (maruder_am != 0)
        {
            GE.text_render(std::to_string(maruder_am), center_width + 1490, center_height + 320);
        }
        if (generate_multiple_leviathans == true)
        {
            GE.text_render("X", center_width + 1648, center_height + 410);
        }
        if (Empires_Random == true)
        {
            GE.text_render("X", center_width + 1360, center_height + 361);
        }
        if (min_hyperlane_am != 0)
        {
            GE.text_render(std::to_string(min_hyperlane_am), center_width + 1590, center_height + 512);
        }
        if (max_hyperlane_am != 0)
        {
            GE.text_render(std::to_string(max_hyperlane_am), center_width + 1683, center_height + 512);
        }
    }

    if (settings_window == true)
    {
        if (!C_S.scrolling)
        {
        Settings();
        }
    }

    if (launchersettings_window == true)
    {
        LauncherSettings();
        if (disable_failed_galaxy_warn == true)
        {
            GE.text_render("X", center_width + 1667, center_height + 252);
        }
        if (disable_wrong_text_warn == true)
        {
            GE.text_render("X", center_width + 1655, center_height + 292);
        }
    }

    if (random_window == true)
    {
        RandomSettings();
        if (CRS.enable_circle)
        {
            GE.text_render_v2("X", 1436, 231);
        }
        if (CRS.enable_spiral)
        {
            GE.text_render_v2("X", 1796, 231);
        }
        if (CRS.enable_resizing)
        {
            GE.text_render_v2("X", 1836, 271);
        }
        std::stringstream ss;
        std::string output;
        if (!CRS.size_from_edited)
        {
            GE.text_render_v2(std::to_string(CRS.size_from), 1403, 270);
        }
        if (!CRS.size_to_edited)
        {
            GE.text_render_v2(std::to_string(CRS.size_to), 1513, 270);
        }
        if (!CRS.hyperlanes_max_length_from_edited)
        {
            GE.text_render_v2(std::to_string(CRS.hyperlanes_max_length_from), 1560, 310);
        }
        if(!CRS.hyperlanes_max_length_to_edited)
        {
            GE.text_render_v2(std::to_string(CRS.hyperlanes_max_length_to), 1680, 310);
        }
        if (!CRS.circle_stars_from_edited)
        {
            GE.text_render_v2(std::to_string(CRS.circle_stars_from), 1500, 390);
        }
        if (!CRS.circle_stars_to_edited)
        {
            GE.text_render_v2(std::to_string(CRS.circle_stars_to), 1580, 390);
        }
        if (!CRS.spiral_stars_from_edited)
        {
            GE.text_render_v2(std::to_string(CRS.spiral_stars_from), 1500, 480);
        }
        if (!CRS.spiral_stars_to_edited)
        {
            GE.text_render_v2(std::to_string(CRS.spiral_stars_to), 1580, 480);
        }
        if (!CRS.rotation_factor_edited)
        {
            GE.text_render_v2(std::to_string(CRS.rotation_factor), 1454, 640);
        }
        if (!CRS.arm_amount_from_edited)
        {
            GE.text_render_v2(std::to_string(CRS.arm_amount_from), 1417, 680);
        }
        if (!CRS.arm_amount_to_edited)
        {
            GE.text_render_v2(std::to_string(CRS.arm_amount_to), 1580, 680);
        }
        if (!CRS.square_factor_edited)
        {
            ss << CRS.square_factor; ss >> output;
            GE.text_render_v2(output, 1435, 520);
        }
        if (!CRS.arm_max_width_from_edited)
        {
            ss.clear(); ss.str(""); ss << CRS.arm_max_width_from; ss >> output;
            GE.text_render_v2(output, 1450, 560);
        }
        if (!CRS.arm_max_width_to_edited)
        {
            ss.clear(); ss.str(""); ss << CRS.arm_max_width_to; ss >> output;
            GE.text_render_v2(output, 1580, 560);
        }
        if (!CRS.arm_random_width_from_edited)
        {
            ss.clear(); ss.str(""); ss << CRS.arm_random_width_from; ss >> output;
            GE.text_render_v2(output, 1495, 600);
        }
        if (!CRS.arm_random_width_to_edited)
        {
            ss.clear(); ss.str(""); ss << CRS.arm_random_width_to; ss >> output;
            GE.text_render_v2(output, 1620, 600);
        }
        if (!CRS.size_ratio_edited)
        {
            ss.clear(); ss.str(""); ss << CRS.size_ratio; ss >> output;
            GE.text_render_v2(output, 1380, 780);
        }
        if (!CRS.arm_ratio_edited)
        {
            ss.clear(); ss.str(""); ss << CRS.arm_ratio; ss >> output;
            GE.text_render_v2(output, 1685, 780);
        }
        if (!CRS.arm_width_ratio_edited)
        {
            ss.clear(); ss.str(""); ss << CRS.arm_width_ratio; ss >> output;
            GE.text_render_v2(output, 1460, 820);
        }
    }
        
    if (CSHM.edit_galaxies_loop)
    {
        gModulatedTexture.setAlpha(233);
        gModulatedTexture.render(center_width + 1220, center_height + 170, 680, 390);
        GE.text_render_v2("Currently edited galaxy " + std::to_string(current_gal_id), 1340, 200);

        GE.text_with_button(140, "Systems:", 1280, 230);
        GE.text_with_button(141, "Size (Radius):", 1280, 260);
        GE.text_with_button(142, "Center X:", 1280, 290);
        GE.text_with_button(143, "Center Y:", 1280, 320);
        GE.text_with_button(144, "Max Hyperlanes Distance:", 1280, 350);

        if (!C_E.star)
        {
            GE.text_render_v2(v_galaxy_generation[current_gal_id].star, 1420, 230);
        }
        if (!C_E.gsize)
        {
            GE.text_render_v2(v_galaxy_generation[current_gal_id].gsize, 1478, 260);
        }
        if (!C_E.posX)
        {
            GE.text_render_v2(v_galaxy_generation[current_gal_id].cen_posX, 1420, 290);
        }
        if (!C_E.posY)
        {
            GE.text_render_v2(v_galaxy_generation[current_gal_id].cen_posY, 1420, 320);
        }
        if (!C_E.max_hyp_dist)
        {
            GE.text_render_v2(v_galaxy_generation[current_gal_id].max_hyp_dis, 1650, 350);
        }

        if (v_galaxy_generation[current_gal_id].galtype == 1)
        {
            GE.text_with_button(145, "Number of Arms:", 1280, 380);
            GE.text_with_button(146, "Arm Max Width:", 1280, 410);
            GE.text_with_button(147, "Random Width:", 1280, 440);
            GE.text_with_button(148, "Arm Rotation:", 1280, 470);

            if (!C_E.num_arms)
            {
                GE.text_render_v2(v_galaxy_generation[current_gal_id].numArms, 1520, 380);
            }
            if (!C_E.arm_offset_max)
            {
                GE.text_render_v2(v_galaxy_generation[current_gal_id].armOffsetMax, 1498, 410);
            }
            if (!C_E.random_arm_offset)
            {
                GE.text_render_v2(v_galaxy_generation[current_gal_id].randomOffsetXY, 1480, 440);
            }
            if (!C_E.rotation_factor)
            {
                GE.text_render_v2(v_galaxy_generation[current_gal_id].rotationFactor, 1470, 470);
            }
        }
    }
    if (galaxies_am > 0)
    {
        alpha1 = 252;
        left(alpha1);
        GE.text_render("- -", center_width + 20, center_height + 10);
        GE.text_render("- +", center_width + 20, center_height + 1040);
        GE.text_render("+ -", center_width + 1150, center_height + 10);
        GE.text_render("+ +", center_width + 1150, center_height + 1040);
        if (!C_S.scrolling)
        {
            for (int i = 0; i < SystemButtons.size(); i++)
            {
                for (int j = 0; j < SystemButtons[i].size(); j++)
                {
                    SystemButtons[i][j].setPosition(-1000, -1000);
                }
            }
            if (show_hyperlanes == true)
            {
                render_hyperlanes();
            }
            draw_galaxy();
        }
        else if (C_S.scrolling)
        {
            for (int i = 150; i < v_galaxy_generation.size(); i++)
            {
                gButtons[i].setPosition(-1000, -1000);
            }
            GE.scrolling_function();
            if (Det_Gen.add_initializer)
            {
                D_S_E.add_initializer_menu();
                if (Det_Gen.add_initializer_mega)
                {
                    D_S_E.add_initializer_mega();
                }
                else if (Det_Gen.add_initializer_leviathan)
                {
                    D_S_E.add_initializer_leviathan();
                }
            }
            else
            {
                D_S_E.menu();
            }
        }
    }
    if (maps_menu_bool)
    {
        F_O.maps_menu();
    }
    if (map_name_bool)
    {
        GE.text_render_v2("Map name: ", center_width + 1240, center_height + 190);
    }
}

void layer_1()
{
    if ((wrong_text == true) && (disable_wrong_text_warn != true))
    {
        gModulatedTexture.setAlpha(250);
        gModulatedTexture.render(center_width + 1410, center_height + 260, 300, 100);
        GE.text_render("Incorrect number", center_width + 1440, center_height + 290);
        SDL_Delay(1000);
    }

    if (patchsettings_window == true)
    {
        PatchSettings();
        if (edit_patch == true)
        {
            firstrunbackground();
        }
    }

    if (galaxy_canceled == true)
    {
        gModulatedTexture.setAlpha(250);
        gModulatedTexture.render(center_width + 310, center_height + 260, 800, 100);
        GE.text_render("Galaxy too dense (Too much sytems in too small size)", center_width + 340, center_height + 290);
    }
}

void DisableOtherWindows()
{
    ThrowOutButtons();
    Det_Gen.false_all_bools();
    Det_Gen.false_initializers();
    Det_Gen.reset_bits();
    if (current_galaxies_window == true)
    {
        current_galaxies_window = false;
    }

    if (saveloadexit_window == true)
    {
        saveloadexit_window = false;
    }

    if (empiresettings_window == true)
    {
        empiresettings_window = false;
    }

    if (choose_galaxy_shape_window == true)
    {
        choose_galaxy_shape_window = false;
    }

    if (settings_window == true)
    {
        settings_window = false;
    }

    if (patchsettings_window == true)
    {
        patchsettings_window = false;
    }

    if (launchersettings_window == true)
    {
        launchersettings_window = false;
    }

    if (random_window == true)
    {
        random_window = false;
    }

    CSHM.redraw_hyperlanes = false;
    CSHM.remove_galaxies = false;
    CSHM.redraw_galaxies = false;
    CSHM.remove_hyperlanes = false;
    if (CSHM.edit_galaxies)
    {
        elipse_galaxy_window = false;
        spiral_galaxy_window = false;
        CSHM.edit_galaxies = false;
        CSHM.edit_galaxies_loop = false;
        edit = false;
    }
    if (map_name_bool)
    {
        map_name_bool = false;
    }
    if (maps_menu_bool)
    {
        maps_menu_bool = false;
    }
    if (C_S.scrolling)
    {
        C_S.scrolling = false;
    }
}

void ThrowOutButtons()
{
    for (int i = 0; i < SystemButtons.size(); i++)
    {
        for (int j = 0; j < SystemButtons[i].size(); j++)
        {
            SystemButtons[i][j].setPosition(-1000, -1000);
        }
    }
    for (int i = 0; i < D_S_E_Buttons.size(); ++i)
    {
        D_S_E_Buttons[i].setPosition(-1000, -1000);
    }
    for (int i = 6; i < 150; i++)
    {
        gButtons[i].setPosition(-1000, -1000);
    }
    for (int i = 0; i < Map_Checkbox_Buttons.size(); ++i)
    {
        Map_Checkbox_Buttons[i].setPosition(-1000, -1000);
    }
}

void background()
{
    SDL_RenderCopy(gRenderer, gBackground, NULL, NULL);
}

void left(Uint8 alpha)
{
    gModulatedTexture.setAlpha(alpha);
    gModulatedTexture.render(center_width, center_height, 1200, 1080);
}

void top_menu(Uint8 alpha)
{
    gModulatedTexture.setAlpha(alpha);
    gModulatedTexture.render(center_width + 1200, center_height, 720, 150);
}

void right_panel(Uint8 alpha)
{
    gModulatedTexture.setAlpha(alpha);
    gModulatedTexture.render(center_width + 1200, center_height + 150, 720, 930);
}

void buttons_render()
{
    for (int i = 0; i < 6; ++i)
    {
        gButtons[i].render();
    }
    GE.text_render("Galaxies", center_width + 1275, center_height + 25);
    GE.text_render("Maps", center_width + 1300, center_height + 90);
    GE.text_render("Settings", center_width + 1500, center_height + 25);
    GE.text_render("Files&Exit", center_width + 1715, center_height + 90);
}

void No_space_found()
{
    gModulatedTexture.setAlpha(243);
    gModulatedTexture.render(center_width + 1620, center_height + 270, 250, 60);
    GE.text_render("Random failed", center_width + 1640, center_height + 290);
}