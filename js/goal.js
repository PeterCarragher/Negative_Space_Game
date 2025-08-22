// Goal class - objectives for players to reach

class Goal extends GameObject {
    constructor() {
        super();
        this.setId(ID.GOAL);
        this.setCollidable(true);
    }
    
    init(texture, x, y, boundX, boundY, collideType) {
        super.init(x, y, 0, 0, 0, 0, boundX, boundY);
        this.setCollideType(collideType);
        
        if (texture) {
            this.sprite = new PIXI.Sprite(texture);
            this.sprite.x = x;
            this.sprite.y = y;
            this.sprite.width = boundX * 2;
            this.sprite.height = boundY * 2;
            this.sprite.anchor.set(0.5, 0.5);
            
            // Tint based on collision type
            if (collideType === COLLIDE_TYPE.WHITE) {
                this.sprite.tint = 0xFFFFFF; // White goal
            } else if (collideType === COLLIDE_TYPE.BLACK) {
                this.sprite.tint = 0x333333; // Black goal
            }
        }
    }
    
    update() {
        // Goals don't need to update
    }
    
    render() {
        super.render();
    }
}