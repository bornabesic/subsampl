
from glob import glob
from setuptools import setup
from pathlib import Path

from pybind11.setup_helpers import Pybind11Extension

this_dir = Path(__file__).parent

ext_modules = [
    Pybind11Extension(
        "pysubsampl",
        sorted(map(str, this_dir.glob("src/*.cpp"))),
        include_dirs=[str(this_dir / "include")]
    )
]

setup(
    name="pysubsampl",
    version="0.0.1",
    ext_modules=ext_modules
)