# LRC-2025-LAMe-Finalist-Submission
Multi-robot coordination system developed for the Lam Research Challenge 2025, featuring an autonomous line follower (ALFR), a mecanum-based robotic manipulator (SARM), arena automation, and parametric CAD design.

# LAMe Multi-Robot Coordination System

### Lam Research Challenge 2025 | Top 24 Finalist Team

A cooperative multi-robot system developed for the **Lam Research Challenge 2025 (LRC)** by **Team LAMe**, comprising an autonomous line-following robot (**ALFR**) and a manually operated robotic manipulator (**SARM**) working together to complete a dynamic obstacle-clearing and navigation challenge.

Our team advanced from a pool of **7000+ applicants** to become one of the **Top 24 teams nationally**, qualifying for the final round held in Bangalore.

---

## Team LAMe

* Adithya Vishnu
* Harsh Chandwani
* Sreeja Srinivasan
* Sparsh Pradeep Jain

---

## Project Overview

The challenge required the development of two robots capable of coordinated task execution:

### ALFR (Advanced Line Follower Robot)

An autonomous robot responsible for:

* Following a predefined arena path
* Detecting and responding to obstacles
* Triggering arena events through gate interactions
* Completing navigation tasks within strict timing constraints

### SARM (Single Arm Moving Robot)

A mecanum-wheel-based robotic manipulator responsible for:

* Omnidirectional movement
* Identifying and removing obstacles
* Pick-and-place operations
* Clearing the path for ALFR navigation

The robots operate together, with SARM removing obstacles while ALFR autonomously continues task execution once the route is cleared.

---

## Key Features

### Autonomous Navigation

* PID-based line following
* Multi-sensor line detection
* Obstacle-aware navigation
* Recovery logic for line loss
* Real-time path correction

### Robotic Manipulation

* Mobile robotic arm platform
* Mecanum wheel omnidirectional drive
* Object grasping and relocation
* Pick-and-place workflow
* Manual control interface

### Arena Automation

* Gate-triggered events
* Relay-based control systems
* Automated LED activation
* Fluid delivery sequence integration
* Event-driven challenge execution

### Mechanical Design

* Custom-designed ALFR chassis
* Custom SARM mechanical components
* Arena infrastructure design
* 3D-printed robot components
* Mechanical integration and assembly

### CAD Automation

* Fully parametric flange-bolt assembly
* Excel-linked SolidWorks design tables
* Equation-driven geometry generation
* Automated design regeneration
* Scalable assembly configuration

---

## Software Stack

### Simulation

* CoppeliaSim

### Programming

* Arduino
* C++
* Python

### CAD

* SolidWorks
* Fusion 360

### Electronics

* ESP32
* IR Sensor Arrays
* Ultrasonic Sensors
* Relay Modules
* Load Cells
* Peristaltic Pump Systems

---

## Competition Workflow

1. ALFR begins autonomous navigation.
2. Obstacles encountered on the route halt progression.
3. SARM identifies and removes obstacles.
4. ALFR resumes navigation.
5. Gate-based events trigger arena automation.
6. Fluid delivery and LED activation tasks are executed.
7. ALFR completes the course and reaches the final checkpoint.

---

## Results

* Qualified among **Top 96** from over **7000 applicants**
* Advanced to the **Top 24 Finalists Nationwide**
* Invited to compete at the **Lam Research Challenge Finals, Bangalore**
* Successfully completed both simulation and hardware evaluation rounds

---

## Repository Structure

```text
├── CAD/
├── CoppeliaSim/
├── Arduino/
├── Documentation/
├── Hardware/
├── Images/
├── Videos/
└── README.md
```

---

## Future Improvements

* ROS2 integration
* Autonomous obstacle removal
* Computer vision-based object detection
* SLAM-assisted navigation
* Multi-agent task planning
* Wireless telemetry dashboard

---

## Acknowledgements

We thank Lam Research, T-Works, IIT Kanpur, and the Robotics Club community for providing the opportunity, resources, and mentorship that made this project possible.
