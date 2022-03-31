#pragma once
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