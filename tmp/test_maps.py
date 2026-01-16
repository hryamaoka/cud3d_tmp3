import os
import subprocess
import glob
import time

VALGRIND_CMD = ["valgrind", "--leak-check=full", "--error-exitcode=42", "--quiet"]
EXEC_PATH = "./cub3D"
VALID_MAPS_DIR = "assets/maps/valid"
INVALID_MAPS_DIR = "assets/maps/invalid"
TIMEOUT_SEC = 10

def run_test(map_path, expect_valid):
    cmd = VALGRIND_CMD + [EXEC_PATH, map_path]
    
    try:
        # Run with timeout
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=TIMEOUT_SEC)
        
        # If we are here, the program finished naturally (or crashed/errored immediately)
        exit_code = result.returncode
        stderr = result.stderr
        
        if exit_code == 139: # Segfault
            return "FAIL (Segfault)", stderr
        elif exit_code == 42: # Valgrind memory error
            return "FAIL (Memory Leak)", stderr
        
        if expect_valid:
            # Valid map should effectively loop forever, so reaching here means it exited early.
            # However, if it exited with 0, maybe the loop isn't infinite? or something closed it.
            # But usually it's an error if it exits early without user input.
            if exit_code != 0:
                 return f"FAIL (Exited with {exit_code})", stderr
            else:
                 return "FAIL (Unexpected Exit 0)", stderr
        else:
            # Invalid map SHOULD exit.
            # We expect exit code 1 (based on perror_and_exit)
            if exit_code == 1:
                return "PASS", stderr
            elif exit_code == 0:
                return "FAIL (Unexpected Success)", stderr
            else:
                 return f"FAIL (Exit code {exit_code})", stderr

    except subprocess.TimeoutExpired as e:
        # Timeout means it kept running
        if expect_valid:
            # This is expected for valid maps (game loop running)
            # We captured what we could. 
            # Note: We can't easily check for leaks if we kill it this way unless we send SIGTERM and the app handles it cleanliness.
            # But "running without crash" is the main success criteria here.
            return "PASS (Timeout/Running)", ""
        else:
            # Invalid map should have exited!
            # If it's still running, it parsed an invalid map as valid?
            # Or got stuck in an infinite loop.
            return "FAIL (Infinite Loop / Didn't Exit)", ""
    except Exception as e:
        return f"ERROR ({str(e)})", ""

import sys

def main():
    print(f"Testing maps in {os.getcwd()}...")
    
    target = "all"
    if len(sys.argv) > 1:
        target = sys.argv[1]

    # invalid maps
    if target in ["all", "invalid"]:
        invalid_maps = glob.glob(os.path.join(INVALID_MAPS_DIR, "*.cub"))
        print(f"\n--- Testing Invalid Maps ({len(invalid_maps)}) ---")
        
        fails = 0
        passed = 0
        
        for map_file in invalid_maps:
            status, output = run_test(map_file, False)
            if "FAIL" in status:
                print(f"[{status}] {map_file}")
                # print(output) # Uncomment for detailed logs
                fails += 1
            else:
                # print(f"[PASS] {map_file}")
                passed += 1
                
        print(f"Invalid Maps: {passed} PASSED, {fails} FAILED")

    # valid maps
    if target in ["all", "valid"]:
        valid_maps = glob.glob(os.path.join(VALID_MAPS_DIR, "*.cub"))
        print(f"\n--- Testing Valid Maps ({len(valid_maps)}) ---")
        
        fails_v = 0
        passed_v = 0
        
        for map_file in valid_maps:
            status, output = run_test(map_file, True)
            if "FAIL" in status:
                print(f"[{status}] {map_file}")
                print(output)
                fails_v += 1
            else:
                # print(f"[PASS] {map_file}")
                passed_v += 1

        print(f"Valid Maps: {passed_v} PASSED, {fails_v} FAILED")

if __name__ == "__main__":
    main()
