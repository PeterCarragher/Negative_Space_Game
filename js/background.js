// Background class - static background elements

class Background extends GameObject {
    constructor() {
        super();
        this.setId(ID.MISC);
        this.setCollidable(false);
    }
    
    init(texture, x, y, width, height) {
        super.init(x, y, 0, 0, 0, 0, 0, 0);
        
        if (texture) {
            this.sprite = new PIXI.Sprite(texture);
            this.sprite.x = x;
            this.sprite.y = y;
            this.sprite.width = width;
            this.sprite.height = height;
        }
    }
    
    update() {
        // Background doesn't need to update
    }
    
    render() {
        super.render();
    }
}