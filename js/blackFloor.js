// BlackFloor class - floor that only black character can stand on

class BlackFloor extends Floor {
    constructor() {
        super();
        this.setCollideType(COLLIDE_TYPE.BLACK);
    }
    
    init(texture, x, y, boundX, boundY) {
        super.init(texture, x, y, boundX, boundY);
        
        // Make the sprite appear black/dark
        if (this.sprite) {
            this.sprite.tint = 0x333333; // Dark gray/black tint
        }
    }
}