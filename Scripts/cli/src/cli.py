import fire

from .command import BaseCommand


def main() -> None:
    """Represents internal entrypoint."""

    fire.Fire(BaseCommand, name="light-detector-cli")
