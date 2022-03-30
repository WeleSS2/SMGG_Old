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
        current_galaxies_buttons();
        GE.text_render("CS:", center_width + 1290, center_height + 260);
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
    }

    if (choose_galaxy_background_window == true)
        choose_galaxy_background();

    if (saveloadexit_window == true)
    {
        SaveLoadExit();
        if (savetoagame == true)
        {
            GE.text_render("X", center_width + 1518, center_height + 279);
        }
        if (initializers == true)
        {
            GE.text_render("X", center_width + 1518, center_height + 239);
        }
        if (setting_hyperlanes == true)
        {
            GE.text_render("X", center_width + 1518, center_height + 319);
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
        Settings();
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
        
    if (galaxies_am > 0)
    {
        alpha1 = 252;
        left(alpha1);
        GE.text_render("- -", center_width + 20, center_height + 10);
        GE.text_render("- +", center_width + 20, center_height + 1040);
        GE.text_render("+ -", center_width + 1150, center_height + 10);
        GE.text_render("+ +", center_width + 1150, center_height + 1040);
        if (show_hyperlanes == true)
        {
            render_hyperlanes();
        }
        draw_galaxy();
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
}

void ThrowOutButtons()
{
    gButtons[6].setPosition(-1000, -1000);
    gButtons[7].setPosition(-1000, -1000);
    gButtons[8].setPosition(-1000, -1000);
    gButtons[9].setPosition(-1000, -1000);
    gButtons[10].setPosition(-1000, -1000);
    gButtons[11].setPosition(-1000, -1000);
    gButtons[12].setPosition(-1000, -1000);
    gButtons[13].setPosition(-1000, -1000);
    gButtons[15].setPosition(-1000, -1000);
    gButtons[16].setPosition(-1000, -1000);
    gButtons[17].setPosition(-1000, -1000);
    gButtons[18].setPosition(-1000, -1000);
    gButtons[19].setPosition(-1000, -1000);
    gButtons[20].setPosition(-1000, -1000);
    gButtons[21].setPosition(-1000, -1000);
    gButtons[22].setPosition(-1000, -1000);
    gButtons[28].setPosition(-1000, -1000);
    gButtons[29].setPosition(-1000, -1000);
    gButtons[30].setPosition(-1000, -1000);
    gButtons[31].setPosition(-1000, -1000);
    gButtons[50].setPosition(-1000, -1000);
    gButtons[51].setPosition(-1000, -1000);
    gButtons[52].setPosition(-1000, -1000);
    gButtons[53].setPosition(-1000, -1000);
    gButtons[54].setPosition(-1000, -1000);
    gButtons[55].setPosition(-1000, -1000);
    gButtons[56].setPosition(-1000, -1000);
    gButtons[60].setPosition(-1000, -1000);
    gButtons[61].setPosition(-1000, -1000);
    gButtons[62].setPosition(-1000, -1000);
    gButtons[98].setPosition(-1000, -1000);
    gButtons[99].setPosition(-1000, -1000);
    gButtons[100].setPosition(-1000, -1000);
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
    GE.text_render("Settings", center_width + 1500, center_height + 25);
    GE.text_render("Files&Exit", center_width + 1715, center_height + 90);
}

void No_space_found()
{
    gModulatedTexture.setAlpha(243);
    gModulatedTexture.render(center_width + 1620, center_height + 270, 250, 60);
    GE.text_render("Random failed", center_width + 1640, center_height + 290);
}