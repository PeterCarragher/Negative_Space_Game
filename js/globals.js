// Global constants and enumerations

const ID = {
    PLAYERWHITE: 0,
    PLAYERBLACK: 1,
    ENEMY: 2,
    SAW: 3,
    BULLET: 4,
    BORDER: 5,
    MISC: 6,
    FLOOR: 7,
    GOAL: 8
};

const STATE = {
    TITLE: 0,
    PLAYING: 1,
    LOST: 2
};

const KEYS = {
    UP: 0,
    DOWN: 1,
    LEFT: 2,
    RIGHT: 3,
    W: 4,
    A: 5,
    S: 6,
    D: 7,
    R: 8,
    SPACE: 9
};

const COLLIDE_TYPE = {
    WHITE: 0,
    BLACK: 1,
    GREY: 2
};

const WIDTH = 512;
const HEIGHT = 512;

// Global game state
let keys = {};
let gameObjects = [];
let fps = 0;
let frameCount = 0;
let lastTime = 0;