import os
import sys
from pathlib import Path

import cmake_build_extension
import setuptools

if (Path(".") / "CMakeLists.txt").exists():
    # Install from sdist
    source_dir = str(Path(".").absolute())
else:
    # Install from sources or build wheel
    source_dir = str(Path(".").absolute().parent.parent)

setuptools.setup(
    cmdclass=dict(build_ext=cmake_build_extension.BuildExtension,
                  sdist=cmake_build_extension.GitSdistFolder,),
    ext_modules=[
        cmake_build_extension.CMakeExtension(
            name="BuildAndInstall",
            install_prefix="proxqp",
            source_dir=source_dir,
            expose_binaries=["proxqp/lib/python3.9/site-packages/proxsuite/"],
            cmake_configure_options=[
                "-DFORCE_GIT_SUBMODULE_UPDATE:BOOL=ON",
                "-DBUILD_TESTING:BOOL=OFF",
                "-DBUILD_PYTHON_INTERFACE:BOOL=ON",
                "-DBUILD_WITH_VECTORIZATION_SUPPORT:BOOL=OFF",  # should be on, but for now I dont know how to install simde
                "-DINSTALL_DOCUMENTATION:BOOL=OFF",
            ],
        ),
    ],
)
