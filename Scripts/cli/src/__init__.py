import logging

import sys

from .cli import *
from .client import *
from .command import *
from .dto import *
from .middleware import *
from .proto import *
from .tools import *
from .visualizer import *

sys.path.insert(0, "./")

# Initializes logger general configuration.
logging.basicConfig(level=logging.INFO, filemode='w', format='%(name)s - %(message)s')