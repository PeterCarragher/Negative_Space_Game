const express = require('express');
const cors = require('cors');
const path = require('path');

const app = express();
const PORT = process.env.PORT || 8000;

// Enable CORS for all routes
app.use(cors());

// Serve static files (HTML, CSS, JS, assets)
app.use(express.static('.'));

// Serve the main game page
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'index.html'));
});

// API endpoint for game data (future use)
app.get('/api/levels', (req, res) => {
    res.json({
        levels: [
            { id: 1, name: "Level 1", file: "assets/levels/level 1.tmx" },
            { id: 2, name: "Level 2", file: "assets/levels/level 2.tmx" },
            { id: 3, name: "Level 3", file: "assets/levels/level 3.tmx" },
            { id: 4, name: "Level 4", file: "assets/levels/level 4.tmx" }
        ]
    });
});

// Health check endpoint
app.get('/health', (req, res) => {
    res.json({ status: 'OK', timestamp: new Date().toISOString() });
});

app.listen(PORT, () => {
    console.log(`🎮 Negative Space Game server running at http://localhost:${PORT}`);
    console.log(`📁 Serving files from: ${__dirname}`);
    console.log(`🌐 Open your browser and navigate to the URL above`);
    console.log(`⛔ Press Ctrl+C to stop the server`);
});