// GreyFloor class - floor that both characters can stand on

class GreyFloor extends Floor {
    constructor() {
        super();
        this.setCollideType(COLLIDE_TYPE.GREY);
    }
    
    init(texture, x, y, boundX, boundY) {
        super.init(texture, x, y, boundX, boundY);
        
        // Make the sprite appear grey
        if (this.sprite) {
            this.sprite.tint = 0x808080; // Grey tint
        }
    }
}