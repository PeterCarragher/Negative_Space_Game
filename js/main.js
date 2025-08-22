// Main game file - handles initialization, game loop, and input

class NegativeSpaceGame {
    constructor() {
        this.app = null;
        this.gameContainer = null;
        this.gameObjects = [];
        this.playerWhite = null;
        this.playerBlack = null;
        
        this.keys = {};
        this.lastTime = 0;
        this.fps = 0;
        this.frameCount = 0;
        this.fpsUpdateTime = 0;
        
        this.assets = {};
        this.map = null;
        
        this.camera = { x: 0, y: 0 };
    }
    
    async init() {
        // Create PIXI application with proper initialization
        try {
            this.app = new PIXI.Application();
            await this.app.init({
                width: WIDTH,
                height: HEIGHT,
                backgroundColor: 0x3399ff // Sky blue background
            });
        } catch (error) {
            // Fallback for older PixiJS versions
            this.app = new PIXI.Application({
                width: WIDTH,
                height: HEIGHT,
                backgroundColor: 0x3399ff
            });
        }
        
        // Add to DOM - use canvas property for newer PixiJS versions
        const gameContainer = document.getElementById('gameContainer');
        const canvas = this.app.canvas || this.app.view;
        if (canvas) {
            gameContainer.appendChild(canvas);
        } else {
            throw new Error('Unable to get canvas from PIXI application');
        }
        
        // Create main game container
        this.gameContainer = new PIXI.Container();
        this.app.stage.addChild(this.gameContainer);
        
        // Initialize input
        this.initInput();
        
        // Load assets
        await this.loadAssets();
        
        // Load map
        await this.loadMap();
        
        // Create players
        this.createPlayers();
        
        // Start game loop
        this.app.ticker.add(this.gameLoop.bind(this));
        
        console.log("Negative Space Game initialized!");
    }
    
    async loadAssets() {
        // Create simple colored rectangles as placeholder textures
        const graphics = new PIXI.Graphics();
        
        // White floor texture
        graphics.beginFill(0xFFFFFF);
        graphics.drawRect(0, 0, 32, 32);
        graphics.endFill();
        this.assets.whiteFloor = this.app.renderer.generateTexture(graphics);
        
        // Black floor texture
        graphics.clear();
        graphics.beginFill(0x333333);
        graphics.drawRect(0, 0, 32, 32);
        graphics.endFill();
        this.assets.blackFloor = this.app.renderer.generateTexture(graphics);
        
        // Grey floor texture
        graphics.clear();
        graphics.beginFill(0x808080);
        graphics.drawRect(0, 0, 32, 32);
        graphics.endFill();
        this.assets.greyFloor = this.app.renderer.generateTexture(graphics);
        
        // Player textures
        graphics.clear();
        graphics.beginFill(0xFFFFFF);
        graphics.drawCircle(16, 16, 12);
        graphics.endFill();
        this.assets.playerWhite = this.app.renderer.generateTexture(graphics);
        
        graphics.clear();
        graphics.beginFill(0x333333);
        graphics.drawCircle(16, 16, 12);
        graphics.endFill();
        this.assets.playerBlack = this.app.renderer.generateTexture(graphics);
        
        // Goal textures
        graphics.clear();
        graphics.beginFill(0xFFD700);
        graphics.drawRect(0, 0, 32, 32);
        graphics.endFill();
        this.assets.goal = this.app.renderer.generateTexture(graphics);
        
        graphics.destroy();
    }
    
    async loadMap() {
        // Try to load the TMX file, fallback to creating a simple level
        try {
            this.map = await TMXLoader.loadTMXFile('assets/levels/level 3.tmx');
        } catch (error) {
            console.log("Could not load TMX file, creating simple level");
            this.createSimpleLevel();
            return;
        }
        
        if (!this.map) {
            this.createSimpleLevel();
            return;
        }
        
        this.createLevelFromMap();
    }
    
    createSimpleLevel() {
        // Create a simple test level
        
        // Floor platforms
        const platforms = [
            { x: 100, y: 400, width: 100, height: 20, type: 'white' },
            { x: 250, y: 350, width: 100, height: 20, type: 'black' },
            { x: 400, y: 300, width: 100, height: 20, type: 'grey' },
            { x: 0, y: 480, width: 512, height: 32, type: 'grey' } // Ground
        ];
        
        platforms.forEach(platform => {
            let floor;
            let texture;
            
            switch (platform.type) {
                case 'white':
                    floor = new Floor();
                    texture = this.assets.whiteFloor;
                    break;
                case 'black':
                    floor = new BlackFloor();
                    texture = this.assets.blackFloor;
                    break;
                case 'grey':
                    floor = new GreyFloor();
                    texture = this.assets.greyFloor;
                    break;
            }
            
            floor.init(texture, platform.x + platform.width/2, platform.y + platform.height/2, 
                      platform.width/2, platform.height/2);
            this.gameContainer.addChild(floor.sprite);
            this.gameObjects.push(floor);
        });
        
        // Goals
        const whiteGoal = new Goal();
        whiteGoal.init(this.assets.goal, 480, 250, 16, 16, COLLIDE_TYPE.WHITE);
        this.gameContainer.addChild(whiteGoal.sprite);
        this.gameObjects.push(whiteGoal);
        
        const blackGoal = new Goal();
        blackGoal.init(this.assets.goal, 480, 200, 16, 16, COLLIDE_TYPE.BLACK);
        blackGoal.sprite.tint = 0x333333;
        this.gameContainer.addChild(blackGoal.sprite);
        this.gameObjects.push(blackGoal);
    }
    
    createLevelFromMap() {
        if (!this.map || !this.map.groups) return;
        
        let manSpawnX = 100, manSpawnY = 100;
        let womanSpawnX = 100, womanSpawnY = 100;
        
        this.map.groups.forEach(group => {
            switch (group.name) {
                case 'whiteob':
                    group.objects.forEach(tile => {
                        const floor = new Floor();
                        floor.init(this.assets.whiteFloor, 
                                 tile.x + tile.width/2, tile.y + tile.height/2,
                                 tile.width/2, tile.height/2);
                        this.gameContainer.addChild(floor.sprite);
                        this.gameObjects.push(floor);
                    });
                    break;
                    
                case 'blackob':
                    group.objects.forEach(tile => {
                        const floor = new BlackFloor();
                        floor.init(this.assets.blackFloor,
                                 tile.x + tile.width/2, tile.y + tile.height/2,
                                 tile.width/2, tile.height/2);
                        this.gameContainer.addChild(floor.sprite);
                        this.gameObjects.push(floor);
                    });
                    break;
                    
                case 'greyob':
                    group.objects.forEach(tile => {
                        const floor = new GreyFloor();
                        floor.init(this.assets.greyFloor,
                                 tile.x + tile.width/2, tile.y + tile.height/2,
                                 tile.width/2, tile.height/2);
                        this.gameContainer.addChild(floor.sprite);
                        this.gameObjects.push(floor);
                    });
                    break;
                    
                case 'whitespawn':
                    group.objects.forEach(tile => {
                        manSpawnX = tile.x + 34;
                        manSpawnY = tile.y + 34;
                    });
                    break;
                    
                case 'blackspawn':
                    group.objects.forEach(tile => {
                        womanSpawnX = tile.x + 34;
                        womanSpawnY = tile.y + 34;
                    });
                    break;
                    
                case 'whitegoal':
                    group.objects.forEach(tile => {
                        const goal = new Goal();
                        goal.init(this.assets.goal, tile.x, tile.y, 16, 16, COLLIDE_TYPE.WHITE);
                        this.gameContainer.addChild(goal.sprite);
                        this.gameObjects.push(goal);
                    });
                    break;
                    
                case 'blackgoal':
                    group.objects.forEach(tile => {
                        const goal = new Goal();
                        goal.init(this.assets.goal, tile.x, tile.y, 16, 16, COLLIDE_TYPE.BLACK);
                        goal.sprite.tint = 0x333333;
                        this.gameContainer.addChild(goal.sprite);
                        this.gameObjects.push(goal);
                    });
                    break;
            }
        });
        
        // Update spawn positions
        this.playerSpawnX = manSpawnX;
        this.playerSpawnY = manSpawnY;
        this.playerBlackSpawnX = womanSpawnX;
        this.playerBlackSpawnY = womanSpawnY;
    }
    
    createPlayers() {
        // Create white player
        this.playerWhite = new PlayerWhite();
        this.playerWhite.init(this.assets.playerWhite, 
                            this.playerSpawnX || 50, this.playerSpawnY || 400);
        this.gameContainer.addChild(this.playerWhite.sprite);
        this.gameObjects.push(this.playerWhite);
        
        // Create black player
        this.playerBlack = new PlayerBlack();
        this.playerBlack.init(this.assets.playerBlack,
                            this.playerBlackSpawnX || 50, this.playerBlackSpawnY || 400);
        this.gameContainer.addChild(this.playerBlack.sprite);
        this.gameObjects.push(this.playerBlack);
    }
    
    initInput() {
        // Keyboard input handling
        document.addEventListener('keydown', (e) => {
            this.keys[e.code] = true;
            
            if (e.code === 'Escape') {
                console.log("Game exit requested");
            }
            if (e.code === 'KeyR') {
                this.resetPlayers();
            }
        });
        
        document.addEventListener('keyup', (e) => {
            this.keys[e.code] = false;
        });
    }
    
    resetPlayers() {
        if (this.playerWhite) {
            this.playerWhite.setX(this.playerSpawnX || 50);
            this.playerWhite.setY(this.playerSpawnY || 400);
            this.playerWhite.setVelX(0);
            this.playerWhite.setVelY(0);
        }
        
        if (this.playerBlack) {
            this.playerBlack.setX(this.playerBlackSpawnX || 50);
            this.playerBlack.setY(this.playerBlackSpawnY || 400);
            this.playerBlack.setVelX(0);
            this.playerBlack.setVelY(0);
        }
        
        this.camera.x = 0;
        this.camera.y = 0;
    }
    
    gameLoop(delta) {
        const currentTime = performance.now();
        
        // Update FPS
        this.frameCount++;
        if (currentTime - this.fpsUpdateTime >= 1000) {
            this.fps = this.frameCount;
            this.frameCount = 0;
            this.fpsUpdateTime = currentTime;
            document.getElementById('fps').textContent = `FPS: ${this.fps}`;
        }
        
        this.handleInput();
        this.updateGame();
        this.updateCamera();
        this.checkCollisions();
        this.renderGame();
        
        this.lastTime = currentTime;
    }
    
    handleInput() {
        if (!this.playerWhite || !this.playerBlack) return;
        
        // Movement input
        if (this.keys['KeyA']) {
            this.playerWhite.moveLeft();
            this.playerBlack.moveLeft();
        }
        if (this.keys['KeyD']) {
            this.playerWhite.moveRight();
            this.playerBlack.moveRight();
        }
        if (!this.keys['KeyA'] && !this.keys['KeyD']) {
            this.playerWhite.resetMovement(KEYS.LEFT);
            this.playerBlack.resetMovement(KEYS.LEFT);
            this.playerWhite.resetAnimation(KEYS.LEFT);
            this.playerBlack.resetAnimation(KEYS.LEFT);
        }
        
        // Jumping (disabled in original but can be enabled)
        if (this.keys['KeyW']) {
            if (this.playerWhite.checkMayJumpAgain()) {
                this.playerWhite.jump();
            }
            if (this.playerBlack.checkMayJumpAgain()) {
                this.playerBlack.jump();
            }
        }
    }
    
    updateGame() {
        // Update all game objects
        this.gameObjects.forEach(obj => {
            if (obj.getAlive()) {
                obj.update();
            }
        });
        
        // Remove dead objects
        this.gameObjects = this.gameObjects.filter(obj => {
            if (!obj.getAlive()) {
                obj.destroy();
                return false;
            }
            return true;
        });
    }
    
    updateCamera() {
        if (this.playerBlack) {
            // Follow the black player with camera (as in original) with smoothing
            const targetCameraX = this.playerBlack.getX() - WIDTH / 2;
            const targetCameraY = this.playerBlack.getY() - HEIGHT / 2;
            
            // Smooth camera interpolation to reduce jitter
            const lerp = 0.05;
            this.camera.x += (targetCameraX - this.camera.x) * lerp;
            this.camera.y += (targetCameraY - this.camera.y) * lerp;
            
            // Apply camera transform (round to avoid sub-pixel rendering jitter)
            this.gameContainer.x = -Math.round(this.camera.x);
            this.gameContainer.y = -Math.round(this.camera.y);
        }
    }
    
    checkCollisions() {
        // Reset ground state for all players at start of collision check
        [this.playerWhite, this.playerBlack].forEach(player => {
            if (player && player.velY >= 0) { // Only reset if not jumping upward
                player.isOnSolidGround = false;
            }
        });
        
        // Check collisions between players and static objects (floors/goals)
        [this.playerWhite, this.playerBlack].forEach(player => {
            if (!player || !player.getCollidable()) return;
            
            this.gameObjects.forEach(obj => {
                if (!obj.getCollidable()) return;
                if (obj.getId() === player.getId()) return;
                
                // Only check floors and goals for player collisions
                if (obj.getId() !== ID.FLOOR && obj.getId() !== ID.GOAL) return;
                
                // Let the player's checkCollisions method handle the collision type logic
                if (player.checkCollisions(obj)) {
                    player.collided(obj);
                }
            });
        });
    }
    
    renderGame() {
        // Rendering is handled automatically by PIXI
        this.gameObjects.forEach(obj => {
            obj.render();
        });
    }
}

// Initialize game when page loads
window.addEventListener('load', async () => {
    const game = new NegativeSpaceGame();
    await game.init();
});