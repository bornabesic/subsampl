
import warnings
from pathlib import Path
from setuptools import setup

from pybind11.setup_helpers import Pybind11Extension

warnings.warn("pysubsampl package will be renamed to subsampl in the next release.", DeprecationWarning)

this_dir = Path(__file__).parent

flags = ["-O3"]
extension = Pybind11Extension(
    "pysubsampl",
    sorted(map(str,
        this_dir.glob("src/**/*.cpp")
    )),
    include_dirs=[str(this_dir / "include")],
    extra_compile_args=flags
)
for flag in flags:
    assert flag in extension.extra_compile_args

ext_modules = [extension]

setup(
    name="pysubsampl",
    version="0.1.0",
    ext_modules=ext_modules
)
