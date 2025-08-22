// TMX Map Loader - simplified version for web

class TMXLoader {
    static async loadTMX(xmlText) {
        const parser = new DOMParser();
        const xmlDoc = parser.parseFromString(xmlText, "text/xml");
        
        const map = {
            width: 0,
            height: 0,
            tilewidth: 0,
            tileheight: 0,
            groups: []
        };
        
        const mapElement = xmlDoc.querySelector("map");
        if (mapElement) {
            map.width = parseInt(mapElement.getAttribute("width")) || 0;
            map.height = parseInt(mapElement.getAttribute("height")) || 0;
            map.tilewidth = parseInt(mapElement.getAttribute("tilewidth")) || 32;
            map.tileheight = parseInt(mapElement.getAttribute("tileheight")) || 32;
        }
        
        // Parse object groups
        const objectGroups = xmlDoc.querySelectorAll("objectgroup");
        objectGroups.forEach(group => {
            const groupData = {
                name: group.getAttribute("name") || "",
                objects: []
            };
            
            const objects = group.querySelectorAll("object");
            objects.forEach(obj => {
                const objData = {
                    x: parseFloat(obj.getAttribute("x")) || 0,
                    y: parseFloat(obj.getAttribute("y")) || 0,
                    width: parseFloat(obj.getAttribute("width")) || 32,
                    height: parseFloat(obj.getAttribute("height")) || 32,
                    name: obj.getAttribute("name") || "",
                    type: obj.getAttribute("type") || ""
                };
                
                groupData.objects.push(objData);
            });
            
            map.groups.push(groupData);
        });
        
        return map;
    }
    
    static async loadTMXFile(url) {
        try {
            const response = await fetch(url);
            const xmlText = await response.text();
            return await this.loadTMX(xmlText);
        } catch (error) {
            console.error("Failed to load TMX file:", error);
            return null;
        }
    }
}