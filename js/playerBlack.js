// PlayerBlack class - the black character

class PlayerBlack extends GameObject {
    constructor() {
        super();
        this.setId(ID.PLAYERBLACK);
        this.setCollidable(true);
        this.setCollideType(COLLIDE_TYPE.BLACK);
        
        this.lives = 3;
        this.score = 0;
        this.animationRow = 0;
        this.gravity = 0.5;
        this.jumpSpeed = -12;
        this.spawnX = 0;
        this.spawnY = 0;
        
        this.dying = false;
        this.jump = false;
        this.mayJumpAgain = true;
        this.isOnSolidGround = false;
        this.jumpFramesLeft = 0;
        this.willJumpLeft = false;
        this.willJumpRight = false;
        this.cameraPosition = [0, 0];
        
        this.moveSpeed = 3;
    }
    
    init(texture, spawnX, spawnY) {
        this.spawnX = spawnX;
        this.spawnY = spawnY;
        this.x = spawnX;
        this.y = spawnY;
        
        this.frameWidth = 32;
        this.frameHeight = 32;
        this.boundX = 16;
        this.boundY = 16;
        
        if (texture) {
            this.sprite = new PIXI.Sprite(texture);
            this.sprite.width = this.frameWidth;
            this.sprite.height = this.frameHeight;
            this.sprite.anchor.set(0.5, 0.5);
            this.sprite.tint = 0x333333; // Dark tint for black player
        }
    }
    
    update() {
        // Apply gravity if not on ground or if velocity is upward (jumping)
        if (!this.isOnSolidGround || this.velY < 0) {
            this.velY += this.gravity;
        }
        
        // Update position
        this.x += this.velX;
        this.y += this.velY;
        
        // If jumping upward, no longer on ground
        if (this.velY < 0) {
            this.isOnSolidGround = false;
        }
    }
    
    render() {
        super.render();
    }
    
    moveLeft() {
        this.velX = -this.moveSpeed;
        this.dirX = -1;
    }
    
    moveRight() {
        this.velX = this.moveSpeed;
        this.dirX = 1;
    }
    
    jump() {
        if (this.mayJumpAgain || this.isOnSolidGround) {
            this.velY = this.jumpSpeed;
            this.jump = true;
            this.mayJumpAgain = false;
        }
    }
    
    resetMovement(direction) {
        if (direction === KEYS.LEFT || direction === KEYS.RIGHT) {
            this.velX = 0;
        }
    }
    
    resetAnimation(position) {
        this.curFrame = 0;
        this.frameCount = 0;
    }
    
    checkMayJumpAgain() {
        return this.mayJumpAgain || this.isOnSolidGround;
    }
    
    checkCollisions(otherObject) {
        if (!this.collidable() || !otherObject.collidable()) {
            return false;
        }
        
        // Black player collides with WHITE floors ONLY (not black floors)
        const otherType = otherObject.getCollideType();
        if (otherType === COLLIDE_TYPE.BLACK) {
            // console.log("Black player checking collision with white object");
            return super.checkCollisions(otherObject);
        }
        
        return false;
    }
    
    collided(otherObject) {
        const otherId = otherObject.getId();
        
        if (otherId === ID.FLOOR && this.velY > 0) {
            // Simple and reliable floor collision
            this.y = otherObject.getY() - otherObject.getBoundY() - this.boundY;
            this.velY = 0;
            this.isOnSolidGround = true;
            this.mayJumpAgain = true;
        } else if (otherId === ID.GOAL) {
            console.log("Black player reached goal!");
        }
    }
    
    cameraUpdate(cameraPosition, playerX, playerY, playerWidth, playerHeight) {
        // Simple camera following with smoothing
        const targetX = playerX - WIDTH / 2;
        const targetY = playerY - HEIGHT / 2;
        
        // Smooth camera movement to reduce jittering
        const lerp = 0.1;
        cameraPosition[0] += (targetX - cameraPosition[0]) * lerp;
        cameraPosition[1] += (targetY - cameraPosition[1]) * lerp;
    }
    
    // Getters and setters
    getVelX() { return this.velX; }
    getVelY() { return this.velY; }
    setVelX(velX) { this.velX = velX; }
    setVelY(velY) { this.velY = velY; }
    
    getWidth() { return this.frameWidth; }
    getHeight() { return this.frameHeight; }
}