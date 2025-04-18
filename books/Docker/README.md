
## Overview
- What are containers 
- What is Docker ?
- Why do you need it ?
- What can it do ?

- Run Docker Container 
- Create a Docker Image
- Network in Docker
- Docker Compose 

- Docker Compose in Depth 
- Docker Concept in Depth 
- Docker Swarm 


### Why do you need docker ? 
- Version compatibility issue with services and OS, services and Libraries, 
    - Service A requires library A version x, whereas service B requires library A version y
- This compatiblity issue is called as " The Matrix from Hell !! "
- Long setup time 
- Different Dev/Test/Prod environments 
- So, we need something which can help us to solve the compatiblity issues and modify one component without affecting other 
- How docker helps ?
    - We can run each component in a separate container, with its own libraries and own dependencies
    - This simplifies the process of development, where one just need to spawn container (`docker run`)
- So, What are containers ? 
    - Complete isolated environment 
    - Own processes, own network interfaces, own interfaces, but they all share same os kernel (more details later)
    - Container are not new with Docker. 
    - Docker utilize AlexC container. Setting these containers are hard, and thus docker comes into picture. A high level tool which simplify the process of setting up containers 


#### Basic of OS
- Os kernel - Interacts with Hardware
    - Kernel remain the same i.e., Linux kernel
    - The software layer above those like Ubuntu, Debian, Fedora, Kali, .. makes different OS
        - Different UI, Different Drivers, Compilers, File Managers, Developer tools etc.
- User level programs / software
- Docker share underlying kernel. What does means ? 
    - Let say you are running your Bare Metal on Ubutu, then kernel here is Linux 
    - So, with docker you can spawn a container with OS which also shares same kernel e.g., Fedora, Debian, Suse, or Central OS
    - Docker utilizes the underlying kernel of the Docker host, which work with all OS above
    - E.g., you can not run a window based container with Linux on it ..
        - But we are able to run Linux container on Window .. how it is possible ? 
            - Essentially you are running Linux container on Linux Virtual Machine (which is on window)


### Install Docker 


## Chapter 2 

## Basic Docker commands
- Run - start a container 
```bash
docker run nginx 
```
- If image not present on host, then pull from the dockerhub and pull image from there (only for first time) subsequent execution will re-use the same image

- ps - list containers
    - List all container 
    ```bash
    docker ps 

    # list all container 
    docker ps -a (all)

    # Stop a container 
    docker stop <NAMES>

    # Remove contianer permanent
    docker rm <NAMES> 

    # list of images
    docker images

    # remove a image 
    docker rmi nginx 
    ```

