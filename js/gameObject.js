// Base GameObject class equivalent to the C++ version

class GameObject {
    constructor() {
        this.id = 0;
        this.alive = true;
        this.canCollide = false;
        this.collideType = 0;
        
        this.x = 0;
        this.y = 0;
        this.velX = 0;
        this.velY = 0;
        this.dirX = 0;
        this.dirY = 0;
        this.boundX = 0;
        this.boundY = 0;
        
        this.maxFrame = 0;
        this.curFrame = 0;
        this.frameCount = 0;
        this.frameDelay = 0;
        this.frameWidth = 0;
        this.frameHeight = 0;
        this.animationColumns = 0;
        this.animationDirection = 0;
        
        this.sprite = null;
        this.texture = null;
    }
    
    destroy() {
        if (this.sprite && this.sprite.parent) {
            this.sprite.parent.removeChild(this.sprite);
        }
    }
    
    init(x, y, velX, velY, dirX, dirY, boundX, boundY) {
        this.x = x;
        this.y = y;
        this.velX = velX;
        this.velY = velY;
        this.dirX = dirX;
        this.dirY = dirY;
        this.boundX = boundX;
        this.boundY = boundY;
    }
    
    update() {
        // Base update logic - to be overridden by subclasses
    }
    
    render() {
        if (this.sprite) {
            this.sprite.x = this.x;
            this.sprite.y = this.y;
        }
    }
    
    // Getters and setters
    getX() { return this.x; }
    getY() { return this.y; }
    setX(x) { this.x = x; }
    setY(y) { this.y = y; }
    
    getBoundX() { return this.boundX; }
    getBoundY() { return this.boundY; }
    
    getId() { return this.id; }
    setId(id) { this.id = id; }
    
    getAlive() { return this.alive; }
    setAlive(alive) { this.alive = alive; }
    
    getCollidable() { return this.canCollide; }
    setCollidable(collidable) { this.canCollide = collidable; }
    
    setCollideType(type) { this.collideType = type; }
    getCollideType() { return this.collideType; }
    
    checkCollisions(otherObject) {
        // Basic AABB collision detection
        return (this.x < otherObject.x + otherObject.boundX &&
                this.x + this.boundX > otherObject.x &&
                this.y < otherObject.y + otherObject.boundY &&
                this.y + this.boundY > otherObject.y);
    }
    
    collided(otherObject) {
        // To be overridden by subclasses
    }
    
    collidable() {
        return this.getCollidable();
    }
}