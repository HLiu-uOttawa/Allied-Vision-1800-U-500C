https://gist.github.com/stefannae/d0f9c3590bbeb6443a70be71f7604a74
# Allied-Vision-1800-U-500C
This repo shows how to install Vimba SDK and run Allied-Vision-1800-U-500C
## 
https://www.alliedvision.com/en/products/software/vimba-x-sdk/

## Vimba X SDK Downloads
[Downloads Page](https://www.alliedvision.com/en/products/software/vimba-x-sdk/#c13326)  
[VimbaX_Setup-2024-1-Linux_ARM64.tar.gz](https://downloads.alliedvision.com/VimbaX/VimbaX_Setup-2024-1-Linux_ARM64.tar.gz)

```bash
wget https://downloads.alliedvision.com/VimbaX/VimbaX_Setup-2024-1-Linux_ARM64.tar.gz
```
## Docker Buildx
Leveraging buildx to create a Docker image tailored for the ARM64 architecture, specifically for the NVIDIA Jetson Orin, using a custom Dockerfile named Dockerfile-jetson-jetpack5. The resulting image is tagged as Object-Tracking-Experiment:latest.
```bash
docker buildx build --platform linux/arm64 -f Dockerfile-jetson-jetpack5 -t allied-vision-1800-u-500c:latest .
```

* Tag

```bash
docker tag allied-vision-1800-u-500c:latest tmetal/allied-vision-1800-u-500c:latest
```
* Push

```bash
docker push tmetal/allied-vision-1800-u-500c:latest
```

## On Jetson 
* pull image 
```bash
docker pull tmetal/allied-vision-1800-u-500c:latest
```

## Docker Compose
```bash
docker compose -f docker-compose-allied-vision.yml up -d
```
```bash
docker attach allied_vision
```
```bash
docker compose down
```

## PYthon code examples
```bash
nvidia@orin-nx:/opt/VimbaX_2024-1/api/python$ pip3 install vmbpy-1.0.5-py3-none-any.whl
Defaulting to user installation because normal site-packages is not writeable
Processing ./vmbpy-1.0.5-py3-none-any.whl
Installing collected packages: vmbpy
Successfully installed vmbpy-1.0.5

```
```bash
-rw-rw-rw- 1 1004 1005 11143 Sep 25 07:48 user_set.py
nvidia@orin-nx:/opt/VimbaX_2024-1/api/examples/VmbPy$ python3 list_cameras.py
//////////////////////////////////
/// VmbPy List Cameras Example ///
//////////////////////////////////

Cameras found: 2
/// Camera Name   : Allied Vision 1800 U-500c
/// Model Name    : 1800 U-500c
/// Camera ID     : DEV_1AB22C013709
/// Serial Number : N/A
/// Interface ID  : VimbaUSBInterface_0x0

/// Camera Name   : Allied Vision 1800 U-500c
/// Model Name    : 1800 U-500c
/// Camera ID     : DEV_1AB22C013709
/// Serial Number : 01PFT
/// Interface ID  : VimbaUSBInterface_0x0

nvidia@orin-nx:/opt/VimbaX_2024-1/api/examples/VmbPy$

```
