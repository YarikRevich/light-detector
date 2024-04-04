import logging
from pathlib import Path

# Initializes logger general configuration.
logging.basicConfig(
    filename=f"{str(Path.home())}/light-detector-cli.log", level=logging.INFO, filemode='w', format='%(name)s - %(message)s')