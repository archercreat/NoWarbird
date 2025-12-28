# dependencies

Standalone dependencies for remill based on [LLVMParty/packages](https://github.com/LLVMParty/packages) (superbuild pattern).

## Building

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

This will create a [CMake prefix](https://cmake.org/cmake/help/latest/command/find_package.html#search-procedure), which you pass to your project with `-DCMAKE_PREFIX_PATH:FILEPATH=/path/to/dependencies/install`. See [presentation.md](https://github.com/LLVMParty/packages/blob/main/presentation.md) and [dependencies.md](https://github.com/LLVMParty/packages/blob/main/dependencies.md) for more information.

## Docker

```sh
export TAG="ghcr.io/llvmparty/remill-template/dependencies:22.04-llvm19.1.7-remill6.0.0"
docker buildx build --platform linux/arm64 -t "$TAG" .
docker buildx build --platform linux/amd64 -t "$TAG" .
docker buildx build --platform linux/arm64,linux/amd64 -t "$TAG" .
docker push "$TAG"
```
