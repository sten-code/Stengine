# ----------------- Python Package Installation -----------------
import subprocess
import pkg_resources

def install(package):
    print(f"Installing {package} module...")
    subprocess.check_call(["python3", "-m", "pip", "install", package])

def validate_package(package):
    required = { package }
    installed = {pkg.key for pkg in pkg_resources.working_set}
    missing = required - installed

    if missing:
        install(package)

validate_package("requests")
validate_package("fake-useragent")
# ---------------------------------------------------------------

import requests
from fake_useragent import UserAgent

import os
from pathlib import Path
import sys
import time

def download_file(url: str, filepath: str):
    # Create the directory recursively if it doesn't exist
    os.makedirs(Path(filepath).parent.absolute(), exist_ok=True)

    # Prepare to write the file in binary format
    with open(filepath, "wb") as f:
        # Create a http request with a user agent
        ua = UserAgent()
        headers = {"User-Agent": ua.chrome}
        response = requests.get(url, headers=headers, stream=True)

        total = response.headers.get("content-length")
        if total is None:
            print("ERROR: Url invalid!")
            f.write(response.content)
        else:
            downloaded = 0
            total = int(total)
            startTime = time.time()
            for data in response.iter_content(chunk_size=max(int(total/1000), 1024*1024)):
                downloaded += len(data)
                f.write(data)
                done = int(50*downloaded/total)
                percentage = (downloaded / total) * 100
                elapsedTime = time.time() - startTime
                avgKBPerSecond = (downloaded / 1024) / elapsedTime
                avgSpeedString = "{:.2f} KB/s".format(avgKBPerSecond)
                if (avgKBPerSecond > 1024):
                    avgMBPerSecond = avgKBPerSecond / 1024
                    avgSpeedString = "{:.2f} MB/s".format(avgMBPerSecond)
                sys.stdout.write("\r[{}{}] {:.2f}% ({})     ".format("█" * done, "." * (50-done), percentage, avgSpeedString))
                sys.stdout.flush()
    sys.stdout.write("\n")

def yes_or_no(msg: str = "", default: bool = True) -> bool:
    while True:
        reply = input(f"{msg} [{'Y' if default else 'y'}/{'n' if default else 'N'}]: ").lower().strip()
        if reply[:1] == "y":
            return True
        if reply[:1] == "n":
            return False
        if reply == "":
            return default

STENGINE_VULKAN_VERSION = "1.2.189.0"
VULKAN_SDK = os.environ.get("VULKAN_SDK")
VULKAN_SDK_INSTALLER_URL = f"https://sdk.lunarg.com/sdk/download/{STENGINE_VULKAN_VERSION}/linux/vulkansdk-linux-x86_64-{STENGINE_VULKAN_VERSION}.tar.gz"
VULKAN_SDK_INSTALLER_PATH = f"Stengine/vendor/VulkanSDK/vulkansdk-linux-x86_64-{STENGINE_VULKAN_VERSION}.tar.gz"

def install_vulkan_sdk():
    print("Downloading {} to {}".format(VULKAN_SDK_INSTALLER_URL, VULKAN_SDK_INSTALLER_PATH))
    download_file(VULKAN_SDK_INSTALLER_URL, VULKAN_SDK_INSTALLER_PATH)
    print("Done!")
    print("Extracting...")
    subprocess.call(["tar", "-xf", VULKAN_SDK_INSTALLER_PATH, "-C", "Stengine/vendor/VulkanSDK"], shell=False)
    print("Running Vulkan SDK Installer...")
    subprocess.call([f"Stengine/vendor/VulkanSDK/{STENGINE_VULKAN_VERSION}/vulkansdk"])
    print(f"please add this to your startup file 'export VULKAN_SDK=\"{os.path.abspath(os.getcwd())}/Stengine/vendor/VulkanSDK/{STENGINE_VULKAN_VERSION}/x86_64\"'")

def install_vulkan_prompt():
    install = yes_or_no("Would you like to install the Vulkan SDK?")
    if install:
        install_vulkan_sdk()
        quit()

def check_vulkan_sdk() -> bool:
    if VULKAN_SDK is None:
        print("You don't have the Vulkan SDK installed!")
        install_vulkan_prompt()
        return False
    elif STENGINE_VULKAN_VERSION not in VULKAN_SDK:
        print(f"Located Vulkan SDK at {VULKAN_SDK}")
        print(f"You don't have the correct Vulkan SDK version! (Stengine requires {STENGINE_VULKAN_VERSION})")
        install_vulkan_prompt()
        return False

    print(f"Correct Vulkan SDK located at {VULKAN_SDK}")
    return True

VULKANSDK_DEBUG_LIBS_URL = f"https://sdk.lunarg.com/sdk/download/{STENGINE_VULKAN_VERSION}/linux/vulkansdk-linux-x86_64-{STENGINE_VULKAN_VERSION}.tar.gz"
OUTDIR = "Stengine/vendor/VulkanSDK"
TEMP_FILE = f"{OUTDIR}/VulkanSDK.tar.gz"
print(f"please add this to your startup file 'export VULKAN_SDK=\"{os.path.abspath(os.getcwd())}/Stengine/vendor/VulkanSDK/{STENGINE_VULKAN_VERSION}/x86_64\"'")
# Change from scripts directory to root
if not check_vulkan_sdk():
    print("Vulkan SDK not installed.")
    exit()

print("Running premake5...")
subprocess.call(["premake5", "gmake"])
