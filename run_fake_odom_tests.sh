#!/bin/bash

colcon build

colcon test --event-handlers console cohesion+

lcov --capture --directory build/ --output-file coverage_report.info

lcov --list coverage_report.info | head -n 10

