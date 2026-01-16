import os

OUTPUT_DIR = "assets/maps/test"
os.makedirs(OUTPUT_DIR, exist_ok=True)

# Base Valid Configuration
VALID_TEX = """NO ./assets/textures/north.xpm
SO ./assets/textures/south.xpm
WE ./assets/textures/west.xpm
EA ./assets/textures/east.xpm
"""
VALID_COL = """F 220,100,0
C 225,30,0
"""
VALID_MAP = """11111
10001
10N01
10001
11111
"""

test_cases = []

# --- 1. VALID CASES ---
test_cases.append({
    "desc": "Standard valid map (Minimal)",
    "content": f"{VALID_TEX}\n{VALID_COL}\n{VALID_MAP}"
})
test_cases.append({
    "desc": "Valid map with whitespace padding",
    "content": f"{VALID_TEX}\n{VALID_COL}\n   11111   \n   10001   \n   10N01   \n   10001   \n   11111   "
})
test_cases.append({
    "desc": "Valid map with irregular shape (Tetris like)",
    "content": f"{VALID_TEX}\n{VALID_COL}\n11111\n1000111\n10N0001\n1111111"
})
test_cases.append({
    "desc": "Valid map largest allowed (simulated)",
    "content": f"{VALID_TEX}\n{VALID_COL}\n" + ("1" * 20 + "\n") + ("1" + "0"*18 + "1\n")*10 + ("1"*20)
})

# --- 2. ELEMENT ERRORS ---
test_cases.append({
    "desc": "Missing NO texture",
    "content": f"SO ./so.xpm\nWE ./we.xpm\nEA ./ea.xpm\n{VALID_COL}\n{VALID_MAP}"
})
test_cases.append({
    "desc": "Duplicate NO texture",
    "content": f"NO ./no.xpm\n{VALID_TEX}\n{VALID_COL}\n{VALID_MAP}"
})
test_cases.append({
    "desc": "Invalid Texture Key (XYZ)",
    "content": f"XYZ ./tex.xpm\n{VALID_TEX}\n{VALID_COL}\n{VALID_MAP}"
})
test_cases.append({
    "desc": "Texture path with no extension (valid in parsing, fail in load)",
    "content": f"NO ./assets/textures/north\nSO ./s.xpm\nWE ./w.xpm\nEA ./e.xpm\n{VALID_COL}\n{VALID_MAP}"
})

# --- 3. COLOR ERRORS ---
test_cases.append({
    "desc": "Missing Floor color",
    "content": f"{VALID_TEX}\nC 200,200,200\n{VALID_MAP}"
})
test_cases.append({
    "desc": "Duplicate Floor color",
    "content": f"{VALID_TEX}\n{VALID_COL}F 0,0,0\n{VALID_MAP}"
})
test_cases.append({
    "desc": "Color value out of range (>255)",
    "content": f"{VALID_TEX}\nF 300,0,0\nC 0,0,0\n{VALID_MAP}"
})
test_cases.append({
    "desc": "Color value negative",
    "content": f"{VALID_TEX}\nF -1,0,0\nC 0,0,0\n{VALID_MAP}"
})
test_cases.append({
    "desc": "Color missing component (2 values)",
    "content": f"{VALID_TEX}\nF 200,200\nC 0,0,0\n{VALID_MAP}"
})
test_cases.append({
    "desc": "Color trailing comma (3 components check)",
    "content": f"{VALID_TEX}\nF 200,200,\nC 0,0,0\n{VALID_MAP}"
})
test_cases.append({
    "desc": "Color invalid non-digit char",
    "content": f"{VALID_TEX}\nF 200,200,X\nC 0,0,0\n{VALID_MAP}"
})
test_cases.append({
    "desc": "Color too many components (4 values)",
    "content": f"{VALID_TEX}\nF 200,200,200,200\nC 0,0,0\n{VALID_MAP}"
})

# --- 4. MAP ERRORS ---
test_cases.append({
    "desc": "Map not closed (Open top)",
    "content": f"{VALID_TEX}\n{VALID_COL}\n00000\n10001\n10N01\n11111"
})
test_cases.append({
    "desc": "Map not closed (Open bottom)",
    "content": f"{VALID_TEX}\n{VALID_COL}\n11111\n10001\n10N01\n00000"
})
test_cases.append({
    "desc": "Map not closed (Open left)",
    "content": f"{VALID_TEX}\n{VALID_COL}\n11111\n00001\n00N01\n11111"
})
test_cases.append({
    "desc": "Map not closed (Open right)",
    "content": f"{VALID_TEX}\n{VALID_COL}\n11111\n10000\n10N00\n11111"
})
test_cases.append({
    "desc": "Invalid character in map (Z)",
    "content": f"{VALID_TEX}\n{VALID_COL}\n11111\n10Z01\n10N01\n11111"
})
test_cases.append({
    "desc": "No player position",
    "content": f"{VALID_TEX}\n{VALID_COL}\n11111\n10001\n10001\n10001\n11111"
})
test_cases.append({
    "desc": "Multiple players (N and S)",
    "content": f"{VALID_TEX}\n{VALID_COL}\n11111\n10001\n10N01\n10S01\n11111"
})
test_cases.append({
    "desc": "Zero touching void (hole in wall)",
    "content": f"{VALID_TEX}\n{VALID_COL}\n11111\n10001\n1 001\n11111"
})
test_cases.append({
    "desc": "Empty line inside map (Split map)",
    "content": f"{VALID_TEX}\n{VALID_COL}\n11111\n10N01\n\n11111"
})

# --- GENERATE FILES ---
for i, case in enumerate(test_cases, 1):
    filename = f"{i}.cub"
    filepath = os.path.join(OUTPUT_DIR, filename)
    
    with open(filepath, "w") as f:
        f.write(f"# Test Case {i}: {case['desc']}\n")
        f.write("# ---------------------------------------------------\n")
        f.write(case["content"])
    
    print(f"Generated {filepath}: {case['desc']}")
