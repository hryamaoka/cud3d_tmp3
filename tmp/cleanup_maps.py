import os
import glob

VALID_MAPS_DIR = "assets/maps/valid"
# 'S' is often used for Sprite texture in older or bonus implementations, check if relevant.
# Looking at previous file contents, some use S.
TEXTURE_KEYS = ["NO", "SO", "WE", "EA", "S"]

deleted_maps = []

def check_map(map_path):
    try:
        with open(map_path, 'r') as f:
            lines = f.readlines()
    except Exception as e:
        print(f"Error reading {map_path}: {e}")
        return False

    for line in lines:
        line = line.strip()
        parts = line.split()
        if not parts:
            continue
        
        # Check if line indicates a texture path
        if parts[0] in TEXTURE_KEYS:
            if len(parts) < 2:
                continue
            
            texture_path = parts[1]
            
            # Paths in cub files are usually relative to the executable location (root of repo)
            if not os.path.exists(texture_path):
                 return False # Found missing asset
                 
    return True

print("Checking maps in " + VALID_MAPS_DIR + "...")
for map_file in glob.glob(os.path.join(VALID_MAPS_DIR, "*.cub")):
    if not check_map(map_file):
        deleted_maps.append(map_file)
        try:
            os.remove(map_file)
        except OSError as e:
            print(f"Error deleting {map_file}: {e}")

print("\nDeleted Files:")
for map_file in deleted_maps:
    print(map_file)
