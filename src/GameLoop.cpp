#include "GameLoop.h"
#include "GameState.h"

#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <chrono>

GameLoop::~GameLoop() {
}

bool GameLoop::init() {
    bool gameInitSuccessful = false;

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		// Create window
		_window = SDL_CreateWindow("SDL Game Jam 2022", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(_window == nullptr)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		}
		else
		{
            // Create renderer
            _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
            if(_renderer == nullptr) {
                std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            }
            else {
                // Render flags
                SDL_RenderSetLogicalSize(_renderer, GAME_WIDTH, GAME_HEIGHT);
                if(SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND) == -1) {
                    std::cout << "Error: failed to set render draw blend mode to SDL_BLENDMODE_BLEND. SDL_Error: " << SDL_GetError << std::endl;
                }
                if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) {
                    std::cout << "Warning: Nearest pixel sampling not enabled!" << std::endl;
                }
                if(!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1")) {
                    std::cout << "Warning: Vsync not enabled!" << std::endl;
                }
                // SDL_Image/SDL_ttf initialization
                if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
                    std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                }
                if(TTF_Init() == -1) {
                    std::cout << "SDL_ttf could not be initialized! SDL_ttf Error: " << TTF_GetError() << std::endl;
                }
                else {
                    // Load resources
                    if(!loadResources()) {
                        std::cout << "Error: failed to load resources!" << std::endl;
                    }
                    else {
                        // State initialization
                        _currentState = new GameState();
                        _currentState->setRenderer(_renderer);
                        _currentState->setGameSize(GAME_WIDTH, GAME_HEIGHT);
                        _currentState->setRenderSize(SCREEN_WIDTH, SCREEN_HEIGHT);
                        _currentState->init();
                        std::cout << "Success!" << std::endl;
                        gameInitSuccessful = true;
                    }
                }
            }
		}
	}

    return gameInitSuccessful;
}

bool GameLoop::loadResources() {
    return true;
}

void GameLoop::startLoop() {
    SDL_Event e;
    auto startTime = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds dTime = std::chrono::milliseconds(0); // deltaTime
    Uint32 frames = 0;
    Uint32 msCount = 0;
    float frameWait = 1.f / 60.f;
    // round framewait to make floating arithmetic a little better
    frameWait = (int)(frameWait / 0.001) * 0.001;
    while(_exitFlag == false) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                _exitFlag = true;
            }
            else if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_ESCAPE) {
                    _exitFlag = true;
                }
            }
            else if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
                _currentState->handleMouseInput(e);
            }
        }

        if(_currentState->getNextState() != nullptr) {
            State* tempState = _currentState->getNextState();
            delete _currentState;
            _currentState = tempState;
            _currentState->setRenderer(_renderer);
            _currentState->setGameSize(GAME_WIDTH, GAME_HEIGHT);
            _currentState->setRenderSize(SCREEN_WIDTH, SCREEN_HEIGHT);
            _currentState->init();
        }

        dTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime);
        if(dTime.count() / 1000.f > frameWait) {
            startTime = std::chrono::high_resolution_clock::now();
            msCount += dTime.count();
            _currentState->handleInput();
            _currentState->tick(frameWait);
            _currentState->render();
            ++frames;
        }

        if(msCount >= 1000) {
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
            msCount = 0;
        }
    }
}

void GameLoop::exit() {
    if(_window) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
    if(_renderer) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }

    IMG_Quit();
    TTF_Quit();
}