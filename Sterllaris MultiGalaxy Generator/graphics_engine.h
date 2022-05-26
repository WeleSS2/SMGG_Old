#pragma once
// Graphical variables e.t.c --------------------------------------------------------------------------------------------------------------------------------------

void rerender();
void draw_galaxy();


// Screen size
int SCREEN_WIDTH = 0;
int SCREEN_HEIGHT = 0;
int center_width, center_height;

class LTexture
{
public:
    LTexture();

    ~LTexture();

    bool loadFromFile(std::string path);

#if defined(SDL_TTF_MAJOR_VERSION)
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

    void free();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    void setBlendMode(SDL_BlendMode blending);

    void setAlpha(Uint8 alpha);

    void render(int x, int y, int w, int h, SDL_Rect* clip = NULL);
    void render_mode(int mode, SDL_Texture* texture, int x, int y, int w, int h, SDL_Rect* clip);
    void renderButton(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void renderButtonDynamicSize(int x, int y, int w, int h, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void renderButtonafterText(int id, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int getWidth();
    int getHeight();

private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};
LTexture LT;

class Graphics_Engine
{
public:
    void handleKeyboardEvent(SDL_Event& e);
    void render_checkbox(int button_id, int button_x, int button_y, int width, int height);
    void render_checkbox_v2(int mode, int button_id, int button_x, int button_y, int width, int height);
    void text_input(int x, int y, int target_string_id);
    void text_render(std::string tekst, int x, int y);
    void text_render_v2(std::string tekst, int x, int y);
    void render_button_with_text(int mode, int button_id, int button_x, int button_y, std::string tekst, int text_x, int text_y);
    void render_button_with_text_dynamic(int mode, int button_id, int button_x, int button_y, int width, int height, std::string tekst, int text_x, int text_y);
    void line(int start_x, int start_y, int end_x, int end_y);
    void text_with_button(int button_id, std::string tekst, int x, int y);
    void click_effect_remove(int button_id);
    void system_box_info(int i, int offsetx, int offsety);

    void wrong_text_input(int x, int y, int id);
    bool isNumber(const std::string& str);
    bool isNumber_not_negative(const std::string& str);
    void render_color_box(int R, int G, int B, int x, int y, int w, int h);
    

    void scrolling_function();
    int hyperlanes_lightness = 13;
    int system_box_x = ( -200 * scrolling_level), system_box_y = ( -200 * scrolling_level);
};
Graphics_Engine GE;

class Detailed_System_Edit {
public:
    void menu();
    void add_initializer_menu();
    void add_initializer_mega();
    void add_initializer_leviathan();
};
Detailed_System_Edit D_S_E;

// Buttons

const int BUTTON_WIDTH = 180;
const int BUTTON_WIDTH_SMALL = 45;
const int BUTTON_HEIGHT = 45;

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_BIG = 0,
    BUTTON_SPRITE_MOUSE_BIG_PRESSED = 1,
    BUTTON_SPRITE_MOUSE_SMALL = 2,
    BUTTON_SPRITE_MOUSE_SMALL_PRESSED = 3,
    BUTTON_SPRITE_TOTAL = 4
};


// Button class
class LButton
{
public:
    LButton();
    void setPosition(int x, int y);
    void handleEvent(SDL_Event* e, int id);
    void handleSystemButtonEvent(SDL_Event& e, int i, int j);
    void handle_D_S_E_ButtonEvent(SDL_Event& e, int i);
    void handleMap_Checkbox_Buttons(SDL_Event& e, int i);
    void render();
    void renderDynamic(int mode, int w, int h);
    void mrender();
    LButtonSprite mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;

private:
    SDL_Point mPosition;
};
std::vector<LButton> D_S_E_Buttons;
std::vector<LButton> gButtons;
std::vector <std::vector <LButton>> SystemButtons;
std::vector<LButton> Map_Checkbox_Buttons;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;
SDL_Texture* gBackground = NULL;

LTexture gModulatedTexture;

SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
LTexture gButtonSpriteSheetTexture;
LTexture mButtonSpriteSheetTexture;

LTexture photo_Text;
// Font mng
SDL_Color SilverTextColor = { 172, 172, 172, 0xFF };
TTF_Font* gFont = NULL;

LTexture gPromptTextTexture;
LTexture gInputTextTexture;
LTexture gCheckboxTexture;

//========================================================================================================================
LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

void LTexture::render(int x, int y, int w, int h, SDL_Rect* clip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, w, h };

    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

void LTexture::renderButton(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{ 
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void LTexture::renderButtonDynamicSize(int x, int y, int w, int h, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, w, h };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = w;
        renderQuad.h = h;
    }

    //Render to screen
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void LTexture::renderButtonafterText(int id, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
    gButtons[id].setPosition(x + renderQuad.w - 3, y - 1);
    SDL_SetRenderDrawColor(gRenderer, 177, 177, 177, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(gRenderer, center_width + x + renderQuad.w, center_height + y + 30, center_width + x + renderQuad.w + 50, center_height + y + 30);
}

bool LTexture::loadFromFile(std::string path)
{
    free();

    SDL_Texture* newTexture = NULL;

    //Load image
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    std::cout << path.c_str() << std::endl;
    if (loadedSurface == NULL)
    {
        std::cout << "Error in LTexture::loadFromFile" << std::endl;
    }
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

        if (newTexture == NULL)
        {
            std::cout << "Error in loadFromFile -> Create texture from surface" << std::endl;
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);

}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if (textSurface != NULL)
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (mTexture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
    else
    {
        //printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }


    //Return success
    return mTexture != NULL;
}
#endif

// Button ==============================================================

LButton::LButton()
{
    mPosition.x = 0;
    mPosition.y = 0;
}

void LButton::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}


void LButton::render()
{
    gButtonSpriteSheetTexture.renderButton(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
}

void LButton::renderDynamic(int mode, int w, int h)
{
    if (mode == 0)
    {
        gButtonSpriteSheetTexture.renderButtonDynamicSize(mPosition.x, mPosition.y, w, h, &gSpriteClips[mCurrentSprite]);
    }
}
// Public ---------------------------------------------------

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            std::cout << "Filtering to linear not enabled" << std::endl;
        //Create window
        gWindow = SDL_CreateWindow("Stellaris MultiGalaxy Generator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, 0, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
                std::cout << "Error in init - > gRenderer" << std::endl;

            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                //Get window surface
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    // Load Background
    gBackground = loadTexture("graphics/backgroundS.png");

    if (!gModulatedTexture.loadFromFile("graphics/black1.png"))
    {
        std::cout << "Error in loadFromFile black1.png" << std::endl;
        success = false;
    }
    else
    {
        gModulatedTexture.setBlendMode(SDL_BLENDMODE_BLEND);
    }


    if (!gCheckboxTexture.loadFromFile("graphics/box.png"))
    {
        std::cout << "Error in loadFromFile box.png" << std::endl;
        success = false;
    }
    else
    {
        gCheckboxTexture.setBlendMode(SDL_BLENDMODE_BLEND);
    }



    //Load sprites
    if (!mButtonSpriteSheetTexture.loadFromFile("graphics/ButtonSmall.png"))
    {
        printf("Failed to load small button sprite texture!\n");
        success = false;
    }
    if (!gButtonSpriteSheetTexture.loadFromFile("graphics/buttonBIG.png"))
    {
        printf("Failed to load button sprite texture!\n");
        success = false;
    }
    //Set sprites
    for (int i = 0; i < 4; ++i)
    {

        gSpriteClips[i].x = 0;
        gSpriteClips[i].y = 0;
        gSpriteClips[i].h = BUTTON_HEIGHT;
        if (i == 0)
        {
            gSpriteClips[i].w = BUTTON_WIDTH;
        }
        else if (i == 1)
        {
            gSpriteClips[i].y = 45;
            gSpriteClips[i].w = BUTTON_WIDTH;
        }
        
    }

    // Create buttons holders

    for (int i = 0; i <= 1000; ++i)
    {
        gButtons.emplace_back();
    }
    for (int i = 0; i < 500; ++i)
    {
        D_S_E_Buttons.emplace_back();
    }

    gButtons[0].setPosition(center_width + 1245, center_height + 20);
    gButtons[1].setPosition(center_width + 1245, center_height + 85);
    gButtons[2].setPosition(center_width + 1465, center_height + 20);
    gButtons[3].setPosition(center_width + 1465, center_height + 85);
    gButtons[4].setPosition(center_width + 1690, center_height + 20);
    gButtons[5].setPosition(center_width + 1690, center_height + 85);

    gFont = TTF_OpenFont("graphics/Orbi.ttf", 24);
    if (gFont == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }


    //Nothing to load
    return success;
}


SDL_Texture* loadTexture(std::string path)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

void close()
{
    //Free loaded image
    gPromptTextTexture.free();
    gInputTextTexture.free();
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;


    gButtonSpriteSheetTexture.free();
    //Destroy window	
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Graphics_Engine::text_input(int x, int y, int target_string_id)
{
    bool quit = false;
    SDL_Event e;

    //The current input text.
    std::string inputText = "";
    gInputTextTexture.loadFromRenderedText(inputText.c_str(), SilverTextColor);

    //Enable text input
    SDL_StartTextInput();

    rerender();
    while (!quit)
    {

        SDL_Delay(100);
        bool renderText = false;

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RETURN)
                {
                    quit = true;
                }
                if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
                {
                    inputText.pop_back();
                    renderText = true;
                    rerender();
                }
                else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
                {
                    SDL_SetClipboardText(inputText.c_str());
                }
                else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
                {
                    inputText = SDL_GetClipboardText();
                    renderText = true;
                }
            }
            //Special text input event
            else if (e.type == SDL_TEXTINPUT)
            {
                if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V')))
                {
                    inputText += e.text.text;
                    renderText = true;
                }
            }
        }

        //Rerender text
        if (renderText)
        {
            if (inputText != "")
            {
                gInputTextTexture.loadFromRenderedText(inputText.c_str(), SilverTextColor);
            }
            else
            {
                gInputTextTexture.loadFromRenderedText(" ", SilverTextColor);
            }
        }
        //Render text textures
        gInputTextTexture.renderButton(x, y);
        GE.render_color_box(255, 255, 255, x - 3, y + 4, 1, 24);
        SDL_RenderPresent(gRenderer);
    }
    if (inputText == "")
    {
        text_input(x, y, target_string_id);
    }
    else
    {
        switch (target_string_id)
        {
        case 0:
            isNumber_not_negative(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 1:
            //if (std::stoi(inputText) < 500)
            {
                isNumber_not_negative(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            //else
            {
                //wrong_text_input(x, y, target_string_id);
            }
            break;
        case 2:
            if (isNumber(inputText))
            {
                ((std::stoi(inputText) < 500) && (std::stoi(inputText) > -500)) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 3:
            if (isNumber(inputText))
            {
                ((std::stoi(inputText) < 500) && (std::stoi(inputText) > -500)) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 4:
            isNumber_not_negative(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 5:
            isNumber(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 6:
            //if (isNumber(inputText))
            {
                (std::stof(inputText) > 0.01 && std::stof(inputText) < 3) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            //else
            {
                //wrong_text_input(x, y, target_string_id);
            }
            break;
        case 7:
            //if (std::stof(inputText) > 0.01 && std::stof(inputText) < 0.9999)
            {
                isNumber(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            //else
            {
                //wrong_text_input(x, y, target_string_id);
            }
            break;
        case 8:
            isNumber(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;

        case 20:
            isNumber_not_negative(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 21:
            isNumber_not_negative(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 22:
            isNumber_not_negative(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 30:
            save_as(inputText, target_string_id);
            break;
        case 55:
            isNumber_not_negative(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 56:
            isNumber_not_negative(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 98:
            save_as(inputText, target_string_id);
            break;
        case 99:
            isNumber_not_negative(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 100:
            pathget = inputText;
            break;
        case 113:
            if (isNumber_not_negative(inputText))
            {
                (std::stoi(inputText) > 25 && std::stoi(inputText) < 500) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 114:
            if (isNumber_not_negative(inputText))
            {
                (std::stoi(inputText) > 25 && std::stoi(inputText) < 500) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 115:
            if (isNumber_not_negative(inputText))
            {
                (std::stoi(inputText) > 0) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 116:
            if (isNumber_not_negative(inputText))
            {
                (std::stoi(inputText) > 0) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 117:
            if (isNumber_not_negative(inputText))
            {
                (std::stoi(inputText) > 0) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 118:
            if (isNumber_not_negative(inputText))
            {
                (std::stoi(inputText) > 0) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 119:
            if (isNumber_not_negative(inputText))
            {
                (std::stoi(inputText) > 0) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 120:
            if (isNumber_not_negative(inputText))
            {
                (std::stoi(inputText) > 0) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 121:
            //if (std::stoi(inputText) > 0)
            {
                isNumber(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            //else
            {
                //wrong_text_input(x, y, target_string_id);
            }
            break;
        case 122:
            if (isNumber_not_negative(inputText))
            {
                (std::stof(inputText) > 0.01 && std::stof(inputText) < 3) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 123:
            if (isNumber_not_negative(inputText))
            {
                (std::stof(inputText) > 0.01 && std::stof(inputText) < 3) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 124:
            if (isNumber_not_negative(inputText))
            {
                (std::stof(inputText) > 0.01 && std::stof(inputText) < 0.9999) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 125:
            if (isNumber_not_negative(inputText))
            {
                (std::stof(inputText) > 0.01 && std::stof(inputText) < 0.9999) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 126:
            if (isNumber_not_negative(inputText))
            {
                (std::stoi(inputText) > 0) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 128:
            if (isNumber_not_negative(inputText))
            {
                (std::stoi(inputText) > 0) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 129:
            if (isNumber_not_negative(inputText))
            {
                (std::stoi(inputText) > 0) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 130:
            if (isNumber_not_negative(inputText))
            {
                (std::stof(inputText) > 0) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 131:
            if (isNumber_not_negative(inputText))
            {
                (std::stof(inputText) > 0) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 132:
            if (isNumber_not_negative(inputText))
            {
                (std::stof(inputText) > 0) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        }

        if (target_string_id != 100)
        {
            gPromptTextTexture.loadFromRenderedText(inputText, SilverTextColor);
            gPromptTextTexture.renderButton(x, y);
        }
        SDL_RenderPresent(gRenderer);

        SDL_StopTextInput();

        SDL_RenderClear(gRenderer);
        rerender();
    }
}

bool Graphics_Engine::isNumber(const std::string& str)
{
    return str.find_first_not_of("0123456789.-") == std::string::npos;
}

bool Graphics_Engine::isNumber_not_negative(const std::string & str)
{
    return str.find_first_not_of("0123456789.") == std::string::npos;
}

void Graphics_Engine::text_render(std::string tekst, int x, int y)
{
    gPromptTextTexture.loadFromRenderedText(tekst, SilverTextColor);
    gPromptTextTexture.renderButton(x, y);
}

void Graphics_Engine::text_render_v2(std::string tekst, int x, int y)
{
    gPromptTextTexture.loadFromRenderedText(tekst, SilverTextColor);
    gPromptTextTexture.renderButton(center_width + x, center_height + y);
}

void Graphics_Engine::text_with_button(int button_id, std::string tekst, int x, int y)
{
    gPromptTextTexture.loadFromRenderedText(tekst, SilverTextColor);
    gPromptTextTexture.renderButtonafterText(button_id, center_width + x, center_height + y);
}

void Graphics_Engine::wrong_text_input(int x, int y, int id)
{
    wrong_text = true;
    rerender();
    wrong_text = false;
    rerender();
    text_input(x, y, id);
}

void save_as(std::string inputText, int id)
{
    switch (id)
    {
    case 0:
        v_galaxy_generation[current_gal_id].star = inputText;
        v_galaxy_generation[current_gal_id].i_star = std::stoi(v_galaxy_generation[current_gal_id].star);
        //std::cout << v_galaxy_generation[current_gal_id].star << "   " << v_galaxy_generation[current_gal_id].i_star << std::endl;
        break;
    case 1:
        v_galaxy_generation[current_gal_id].gsize = inputText;
        v_galaxy_generation[current_gal_id].i_gsize = std::stoi(v_galaxy_generation[current_gal_id].gsize);
        break;
    case 2:
        v_galaxy_generation[current_gal_id].cen_posX = inputText;
        v_galaxy_generation[current_gal_id].i_cen_posX = std::stoi(v_galaxy_generation[current_gal_id].cen_posX);
        break;
    case 3:
        v_galaxy_generation[current_gal_id].cen_posY = inputText;
        v_galaxy_generation[current_gal_id].i_cen_posY = std::stoi(v_galaxy_generation[current_gal_id].cen_posY);
        break;
    case 4:
        v_galaxy_generation[current_gal_id].max_hyp_dis = inputText;
        v_galaxy_generation[current_gal_id].i_max_hyp_dis = std::stoi(v_galaxy_generation[current_gal_id].max_hyp_dis);
        break;
    case 5:
        v_galaxy_generation[current_gal_id].numArms = inputText;
        v_galaxy_generation[current_gal_id].i_numArms = std::stoi(v_galaxy_generation[current_gal_id].numArms);
        break;
    case 6:
        v_galaxy_generation[current_gal_id].armOffsetMax = inputText;
        v_galaxy_generation[current_gal_id].f_armOffsetMax = std::stof(v_galaxy_generation[current_gal_id].armOffsetMax);
        break;
    case 7:
        v_galaxy_generation[current_gal_id].randomOffsetXY = inputText;
        v_galaxy_generation[current_gal_id].f_randomOffsetXY = std::stof(v_galaxy_generation[current_gal_id].randomOffsetXY);

        break;
    case 8:
        v_galaxy_generation[current_gal_id].rotationFactor = inputText;
        v_galaxy_generation[current_gal_id].f_rotationFactor = std::stof(v_galaxy_generation[current_gal_id].rotationFactor);
        break;

    case 20:
        empire_am = std::stoi(inputText);
        break;
    case 21:
        fallen_am = std::stoi(inputText);
        break;
    case 22:
        maruder_am = std::stoi(inputText);
        break;
    case 30:
        break;
    case 55:
        min_hyperlane_am = std::stoi(inputText);
        break;
    case 56:
        max_hyperlane_am = std::stoi(inputText);
        break;
    case 98:
        F_O.mapname = inputText;
        map_name_bool = false;
        break;
    case 99:
        current_gal_id = std::stoi(inputText);
        if ((current_gal_id > v_galaxy_generation.size() - 1))
        {
            GE.wrong_text_input(center_width + 1320, center_height + 510, 99);
        }
        break;
    case 100:
        pathget = inputText;
        break;
    case 113:
        CRS.size_from = std::stoi(inputText);
        break;
    case 114:
        CRS.size_to = std::stoi(inputText);
        break;
    case 115:
        CRS.hyperlanes_max_length_from = std::stoi(inputText);
        break;
    case 116:
        CRS.hyperlanes_max_length_to = std::stoi(inputText);
        break;
    case 117:
        CRS.circle_stars_from = std::stoi(inputText);
        break;
    case 118:
        CRS.circle_stars_to = std::stoi(inputText);
        break;
    case 119:
        CRS.spiral_stars_from = std::stoi(inputText);
        break;
    case 120:
        CRS.spiral_stars_to = std::stoi(inputText);
        break;
    case 121:
        CRS.square_factor = std::stof(inputText);
        break;
    case 122:
        CRS.arm_max_width_from = std::stof(inputText);
        break;
    case 123:
        CRS.arm_max_width_to = std::stof(inputText);
        break;
    case 124:
        CRS.arm_random_width_from = std::stof(inputText);
        break;
    case 125:
        CRS.arm_random_width_to = std::stof(inputText);
        break;
    case 126:
        CRS.rotation_factor = std::stoi(inputText);
        break;
    case 128:
        CRS.arm_amount_from = std::stoi(inputText);
        break;
    case 129:
        CRS.arm_amount_to = std::stoi(inputText);
        break;
    case 130:
        CRS.size_ratio = std::stof(inputText);
        break;
    case 131:
        CRS.arm_ratio = std::stof(inputText);
        break;
    case 132:
        CRS.arm_width_ratio = std::stof(inputText);
        break;
    }
    if ((id < 9) && (edit))
    {
        redraw_galaxy();
        rerender();
    }
    rerender();
}

void Graphics_Engine::render_button_with_text(int mode, int button_id, int button_x, int button_y, std::string tekst, int text_x, int text_y)
{ 
    if (mode < 10)
    {
        gButtons[button_id].setPosition(center_width + button_x, center_height + button_y);
        if (mode == 0)
        {
            gButtons[button_id].render();
        }
        else if (mode == 1)
        {
            
        }
    }
    else if ((mode >= 10) && (mode < 20))
    {
        D_S_E_Buttons[button_id].setPosition(center_width + button_x, center_height + button_y);
        D_S_E_Buttons[button_id].render();
    }
    text_render(tekst, center_width + text_x, center_height + text_y);
}

void Graphics_Engine::render_button_with_text_dynamic(int mode, int button_id, int button_x, int button_y, int width, int height, std::string tekst, int text_x, int text_y)
{
    if (mode < 10)
    {
        gButtons[button_id].setPosition(center_width + button_x, center_height + button_y);
        if (mode == 0)
        {
            gButtons[button_id].renderDynamic(0, width, height);
        }
        else if (mode == 1)
        {

        }
    }
    else if ((mode >= 10) && (mode < 20))
    {
        D_S_E_Buttons[button_id].setPosition(center_width + button_x, center_height + button_y);
        D_S_E_Buttons[button_id].renderDynamic(0, width, height);
    }
    text_render(tekst, center_width + text_x, center_height + text_y);
}

void Graphics_Engine::render_checkbox(int button_id, int button_x, int button_y, int width, int height)
{
    gButtons[button_id].setPosition(center_width + button_x, center_height + button_y);
    gCheckboxTexture.render(center_width + button_x , center_height + button_y, width, height);
}

void Graphics_Engine::render_checkbox_v2(int mode, int button_id, int button_x, int button_y, int width, int height)
{
    if (mode == 1)
    {
        gButtons[button_id].setPosition(center_width + button_x, center_height + button_y);
        gCheckboxTexture.render(center_width + button_x, center_height + button_y, width, height);
    }
    else if (mode == 2)
    {
        Map_Checkbox_Buttons[button_id].setPosition(center_width + button_x, center_height + button_y);
    }
}

void render_hyperlanes()
{
    //std::cout << galaxies_am << std::endl;
        for (int i = 0; i < galaxies_am; i++)
        {
            //if (v_galaxy_generation[i].hyperlanes_generated == true)
            {
                if (v_hyperlanes.size() != 0)
                {
                    if (v_hyperlanes[i].size() != 0)
                    {
                        for (int j = 0; j < v_hyperlanes[i].size(); j++)
                        {
                            if (v_hyperlanes[i][j].size() != 0)
                            {
                                for (int z = 0; z < v_hyperlanes[i][j].size(); z++)
                                {
                                    SDL_SetRenderDrawColor(gRenderer, 3 * GE.hyperlanes_lightness, 4 * GE.hyperlanes_lightness, 4 * GE.hyperlanes_lightness, SDL_ALPHA_OPAQUE);
                                    SDL_RenderDrawLine(gRenderer, center_width + v_system_data[i][v_hyperlanes[i][j][z].from].gal_x + 550, center_width + v_system_data[i][v_hyperlanes[i][j][z].from].gal_y + 550, center_height + v_system_data[i][v_hyperlanes[i][j][z].to].gal_x + 550, center_height + v_system_data[i][v_hyperlanes[i][j][z].to].gal_y + 550);
                                }
                            }
                        }
                    }
                }
            }
        }
}

void Graphics_Engine::line(int start_x, int start_y, int end_x, int end_y)
{
    SDL_SetRenderDrawColor(gRenderer, 122, 122, 122, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(gRenderer, start_x, start_y, end_x, end_y);
}

void Graphics_Engine::scrolling_function()
{
    if (!C_S.done)
    {
        SDL_GetMouseState(&C_S.donex, &C_S.doney);
    }
    for (int i = 0; i < SystemButtons.size(); i++)
    {
            if (v_hyperlanes.size() != 0)
            {
                if (v_hyperlanes[i].size() != 0)
                {
                    for (int j = 0; j < v_hyperlanes[i].size(); j++)
                    {
                        for (int z = 0; z < v_hyperlanes[i][j].size(); z++)
                        {
                            if ((center_width + ((v_system_data[i][v_hyperlanes[i][j][z].from].gal_x - (C_S.donex - 550)) * scrolling_level) + 550 > -50)
                                && (center_width + ((v_system_data[i][v_hyperlanes[i][j][z].from].gal_x - (C_S.donex - 550)) * scrolling_level) + 550 < 1199))
                            {
                                SDL_SetRenderDrawColor(gRenderer, 3 * GE.hyperlanes_lightness, 4 * GE.hyperlanes_lightness, 4 * GE.hyperlanes_lightness, SDL_ALPHA_OPAQUE);
                                SDL_RenderDrawLine(gRenderer,
                                    center_width + ((v_system_data[i][v_hyperlanes[i][j][z].from].gal_x - (C_S.donex - 550)) * scrolling_level) + 550,
                                    center_width + ((v_system_data[i][v_hyperlanes[i][j][z].from].gal_y - (C_S.doney - 550)) * scrolling_level) + 550,
                                    center_height + ((v_system_data[i][v_hyperlanes[i][j][z].to].gal_x - (C_S.donex - 550)) * scrolling_level) + 550,
                                    center_height + ((v_system_data[i][v_hyperlanes[i][j][z].to].gal_y - (C_S.doney - 550)) * scrolling_level) + 550);
                            }
                        }
                    }
                }
            }
        for (int j = 0; j < SystemButtons[i].size(); j++)
        {
            //std::cout << v_system_data[i][j].gal_x + 550 << " " << x << std::endl;
            int x_base_formula{ (center_width + ((v_system_data[i][j].gal_x - (C_S.donex - 550)) * scrolling_level))},
                y_base_formula{ (center_height + ((v_system_data[i][j].gal_y - (C_S.doney - 550)) * scrolling_level))};
            int limit = 100;
            if (((x_base_formula + 550)> -50)
                && ((x_base_formula + 550) < 1199))
            {
                if (((y_base_formula + 550) > -50)
                    && ((y_base_formula + 550) < 1199))
                {
                    SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 0);
                    SDL_Rect Rect;
                    Rect.x = x_base_formula + 550 - scrolling_level;
                    Rect.y = y_base_formula + 550 - scrolling_level;
                    Rect.w = (scrolling_level * 2 - 1);
                    Rect.h = (scrolling_level * 2 - 1);
                    SDL_RenderDrawRect(gRenderer, &Rect);
                    SystemButtons[i][j].setPosition(
                        x_base_formula + 548,
                        y_base_formula + 548
                    );
                    if (show_initializers)
                    {
                        if (v_system_data[i][j].inicjalizer)
                        {
                            int static_X_cord_ini_boxes{ x_base_formula + 549 - scrolling_level },
                                static_Y_cord_ini_boxes{ y_base_formula + 549 - scrolling_level },
                                box_width = (scrolling_level * 2) + 2,
                                box_height = (scrolling_level * 2) + 2;
                            if (v_system_data[i][j].init_type == 1)
                            {

                                GE.render_color_box(255, 170, 170, static_X_cord_ini_boxes, static_Y_cord_ini_boxes, box_width, box_height);
                            }
                            else if (v_system_data[i][j].init_type == 2)
                            {
                                GE.render_color_box(255, 0, 255, static_X_cord_ini_boxes, static_Y_cord_ini_boxes, box_width, box_height);
                            }
                            else if (v_system_data[i][j].init_type == 3)
                            {
                                GE.render_color_box(255, 81, 0, static_X_cord_ini_boxes, static_Y_cord_ini_boxes, box_width, box_height);
                            }
                            else if (v_system_data[i][j].init_type == 4)
                            {
                                GE.render_color_box(0, 255, 255, static_X_cord_ini_boxes, static_Y_cord_ini_boxes, box_width, box_height);
                            }
                            else if (v_system_data[i][j].init_type == 5)
                            {
                                GE.render_color_box(255, 0, 0, static_X_cord_ini_boxes, static_Y_cord_ini_boxes, box_width, box_height);
                            }
                            else if (v_system_data[i][j].init_type == 10)
                            {
                                GE.render_color_box(0, 255, 0, static_X_cord_ini_boxes, static_Y_cord_ini_boxes, box_width, box_height);
                            }
                            else if (v_system_data[i][j].init_type == 99)
                            {
                                GE.render_color_box(122, 122, 122, static_X_cord_ini_boxes, static_Y_cord_ini_boxes, box_width, box_height);
                            }
                            else if(db.debug_initializers)
                            {
                                GE.render_color_box(255, 255, 255, static_X_cord_ini_boxes, static_Y_cord_ini_boxes, box_width, box_height);
                            }
                        }
                    }
                }
            }
        }
        if (C_S.box_open)
        {

            gModulatedTexture.setAlpha(233);
            if (GE.system_box_y > 750)
            {
                if (GE.system_box_x > 850)
                {
                    system_box_info(i, 380, 300);
                }
                else
                {
                    system_box_info(i, 0, 300);
                }

            }
            else
            {
                if (GE.system_box_x > 850)
                {
                    system_box_info(i, 380, 0);
                }
                else
                {
                    system_box_info(i, 0, 0);
                }
            }
        }
    }
}
/*
void Graphics_Engine::scrolling_function()
{
    if (!C_S.done)
    {
        SDL_GetMouseState(&C_S.donex, &C_S.doney);
    }
    for (int i = 0; i < SystemButtons.size(); i++)
    {
        if (v_galaxy_generation[i].hyperlanes_generated == true)
        {
            if (v_hyperlanes.size() != 0)
            {
                if (v_hyperlanes[i].size() != 0)
                {
                    for (int j = 0; j < v_hyperlanes[i].size(); j++)
                    {
                        for (int z = 0; z < v_hyperlanes[i][j].size(); z++)
                        {
                            if ((center_width + ((v_system_data[i][v_hyperlanes[i][j][z].from].gal_x - (C_S.donex - 550)) * scrolling_level) + 550 > -50)
                                && (center_width + ((v_system_data[i][v_hyperlanes[i][j][z].from].gal_x - (C_S.donex - 550)) * scrolling_level) + 550 < 1199))
                            {
                                SDL_SetRenderDrawColor(gRenderer, 3 * GE.hyperlanes_lightness, 4 * GE.hyperlanes_lightness, 4 * GE.hyperlanes_lightness, SDL_ALPHA_OPAQUE);
                                SDL_RenderDrawLine(gRenderer,
                                    center_width + ((v_system_data[i][v_hyperlanes[i][j][z].from].gal_x - (C_S.donex - 550)) * scrolling_level) + 550,
                                    center_width + ((v_system_data[i][v_hyperlanes[i][j][z].from].gal_y - (C_S.doney - 550)) * scrolling_level) + 550,
                                    center_height + ((v_system_data[i][v_hyperlanes[i][j][z].to].gal_x - (C_S.donex - 550)) * scrolling_level) + 550,
                                    center_height + ((v_system_data[i][v_hyperlanes[i][j][z].to].gal_y - (C_S.doney - 550)) * scrolling_level) + 550);
                            }
                        }
                    }
                }
            }
        }
        for (int j = 0; j < SystemButtons[i].size(); j++)
        {
            //std::cout << v_system_data[i][j].gal_x + 550 << " " << x << std::endl;
            int limit = 100;
            if ((center_width + ((v_system_data[i][j].gal_x - (C_S.donex - 550)) * scrolling_level) + 550 > -50) 
                && (center_width + ((v_system_data[i][j].gal_x - (C_S.donex - 550)) * scrolling_level) + 550 < 1199))
            {
                if ((center_width + ((v_system_data[i][j].gal_y - (C_S.doney - 550)) * scrolling_level) + 550 > -50) 
                    && (center_width + ((v_system_data[i][j].gal_y - (C_S.doney - 550)) * scrolling_level) + 550 < 1199))
                {
                    SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 0);
                    SDL_Rect Rect;
                    Rect.x = center_width + ((v_system_data[i][j].gal_x - (C_S.donex - 550)) * scrolling_level) + 548 - scrolling_level;
                    Rect.y = center_height + ((v_system_data[i][j].gal_y - (C_S.doney - 550)) * scrolling_level) + 548 - scrolling_level;
                    Rect.w = (scrolling_level * 2 - 1);
                    Rect.h = (scrolling_level * 2 - 1);
                    SDL_RenderDrawRect(gRenderer, &Rect);
                    SystemButtons[i][j].setPosition(
                        center_width + ((v_system_data[i][j].gal_x - (C_S.donex - 550)) * scrolling_level) + 548,
                        center_height + ((v_system_data[i][j].gal_y - (C_S.doney - 550)) * scrolling_level) + 548
                    );
                    if (show_initializers)
                    {
                        if (v_system_data[i][j].inicjalizer)
                        {
                            if (v_system_data[i][j].init_type == 1)
                            {

                                GE.render_color_box(255, 170, 170, ((v_system_data[i][j].gal_x - (C_S.donex - 550)) * scrolling_level) + 546 - scrolling_level, 
                                    ((v_system_data[i][j].gal_y - (C_S.doney - 550)) * scrolling_level) + 546 - scrolling_level,
                                    (scrolling_level * 2), (scrolling_level * 2));
                            }
                            else if (v_system_data[i][j].init_type == 2)
                            {
                                GE.render_color_box(255, 0, 255, ((v_system_data[i][j].gal_x - (C_S.donex - 550)) * scrolling_level) + 546 - scrolling_level, 
                                    ((v_system_data[i][j].gal_y - (C_S.doney - 550)) * scrolling_level) + 546 - scrolling_level, 
                                    (scrolling_level * 2), (scrolling_level * 2));
                            }
                            else if (v_system_data[i][j].init_type == 3)
                            {
                                GE.render_color_box(255, 81, 0, ((v_system_data[i][j].gal_x - (C_S.donex - 550)) * scrolling_level) + 546 - scrolling_level, 
                                    ((v_system_data[i][j].gal_y - (C_S.doney - 550)) * scrolling_level) + 546 - scrolling_level, 
                                    (scrolling_level * 2), (scrolling_level * 2));
                            }
                            else if (v_system_data[i][j].init_type == 4)
                            {
                                GE.render_color_box(0, 255, 255, ((v_system_data[i][j].gal_x - (C_S.donex - 550)) * scrolling_level) + 546 - scrolling_level, 
                                    ((v_system_data[i][j].gal_y - (C_S.doney - 550)) * scrolling_level) + 546 - scrolling_level, 
                                    (scrolling_level * 2), (scrolling_level * 2));
                            }
                            else if (v_system_data[i][j].init_type == 5)
                            {
                                GE.render_color_box(255, 0, 0, ((v_system_data[i][j].gal_x - (C_S.donex - 550)) * scrolling_level) + 546 - scrolling_level, 
                                    ((v_system_data[i][j].gal_y - (C_S.doney - 550)) * scrolling_level) + 546 - scrolling_level, 
                                    (scrolling_level * 2), (scrolling_level * 2));
                            }
                            else if (v_system_data[i][j].init_type == 10)
                            {
                                GE.render_color_box(0, 255, 0, ((v_system_data[i][j].gal_x - (C_S.donex - 550)) * scrolling_level) + 546 - scrolling_level, 
                                    ((v_system_data[i][j].gal_y - (C_S.doney - 550)) * scrolling_level) + 546 - scrolling_level, 
                                    (scrolling_level * 2), (scrolling_level * 2));
                            }
                        }
                    }
                }
            }
        }
        if (C_S.box_open)
        {
            
            gModulatedTexture.setAlpha(233);
            if (GE.system_box_y > 750)
            {
                if (GE.system_box_x > 850)
                {
                    system_box_info(i, 380, 300);
                }
                else
                {
                    system_box_info(i, 0, 300);
                }
                
            }
            else
            {
                if (GE.system_box_x > 850)
                {
                    system_box_info(i, 380, 0);
                }
                else 
                {
                    system_box_info(i, 0, 0);
                }
            }
        }
    }
}
*/

void Graphics_Engine::system_box_info(int i, int offsetX, int offsetY)
{
    //         (center_width + ((v_system_data[i][j].gal_x - (C_S.donex - 550)) * scrolling_level) + 550
    //gModulatedTexture.render(GE.system_box_x - offsetX, GE.system_box_y - offset, 380, 300);
    int static_X_cord{ (center_width + ((v_system_data[C_S.current_gal][C_S.current_system].gal_x - (C_S.donex - 550)) * scrolling_level) + 550) },
        static_Y_cord{ (center_width + ((v_system_data[C_S.current_gal][C_S.current_system].gal_y - (C_S.doney - 550)) * scrolling_level) + 550) };
    gModulatedTexture.render(static_X_cord - offsetX,
        static_Y_cord - offsetY,
        500, 300);
    GE.text_render_v2("Current system " + std::to_string(C_S.current_system), static_X_cord - offsetX + (2 * scrolling_level), static_Y_cord - offsetY + (2 * scrolling_level));
    GE.text_render_v2("X position " + std::to_string(v_system_data[C_S.current_gal][C_S.current_system].gal_x), static_X_cord - offsetX + (2 * scrolling_level), static_Y_cord - offsetY + 50);
    GE.text_render_v2("Y position " + std::to_string(v_system_data[C_S.current_gal][C_S.current_system].gal_y), static_X_cord - offsetX + (2 * scrolling_level), static_Y_cord - offsetY + 90);
    if (v_system_data[C_S.current_gal][C_S.current_system].inicjalizer)
    {
       /*
       1 - zwyk³e imperium
2 - Upad³e Imperium
3 - Leviathany
4 - Mega
5 - Maruderzy
       */
        if (v_system_data[C_S.current_gal][C_S.current_system].init_type == 1)
        {
            GE.text_render_v2("Empire initializer", static_X_cord - offsetX + (2 * scrolling_level), static_Y_cord - offsetY + 130);
        }
        else if (v_system_data[C_S.current_gal][C_S.current_system].init_type == 2)
        {
            GE.text_render_v2("Fallen initializer", static_X_cord - offsetX + (2 * scrolling_level), static_Y_cord - offsetY + 130);
        }
        else if (v_system_data[C_S.current_gal][C_S.current_system].init_type == 3)
        {
            /*
             "guardians_init_stellarites",
            "guardians_init_dragon",
              "guardians_init_horror",
           "guardians_init_dreadnought",
         "guardians_init_hive",
          "guardians_init_technosphere",
               "guardians_init_fortress",
           "guardians_init_wraith",
            */
            std::string lev_type = "";
            switch (v_system_data[C_S.current_gal][C_S.current_system].init_number)
            {
            case 0:
                lev_type = "Stellarite";
                break;
            case 1:
                lev_type = "Ether Drake";
                break;
            case 2:
                lev_type = "Dimensional Horror";
                break;
            case 3:
                lev_type = "Dreadnought";
                break;
            case 4:
                lev_type = "Crystal Hive";
                break;
            case 5:
                lev_type = "Technosphere";
                break;
            case 6:
                lev_type = "Fortress";
                break;
            case 7:
                lev_type = "Wraith";
                break;
            case 8:
                lev_type = "Void Spawn";
                break;
            case 9:
                lev_type = "Scavenger";
                break;
            case 10:
                lev_type = "Tiyanki Matriarch";
                break;

            }
            GE.text_render_v2("Leviathan - " + lev_type, static_X_cord - offsetX + (2 * scrolling_level), static_Y_cord - offsetY + 130);
        }
        else if (v_system_data[C_S.current_gal][C_S.current_system].init_type == 4)
        {
            /*
                "dyson_sphere_init_01",
    "science_nexus_init_01",
    "sentry_array_init_01",
    "ring_world_init_01",
            */
            std::string mega_type = "";
            switch (v_system_data[C_S.current_gal][C_S.current_system].init_number)
            {
            case 0:
                mega_type = "Dyson Sphere";
                break;
            case 1:
                mega_type = "Science Nexus";
                break;
            case 2:
                mega_type = "Sentry Array";
                break;
            case 3:
                mega_type = "Ring World";
                break;
            case 4:
                mega_type = "Matter Decompresor";
                break;
            case 5:
                mega_type = "Coordination Center";
                break;
            case 6:
                mega_type = "Mega Art Installation";
                break;
            case 7:
                mega_type = "Interstellar Assembly";
                break;
            case 8:
                mega_type = "Mega Shipyard";
                break;
            case 9:
                mega_type = "Quantum Catapult";
                break;
            case 10:
                mega_type = "Orbital Ring";
                break;

            }
            GE.text_render_v2("Ruined megaconstruction:", static_X_cord - offsetX + (2 * scrolling_level), static_Y_cord - offsetY + 130);
            GE.text_render_v2(mega_type, static_X_cord - offsetX + (2 * scrolling_level), static_Y_cord - offsetY + 170);
        }
        else if (v_system_data[C_S.current_gal][C_S.current_system].init_type == 5)
        {
            GE.text_render_v2("Marauder initializer", static_X_cord - offsetX + (2 * scrolling_level), static_Y_cord - offsetY + 130);
        }
        else if (v_system_data[C_S.current_gal][C_S.current_system].init_type == 10)
        {
            GE.text_render_v2("Player initializer " + std::to_string(v_system_data[C_S.current_gal][C_S.current_system].player_id), static_X_cord - offsetX + (2 * scrolling_level), static_Y_cord - offsetY + 130);
        }
        else if (v_system_data[C_S.current_gal][C_S.current_system].init_type == 99)
        {
            GE.text_render_v2("Cental black hole", static_X_cord - offsetX + (2 * scrolling_level), static_Y_cord - offsetY + 130);
        }
    }
}

void Graphics_Engine::click_effect_remove(int button_id)
{
    SDL_Delay(80);
    gButtons[button_id].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
}

void Graphics_Engine::render_color_box(int R, int G, int B, int xa, int ya, int wa, int ha)
{
    SDL_SetRenderDrawColor(gRenderer, R, G, B, 0);
    SDL_Rect Rect;
    Rect.x = center_width + xa;
    Rect.y = center_height + ya;
    Rect.w = wa;
    Rect.h = ha;
    SDL_RenderFillRect(gRenderer, &Rect);
}

void Detailed_System_Edit::menu()
{
    gModulatedTexture.setAlpha(233);
    gModulatedTexture.render(center_width + 1220, center_height + 170, 680, 860);
    GE.text_render_v2("Detailed Generation", 1420, 180);
    GE.text_render_v2("Edit System", 1310, 220);
    GE.render_button_with_text(10, 0, 1270, 260, "Remove", 1307, 265);
    GE.render_button_with_text(10, 4, 1270, 320, "Add", 1335, 325);
    GE.render_button_with_text(10, 5, 1270, 380, "Move", 1325, 385);
    GE.text_render_v2("Edit Hyperlanes", 1260, 520);
    GE.render_button_with_text(10, 1, 1270, 570, "Remove", 1307, 575);
    GE.render_button_with_text(10, 6, 1270, 630, "Add", 1335, 635);
    GE.text_render_v2("Initializers", 1660, 220);
    GE.text_render_v2("Show", 1660, 260);
    GE.render_checkbox(63, 1740, 260, 30, 30);
    if (show_initializers)
    {
        GE.text_render_v2("X", 1745, 261);
    }
    GE.render_button_with_text(10, 8, 1640, 300, "Remove", 1675, 305);
    GE.render_button_with_text(10, 9, 1640, 360, "Add", 1707, 365);

    //GE.render_button_with_text(10, 7, 1640, 420, "Change", 1710, 425);
    GE.text_render_v2("Empires: " + std::to_string(empire_am), 1620, 430);
    GE.text_render_v2("Fallen Empires: " + std::to_string(fallen_am), 1620, 470);
    GE.text_render_v2("Marauders: " + std::to_string(maruder_am), 1620, 510);
    
    GE.text_render_v2("Colors", 1660, 600);
    GE.text_render_v2("Player", 1520, 640);
    GE.render_color_box(0, 255, 0, 1620, 652, 9, 9);
    GE.text_render_v2("Bot", 1720, 640);
    GE.render_color_box(255, 170, 170, 1775, 652, 9, 9);
    GE.text_render_v2("Fallen", 1520, 680);
    GE.render_color_box(255, 0, 255, 1615, 692, 9, 9);
    GE.text_render_v2("Marauders", 1680, 680);
    GE.render_color_box(255, 0, 0, 1840, 692, 9, 9);
    GE.text_render_v2("Ruined Megastructure", 1520, 720);
    GE.render_color_box(0, 255, 255, 1830, 732, 9, 9);
    GE.text_render_v2("Leviathans", 1520, 760);
    GE.render_color_box(255, 81, 0, 1680, 772, 9, 9);

}

void Detailed_System_Edit::add_initializer_menu()
{
    gModulatedTexture.setAlpha(233);
    gModulatedTexture.render(center_width + 1220, center_height + 170, 680, 860);
    GE.text_render_v2("Add Initializer", center_width + 1400, center_height + 180);
    GE.render_button_with_text(10, 11, 1290, 260, "Player", 1341, 265);
    GE.render_button_with_text(10, 12, 1290, 320, "Bot", 1360, 325); 
    GE.render_button_with_text(10, 13, 1290, 380, "Fallen", 1340, 385);
    GE.render_button_with_text(10, 14, 1290, 440, "Marauder", 1320, 445);
    GE.render_button_with_text_dynamic(10, 15, 1270, 500, 220, 45, "Ruined Mega", 1295, 505);
    GE.render_button_with_text(10, 16, 1290, 560, "Leviathan", 1315, 565);
    GE.render_button_with_text(10, 17, 1290, 620, "Central BH", 1300, 625);
}

void Detailed_System_Edit::add_initializer_mega()
{
    GE.render_button_with_text_dynamic(10, 20, 1620, 260, 240, 45, "Dyson Sphere", 1650, 265);
    GE.render_button_with_text_dynamic(10, 21, 1620, 320, 240, 45, "Science Nexus", 1640, 325);
    GE.render_button_with_text_dynamic(10, 22, 1620, 380, 240, 45, "Sentry Array", 1652, 385);
    GE.render_button_with_text_dynamic(10, 23, 1620, 440, 240, 45, "Ring World", 1670, 445);
    GE.render_button_with_text_dynamic(10, 24, 1590, 500, 300, 45, "Matter Decompresor", 1597, 505);
    GE.render_button_with_text_dynamic(10, 25, 1590, 560, 300, 45, "Coordination Center", 1605, 565);
    GE.render_button_with_text_dynamic(10, 26, 1590, 620, 300, 45, "Mega Art Installation", 1605, 625);
    GE.render_button_with_text_dynamic(10, 27, 1590, 680, 300, 45, "Interstellar Assembly", 1597, 685);
    GE.render_button_with_text_dynamic(10, 28, 1620, 740, 240, 45, "Mega Shipyard", 1640, 745);
    GE.render_button_with_text_dynamic(10, 29, 1590, 800, 300, 45, "Quantum Catapult", 1620, 805);
    GE.render_button_with_text_dynamic(10, 201, 1620, 860, 240, 45, "Orbital Ring", 1668, 865);
}

void Detailed_System_Edit::add_initializer_leviathan()
{
    GE.render_button_with_text(10, 30, 1650, 260, "Stellarite", 1685, 265);
    GE.render_button_with_text_dynamic(10, 31, 1620, 320, 240, 45, "Ether Drake", 1662, 325);
    GE.render_button_with_text(10, 32, 1650, 380, "Horror", 1700, 385);
    GE.render_button_with_text_dynamic(10, 33, 1620, 440, 240, 45, "Dreadnought", 1658, 445);
    GE.render_button_with_text(10, 34, 1650, 500, "Hive", 1715, 505);
    GE.render_button_with_text_dynamic(10, 35, 1620, 560, 240, 45, "Technosphere", 1650, 565);
    GE.render_button_with_text(10, 36, 1650, 620,  "Fortress", 1682, 625);
    GE.render_button_with_text(10, 37, 1650, 680, "Wraith", 1700, 685);
    GE.render_button_with_text(10, 38, 1650, 740, "Void Spawn", 1657, 745);
    GE.render_button_with_text(10, 39, 1650, 800, "Scavenger", 1665, 805);
    GE.render_button_with_text(10, 40, 1650, 860, "Matriarch", 1675, 865);
}

void Detailed_Generation::set_default_button()
{
    for (int i = 0; i < D_S_E_Buttons.size(); ++i)
    {
        D_S_E_Buttons[i].mCurrentSprite = BUTTON_SPRITE_MOUSE_BIG;
    }
}

void Image_To_Map::window()
{
    gModulatedTexture.setAlpha(240);
    gModulatedTexture.render(center_width + 20, center_height + 20, 1880, 1040);
    GE.text_render_v2("Image to map converter", 1200, 60);
    GE.render_button_with_text(0, 40, 1260, 120, "Load", 1320, 125);

    Print_Image();
}

void Image_To_Map::Print_Image()
{
    photo_Text.render(center_width + 30, center_height + 30, 1000, 1000);
}

void Image_To_Map::photo_patch_windows()
{
    using namespace cv;
    //photo = loadTexture(F_O.backslashes_to_slashes(pwstr_to_string(LoadFile(1))));
    //photo_Text.loadFromFile(F_O.backslashes_to_slashes(pwstr_to_string(LoadFile(1))));
    Mat img = imread(F_O.backslashes_to_slashes(pwstr_to_string(LoadFile(1))));

    while (1)
    {
        imshow("Image", img);
    }
    photo = SDL_CreateTexture(
        gRenderer, SDL_PIXELFORMAT_BGR24, SDL_TEXTUREACCESS_STREAMING, img.cols,
        img.rows);
    SDL_UpdateTexture(photo, NULL, (void*)img.data, img.step1());
}

std::string wstring_to_string(const std::wstring& source_str) {
    if (source_str.size() == 0) {
        // empty source string, we're done
        return std::string{};
    }

    // work out how much storage space we need
    auto new_size = WideCharToMultiByte(
        CP_UTF8,   // assuming you want UTF-8 text
        WC_ERR_INVALID_CHARS,
        source_str.data(),
        static_cast<int>(source_str.size()),
        nullptr,   // no output yet
        0,         // we just want to see how much space we need
        nullptr,
        nullptr
    );

    // check for errors
    if (new_size == 0) {
        throw std::system_error(GetLastError(), std::system_category());
    }

    // allocate memory for the new string
    std::string dest_str(static_cast<std::string::size_type>(new_size), '\0');

    // write into the string the values
    auto result = WideCharToMultiByte(
        CP_UTF8,
        0,   // already checked that there's no invalid chars, we're good
        source_str.data(),
        static_cast<int>(source_str.size()),
        dest_str.data(),  // now we pass the string to do
        static_cast<int>(dest_str.size()),
        nullptr,
        nullptr
    );

    // double-check we didn't mysteriously get another error
    if (result == 0) {
        throw std::system_error(GetLastError(), std::system_category());
    }

    // otherwise return the string
    return dest_str;
}

std::string pwstr_to_string(PWSTR path)
{
    wchar_t* localAppData = path;

    std::wstring ws(localAppData);
    
    std::string string = wstring_to_string(ws);

    return string;
}