// Saw class - dangerous obstacle

class Saw extends GameObject {
    constructor() {
        super();
        this.setId(ID.SAW);
        this.setCollidable(true);
        
        this.rotationSpeed = 0.1;
    }
    
    init(texture, x, y, boundX, boundY) {
        super.init(x, y, 0, 0, 0, 0, boundX, boundY);
        
        if (texture) {
            this.sprite = new PIXI.Sprite(texture);
            this.sprite.x = x;
            this.sprite.y = y;
            this.sprite.width = boundX * 2;
            this.sprite.height = boundY * 2;
            this.sprite.anchor.set(0.5, 0.5);
        }
        
        this.frameWidth = boundX * 2;
        this.frameHeight = boundY * 2;
    }
    
    update() {
        // Rotate the saw
        if (this.sprite) {
            this.sprite.rotation += this.rotationSpeed;
        }
    }
    
    render() {
        super.render();
    }
    
    checkCollisions(otherObject) {
        if (!this.collidable() || !otherObject.collidable()) {
            return false;
        }
        
        // Saws are dangerous to players
        const otherId = otherObject.getId();
        if (otherId === ID.PLAYERWHITE || otherId === ID.PLAYERBLACK) {
            return super.checkCollisions(otherObject);
        }
        
        return false;
    }
    
    collided(otherObject) {
        const otherId = otherObject.getId();
        
        if (otherId === ID.PLAYERWHITE || otherId === ID.PLAYERBLACK) {
            // Damage the player
            otherObject.loseLife();
            console.log("Player hit by saw!");
        }
    }
}