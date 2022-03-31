bool edit = false;
bool pathsaved = false;
bool edit_patch = false;

bool choose_galaxy_background_window = false;
bool current_galaxies_window = false;
bool choose_galaxy_shape_window = false;
bool elipse_galaxy_window = false;
bool spiral_galaxy_window = false;
bool saveloadexit_window = false;
bool launchersettings_window = false;
bool empiresettings_window = false;
bool patchsettings_window = false;
bool settings_window = false;
bool random_window = false;


bool no_space_found = false;
bool failed_initializers = false;
bool disable_failed_galaxy_warn = false;
bool wrong_text = false;
bool disable_wrong_text_warn = false;
bool generate_multiple_leviathans = false;
bool initializers = false;
bool initializers_loaded = false;
bool hyperlanes_loaded = false;
bool setting_hyperlanes = false;
bool galaxy_canceled = false;

bool show_hyperlanes = false;

std::string appdata = getenv("APPDATA");
std::string constpath = appdata + "\\SMGGLocal";
std::string modfolderpath;
std::string pathget = "";


float PI = 3.1415;
float holderX, holderY;

int galaxies_am = 0;
int current_gal_id = NULL;
int mult = 0;
int min_hyperlane_am = 0,
    max_hyperlane_am = 0;

int sys_sum = 0;

// Empire variables
int empire_am = 0,
fallen_am = 0,
maruder_am = 0;
bool Empires_Random = false,
    savetoagame = false;
std::string marauder_init_tab[3] = {
    "marauder_1_1",
    "marauder_2_1",
    "marauder_3_1",
};
std::string empire_init_tab[6] = {
    "random_empire_init_01",
    "random_empire_init_02",
    "random_empire_init_03",
    "random_empire_init_04",
    "random_empire_init_05",
    "random_empire_init_06",
};
class fallen_empires {
public:
    std::string fallen_empire_init_tab[10] = {
    "smgg_fallen_1",
    "smgg_fallen_2",
    "smgg_fallen_3",
    "smgg_fallen_4",
    "smgg_fallen_5",
    "smgg_fallen_6",
    "smgg_fallen_7",
    "smgg_fallen_8",
    "smgg_fallen_9",
    "smgg_fallen_10",
    };
    bool exist[10];
};
fallen_empires C_fallen;
std::string mega_ruined_init_tab[4] = {
    "dyson_sphere_init_01",
    "science_nexus_init_01",
    "sentry_array_init_01",
    "ring_world_init_01",
};
class leviathans {
public:
    std::string name[8] = {
    "guardians_init_stellarites",
    "guardians_init_dragon",
    "guardians_init_horror",
    "guardians_init_dreadnought",
    "guardians_init_hive",
    "guardians_init_technosphere",
    "guardians_init_fortress",
    "guardians_init_wraith",
    };
    bool exist[8];
    std::string enclaves = {

    };
};
leviathans Class_lev;


//Temp --
int numArms;
float armSeparationDistance;
float armOffsetMax;
float rotationFactor;
float randomOffsetXY;

struct temp_gal
{
    int con_max;
    int con;
    int gal_id;
    int gal_x;
    int gal_y;
};
std::vector<temp_gal> v_temp;
// Temp Over
struct dist_id {
    int distance,
        from,
        to;
};
std::vector<dist_id> v_dist_id;

struct hyperlanes {
    int from;
    int to;
};
std::vector <std::vector<struct hyperlanes>> v_hyperlanes;

struct s_wave {
    int id;
};
std::vector <s_wave> wave;

struct system_data {
    int con_max;
    int con;
    int gal_id;
    int gal_x;
    int gal_y;
    bool inicjalizer = false;
    int init_type = 0;
    int init_number = 0;
    bool exported = false;
    bool blocked = false;
};
std::vector<std::vector <struct system_data>> v_system_data;
std::vector<system_data> v_system_data_copy;

std::string temp_star, temp_gsize, temp_cen_posX, temp_cen_posY, temp_max_hyp_dis;
struct galaxy_generation {
    std::string star,
        gsize,
        cen_posX,
        cen_posY,
        max_hyp_dis,
        numArms,
        armOffsetMax,
        rotationFactor,
        randomOffsetXY;
    int galtype,
        i_star,
        i_gsize,
        i_cen_posX,
        i_cen_posY,
        i_max_hyp_dis,
        i_numArms,
        empire_am,
        fallen_am,
        maruder_am;
    float   f_armOffsetMax,
        f_rotationFactor,
        f_randomOffsetXY,
        density;
    bool hyperlanes_generated = false;
    bool exported = false;
};
std::vector<galaxy_generation> v_galaxy_generation;


struct less_than_key
{
    inline bool operator() (const dist_id& struct1, const dist_id& struct2)
    {
        return (struct1.distance < struct2.distance);
    }
};