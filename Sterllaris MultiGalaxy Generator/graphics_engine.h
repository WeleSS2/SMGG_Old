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
    void renderButton(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
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
    void text_input(int x, int y, int target_string_id);
    void text_render(std::string tekst, int x, int y);
    void text_render_v2(std::string tekst, int x, int y);
    void render_button_with_text(int mode, int button_id, int button_x, int button_y, std::string tekst, int text_x, int text_y);
    void line(int start_x, int start_y, int end_x, int end_y);
    void text_with_button(int button_id, std::string tekst, int x, int y);

    void wrong_text_input(int x, int y, int id);
    bool isNumber(const std::string& str);
    bool fucking_minus(const std::string& str);
};
Graphics_Engine GE;


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
    void render();
    void mrender();

private:
    SDL_Point mPosition;
    LButtonSprite mCurrentSprite;
};
std::vector<LButton> gButtons;

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
}

bool LTexture::loadFromFile(std::string path)
{
    free();

    SDL_Texture* newTexture = NULL;

    //Load image
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
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
    gButtonSpriteSheetTexture.renderButton(mPosition.x, mPosition.y, &gSpriteClips[BUTTON_SPRITE_MOUSE_BIG]);
}

void LButton::mrender()
{
    mButtonSpriteSheetTexture.renderButton(mPosition.x, mPosition.y, &gSpriteClips[BUTTON_SPRITE_MOUSE_SMALL]);
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
    else
    {
        ;
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
            else
            {
                gSpriteClips[i].w = BUTTON_WIDTH_SMALL;
            }
        }
        for (int i = 0; i <= 500; ++i)
        {
            gButtons.emplace_back();
        }
        gButtons[0].setPosition(center_width + 1245, center_height + 20);
        gButtons[1].setPosition(center_width + 1245, center_height + 85);
        gButtons[2].setPosition(center_width + 1465, center_height + 20);
        gButtons[3].setPosition(center_width + 1465, center_height + 85);
        gButtons[4].setPosition(center_width + 1690, center_height + 20);
        gButtons[5].setPosition(center_width + 1690, center_height + 85);
    }

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

        if (target_string_id != 100)
        {
            draw_galaxy();
        }

        //Render text textures
        gInputTextTexture.renderButton(x, y);
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
            fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 1:
        fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 2:
            isNumber(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 3:
            isNumber(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 4:
            fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 5:
            fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 6:
            fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 7:
            fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 8:
            isNumber(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;

        case 20:
            fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 21:
            fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 22:
            fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 55:
            fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 56:
            fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 99:
            fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            break;
        case 100:
            pathget = inputText;
            break;
        case 113:
            if (std::stoi(inputText) > 25 && std::stoi(inputText) < 500)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 114:
            if (std::stoi(inputText) > 25 && std::stoi(inputText) < 500)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 115:
            if (std::stoi(inputText) > 0)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 116:
            if (std::stoi(inputText) > 0)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 117:
            if (std::stoi(inputText) > 0)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 118:
            if (std::stoi(inputText) > 0)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 119:
            if (std::stoi(inputText) > 0)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 120:
            if (std::stoi(inputText) > 0)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 121:
            if (std::stoi(inputText) > 0)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 122:
            if (std::stof(inputText) > 0.01 && std::stof(inputText) < 0.9999)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 123:
            if (std::stof(inputText) > 0.01 && std::stof(inputText) < 0.9999)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 124:
            if (std::stof(inputText) > 0.01 && std::stof(inputText) < 0.9999)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 125:
            if (std::stof(inputText) > 0.01 && std::stof(inputText) < 0.9999)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 126:
            if (std::stoi(inputText) > 0)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 128:
            if (std::stoi(inputText) > 0)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 129:
            if (std::stoi(inputText) > 0)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 130:
            if (std::stof(inputText) > 0)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 131:
            if (std::stof(inputText) > 0)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
            }
            else
            {
                wrong_text_input(x, y, target_string_id);
            }
            break;
        case 132:
            if (std::stof(inputText) > 0)
            {
                fucking_minus(inputText) ? save_as(inputText, target_string_id) : wrong_text_input(x, y, target_string_id);
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

bool Graphics_Engine::fucking_minus(const std::string & str)
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
    case 55:
        min_hyperlane_am = std::stoi(inputText);
        break;
    case 56:
        max_hyperlane_am = std::stoi(inputText);
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
    rerender();
}

void Graphics_Engine::render_button_with_text(int mode, int button_id, int button_x, int button_y, std::string tekst, int text_x, int text_y)
{
    gButtons[button_id].setPosition(center_width + button_x, center_height + button_y);
    if (mode == 0)
    {
        gButtons[button_id].render();
    }
    else if (mode == 1)
    {

    }
    text_render(tekst, center_width + text_x, center_height + text_y);
}

void Graphics_Engine::render_checkbox(int button_id, int button_x, int button_y, int width, int height)
{
    gButtons[button_id].setPosition(center_width + button_x, center_height + button_y);
    gCheckboxTexture.render(center_width + button_x , center_height + button_y, width, height);
}

void render_hyperlanes()
{
    //std::cout << galaxies_am << std::endl;
        for (int i = 0; i < galaxies_am; i++)
        {
            if (v_galaxy_generation[i].hyperlanes_generated == true)
            {
                if (v_hyperlanes.size() != 0)
                {
                    if (v_hyperlanes[i].size() != 0)
                    {
                        for (int j = 0; j < v_hyperlanes[i].size(); j++)
                        {
                            SDL_SetRenderDrawColor(gRenderer, 22, 35, 35, SDL_ALPHA_OPAQUE);
                            SDL_RenderDrawLine(gRenderer, v_system_data[i][v_hyperlanes[i][j].from].gal_x + 550, v_system_data[i][v_hyperlanes[i][j].from].gal_y + 550, v_system_data[i][v_hyperlanes[i][j].to].gal_x + 550, v_system_data[i][v_hyperlanes[i][j].to].gal_y + 550);
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