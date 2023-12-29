import subprocess
import pkg_resources

def install(package):
    print(f"Installing {package} module...")
    subprocess.check_call(["python", "-m", "pip", "install", package])

def validate_package(package):
    required = { package }
    installed = {pkg.key for pkg in pkg_resources.working_set}
    missing = required - installed

    if missing:
        install(package)

validate_package("requests")
validate_package("fake-useragent")

import requests
from fake_useragent import UserAgent

import os
import sys
from pathlib import Path
from io import BytesIO
from urllib.request import urlopen, Request
from zipfile import ZipFile

import time

def download_file(url: str, filepath: str):
    os.makedirs(Path(filepath).parent.absolute(), exist_ok=True)
    with open(filepath, "wb") as f:
        ua = UserAgent()
        headers = {"User-Agent": ua.chrome}
        response = requests.get(url, headers=headers, stream=True)
        total = response.headers.get("content-length")

        if total is None:
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

def yes_or_no() -> bool:
    while True:
        reply = str(input("[Y/N]: ")).lower().strip()
        if reply[:1] == "y":
            return True
        if reply[:1] == "n":
            return False

STENGINE_VULKAN_VERSION = "1.2.189.0"
VULKAN_SDK = os.environ.get("VULKAN_SDK")
VULKAN_SDK_INSTALLER_URL = f"https://sdk.lunarg.com/sdk/download/{STENGINE_VULKAN_VERSION}/windows/vulkan_sdk.exe"
VULKAN_SDK_EXE_PATH = "Stengine/vendor/VulkanSDK/VulkanSDK.exe"

def install_vulkan_sdk():
    print("Downloading {} to {}".format(VULKAN_SDK_INSTALLER_URL, VULKAN_SDK_EXE_PATH))
    download_file(VULKAN_SDK_INSTALLER_URL, VULKAN_SDK_EXE_PATH)
    print("Done!")
    print("Running Vulkan SDK installer...")
    os.startfile(os.path.abspath(VULKAN_SDK_EXE_PATH))
    print("Re-run this script after installation")

def install_vulkan_prompt():
    print("Would you like to install the Vulkan SDK?")
    install = yes_or_no()
    if (install):
        install_vulkan_sdk()
        quit()

def check_vulkan_sdk() -> bool:
    if (VULKAN_SDK is None):
        print("You don't have the Vulkan SDK installed!")
        install_vulkan_prompt()
        return False
    elif (STENGINE_VULKAN_VERSION not in VULKAN_SDK):
        print(f"Located Vulkan SDK at {VULKAN_SDK}")
        print(f"You don't have the correct Vulkan SDK version! (Stengine requires {STENGINE_VULKAN_VERSION})")
        install_vulkan_prompt()
        return False
    
    print(f"Correct Vulkan SDK located at {VULKAN_SDK}")
    return True

VULKANSDK_DEBUG_LIBS_URL = f"https://sdk.lunarg.com/sdk/download/{STENGINE_VULKAN_VERSION}/windows/VulkanSDK-{STENGINE_VULKAN_VERSION}-DebugLibs.zip"
OUTDIR = "Stengine/vendor/VulkanSDK"
TEMP_ZIP_FILE = f"{OUTDIR}/VulkanSDK.zip"

def check_vulkan_sdk_debug_libs():
    shadercdLib = Path(f"{OUTDIR}/Lib/shaderc_sharedd.lib")
    if (not shadercdLib.exists()):
        print(f"No Vulkan SDK debug libs found. (Checked {shadercdLib})")
        print("Downloading", VULKANSDK_DEBUG_LIBS_URL)
        req = Request(VULKANSDK_DEBUG_LIBS_URL)
        req.add_header("User-Agent", "Stengine Setup Script")
        with urlopen(req) as zipresp:
            with ZipFile(BytesIO(zipresp.read())) as zfile:
                zfile.extractall(OUTDIR)

    print(f"Vulkan SDK debug libs located at {OUTDIR}")
    return True

# Change from Scripts directory to root
os.chdir('../')

if (not check_vulkan_sdk()):
    print("Vulkan SDK not installed.")
    
if (not check_vulkan_sdk_debug_libs()):
    print("Vulkan SDK debug libs not found.")

print("Running premake5 (vendor/premake/bin/premake5.exe)...")
subprocess.call(["vendor/premake/bin/premake5.exe", "vs2022"])