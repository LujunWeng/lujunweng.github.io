# Data Management

## Storing in the host machine
There are two options: volumes and bind mounts.

### Volumes
Managed by Docker and by default stored somewhere in the host machine.

### Bind Mount
Mounting a file or directory on the host machine onto a container. "The file or directory is referenced by its **full path** on the host machine. The file or directory does not need to exist on the Docker host already. It is created on demand if it does not yet exist."

### tmpfs mounts
A tmpfs mount is not persisted on disk, only during the lifetime of the container. Good for mounting secrets into containers.

### How to specify?
Better to use `--mount` for docker CLI and `volumes` with long syntax for docker compose file.

### Questions
1. Which type to use for database?

## References
1. [Volume Overview](https://docs.docker.com/storage/#good-use-cases-for-tmpfs-mounts)
