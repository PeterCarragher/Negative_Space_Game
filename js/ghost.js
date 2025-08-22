// Ghost class - enemy that patrols between points

class Ghost extends GameObject {
    constructor() {
        super();
        this.setId(ID.ENEMY);
        this.setCollidable(true);
        
        this.lives = 1;
        this.animationRow = 0;
        this.patrol = [0, 0];
        this.patrolDirection = 1;
        this.moveSpeed = 1;
    }
    
    init(texture, spawnX, spawnY, patrolPoints) {
        super.init(spawnX, spawnY, 0, 0, 1, 0, 16, 16);
        
        this.patrol[0] = patrolPoints[0];
        this.patrol[1] = patrolPoints[1];
        
        if (texture) {
            this.sprite = new PIXI.Sprite(texture);
            this.sprite.width = 32;
            this.sprite.height = 32;
            this.sprite.anchor.set(0.5, 0.5);
            this.sprite.tint = 0x888888; // Ghost-like appearance
        }
        
        this.frameWidth = 32;
        this.frameHeight = 32;
    }
    
    update() {
        // Patrol between two points
        if (this.patrolDirection > 0) {
            this.x += this.moveSpeed;
            if (this.x >= this.patrol[1]) {
                this.patrolDirection = -1;
            }
        } else {
            this.x -= this.moveSpeed;
            if (this.x <= this.patrol[0]) {
                this.patrolDirection = 1;
            }
        }
        
        this.velX = this.moveSpeed * this.patrolDirection;
        
        // Update animation
        this.frameCount++;
        if (this.frameCount >= 10) { // Frame delay
            this.frameCount = 0;
            this.curFrame++;
            if (this.curFrame >= 4) { // Assuming 4 frames of animation
                this.curFrame = 0;
            }
        }
    }
    
    render() {
        super.render();
    }
    
    moveLeft() {
        this.patrolDirection = -1;
    }
    
    moveRight() {
        this.patrolDirection = 1;
    }
    
    attack() {
        // Ghost attack behavior
    }
    
    die() {
        this.setAlive(false);
    }
}