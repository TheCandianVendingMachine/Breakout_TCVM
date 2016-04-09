// game.hpp
// the game loop. Initializes the window and resources that will be used in the game
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class game
    {
        private:
            sf::RenderWindow *app;

            void initializeWindow();
            void initializeSounds();
            void initializeTextures();
            void initializeControls();
            void initialize();

            void cleanup();

        public:
            void start();

            ~game();

    };