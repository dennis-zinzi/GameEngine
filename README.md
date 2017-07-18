# Game Engine with demo Target Practice game

## CSC3224: Computer Games Development Project Specification

"Produce a game engine suited to deploying a game of your own design and specification. This engine
is expected to employ middleware, and assessment is based upon the integration and, where
appropriate, extension of that middleware. The engine itself will be data driven, either in terms of
read-in files contaning game information, or through a clearly demarcated procedural generation
subsystem."

## Engine Subsystems
The Engine has the following subsystems:
- Audio – allows the engine to give audio cues and responses, and play background music (written using SDL_mixer 2.0)
- File I/O – interprets data from external data files (in the Assets/Files directory) to construct environments/levels and load the settings of the game
- Graphics – renders the game on screen (written using SDL2 and OpenGL)
- Human Interface – permits the user to actually interact with the game (written using SDL2)
- Initialise/Shutdown – loads the game engine in a managed fashion, and closes cleanly
- Profiler – provides information regarding performance of individual subsystems
- Physics – manages movement and interface detections (written using Bullet Physics v2.82)
- Resource Management – controls the loading and unloading of assets


### Audio Subsystem (code in Audio directory)
The audio subsystem, managed by the AudioPlayer class, is responsible for allowing the loading and playback of music and sound effects, 
in the Assets/Music and Assets/Sounds directories respectively. The supported sound effect format is currently only .wav, whilst
music files can be either .wav or .mp3.

### File I/O (code in FileIO directory)
The File I/O subsystem, managed by the FileReader class, is responsible for reading data from the .txt files in the Assets/Files, 
and parsing the information in a suitable way in order for a game written using this engine to be able to be data-driven rather than
hard-coded.

### Graphics Subsystem (code in Graphics directory)
The graphics subsystem, mostly managed by the GraphicsRenderer class, is responsible for rendering all objects in the 3-D game space; 
provide means to load textures and fonts in the Assets/Images and Assets/Fonts (and to avoid repeated loading); 
displaying the game HUD; and handling the game's camera.

### Human Interface (code in HumanInterface directory)
The human interface subsystem, managed by the InputManager class, is responsible for handling possible player interactions with 
the game world, and react to keyboard shortcuts.

### Initialise/Shutdown (code in InitShutdown directory)
The initialisation and shutdown subsysten, managed by the StartupShutdown class, is responsible for initialising and closing 
all other subsystems in an orderly fashion, avoiding any memory leaks when closing the subsystems.

### Profiler (code in Profiler directory)
The profiler subsystem, managed by the Profiler class, is responsible for reporting the engine's performance by displaying statistics 
about each subsystem, and the current frames per second (FPS) the game is running at.

### Physics (code in Physics directory)
The physics subsystem, managed by the PhysicsManager class, is responsible for the physical updates to the game objects and 
handling collision responses. The code adapts the Bullet Physics library in order to represent physical interactions between PhysicsObjects
appropriately, triggering their HandleHit function on a collision.

### Resource Managemet (code in ResourceManager directory)
The resource management subsystem, managed by the ResourceManager class, is responsible for the loading and unloading of all the assets
and resources the game needs. The loading makes use of other subsystems such as File I/O, Audio, and Graphics in order to iterate through
the Assets file directories and load the audio, textures, and fonts the game might need. This is done in order to increase performance 
whilst the game is running, as no additional time is spent loading assets.

## Target Practice game (game logic code in NewEngine directory)
This repository comes with a Target Practice game, as a demo of the engine's capabilities and demonstrates how to take advantage of the 
data-driven approach to create levels and change the settings for a game, whitout the need to compile any of the code. The code is 
structured in the following classes:
- Player - handles the player's possible actions he/she can take, along with the game camera
- GameObject - represents an object in the game world, including how it should be rendered and the collision callback function to 
execute when hit
- GameLoader - reads in the data from Assets/Files and creates all the game objects, HUD elements, and game settings
- GameLevel - handles updates to the game progression (such as current points, highscores, and time), and holds settings information
loaded in the GameLoader class (such as points when hitting a target, and time the level runs for)
- GameHUDObject - represents an object on the HUD screen, its purpose, and how to visually represent it
