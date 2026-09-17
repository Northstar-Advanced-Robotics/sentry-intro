#!/usr/bin/env python3
import subprocess
import argparse
import os
from enum import Enum


class Commands(str, Enum):
    shell = "shell"
    build = "build"

    def __str__(self):
        return self.value


root_dir = os.path.dirname(os.path.abspath(__file__))
image_name = "northstar/sentry:intro"
build_type = "Debug"
docker_cmd = "podman"
docker_run_args = [
    "-it",
    "--rm",
    "-v",  f"{root_dir}:/ws:Z",
    "-w",  "/ws"
]

colcon_args = [
    "--symlink-install",
    "--event-handlers",
    "console_cohesion+"
]

def shell():
    subprocess.run([docker_cmd, "build", "-t", image_name, "-f", "Dockerfile", "."])
    subprocess.run([docker_cmd, "run", *docker_run_args, image_name, "bash"])


def build():
    subprocess.run(["colcon", "build", *colcon_args])

def main():
    parser = argparse.ArgumentParser(description="Repo actions script")
    parser.add_argument(
        "cmd", type=Commands, choices=list(Commands), help="Subcommand to execute"
    )

    args = parser.parse_args()
    match args.cmd:
        case Commands.shell:
            shell()
        case Commands.build:
            build()


if __name__ == "__main__":
    main()
