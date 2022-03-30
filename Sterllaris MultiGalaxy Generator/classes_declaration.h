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