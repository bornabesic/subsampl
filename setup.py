
from glob import glob
from setuptools import setup
from pathlib import Path

from pybind11.setup_helpers import Pybind11Extension

this_dir = Path(__file__).parent

flags = ["-Os"]
extension = Pybind11Extension(
    "pysubsampl",
    sorted(map(str,
        filter(lambda p: not p.name.startswith("test"),
        this_dir.glob("src/*.cpp")
    ))),
    include_dirs=[str(this_dir / "include")],
    extra_compile_args=flags
)
for flag in flags:
    assert flag in extension.extra_compile_args

ext_modules = [extension]

setup(
    name="pysubsampl",
    version="0.0.1",
    ext_modules=ext_modules
)