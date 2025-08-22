# Negative Space Game - Web Version

This is a web version of the Negative Space Game, converted from the original Allegro5 C++ version to use PixiJS and run in web browsers.

## Features

- **Dual Character Control**: Control both white and black characters simultaneously
- **Physics-based Movement**: Gravity, jumping, and collision detection
- **Color-based Collision**: Characters can only interact with platforms of their color (or grey)
- **Goal System**: Guide each character to their respective colored goals
- **Web-based**: Runs in any modern web browser

## Controls

- **A/D**: Move both characters left/right
- **W**: Jump (both characters)
- **R**: Reset character positions
- **ESC**: Exit game

## Game Mechanics

1. **White Character**: Can only stand on white and grey platforms
2. **Black Character**: Can only stand on black and grey platforms  
3. **Grey Platforms**: Both characters can use these
4. **Goals**: Each character must reach their matching colored goal
5. **Synchronized Movement**: Both characters move together

## Running the Game

### Option 1: Node.js Server (Recommended)
```bash
# Install dependencies (first time only)
npm install

# Start the development server
npm start

# Or for auto-restart on file changes
npm run dev

# Then open http://localhost:8000 in your browser
```

### Option 2: Simple Static Server
```bash
# Using the included http-server
npm run serve

# Or using Python 3
python3 -m http.server 8000

# Then open http://localhost:8000 in your browser
```

### Option 3: Live Server (VS Code)
If using VS Code, install the "Live Server" extension and right-click on `index.html` → "Open with Live Server"

## File Structure

```
├── index.html              # Main HTML file
├── js/
│   ├── main.js            # Main game logic and initialization
│   ├── globals.js         # Game constants and global variables
│   ├── gameObject.js      # Base GameObject class
│   ├── playerWhite.js     # White character class
│   ├── playerBlack.js     # Black character class
│   ├── floor.js           # Base floor/platform class
│   ├── blackFloor.js      # Black platforms
│   ├── greyFloor.js       # Grey platforms (both can use)
│   ├── goal.js            # Goal objects
│   ├── ghost.js           # Enemy class (future use)
│   ├── saw.js             # Hazard class (future use)
│   ├── background.js      # Background elements
│   └── tmxLoader.js       # TMX map file loader
├── assets/                 # Game assets (copied from original)
├── server.js              # Express.js server
├── package.json           # Node.js dependencies and scripts
├── .nvmrc                 # Node.js version specification
└── README_WEB.md          # This file
```

## Technical Details

- **Engine**: PixiJS v7.x for 2D rendering
- **Language**: Modern JavaScript (ES6+)
- **Architecture**: Object-oriented design mirroring the original C++ structure
- **Collision Detection**: AABB (Axis-Aligned Bounding Box) collision detection
- **Asset Loading**: Dynamic texture generation and optional TMX map loading

## Differences from Original

1. **Simplified Graphics**: Uses generated colored rectangles instead of sprite sheets
2. **Web-based Input**: Uses DOM keyboard events instead of Allegro input
3. **Asset Loading**: Simplified asset system, no need for external image files
4. **TMX Loading**: Optional - falls back to procedurally generated level if TMX not found
5. **Frame Rate**: Uses requestAnimationFrame for smooth 60fps gameplay

## Future Enhancements

- [ ] Load actual sprite textures from image files
- [ ] Add sound effects and music
- [ ] Implement enemy AI (Ghost, Saw classes are ready)
- [ ] Add particle effects
- [ ] Level editor functionality
- [ ] Mobile touch controls
- [ ] Progressive Web App (PWA) support

## Browser Compatibility

- Chrome 60+
- Firefox 55+
- Safari 11+
- Edge 79+

Requires support for ES6 classes and async/await.