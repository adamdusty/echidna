set shell := ["powershell.exe", "-c"]

samples:
    cmake --build --preset samples
    cp "build\samples\_deps\wgpu-src\wgpu_native.dll" "build\samples\samples\"
    cp "build\samples\_deps\admat-build\libadmat.dll" "build\samples\samples\"
    cp "build\samples\libechidna.dll" "build\samples\samples\"
