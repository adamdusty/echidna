set windows-shell := ["pwsh.exe", "-c"]

alias c := configure
alias b := build
alias t := test

alias bt := build-test
alias cbt := configure-build-test

configure:
    cmake --preset dev -G Ninja

build:
    cmake --build --preset dev

test:
    ctest --preset dev

testv:
    ctest --preset dev --verbose

clean:
    cmake --build --preset dev --target clean

samples: build
    cp "build/dev/_deps/wgpu-src/wgpu_native.dll" "build/dev/samples/"
    cp "build/dev/_deps/admat-build/libadmat.dll" "build/dev/samples/"
    cp "build/dev/libechidna.dll" "build/dev/samples/"

phong:
    ./build/dev/samples/phong
    
triangle:
    ./build/dev/samples/triangle

build-test: build test
configure-build-test: configure build test