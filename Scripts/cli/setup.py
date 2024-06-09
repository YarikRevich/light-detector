import io
import os

from setuptools import find_packages, setup


def read(*paths, **kwargs):
    """Reads content at the given location."""

    content = ""
    with io.open(
            os.path.join(os.path.dirname(__file__), *paths),
            encoding=kwargs.get("encoding", "utf8"),
    ) as open_file:
        content = open_file.read().strip()
    return content


def read_description() -> str:
    """Reads description at the static location."""

    return read("README.md")


def read_requirements() -> list[str]:
    """Reads requirements file at the static location."""

    return [
        line.strip()
        for line in read("requirements.txt").split("\n")
        if not line.startswith(('"', "#", "-", "git+"))
    ]


setup(
    name="light-detector-cli",
    version="0.0.1",
    description="A tool used to allows to perform operations on STM32L476RG board with installed TSL2591X light sensor with the help of serial connection.",
    url="https://github.com/YarikRevich/light-detector",
    long_description=read_description(),
    long_description_content_type="text/markdown",
    author="YarikRevich",
    packages=find_packages(exclude=["tests", ".github"]),
    install_requires=read_requirements(),
    entry_points={
        "console_scripts": ["light-detector-cli = src.__main__:main"]
    },
)
