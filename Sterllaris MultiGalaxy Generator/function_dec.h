#pragma once
float RandFloat();
void debug();

// Rendering loop
void base();
void layer_1();
Uint8 alpha1, alpha2, alpha3;
void background();
void left(Uint8 alpha);
void top_menu(Uint8 alpha);
void right_panel(Uint8 alpha);
void buttons_render();
void rerender();
void elipse_background();
void spiral_background();
void current_galaxies_buttons();
void draw_galaxy();
void choose_galaxy_background();
void SaveLoadExit();
void EmpireSettings();
void Settings();
void LauncherSettings();
void RandomSettings();
void PatchSettings();
void No_space_found();
void render_hyperlanes();



void save_as(std::string text, int target_id);

void ThrowOutButtons();
void DisableOtherWindows();


// One time rendering
void add_galaxy_elipse();
void add_galaxy_spiral();
void edit_button(int mode, int gal_id);
void edit_circle(int mode, int gal_id);
void edit_spiral(int mode, int gal_id);

// Generators
void generate_elipse(int gal_id);
void generate_spiral(int gal_id);
void generate_center(int gal_id);
void set_center(int gal_id);
void remove_galaxy(int gal_id);
void remove_galaxy_full(int gal_id);
void clear_map();
void redraw_galaxy();
void random_generator();
void void_dens();
void link(int mode, int gal_id);
void link_wave(int mode, int gal_id, int system_id);
void link_wave_sub(int mode, int gal_id, int wave_start);
void link_wave_save(int mode, int gal_id, int i);
int link_wave_check(int mode, int gal_id, int mult, int j);
void check_systems(int mode, int gal_id);
void clear_hyperlanes_data();
void remove_hyperlanes(int mode, int gal_id);

// File operation
void firstrunsettings();
void firstrunbackground();
void firstrun_create_directory();
void osfile(std::string path);
void savepath();
void loadsettings();
void SaveSettings();
PWSTR LoadFile();
PWSTR SaveFile();
void LoadRandomDefaultSettings();
void RandomDefaultSettings();
void LoadRandomSettings();
void SaveRandomSettings();

void HideConsole();
void ShowConsole();