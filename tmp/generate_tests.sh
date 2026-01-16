#!/bin/bash

# Clean previous test dir if exists
rm -rf assets/maps/test
mkdir -p assets/maps/valid
mkdir -p assets/maps/invalid

# --- VALID BASE ---
VALID_TEX="NO ./assets/textures/north.xpm
SO ./assets/textures/south.xpm
WE ./assets/textures/west.xpm
EA ./assets/textures/east.xpm"
VALID_COL="F 220,100,0
C 225,30,0"

# Helper to create file
create_map() {
    local type=$1 # "valid" or "invalid"
    local name=$2
    local desc=$3
    local content=$4
    
    local filepath="assets/maps/$type/$name.cub"
    
    echo "# Test Case $name ($type): $desc" > "$filepath"
    echo "# ---------------------------------------------------" >> "$filepath"
    echo -e "$content" >> "$filepath"
    echo "Generated $filepath"
}

# 1. Valid Minimal
create_map "valid" "01" "Standard valid map (Minimal)" "$VALID_TEX\n$VALID_COL\n11111\n10001\n10N01\n10001\n11111"

# 2. Valid Padding
create_map "valid" "02" "Valid map with whitespace padding" "$VALID_TEX\n$VALID_COL\n   11111   \n   10001   \n   10N01   \n   10001   \n   11111   "

# 3. Valid Irregular
create_map "valid" "03" "Valid map with irregular shape" "$VALID_TEX\n$VALID_COL\n11111\n1000111\n10N0001\n1111111"

# 4. Missing NO
create_map "invalid" "04" "Missing NO texture" "SO ./so.xpm\nWE ./we.xpm\nEA ./ea.xpm\n$VALID_COL\n11111\n10N01\n11111"

# 5. Duplicate NO
create_map "invalid" "05" "Duplicate NO texture" "NO ./no.xpm\n$VALID_TEX\n$VALID_COL\n11111\n10N01\n11111"

# 6. Invalid Key
create_map "invalid" "06" "Invalid Texture Key (XYZ)" "XYZ ./tex.xpm\n$VALID_TEX\n$VALID_COL\n11111\n10N01\n11111"

# 7. No Ext
create_map "invalid" "07" "Texture path with no extension" "NO ./assets/textures/north\nSO ./s.xpm\nWE ./w.xpm\nEA ./e.xpm\n$VALID_COL\n11111\n10N01\n11111"

# 8. Missing Floor
create_map "invalid" "08" "Missing Floor color" "$VALID_TEX\nC 200,200,200\n11111\n10N01\n11111"

# 9. Dup Floor
create_map "invalid" "09" "Duplicate Floor color" "$VALID_TEX\n$VALID_COL\nF 0,0,0\n11111\n10N01\n11111"

# 10. Color > 255
create_map "invalid" "10" "Color value out of range (>255)" "$VALID_TEX\nF 300,0,0\nC 0,0,0\n11111\n10N01\n11111"

# 11. Color Negative
create_map "invalid" "11" "Color value negative" "$VALID_TEX\nF -1,0,0\nC 0,0,0\n11111\n10N01\n11111"

# 12. Color 2 Comps
create_map "invalid" "12" "Color missing component (2 values)" "$VALID_TEX\nF 200,200\nC 0,0,0\n11111\n10N01\n11111"

# 13. Color Trailing Comma
create_map "invalid" "13" "Color trailing comma" "$VALID_TEX\nF 200,200,\nC 0,0,0\n11111\n10N01\n11111"

# 14. Color Invalid Char
create_map "invalid" "14" "Color invalid non-digit char" "$VALID_TEX\nF 200,200,X\nC 0,0,0\n11111\n10N01\n11111"

# 15. Color 4 Comps
create_map "invalid" "15" "Color too many components (4 values)" "$VALID_TEX\nF 200,200,200,200\nC 0,0,0\n11111\n10N01\n11111"

# 16. Open Top
create_map "invalid" "16" "Map not closed (Open top)" "$VALID_TEX\n$VALID_COL\n00000\n10001\n10N01\n11111"

# 17. Open Bot
create_map "invalid" "17" "Map not closed (Open bottom)" "$VALID_TEX\n$VALID_COL\n11111\n10001\n10N01\n00000"

# 18. Open Left
create_map "invalid" "18" "Map not closed (Open left)" "$VALID_TEX\n$VALID_COL\n11111\n00001\n00N01\n11111"

# 19. Open Right
create_map "invalid" "19" "Map not closed (Open right)" "$VALID_TEX\n$VALID_COL\n11111\n10000\n10N00\n11111"

# 20. Invalid Char Z
create_map "invalid" "20" "Invalid character in map (Z)" "$VALID_TEX\n$VALID_COL\n11111\n10Z01\n10N01\n11111"

# 21. No Player
create_map "invalid" "21" "No player position" "$VALID_TEX\n$VALID_COL\n11111\n10001\n10001\n10001\n11111"

# 22. Multi Player
create_map "invalid" "22" "Multiple players (N and S)" "$VALID_TEX\n$VALID_COL\n11111\n10001\n10N01\n10S01\n11111"

# 23. Zero Void
create_map "invalid" "23" "Zero touching void (hole in wall)" "$VALID_TEX\n$VALID_COL\n11111\n10001\n1 001\n11111"

# 24. Split Map
create_map "invalid" "24" "Empty line inside map (Split map)" "$VALID_TEX\n$VALID_COL\n11111\n10N01\n\n11111"
