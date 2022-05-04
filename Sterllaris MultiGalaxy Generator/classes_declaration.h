#pragma once
// Button class

class c_init {
public:
    int random_sys, prev_star_sum = 0,
        dist, fallen_dist, leviathan_dist, marauder_dist;
    bool placed, specific_init, everything_filled;
    void initilizers();
    void min_together(int gal_id);
    void min_dist(int gal_id);
    void min_dist_specific(int gal_id, int min_distance, int init_id);
};
c_init Classinit;


class Chyperlanes {
public:
    struct hyperlanes {
        int link_number,
            from,
            to;
    };
    std::vector<hyperlanes> v_hyperlanes;
};
Chyperlanes Class_hyperlanes;

class C_systems_hyperlanes_manipulation {
public:
    bool edit_galaxies = false;
    bool edit_galaxies_loop = false;
    bool remove_galaxies = false;
    bool redraw_galaxies = false;
    bool remove_hyperlanes = false;
    bool redraw_hyperlanes = false;
};
C_systems_hyperlanes_manipulation CSHM;

class C_random_settings {
public:
    bool enable_circle = false,
        enable_spiral = false,
        enable_resizing = false,
        size_from_edited = false,
        size_to_edited = false,
        hyperlanes_max_length_from_edited = false,
        hyperlanes_max_length_to_edited = false,
        circle_stars_from_edited = false,
        circle_stars_to_edited = false,
        spiral_stars_from_edited = false,
        spiral_stars_to_edited = false,
        rotation_factor_edited = false,
        arm_amount_from_edited = false,
        arm_amount_to_edited = false,
        square_factor_edited = false,
        arm_max_width_from_edited = false,
        arm_max_width_to_edited = false,
        arm_random_width_from_edited = false,
        arm_random_width_to_edited = false,
        size_ratio_edited = false,
        arm_ratio_edited = false,
        arm_width_ratio_edited = false;
    int size_from,
        size_to,
        hyperlanes_max_length_from,
        hyperlanes_max_length_to,
        circle_stars_from,
        circle_stars_to,
        spiral_stars_from,
        spiral_stars_to,
        rotation_factor,
        arm_amount_from,
        arm_amount_to;
    float square_factor,
        arm_max_width_from,
        arm_max_width_to,
        arm_random_width_from,
        arm_random_width_to,
        size_ratio,
        arm_ratio,
        arm_width_ratio;
};

C_random_settings CRS;

class C_Edit {
public:
    bool star,
        gsize,
        posX,
        posY,
        max_hyp_dist,
        num_arms,
        arm_offset_max,
        random_arm_offset,
        rotation_factor;
};
C_Edit C_E;

class C_scroll {
public:
    bool scrolling = false;
    bool done = 0;
    int donex, doney, current_system, current_gal;
    bool box_open = false;
};
C_scroll C_S;

class Detailed_Generation {
public:
    bool remove_system = 0,
        add_system = 0,
        move_system = 0,
        remove_hyperlanes = 0,
        add_hyperlanes = 0,
        add_initializer = 0,
        remove_initializer = 0,
        add_initializer_player = 0,
        add_initializer_bot = 0,
        add_initializer_fallen = 0,
        add_initializer_marauder = 0,
        add_initializer_mega = 0,
        add_initializer_leviathan = 0,
        add_initializer_mods = 0;
    int previous_id = 0, player_am = 0;
    /*
    Detailed_Generation(bool con_remove_system, bool con_remove_hyperlanes, bool con_add_initializer, bool con_remove_initializer)
    {
        remove_system = con_remove_system,
        remove_hyperlanes = con_remove_hyperlanes,
        add_initializer = con_add_initializer,
        remove_initializer = con_remove_initializer;
    }
    */
    void false_all_bools()
    {
        remove_system = 0,
            add_system = 0,
            move_system = 0,
            remove_hyperlanes = 0,
            add_hyperlanes = 0,
            add_initializer = 0,
            remove_initializer = 0;
    }
    void false_initializers()
    {
        add_initializer_player = 0,
        add_initializer_bot = 0,
        add_initializer_fallen = 0,
        add_initializer_marauder = 0,
        add_initializer_mega = 0,
        add_initializer_leviathan = 0,
        add_initializer_mods = 0;
    }

    std::bitset<8> bits_mega{ 0b0000'0000 };
    std::bitset<8> bits_leviathan{ 0b0000'0000 };

    void reset_bits()
    {
        for (int i = 0; i < 8; ++i)
        {
            bits_mega.reset(i);
            bits_leviathan.reset(i);
        }
    }
    void set_default_button();
};
Detailed_Generation Det_Gen;

class File_Operation {
public:
    struct local_maps {
        std::string map_steam;
        std::string map_local;
        std::string map_name;
        bool enabled = 0;
    };
    std::vector <local_maps> v_local_maps;
    std::string mapname = "MultiGalaxy";
    bool mapsloaded = false;
    bool mapname_input_on = false;
    int top_showed = 0;

    void create_folder();
    void map_name();
    void maps_menu();
    //void load_files_from_steammod_folder();
    void load_maps();
    void save_maps();
    void add_map();
    void export_file(std::string path);
    void import_map(std::string path);
    std::string slash_to_backslashes(std::string text);
    std::string backspace_to_under(std::string text);
    std::string under_to_backspace(std::string text);
    //void overwrite_data_map();
    //PWSTR SaveMap();
};
File_Operation F_O;