import time

# Represents throttle request duration time.
THROTTLE_REQUEST_DURATION: float = 0.3


def perform_request_await() -> None:
    """Performs throttle request operation."""

    time.sleep(THROTTLE_REQUEST_DURATION)
