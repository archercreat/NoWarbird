# remill-template

Simple template for using Remill. To understand remill, take a look at the following documentation pages:

- [Step-by-step guide on how Remill lifts an instruction](https://github.com/lifting-bits/remill/blob/master/docs/LIFE_OF_AN_INSTRUCTION.md)
- [The design and architecture of Remill](https://github.com/lifting-bits/remill/blob/master/docs/DESIGN.md)

The [`example.cpp`](src/example.cpp) lifts `mov rcx, 1337` and prints the lifted basic block function.

## Setting up the environment

This repository uses a [`devcontainer.json`](./.devcontainer/devcontainer.json) file to allow you to quickly get started.

### 1) GitHub Codespaces

**Using Codespaces is required for the training**

1. [Fork this repository](https://github.com/mrexodia/RiscyWorkshop/fork)
2. Click the green `<> Code` button
3. Press `...` and then `New with options...`
4. Change `Machine type` to `4-core`
5. Then `Create codespace`
6. Wait a ~5 minutes while the image is loading ☕

Troubleshooting:
- **Firefox (specifically on Linux) often does not work, try Chrome!**
- Reload the page if
  - Syntax highlighting fails to work
  - Startup takes too long
- If pasting from the clipboard fails, explicitly grant permission (settings icon on the left of the URL)
- **Remember**: save files before trying to recompile!

| ![](.devcontainer/new-codespace.png) | ![](.devcontainer/machine-type.png) |
|---|---|

#### **Remember to shut down your codespace [here](https://github.com/codespaces) when you're finished.**

I recommend switching to the `GitHub Dark` theme, because the syntax highlighting works better there.

When prompted by the CMake tools, just close the notifications:

![](.devcontainer/cmake-notifications.png)

### 2) Locally with Docker Desktop

<details>

<summary><sub>At a later date you can set things up locally with Docker Desktop</sub></summary>

- Install/Update [Docker Desktop](https://www.docker.com/products/docker-desktop/) ([alternatives](https://code.visualstudio.com/remote/advancedcontainers/docker-options))
- **Start Docker Desktop**
- Install [Visual Studio Code](https://code.visualstudio.com)
- Clone and open this repository in VS Code (**use the HTTPS protocol**)
- Install the [Dev Containers](vscode:extension/ms-vscode-remote.remote-containers) extension in VS Code (you should be prompted for recommended extensions)
- Click the blue 'Reopen in Container' button when prompted (you can also find it in the command palette)

For more detailed steps, check out the [Dev Containers tutorial](https://code.visualstudio.com/docs/devcontainers/tutorial). The instructions after this assume you are running _inside_ the container.

#### Windows

Because the host filesystem is mounted inside the container you _may_ need to configure Git to not automatically convert line endings:

```sh
git config --global core.autocrlf false
```

Additionally it's recommended to configure Docker to use the WSL 2 backend.

</details>

### 3) Local build

First build the dependencies, this includes LLVM per default. To use your own LLVM, pass `-DUSE_EXTERNAL_LLVM=ON`:

```bash
cmake -G Ninja -B dependencies/build -S dependencies -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build dependencies/build
```

_Note_: On Windows this requires a development command prompt and MSVC is _not_ supported, you _need_ to use `-DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl`.

You should then have a `dependencies/install` folder.

Then build the main project:

```bash
cmake -G Ninja -B build "-DCMAKE_PREFIX_PATH:FILEPATH=dependencies/install" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
cmake --build build
```

For more information, see [`LLVMParty/packages/dependencies.md`](https://github.com/LLVMParty/packages/blob/main/dependencies.md).

If you do not want to build LLVM on Windows you can download [`llvm-19.1.6-install.7z`](https://github.com/LLVMParty/remill-template/releases/download/llvm-prebuild/llvm-19.1.6-install.7z). See [`build.yml`](.github/workflows/build.yml) for an example in GitHub Actions.
